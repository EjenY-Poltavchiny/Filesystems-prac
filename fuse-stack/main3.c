#define FUSE_USE_VERSION 30
 
#include <errno.h>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>
 
 
bool is_process(const char* name) 
{
	int count = 0;
	while(name[count] != '\0') 
	{
		if(!isdigit(name[count])) 
		{
			return false;
		}
		count++;
    }
    return true;
}
 
char* next_dir(DIR* dirp) 
{ 
	char* name = NULL; 
	struct dirent* dir_info;
	while((dir_info = readdir(dirp))) 
	{
		if (errno) 
		{
			printf("error %d: /proc/", errno);
		}
		if(is_process(dir_info->d_name)) 
		{
			name = dir_info->d_name;
			break;
		}
	}
	return name;
}
 
int symb_amount(const char* path, char sym) 
{
	int count = 0;
	for (int i = 0; i < strlen(path); ++i) 
	{
		if (path[i] == sym)
		{
			count++;
		}
	}
	return count;
}
 
 
static int do_getattr(const char *path, struct stat *st) 
{
	st->st_uid = fuse_get_context()->uid;
	st->st_gid = fuse_get_context()->gid;
	st->st_atime = time(NULL);
	st->st_mtime = time(NULL);
 
	if (!strcmp( path, "/" )) 
	{
		st->st_mode = S_IFDIR | 0775;
		st->st_nlink = 2;
	}
	else if (symb_amount(path, '/') == 1)
	{
		st->st_mode = S_IFDIR | 0444;
		st->st_nlink = 1;
		st->st_size = 6;
    	}
	else {
		st->st_mode = S_IFREG | 0444;
		st->st_nlink = 1;
		st->st_size = 1024;
	}
	return 0;
}

static int do_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *info) 
{
	if (!strcmp(path, "/")) 
	{
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		char* pid_str;
		DIR* dp = opendir("/proc");
		if (NULL == dp) 
		{
			return -1;
		}
		while ((pid_str = next_dir(dp))) 
		{
			filler(buf, pid_str, NULL, 0);
		}
		closedir(dp);
		return 0;
	}
	char* pid_str;
	DIR* dp = opendir("/proc");
	if (NULL == dp) 
	{
		return -1;
	}
	path++;
	while ((pid_str = next_dir(dp)))
	{
		if (!strcmp(path, pid_str)) 
		{
			char* thread_str;
			char* PID_path = (char* )malloc(sizeof("/proc") + sizeof(pid_str) + sizeof("/task"));
			memset(PID_path, 0, sizeof(PID_path));
			sprintf(PID_path, "/proc/%s/task", pid_str);
			
			DIR* PID_dir = opendir(PID_path);
			if (NULL == PID_dir) 
			{
				return -1;
			}
			while ((thread_str = next_dir(PID_dir))) 
			{
				filler(buf, thread_str, NULL, 0);
			}
			closedir(PID_dir);
			free(PID_path);
			break;
		}
	}
	closedir(dp);
	return 0;
}
 
static int do_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *info)
{
	//for pids
	if (symb_amount(path, '/') != 2)
	{
		return -1;
	}
	char* PID = (char* )malloc(strlen(path) * sizeof(path));
	char* thread_id = (char* )malloc(strlen(path) * sizeof(path));
	memset(PID, 0, sizeof(PID));
	memset(thread_id, 0, sizeof(thread_id));
	bool is_pid = true;
	for (int i = 0; i < strlen(path) - 1; ++i) 
	{
		if (path[i + 1] == '/') 
		{
			is_pid = false;
			continue;
		}
		if (is_pid) 
		{
			PID[i] = path[i + 1];
		}
		else 
		{
			thread_id[i - strlen(PID) - 1] = path[i + 1];
		}
	}
	bool is_dir = false;
	
	// for threads
	char* pid_str;
	DIR* dp = opendir("/proc");
	if (NULL == dp) 
	{
		free(PID);
		free(thread_id);
		return -1;
	}
	while ((pid_str = next_dir(dp))) 
	{
		if (!strcmp(pid_str, PID))
		{
			is_dir = true;
			break;
		}
	}
	closedir(dp);
	if (!is_dir)
	{
		free(PID);
		free(thread_id);
		return -1;
	}
	
	
	bool is_file = false;
	char* thread_str;
	char* PID_path = (char* )malloc(sizeof("/proc") + sizeof(pid_str) + sizeof("/task"));
	memset(PID_path, 0, sizeof(PID_path));
	sprintf(PID_path, "/proc/%s/task", PID);
	DIR* PID_dir = opendir(PID_path);
	if (NULL == PID_dir) 
	{
		free(PID);
		free(thread_id);
		free(PID_path);
		return -1;
	}
	while ((thread_str = next_dir(PID_dir))) 
	{
		if (!strcmp(thread_str, thread_id)) 
		{
			is_file = true;
			break;
		}
	}
	closedir(PID_dir);
	if (!is_file)
	{
                free(PID);
                free(thread_id);
                free(PID_path);
		return -1;
	}
	
	char* stack_path = (char* )malloc((strlen(PID_path) + strlen(thread_id) + 2) * sizeof(char) + sizeof("/stack"));
	memset(stack_path, 0, sizeof(stack_path));
	sprintf(stack_path, "%s/%s/stack", PID_path, thread_id);
 
	int stack = open(stack_path, O_RDONLY);
	size_t len = read(stack, buf, size);
   	close(stack);
 
	free(stack_path);
	free(PID_path);
	free(PID);
	free(thread_id);
	return len;
}
 
static const struct fuse_operations hellofs_ops = {
	.getattr = do_getattr,
	.readdir = do_readdir,
   	.read = do_read,
};
 
int main(int argc, char** argv) {
	fuse_main(argc, argv, &hellofs_ops, NULL);
	return 0;
}
