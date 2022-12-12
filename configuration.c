/
// Created by flassabe on 14/10/22.
//

#include "configuration.h"

#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "utility.h"

char *skip_spaces(char *str);
char *check_equal(char *str);
char *get_word(char *source, char *target);

void main_test_configuration(int argc,char *argv[]){

	//Variable pour skip_spaces() check_equal() get_word()
	char str[99],target[99];
	char *ptr;
	
	/* //Récupère un string
	puts("Entrez la chaine de carac : ");
	fgets(str, 99, stdin);
	*/
	
	/* //TEST skip_spaces(); MARCHE
	ptr = skip_spaces(str);
	printf("\nPointeur sur la chaine au premiere espace : \n%s\n",ptr);
	*/ 
	
	/* //TEST check_equal(); MARCHE
	ptr = check_equal(str);
	printf("\nPointeur sur la chaine au premiere espace après égale : \n%s\n",ptr);
	*/
	
	/* //TEST get_word(); MARCHE
	ptr = get_word(str,target);
	printf("\nLe mot : \n%s\n",target);
	printf("\nPointeur sur la chaine après le mot : \n%s\n",ptr);
	*/
	
	/* //TEST make_configuration() MARCHE
	configuration_t *nouvelle_configuration = malloc(sizeof(configuration_t));
	make_configuration(nouvelle_configuration, argv, argc);
	display_configuration(nouvelle_configuration);
	*/ //COMMANDE : ./config /bin/usr /Documents/Temp_directory /Documents/Output_file false 2 12

	/* //TEST read_cfg_file() MARCHE
	char *path_to_cfg_file = "Repertory_config/config_1.txt";
	configuration_t *nouvelle_configuration = malloc(sizeof(configuration_t));	
	read_cfg_file(nouvelle_configuration, path_to_cfg_file);
	display_configuration(nouvelle_configuration);
	*/
	
	return;
}


/*!
 * @brief make_configuration makes the configuration from the program parameters. CLI parameters are applied after
 * file parameters. You shall keep two configuration sets: one with the default values updated by file reading (if
 * configuration file is used), a second one with CLI parameters, to overwrite the first one with its values if any.
 * @param base_configuration a pointer to the base configuration to be updated
 * @param argv the main argv
 * @param argc the main argc
 * @return the pointer to the updated base configuration
 */
configuration_t *make_configuration(configuration_t *base_configuration, char *argv[], int argc) {
	
	if(argc == 7){
		
		strcpy(base_configuration->data_path,argv[1]);  //copie arg 1 dans data path
		strcpy(base_configuration->temporary_directory,argv[2]); //copie arg 2 dans temporary directory
		strcpy(base_configuration->output_file,argv[3]); //copie arg 3 dans output_file
		
		if(strcmp(argv[4],"true") == 0){ //compare pour savoir si arg 4 est true ou false
			base_configuration->is_verbose = 1; //True
		}
		else{
			base_configuration->is_verbose = 0; //False
		}
		
		base_configuration->cpu_core_multiplier = atoi(argv[5]); //converti arg 5 en int
		base_configuration->process_count = atoi(argv[6]); //converti arg 6 en int
		
		return base_configuration;
	}
	else{
		puts("Pas assez d'arguments pour initialiser la configuration !");
	}
}

/*!
 * @brief skip_spaces advances a string pointer to the first non-space character
 * @param str the pointer to advance in a string
 * @return a pointer to the first non-space character in str
 */
char *skip_spaces(char *str) {
	int i=0;
	char* copie = str;
	while(i != strlen(str)){//boucle dans str
		++i;
		if(*copie == ' ') return ++copie; //si espace retourne pointeur sur carac. après espace
		++copie;
	}

}

/*!
 * @brief check_equal looks for an optional sequence of spaces, an equal '=' sign, then a second optional sequence
 * of spaces
 * @param str the string to analyze
 * @return a pointer to the first non-space character after the =, NULL if no equal was found
 */
char *check_equal(char *str) {
	int i=0;
	char* copie = str;
	while(i != strlen(str)){ //boucle dans str
		++i;
		if(*copie == '=' && *++copie == ' '){ //Si egale suivie espace alors
			return ++copie; //renvoie pointeur sur carac. après espace
		}
		++copie;
	}
	return NULL;
}

/*!
 * @brief get_word extracts a word (a sequence of non-space characters) from the source
 * @param source the source string, where to find the word
 * @param target the target string, where to copy the word
 * @return a pointer to the character after the end of the extracted word
 */
