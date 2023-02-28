#define FUSE_USE_VERSION 30
 
#include <errno.h>
#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
 
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>
 
 
char* src_path = "/home/ejeny/EjenY_FS/fs_prac/fuse/srcdir";
char* src_parent_path = "/home/ejeny/EjenY_FS/fs_prac/fuse/";
 
 
static int hello_getattr(const char *path, struct stat *st) {
	struct stat parent_info;
	stat(src_parent_path, st);
 
    if (!strcmp( path, "/")) {
		struct stat info;
		stat(src_path, st);
		return 0;
    }
 
	DIR* src = opendir(src_path);
	struct dirent* dir_info;
	path++;
	while ((dir_info = readdir(src))) {
		if (!strcmp(path, dir_info->d_name)) {
			struct stat info;
			int len = strlen(src_path) + strlen(dir_info->d_name) + 2;
			char* file_path = (char* )malloc(len * sizeof(char));
			memset(file_path, '\0', len * sizeof(char));
			sprintf(file_path, "%s/%s", src_path, dir_info->d_name);
			stat(file_path, st);
			free(file_path);
			break;
		}
	}
 
	closedir(src);
 
	return 0;
}
 
 
static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *info) {
	if (!strcmp(path, "/")) {
		DIR* src = opendir(src_path);
		struct dirent* dir_info;
		while ((dir_info = readdir(src)))
			filler(buf, dir_info->d_name, NULL, 0);
		closedir(src);
	}
	return 0;
}
 
 
static int hello_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *info) {
	path++;
	DIR* src = opendir(src_path);
	struct dirent* dir_info;
	while ((dir_info = readdir(src))) {
		if (!strcmp(path, dir_info->d_name)) {
			struct stat info;
			int len = strlen(src_path) + strlen(dir_info->d_name) + 2;
			char* file_path = (char* )malloc(len * sizeof(char));
			memset(file_path, '\0', len * sizeof(char));
			sprintf(file_path, "%s/%s", src_path, dir_info->d_name);
			lstat(file_path, &info);
			if (S_ISREG(info.st_mode)) {
				int fd = open(file_path, O_RDONLY);
				int num = read(fd, buf, size);
				close(fd);
				free(file_path);
				closedir(src);
				return num;
			}
			else if (S_ISLNK(info.st_mode)) {
				char name[1024] = { '\0' };
				readlink(file_path, name, 1024);
				int real_path_len = strlen(src_path) + strlen(name) + 2;
				char* real_path = (char* )malloc(real_path_len * sizeof(char));
				memset(real_path, '\0', real_path_len * sizeof(char));
				sprintf(real_path, "%s/%s", src_path, name);
				int fd = open(real_path, O_RDONLY);
				free(real_path);
				int num = read(fd, buf, size);
				close(fd);
				free(file_path);
				closedir(src);
				return num;
			}
 
		}
	}
	closedir(src);
	return 0;
}
 
 
static const struct fuse_operations hellofs_ops = {
	.getattr = hello_getattr,
    	.readdir = hello_readdir,
    	.read = hello_read,
};
 
int main(int argc, char** argv) {
	fuse_main(argc, argv, &hellofs_ops, NULL);
	return 0;
}
