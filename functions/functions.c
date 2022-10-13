#include "functions.h"

int i;				/* this var contains the position of the "=" in the parsed array. */
int arrayofstrsize;		/* the size of array which contains the parsed command. */

char *command_parsed_holder[100];	/* array of strings which contains the parsed command */
localvarobj_t all_local_var_arr[100];	/* Array of struct has 100 element which is the maximum count of local var to this shell. */

int count;			/* global var which contains the number of local var in the "all_local_var_arr". */

/*============================= Start of Functions Definitions ================================*/
/**
 * @description This function will parse the input command from user to an array of strings.
 * @param str -> char*
 * @return void
 * @complexity : O(n)
 */
void parseString(char *str)
{
    int j = 0;
    char *token = strtok(str, " ");
    command_parsed_holder[0] = token;
    // loop through the string to extract all other tokens
    while (token != NULL) {
	j++;
	token = strtok(NULL, " ");
	command_parsed_holder[j] = token;

    }
    arrayofstrsize = j;
}

/**
 * @description This function check if the string has equal or not 
 *              and if it has equal it well be considerd as local var.
 * @param str -> char*
 * @return void
 * @complexity : O(n)
 */
int is_string_has_equal(char *str)
{
    i = 0;
    while (str[i]) {
	if (str[i] == '=') {
	    return 1;
	}
	i++;
    }
    return 0;
}

/**
 * @description This function check if the string has a special char or not 
 *              and if it has special char it well do a specific command (<,>,2>,|).
 * @param str -> char*
 * @param string -> char* "array of strings"
 * @return int -> it will return if the this string contains this special char or symbol or not.
 * @complexity : O(1)
 */
int search_in_string_with_specific_symbol(char *str, char **string)
{
    int flag = 0;
    int i;
    for (i = 0; i <= arrayofstrsize - 1; i++) {
	if (!strcmp(str, string[i])) {
	    flag = 1;
	    break;
	}
    }
    if (flag == 1) {
	return i;
    } else {
	return -1;
    }
}

/**
 * @description This function used to set a local var in an global array contains 100 local var only.
 * @param str -> char*
 * @return void.
 * @complexity : O(1)
 */
void SetLocalVar(char *str)
{
    int len = strlen(command_parsed_holder[0]);

    int z = i;
    for (int n = 0; n < z; n++) {
	all_local_var_arr[count].key[n] = str[n];
    }

    for (int n = z + 1; n < len; n++) {
	all_local_var_arr[count].value[n - z - 1] = str[n];
    }
    count++;
}

/**
 * @description This function used to list all local var wich stored in the global array.
 * @param void.
 * @return coid.
 * @complexity : O(1)
 */
void ListAllLocalVar(void)
{
    for (int i = 0; i < count; i++) {
	printf("localvar[%d]: %s = %s \n", i, all_local_var_arr[i].key,
	       all_local_var_arr[i].value);

    }
}

/**
 * @description This function used to search for a local var 
 *              when the user want to add this var to the env variables.
 * @param void.
 * @return int -> will return the position of this var in the array and in fail will return -1.
 * @complexity : O(1)
 */
int SearchForLcalVar(void)
{
    for (int i = 0; i < count; i++) {
	if (!(strcmp(command_parsed_holder[1], all_local_var_arr[i].key))) {

	    return i;
	}
    }
    return -1;
}

/**
 * @description This function used to remove an env var.
 * @param var -> the name of this var.
 * @return int -> the status of this sys call (unsetenv).
 * @complexity : O(1)
 */
int RemoveEnvVar(char *var)
{
    int x = unsetenv(var);
    return x;
}

/**
 * @description This function used to list all info about this shell and its features till now.
 * @param void.
 * @return void.
 * @complexity : O(1)
 */
void help(void)
{

    printf("\n\n\n\n******************" 
        "************************\n\n");

    printf("\nin this SHELL you can do:\n\t-run any command you want in foreground or background."
            "\n\n\t-you can set a local var upto 100 local var."
            "\n\n\t-you can also set a multiple local var in one line."
            "\n\n\t-you can set an env var by using \"export local_varname\" built in command."
            "\n\n\t-you can remove an env var by using \"unset local_varname\" built in command."
            "\n\n\t-you can list all local vars by using \"set\" built in command."
            "\n\n\t-you can list all env vars by using \"env\" command."
            "\n\n\t-you can navigate in your system by using \"cd\" built in command."
            "\n\t\t-\"cd /\" to go to the root dir."
            "\n\t\t-\"cd ~\" to go to the home dir."
            "\n\t\t-\"cd ..\" to go to the parent dir."
            "\n\t\t-\"cd Path\" to go to any path (relative or absolute).");

    printf("\n\n\n******************" 
        "************************\n\n");
}

/***************************************************************************************************/
