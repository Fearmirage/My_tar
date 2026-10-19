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
Combine files together into a .tar file. These .tar files are called archives
--OPTIONS - optionss--
All optionss are mutually exclusive
-c creates a new archive containing the specified items. if not with -f prints it out on stdout
-r is like -c except it appends new entries. needs -f
-t print out all files compacted in a given archive.
-u like -r except the new entries are only added if the modification date is superior.
-x unpack an archive
-- --
In -c, -r, or -u options, each specified file or directory is added to the archive in the order specified on the command line.
By default, the contents of each directory are also archived.

-f is always after the options.
my_tar will not handle file inside subdirectory.
*/
/* Method -
Make one chunk of code that completes an objective (For example, >>>>Get options from input), make sure it works,
then, make it readable (seperating it into multiple small functions)
*/
#include <stdio.h> // TEMPORARY, FOR PRINTF



int my_tar(int input_len, char** input){
    //printf starting with '>' in the terminal means it's a debug printf
    printf(">my_tar executes...\n");
    // Dont forget input includes "./my_tar" in position 0!

    // >>>> Print out the inputs (debugging)
    printf(">%d INPUT(S): {",input_len);
    for (int i = 1 ;i <= input_len; i++) {
        printf("%s",input[i]);
        if(i != input_len){
            printf(",");
        }
    }
    printf("}\n");

    // >>>> Get options from input
    // >> There needs to be options in the first place:
    if(input_len <= 0){
        printf("Must specify one of -c, -r, -t, -u, -x\n");
        return 1;
    }
    // >> Get all options
    char options[] = "??";
    int i = 1;
    while((i <= input_len) && (input[i][0] == '-')){ // Loops through all options
        printf(">Looping through %s...\n",input[i]);
        // >> Loop through option in case of things like '-cf'
        int j = 1; // input[i][0] is '-', so we begin at 1
        while(input[i][j] != '\0'){
            if(input[i][j] == 'c' ||input[i][j] == 'r' ||input[i][j] == 'u' ||input[i][j] == 't' ||input[i][j] == 'x'){
                if(options[0] == '?'){
                    options[0] = input[i][j];
                }else{
                    printf("Can't specify both -%c and -%c\n", input[i][j], options[0]);
                    return 1;
                }
            }else if(input[i][j] == 'f'){
                if(options[0] == '?'){
                    printf("Must specify one of -c, -r, -t, -u, -x\n");
                    return 1;
                }
                options[1] = 'f';
            }
            j++;
        }
        i++;
    }
    printf(">LOOP END options is -%c and -%c\n",options[0],options[1]);

    return 0;
}

int main(int argc, char **argv){

    my_tar(argc-1,argv);

    return 0;
}