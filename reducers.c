//
// Created by flassabe on 26/10/22.
//

#include "reducers.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "global_defs.h"
#include "utility.h"

// POUR TESTER LES FONCTIONS
int main()
{
    // TEST : add_source_to_list
    char *testmail = "test@gmail.com";
    sender_t *testlist = NULL;
    testlist = add_source_to_list(testlist, testmail);
    testmail = "test2@gmail.com";
    testlist = add_source_to_list(testlist, testmail);
    testmail = "test3@gmail.com";
    testlist = add_source_to_list(testlist, testmail);
    testmail = "test4@gmail.com";
    testlist = add_source_to_list(testlist, testmail);
    testmail = "test4@gmail.com";
    testlist = add_source_to_list(testlist, testmail);
    /*
    while (testlist != NULL)
    {
        printf("%s\n", testlist->recipient_address);
        testlist = testlist->next;
    }
    */
    // CONCLUSION : fonction qui marche, comprendre utilité de head et tail car pour le moment null

    // Test : clear_sources_list
    /*
    clear_sources_list(testlist);
    while (testlist != NULL)
    {
        printf("%s\n", testlist->recipient_address);
        testlist = testlist->next;
    }*/
    // CONCLUSION : marche

    // TEST : find_source_in_list
    testmail = "test@gmail.com";
    testlist = find_source_in_list(testlist, testmail);
    printf("%s\n", testlist->recipient_address);
    // CONCLUSION : marche

    // TEST : add_recipient_to_source
    char *testmail2 = "test@gmail.com";
    sender_t *testlist2 = NULL;
    testlist2 = add_recipient_to_source(testlist2, testmail2);
    testmail2 = "test2@gmail.com";
    testlist2 = add_recipient_to_source(testlist2, testmail2);
    testmail2 = "test3@gmail.com";
    testlist2 = add_recipient_to_source(testlist2, testmail2);
    testmail2 = "test4@gmail.com";
    testlist2 = add_recipient_to_source(testlist2, testmail2);
    testmail2 = "test4@gmail.com";
    testlist2 = add_recipient_to_source(testlist2, testmail2);
    /*
    while (testlist != NULL)
    {
        printf("%s\n", testlist->recipient_address);
        testlist = testlist->next;
    }
    */
}

/*!
 * @brief add_source_to_list adds an e-mail to the sources list. If the e-mail already exists, do not add it.
 * @param list the list to update
 * @param source_email the e-mail to add as a string
 * @return a pointer to the updated beginning of the list
 */
sender_t *add_source_to_list(sender_t *list, char *source_email)
{
    // 1. Check parameters
    if (source_email == NULL)
    {
        return list;
    }

    // 2. Check if e-mail already exists in list
    sender_t *source = find_source_in_list(list, source_email);
    if (source != NULL)
    {
        // printf("email existe deja");
        return list;
    }
    else
    {
        // printf("nouvel email");
    }
    // 3. Create new source
    sender_t *new_source = (sender_t *)malloc(sizeof(sender_t));
    strcpy(new_source->recipient_address, source_email);
    new_source->head = NULL;
    new_source->tail = NULL;
    new_source->next = list;
    new_source->prev = NULL;
    if (list != NULL)
    {
        list->prev = new_source;
    }
    // 4. Return new list
    return new_source;
}

/*!
 * @brief clear_sources_list clears the list of e-mail sources (therefore clearing the recipients of each source)
 * @param list a pointer to the list to clear
 */
void clear_sources_list(sender_t *list)
{
    if (list == NULL)
    {
    }
    else if (list->next == NULL)
    {
        free(list);
    }
    else
    {
        if (list->next != NULL)
        {
            clear_sources_list(list->next);
            free(list);
        }
    }
}

/*!
 * @brief find_source_in_list looks for an e-mail address in the sources list and returns a pointer to it.
 * @param list the list to look into for the e-mail
 * @param source_email the e-mail as a string to look for
 * @return a pointer to the matching source, NULL if none exists
 */
sender_t *find_source_in_list(sender_t *list, char *source_email)
{
    sender_t *templist = list;
    bool found = 0;
    while (templist != NULL && found != 1)
    {
        if (!strcmp(templist->recipient_address, source_email))
        {
            found = 1;
        }
        else
        {

            templist = templist->next;
        }
    }
    if (found == 1)
    {
        return templist;
    }
    else
    {
        return NULL;
    }
}

/*!
 * @brief add_recipient_to_source adds or updates a recipient in the recipients list of a source. It looks for
 * the e-mail in the recipients list: if it is found, its occurrences is incremented, else a new recipient is created
 * with its occurrences = to 1.
 * @param source a pointer to the source to add/update the recipient to
 * @param recipient_email the recipient e-mail to add/update as a string
 */
void add_recipient_to_source(sender_t *source, char *recipient_email)
{
}

/*!
 * @brief files_list_reducer is the first reducer. It uses concatenates all temporary files from the first step into
 * a single file. Don't forget to sync filesystem before leaving the function.
 * @param data_source the data source directory (its directories have the same names as the temp files to concatenate)
 * @param temp_files the temporary files directory, where to read files to be concatenated
 * @param output_file path to the output file (default name is step1_output, but we'll keep it as a parameter).
 */
void files_list_reducer(char *data_source, char *temp_files, char *output_file)
{
}

/*!
 * @brief files_reducer opens the second temporary output file (default step2_output) and collates all sender/recipient
 * information as defined in the project instructions. Stores data in a double level linked list (list of source e-mails
 * containing each a list of recipients with their occurrences).
 * @param temp_file path to temp output file
 * @param output_file final output file to be written by your function
 */
void files_reducer(char *temp_file, char *output_file)
{
}