char *get_word(char *source, char *target) {
	int i=0;
	char *copie = source;
	while(i != strlen(source)){ //boucle dans str
		++i;
		if(*copie == ' ') return ++copie;//envoie le mot car il y à un espace
		else{
			*target = *copie;//copie lettre
			++target;//passe au caratère d'après
			++copie;//passe au caratère d'après
		}	
		
	}
	return copie; //envoie le mot qui équivalent a la source
}

/*!
 * @brief read_cfg_file reads a configuration file (with key = value lines) and extracts all key/values for
 * configuring the program (data_path, output_file, temporary_directory, is_verbose, cpu_core_multiplier)
 * @param base_configuration a pointer to the configuration to update and return
 * @param path_to_cfg_file the path to the configuration file
 * @return a pointer to the base configuration after update, NULL is reading failed.
 */
configuration_t *read_cfg_file(configuration_t *base_configuration, char *path_to_cfg_file) {
	FILE *texte = fopen(path_to_cfg_file, "r");
	
	if(texte == NULL){ //verifie si le fichier existe / si il y à du texte dedans
		puts("Erreur fichier vide ou mauvais chemin.");
		return NULL;
	}

	char ligne[256],target[256],*ptr;
	
	base_configuration->cpu_core_multiplier = 2; //valeur par défaut 2
	
	while(fgets(ligne,256,texte) != NULL){
		memset(target,0,sizeof(target)); //reset le str
		get_word(ligne,target);

		if(strcmp(target,"is_verbose") == 0){ //Compare pour savoir quel param c'est de la config
			ptr = check_equal(ligne);
			memset(target,0,sizeof(target)); //reset le str
			get_word(ptr,target);
			
			if(strstr(target,"true") != NULL){ //compare pour savoir si target est true ou false
				base_configuration->is_verbose = 1; //True
			}
			else{
				base_configuration->is_verbose = 0; //False
			}
			
		}
		
		
		else if(strcmp(target,"data_path") == 0){ //Compare pour savoir quel param c'est de la config
			ptr = check_equal(ligne);
			strcpy(base_configuration->data_path,ptr);
		}
		
		
		else if(strcmp(target,"temporary_directory") == 0){ //Compare pour savoir quel param c'est de la config
			ptr = check_equal(ligne);
			strcpy(base_configuration->temporary_directory,ptr);
		}
		
		
		else if(strcmp(target,"output_file") == 0){ //Compare pour savoir quel param c'est de la config
			ptr = check_equal(ligne);
			strcpy(base_configuration->output_file,ptr);
		}
		
		
		else if(strcmp(target,"cpu_core_multiplier") == 0){ //Compare pour savoir quel param c'est de la config
			ptr = check_equal(ligne);
			base_configuration->cpu_core_multiplier = atoi(ptr);

		}
		
		
		else if(strcmp(target,"process_count") == 0){ //Compare pour savoir quel param c'est de la config
			ptr = check_equal(ligne);
			base_configuration->process_count = atoi(ptr);
		}
		
	}
	
	return base_configuration;
}

/*!
 * @brief display_configuration displays the content of a configuration
 * @param configuration a pointer to the configuration to print
 */
void display_configuration(configuration_t *configuration) {
    printf("\nCurrent configuration:\n");
    printf("\tData source: %s\n", configuration->data_path);
    printf("\tTemporary directory: %s\n", configuration->temporary_directory);
    printf("\tOutput file: %s\n", configuration->output_file);
    printf("\tVerbose mode is %s\n", configuration->is_verbose?"on":"off");
    printf("\tCPU multiplier is %d\n", configuration->cpu_core_multiplier);
    printf("\tProcess count is %d\n", configuration->process_count);
    printf("End configuration\n");
}

/*!
 * @brief is_configuration_valid tests a configuration to check if it is executable (i.e. data directory and temporary
 * directory both exist, and path to output file exists @see directory_exists and path_to_file_exists in utility.c)
 * @param configuration the configuration to be tested
 * @return true if configuration is valid, false else
 */
bool is_configuration_valid(configuration_t *configuration) {
	//data directory
	if(directory_exists(configuration->data_path)){
		printf("\nData directory OK");
	}
	else{
		printf("\nData directory ERREUR");
		return false
	}
	//temporary directory
	if(directory_exists(configuration->temporary_directory)){
		printf("\nTemporary directory OK");
	}
	else{
		printf("\nTemporary directory ERREUR");
		return false
	}
	//path output file
	if(directory_exists(configuration->output_file)){
		printf("\nOutput file OK");
	}
	else{
		printf("\nOutput file ERREUR");
		return false
	}
	
	return true;
}
