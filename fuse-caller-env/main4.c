#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int envp_len;

char** get_envp_by_pid(int pid)
{
        FILE *stream;
	char buf[1024];
        snprintf(buf, sizeof(buf), "/proc/%d/environ", pid);
        stream = fopen(buf, "r");

        envp_len = 128;
        char** envp;
        size_t len = 0;
        envp = (char **)calloc(128, sizeof(char *));
        if (stream)
        {
                for (size_t i = 0; i < envp_len; ++i)
                {
                        if (i == envp_len - 1)
                        {
                                envp_len *= 2;
                                envp = realloc(envp, envp_len * sizeof(char *));
                        }
                        envp[i] = NULL;
                        if (getdelim(&envp[i], &len, '\0', stream) == -1)
                        {
                                free(envp[i]);
                                envp[i] = NULL;
                                break;
                        }
                        if (envp[i][0] == '\0')
                        {
                                free(envp[i]);
                                envp[i] = NULL;
                                break;
                        }
                }
                fclose(stream);
        }
	return envp;
}

void free_envp(char** envp, int envp_len)
{
	for (int i = 0; i < envp_len; ++i)
	{
		if (envp[i] == NULL)
			break;
		free(envp[i]);
	}
	free(envp);
}

static int do_getattr(const char *path, struct stat *st) {
        st->st_uid = getuid();
        st->st_gid = getgid();
        st->st_atime = time(NULL);
        st->st_mtime = time(NULL);

        if ( strcmp( path, "/" ) == 0 ) 
	{
                st->st_mode = S_IFDIR | 0755;
                st->st_nlink = 2;
        } 
	else 
	{
                st->st_mode = S_IFREG | 0444;
                st->st_nlink = 1;
                st->st_size = 4096;
        }

        return 0;
}

static int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) 
{
	filler(buffer, ".", NULL, 0);
        filler(buffer, "..", NULL, 0);

        char** envp = get_envp_by_pid(fuse_get_context()->pid);
	char* envp_name;
	for (size_t i = 0; i < envp_len; ++i)
	{
		if (envp[i] == NULL)
		{	
			break;
		}
		envp_name = (char*)malloc(strlen(envp[i] + 1) * sizeof(char));
		int j = 0;
		while(envp[i][j] != '\0')
		{
			if (envp[i][j] == '=')
			{
				envp_name[j] = '\0';
				break;
			}
			envp_name[j] = envp[i][j];
			++j;
		}
	        if (strcmp(path, "/") == 0)
		{
	                filler(buffer, envp_name, NULL, 0);
		}
		free(envp_name);
	}
	free_envp(envp, envp_len);
	return 0;
}

static int do_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) 
{	
	char** envp = get_envp_by_pid(fuse_get_context()->pid);
	int name_len = 5;
	char* envp_name = (char* )malloc(name_len * sizeof(char));
	int value_len = 5;
	char* envp_value = (char* )malloc(value_len * sizeof(char));
	bool name_space = true;
        for (size_t i = 0; i < envp_len; ++i)
        {
                if (envp[i] == NULL)
                {
                        break;
		}
		envp_name[0] = '/';
		int j = 0;
		int val_pos = 0;
                while(envp[i][j])
                {
			if (name_space)
			{
	                        if (envp[i][j] == '=')
                        	{
                                	envp_name[j+1] = '\0';
                                	name_space = false;
					++j;
					++val_pos;
					continue;
                       		}
                        	envp_name[j+1] = envp[i][j];
                        	++j;
				++val_pos;
                                if (j == name_len - 1) {
                                        name_len *= 2;
                                        envp_name = (char* )realloc(envp_name, name_len * sizeof(char));
                                }
			}
			else
			{
				envp_value[j-val_pos] = envp[i][j];
				++j;
				if (j - val_pos == value_len - 1) {
					value_len *= 2;
					envp_value = (char* )realloc(envp_value, value_len * sizeof(char));
				}
			}
                }
		envp_value[j-val_pos] = '\0';
		name_space = true;
                if (strcmp(path, envp_name) == 0)
                {
			strcat(envp_value, "\n");	
			size_t len = strlen(envp_value);
			if ((size_t)offset >= len)
			{
				free_envp(envp, envp_len);
				return 0;
			}
			len = (len - (size_t)offset < size) ? len - (size_t)offset : size;
			memcpy(buf, envp_value + offset, len);
			free_envp(envp, envp_len);
			free(envp_value);
			free(envp_name);
			return len;
                }
        }
        free_envp(envp, envp_len);
	free(envp_value);
	free(envp_name);
	return -1;
}

static struct fuse_operations operations = {
	.getattr = do_getattr,
    	.readdir = do_readdir,
    	.read = do_read,
};

int main(int argc, char *argv[]) {
        return fuse_main(argc, argv, &operations, NULL);
}

