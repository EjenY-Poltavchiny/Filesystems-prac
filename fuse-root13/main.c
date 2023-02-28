#define FUSE_USE_VERSION 30
 
#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
 
char* src_path = "/home/ejeny/EjenY_FS/fs_prac/fuse_5/srcdir";
 
void Rot13(char* str) 
{
	char* current_char = str;
	int i = 0;
	while(current_char[i] != '\0')
	{
		if((current_char[i] >= 97 && current_char[i] <= 122) || (current_char[i] >= 65 && current_char[i] <= 90))
		{
			if (current_char[i] > 109 || (current_char[i] > 77 && current_char[i] < 91))
			{
				current_char[i] -= 13;
			}	  
			else
			{
				current_char[i] += 13;
			}	  
		}
		i++;
	}
}
 
static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi ) 
{
	int len = strlen(src_path) + strlen(path) + 1;
	char* file_path = (char* )malloc(len * sizeof(char));
	memset(file_path, '\0', len * sizeof(char));
	strcpy(file_path, src_path);
	strcat(file_path, path);
	
	int fd = open(file_path, O_RDONLY);
	if (fd == -1) 
	{
		strcpy(buffer, "No such file\n");
		free(file_path);
		return 0;
	}

	memset(buffer, '\0', size);
	int num = read(fd, buffer, size);
	Rot13(buffer);
	free(file_path);
	close(fd);
	return num;
}
 
static int do_write( const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *info ) 
{
	int len = strlen(src_path) + strlen(path) + 2;
	char* file_path = (char* )malloc(len * sizeof(char));
	memset(file_path, '\0', len * sizeof(char));
    	strcpy(file_path, src_path);
    	strcat(file_path, path);
	
	printf("%s\n", file_path);


    	int fd = open(file_path, O_CREAT | O_WRONLY, 0666);
    	if (fd == -1) 
	{
		free(file_path);
        	return 0;
    	}

	char* new_buf = (char* )malloc((size + 1) * sizeof(char));
	memset(new_buf, '\0', (size + 1) * sizeof(char));
	memcpy(new_buf, buffer, size);
	Rot13(new_buf);
	
	printf("%s\n", new_buf);
	
	int num = write(fd, new_buf, size);
	free(file_path);
	free(new_buf);
	close(fd);
	return num;
}
 
static int do_getattr( const char *path, struct stat *st ) {
	st->st_uid = fuse_get_context()->uid; 
    	st->st_gid = fuse_get_context()->gid;
	st->st_atime = time( NULL );
    	st->st_mtime = time( NULL );
 
    	if ( strcmp( path, "/" ) == 0 )
    	{
        	st->st_mode = S_IFDIR | 0755;
        	st->st_nlink = 2;
    	}
    	else
    	{
        	st->st_mode = S_IFREG | 0666;
        	st->st_nlink = 1;
		int len = strlen(src_path) + strlen(path) + 1;
		char* file_path = (char* )malloc(len * sizeof(char));
		memset(file_path, '\0', len * sizeof(char));
		strcpy(file_path, src_path);
		strcat(file_path, path);
		FILE* file = fopen(file_path, "r+");
		if (file != NULL) 
		{
			fseek(file, 0L, SEEK_END);
			st->st_size = ftell(file);
			rewind(file);
			fclose(file);
		}
		free(file_path);
    	}
    	return 0;
}
 
static int do_open(const char *path, struct fuse_file_info *fi) {
	return 0;
}
 
static int do_create(const char *path, mode_t mode, struct fuse_file_info * fi) {
	return 0;
}
 
static int do_truncate(const char *path, off_t offset) {
	return 0;
}

static int do_access(const char *path, int type) {
	return 0;
}

static struct fuse_operations operations = {
	.getattr = do_getattr,
    	.read = do_read,
	.write = do_write,
	.open = do_open,
	.create	= do_create,
	.truncate = do_truncate,
	.access = do_access,
};
 
int main( int argc, char *argv[] )
{
	return fuse_main( argc, argv, &operations, NULL );
}
