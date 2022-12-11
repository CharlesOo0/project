//
// Created by flassabe on 26/10/22.
// Test syncronisation
//

#include "analysis.h"

#include <dirent.h>
#include <stddef.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/file.h>

#include "utility.h"

// Fonction main pour tester les différentes fonctions avant l'assemblage
int main()
{
    // TEST : parse_dir (à compiler uniquement sur LINUX)
    /*
    FILE *output_file = fopen("texte.txt", "r+");
    char *testpath = "/home/gabflrt/Documents/Dossier";
    parse_dir(testpath, output_file);
    */
    // CONCLUSION : CA MARCHE MAIS CA CONTINUE PAS DANS SOUS DOSSIER, AJOUTER RECURSIVITE

    // TEST : add_recipient_to_list
    char *testmail = "test@gmail.com";
    simple_recipient_t *testrecipient = NULL;
    testrecipient = add_recipient_to_list(testmail, testrecipient);
    testmail = "test2@gmail.com";
    testrecipient = add_recipient_to_list(testmail, testrecipient);
    testmail = "test3@gmail.com";
    testrecipient = add_recipient_to_list(testmail, testrecipient);
    testmail = "test4@gmail.com";
    testrecipient = add_recipient_to_list(testmail, testrecipient);
    /*
    while (testrecipient != NULL)
    {
        printf("%s\n", testrecipient->email);
        testrecipient = testrecipient->next;
    }
    */
    // CONCLUSION : marche

    //  TEST : clear_recipient_list
    clear_recipient_list(testrecipient);
    printf("test: %d\n", testrecipient);
    while (testrecipient != NULL)
    {
        printf("%s\n", testrecipient->email);
        testrecipient = testrecipient->next;
    }
    // CONCLUSION : les free marchent pas, jsp pourquoi
}

/*!
 * @brief parse_dir parses a directory to find all files in it and its subdirs (recursive analysis of root directory)
 * All files must be output with their full path into the output file.
 * @param path the path to the object directory
 * @param output_file a pointer to an already opened file
 */
void parse_dir(char *path, FILE *output_file)
{
    // 1. Check parameters
    if (output_file == NULL || !directory_exists(path))
    {
        printf("Erreur\n");
    }
    else
    {
        printf("Analyse du dossier\n");
        // 2. Go through all entries: if file, write it to the output file; if a dir, call parse dir on it
        DIR *dir = opendir(path);
        struct dirent *entity = readdir(dir); // entity c'est le fichier ou dossier trouvé dans dir
        if (dir)
        {
            while (entity != NULL)
            {
                fprintf(output_file, "%s\n", entity->d_name);
                entity = readdir(dir);
                if(directory_exists(path)){
                    parse_dir(entity,output_file);
                }
            }
        }
        closedir(dir);

        // 3. Clear all allocated resources
    }
}

/*!
 * @brief clear_recipient_list clears all recipients in a recipients list
 * @param list the list to be cleared
 */
void clear_recipient_list(simple_recipient_t *list)
{
    if (list == NULL)
    {
        printf("La liste est bien vide\n");
    }
    /*
    else if (list->next == NULL)
    {
        printf("dernier : %s\n", list->email);
        free(list);
        list = NULL;
        printf("dernier : %s\n", list->email);
    }
    */
    else
    {
        clear_recipient_list(list->next);
        printf("autres : %s\n", list->email);
        free(list);
        list = NULL;
        printf("autres : %s\n", list->email);
        printf("test: %d\n", list);
    }
}

/*!
 * @brief add_recipient_to_list adds a recipient to a recipients list (as a pointer to a recipient)
 * @param recipient_email the string containing the e-mail to add
 * @param list the list to add the e-mail to
 * @return a pointer to the new recipient (to update the list with)
 */
simple_recipient_t *add_recipient_to_list(char *recipient_email, simple_recipient_t *list)
{
    if (recipient_email == NULL)
    {
        return list;
    }
    else
    {
        simple_recipient_t *new_recipient = (simple_recipient_t *)malloc(sizeof(simple_recipient_t));
        strcpy(new_recipient->email, recipient_email);
        new_recipient->next = list;
        return new_recipient;
    }
}

/*!
 * @brief extract_emails extracts all the e-mails from a buffer and put the e-mails into a recipients list
 * @param buffer the buffer containing one or more e-mails
 * @param list the resulting list
 * @return the updated list
 */
simple_recipient_t *extract_emails(char *buffer, simple_recipient_t *list)
{
    // 1. Check parameters
    int i_buffer=0;
    char email[100];
    int i_email=0;
    //le while permet de tester si le buffer est vide
    while(buffer!=NULL){
        i_email=0;
        while (buffer[i_buffer]!=" "){
            email[i_email]=buffer[i_buffer];
            i_buffer++;
            i_email++;        
        }
        i_buffer++;//on est sur l'espace, il faut passer au carac suivant sinon on ne rentrera pas dans le deuxième while
        list=add_recipient_to_list(email,list);

        //vider email
        for(int i=0; i<strlen(email);i++){
            email[i]="";
        }
    }

    return list;
}

/*!
 * @brief extract_e_mail extracts an e-mail from a buffer
 * @param buffer the buffer containing the e-mail
 * @param destination the buffer into which the e-mail is copied
 */
void extract_e_mail(char buffer[], char destination[])
{
}

// Used to track status in e-mail (for multi lines To, Cc, and Bcc fields)
typedef enum
{
    IN_DEST_FIELD,
    OUT_OF_DEST_FIELD
} read_status_t;

/*!
 * @brief parse_file parses mail file at filepath location and writes the result to
 * file whose location is on path output
 * @param filepath name of the e-mail file to analyze
 * @param output path to output file
 * Uses previous utility functions: extract_email, extract_emails, add_recipient_to_list,
 * and clear_recipient_list
 */
void parse_file(char *filepath, char *output)
{
    // 1. Check parameters
    // 2. Go through e-mail and extract From: address into a buffer
    // 3. Extract recipients (To, Cc, Bcc fields) and put it to a recipients list.
    // 4. Lock output file
    // 5. Write to output file according to project instructions
    // 6. Unlock file
    // 7. Close file
    // 8. Clear all allocated resources
}

/*!
 * @brief process_directory goes recursively into directory pointed by its task parameter object_directory
 * and lists all of its files (with complete path) into the file defined by task parameter temporary_directory/name of
 * object directory
 * @param task the task to execute: it is a directory_task_t that shall be cast from task pointer
 * Use parse_dir.
 */
void process_directory(task_t *task)
{
    // 1. Check parameters
    // 2. Go through dir tree and find all regular files
    // 3. Write all file names into output file
    // 4. Clear all allocated resources
}

/*!
 * @brief process_file processes one e-mail file.
 * @param task a file_task_t as a pointer to a task (you shall cast it to the proper type)
 * Uses parse_file
 */
void process_file(task_t *task)
{
    // 1. Check parameters
    // 2. Build full path to all parameters
    // 3. Call parse_file
}
