#include "solution.h"
#include <errno.h>
#include <ext2fs/ext2_fs.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <err.h> 

void report_file(int inode_nr, char type, const char *name, char* filepath)
{
        printf("%d %c %s%s\n", inode_nr, type, filepath, name);
}

int dir_block_data(int img, off_t i_offset, unsigned int* data_size, unsigned int block_size, char* filepath)
{
	int lenght = strlen(filepath);
        unsigned int curr_size = (*data_size > block_size) ? block_size : *data_size;
        *data_size -= curr_size;
        unsigned int* buffer  = (unsigned int*)malloc(curr_size * sizeof(unsigned int));

        int b_read_check = pread(img, buffer, curr_size, i_offset);
        if (b_read_check < 0)
        {
                free(buffer);
                return -1;
        }

        int size = 0;                                                                 /* keep track of the bytes read */
        struct ext2_dir_entry_2 *entry;
        while(size < curr_size)
        {
                entry = (void*) buffer + size;
                if (entry->inode == 0)
                {
                        break;
                }
                char file_name[EXT2_NAME_LEN+1] = { '\0' };
                char file_type = entry->file_type == 2 ? 'd' : 'f';
                memcpy(file_name, entry->name,  entry->name_len);
                file_name[entry->name_len] = '\0';                                       /* append null char to the file name */
                size += entry->rec_len;
		if (!(strcmp(file_name,".") == 0 || strcmp(file_name, "..") == 0 || strcmp(file_name, "lost+found") == 0))
                {
			if (file_type == 'f'/* && file_name[entry->name_len - 1] == 't' && file_name[entry->name_len - 2] == 'x' && file_name[entry->name_len - 3] == 't' && file_name[entry->name_len - 4] == '.'*/)
			{	
                        	report_file(entry->inode, file_type, file_name, filepath);
			}
			if (file_type == 'd')
			{	

				lenght += strlen(file_name); 
				char* new_filepath = (char*)malloc((lenght + 2) * sizeof(char));
				memset(new_filepath, '\0', (lenght + 2) * sizeof(char));
				strcpy(new_filepath, filepath);
				strcat(new_filepath, file_name);
				strcat(new_filepath, "/");
				dump_dir(img, entry->inode, new_filepath);
				free(new_filepath);
			}
	       	}
        }
	free(buffer);
        return 0;
}

int indir_block_data(int img, off_t i_offset, unsigned int* i_size, unsigned int block_size, char* filepath) {
        int i_num = block_size / sizeof (unsigned int);
        unsigned int* buffer = (unsigned int* )malloc(block_size * sizeof(unsigned int));
        memset (buffer, 0, block_size);
	int b_read_check = pread(img, buffer, block_size, i_offset);
        if (b_read_check < 0)
        {
                free(buffer);
                return -1;
        }
        for (int i = 0; i < i_num; ++i) {
                if (dir_block_data(img, buffer[i] * block_size, i_size, block_size, filepath) != 0)
                {
                        free(buffer);
                        return -1;
                }
        }
        free(buffer);
        return 0;
}

int dindir_block_data(int img, off_t i_offset, unsigned int* i_size, unsigned int block_size, char* filepath) {
        int i_num = block_size / sizeof (unsigned int);
        unsigned int* buffer = (unsigned int* )malloc(block_size * sizeof(unsigned int));
        int b_read_check = pread(img, buffer, block_size, i_offset);
        if (b_read_check < 0)
        {
                free(buffer);
                return -1;
        }
        for (int i = 0; i < i_num; ++i) {
                if (indir_block_data(img, buffer[i] * block_size, i_size, block_size, filepath) != 0) {
                        free(buffer);
                        return -1;
               }
        }
        free(buffer);
        return 0;
}

int dump_dir(int img, int inode_nr, char* filepath)
{
        struct ext2_super_block super_block;
        struct ext2_group_desc group_desc;
        struct ext2_inode inode;

        // super_block
        if (pread(img, &super_block, sizeof(struct ext2_super_block), 1024) == -1)
                return -errno;
        // group
        unsigned int inodes_per_group = super_block.s_inodes_per_group;
        unsigned int block_group_needed = (inode_nr - 1) / inodes_per_group;
        unsigned int block_size = 1024 << super_block.s_log_block_size;
        unsigned int super_block_size = block_size;
        off_t group_position = super_block.s_first_data_block * block_size + super_block_size + super_block.s_blocks_per_group * block_group_needed * block_size;

        if (pread(img, &group_desc, sizeof(struct ext2_group_desc), group_position) == -1)
                return -errno;

        // inode
        unsigned int inode_index = (inode_nr - 1) % inodes_per_group;
        unsigned int inode_size = super_block.s_inode_size;
        off_t inode_needed = group_desc.bg_inode_table * block_size + inode_index * inode_size;

        if (pread(img, &inode, inode_size, inode_needed) == -1)
                return -errno;
	
        //printf(" Inodes per group: %u\n Group w'r looking for: %u\n Block size: %u\n Inode_needed: %lu\n", inodes_per_group, block_group_needed, block_size, inode_needed);

        unsigned int data_size = inode.i_size;
        //printf(" Data_size: %u\n Some block inode.i_block_i %u\n", data_size, inode.i_block[0] * block_size);
        for (int i = 0; i  < EXT2_N_BLOCKS; ++i) {
                off_t i_offset = inode.i_block[i] * block_size;
                if (i < EXT2_NDIR_BLOCKS)
                {
                        int dir_check = dir_block_data(img, i_offset, &data_size, block_size, filepath);
                        if (dir_check < 0)
                        {
                                return -errno;
                        }
                }
                else if (i == EXT2_IND_BLOCK) {
                        int indir_check = indir_block_data(img, i_offset, &data_size, block_size, filepath);
                        if (indir_check < 0)
                        {
                                return -errno;
                        }
                }
                else if (i == EXT2_DIND_BLOCK) {
                        int dindir_check = dindir_block_data(img, i_offset, &data_size, block_size, filepath);
                        if (dindir_check < 0)
                        {
                                return -errno;
                        }
                }
        }
}

