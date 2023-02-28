#define FUSE_USE_VERSION 30
 
#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
 
static int do_getattr(const char *path, struct stat *st) {
	st->st_uid = getuid(); 
	st->st_gid = getgid(); 
	st->st_atime = time(NULL); 
	st->st_mtime = time(NULL); 
 
	if ( strcmp( path, "/" ) == 0 ) {
		st->st_mode = S_IFDIR | 0755;
		st->st_nlink = 2;
	} else {
		st->st_mode = S_IFREG | 0400;
		st->st_nlink = 1;
		st->st_size = 1024;
	}
 
	return 0;
}
 
static int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
	filler(buffer, ".", NULL, 0); 
	filler(buffer, "..", NULL, 0); 
 
	if (strcmp(path, "/") == 0) 
		filler(buffer, "hello", NULL, 0);
 
	return 0;
}
 
static int do_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	if (strcmp(path, "/hello"))
        return -1;
    char data[20] = { '\0' };
    sprintf(data, "Hello, %d\n", fuse_get_context()->pid);
    size_t len = strlen(data);
    if ((size_t)offset >= len)
        return 0;
    len = (len - (size_t)offset < size) ? len - (size_t)offset : size;
    memcpy(buf, data + offset, len);
    return len;
}
 
static struct fuse_operations operations = {
    .getattr = do_getattr,
    .readdir = do_readdir,
    .read = do_read,
};
 
int main(int argc, char *argv[]) {
	return fuse_main(argc, argv, &operations, NULL);
}
