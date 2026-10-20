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
All options are mutually exclusive with the exception of -f
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
#include <stdio.h> // TEMPORARY, FOR PRINTF (printf is not authorized... :( ), will have to be replaced with write()

#include <dirent.h> // for opendir, readdir, closedir

int my_tar_option_is_supported(char c){
    return c == 'c' ||c == 'r' ||c == 'u' ||c == 't' ||c == 'x' ||c == 'f';
}

char* my_tar_get_options(int raw_input_len, char** raw_input){
    char options[] = "??";
    int i = 1;
    while((i <= raw_input_len) && (raw_input[i][0] == '-')){ // Loops through all options
        char* string = raw_input[i];
        printf(">Looping through %s...\n",string);
        // >> Loop through option in case of things like '-cf'
        int j = 1; // raw_input[i][0] is '-', so we begin at 1
        while(string[j] != '\0'){
            char letter = string[j];
            if(my_tar_option_is_supported(letter)){
                if(letter == 'f'){
                    if(options[0] == '?'){
                        printf("my_tar: Must specify one of -c, -r, -t, -u, -x\n");
                        return "XX"; // Error signal
                    }
                    options[1] = 'f';
                    j++;
                    continue;
                }

                if(options[0] == '?'){
                    options[0] = letter;
                }else{
                    printf("my_tar: Can't specify both -%c and -%c\n", letter, options[0]);
                    return "XX"; // Error signal
                }
            }else{
                printf("my_tar: Must specify one of -c, -r, -t, -u, -x\n");
                return "XX"; // Error signal
            }
            j++;
        }
        i++;
    }

    char* read_only_options = options;
    return read_only_options;
}

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
        printf("my_tar: Must specify one of -c, -r, -t, -u, -x\n");
        return 1;
    }
    // >> Get all options
    char* options = my_tar_get_options(input_len, input); // When an error occurs, options = "XX"
    if(options[0] == 'X'){
        return 1;
    }else if(options[0] == '?'){
        printf("my_tar: Must specify one of -c, -r, -t, -u, -x\n"); // Inaccurate message compared to tar.
        return 1;
    }
    printf(">LOOP END options is -%c and -%c\n",options[0],options[1]);

    // >>>> -c
    // >> Get all file paths
    // > Get index where files start
    int index_paths = 2; // input[1] must be an option, so start at 2
    char* archive_filename = "";
    while(*input[index_paths] == '-' && index_paths <= input_len){
        index_paths++;
    }
    if(options[1] == 'f'){
        archive_filename = input[index_paths];
        index_paths++;
    }
    printf(">archive_filename = %s; index_paths = %d; first file is %s \n",archive_filename, index_paths, input[index_paths]);
    // All files are from input[index_paths] to input[input_len]
    char* file = "my_tar.c";
    DIR* stream = opendir(file);
    if(stream == NULL){
        printf("my_tar: %s: Cannot stat: No such file or directory");
        return 1; // cannot close a stream that doesn't exist, so, must return.
    }
    closedir(stream);

    return 0;
}

int main(int argc, char **argv){

    my_tar(argc-1,argv);

    return 0;
}