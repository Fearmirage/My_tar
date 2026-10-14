/* All authorized functions -
chmod : handle file permissions

stat & fstat & lstat : get file status ?

getpwuid : search for user database with an entry matching uid
getgrgid : searches the group database for an entry with matching ' gid ' ?

mkdir : make a directory ??
opendir : creates directory stream
readdir : reads directory contents from directory streams (returns dirent) ?

symlink : creates a symbolic link named linkpath which contains the string ' target '
readlink : read value of a symbolic link

unlink : Delete a name from the filesystem. File having this name are also deleted if it was not in use

major : gets the major ID of a device ID; i.e the identifying class of the device ?
minor : gets the minor ID of a device ID; i.e gets the specific instance of the device

open : opens a file specified by a path. returns a file descriptor. read, write, lseek, fcntl can be used on it afterwards.
read : read from a file descriptor ??
write : writes to a file descriptor
lseek : repositions file offset of an open file description ??
close : closes a file descriptor so that it can be reused

malloc : allocate dynamic memory
free : free memory that was malloc'd ?

getxattr : get attributes from files, directories, symbolic links, etc ?
listxattr : retrives list of extended attribute names from files, directories, symbolic links, etc ??

time : returns time in seconds since Epoch
utime : change file last access and modification times ?
ctime : converts time into a format of "Wed Jun 30 21:49:08 1993\n" ?
*/
/* What does tar even do? -
Combine files together into a .tar file. Functions as a Fixed Archive
*/
#include <stdio.h> // TEMPORARY, FOR PRINTF

int my_tar(){
    printf("my_tar executes...\n");
    return 0;
}

int main(int argc, char **argv){
    printf(">%d INPUT(S): {",argc);
    for (int i = 1 ;i < argc; i++) {
        printf("%s",argv[i]);
        if(i != (argc-1)){
            printf(",");
        }
    }
    printf("}\n");
    my_tar();
    return 0;
}