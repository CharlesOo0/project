//
// Created by flassabe on 26/10/22.
//

#include "utility.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <libgen.h>
#include <unistd.h>

#include "global_defs.h"
#include "reducers.h"



int main(){
    
    char path[1024]=".git/hooks/update.sample";
    char *prefix="bon";
    char *suffix="jour";
    char *mot=NULL;
   /*   
    mot=concat_path(prefix,suffix,mot);
    printf("Mot : %s\n",mot);
    */
    printf("%s",dirname(path));

   bool dir_exist = path_to_file_exists(NULL);

    
}

/*!
 * @brief cat_path concatenates two file system paths into a result. It adds the separation /  if required.
 * @param prefix first part of the complete path
 * @param suffix second part of the complete path
 * @param full_path resulting path
 * @return pointer to full_path if operation succeeded, NULL else
 */
char *concat_path(char *prefix, char *suffix, char *full_path) {
    full_path=(char *)malloc(sizeof(char));
    strcat(strcpy(full_path,prefix),suffix);
    return full_path;
}

/*!
 * @brief directory_exists tests if directory located at path exists
 * @param path the path whose existence to test
 * @return true if directory exists, false else
 */
bool directory_exists(char *path) {
    DIR *dir =opendir(path);
    if(dir){
        return true;
    }else{
        return false;
    }
    
}

/*!
 * @brief path_to_file_exists tests if a path leading to a file exists. It separates the path to the file from the
 * file name itself. For instance, path_to_file_exists("/var/log/Xorg.0.log") will test if /var/log exists and is a
 * directory.
 * @param path the path to the file
 * @return true if path to file exists, false else
 */
bool path_to_file_exists(char *path) {
    if(path==NULL){
        printf("Erreur : path=NULL");
        return false;
    }else{
            return directory_exists(dirname(path));//dirname renvoi le chemin sans le nom
    }
}

/*!
 * @brief sync_temporary_files waits for filesystem syncing for a path
 * @param temp_dir the path to the directory to wait for
 * Use fsync and dirfd
 */
void sync_temporary_files(char *temp_dir) {
    
}

/*!
 * @brief next_dir returns the next directory entry that is not . or ..
 * @param entry a pointer to the current struct dirent in caller
 * @param dir a pointer to the already opened directory
 * @return a pointer to the next not . or .. directory, NULL if none remain
 */
struct dirent *next_dir(struct dirent *entry, DIR *dir) {
    return NULL;
}