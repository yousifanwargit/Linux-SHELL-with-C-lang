#ifndef _FUNCTIONS
#define _FUNCTIONS
/*===================================== INCLUDES ===================================*/
#include "../includes.h"
/***********************************************************************************************/

/*========================================= Datatypes Declarations =================================================*/
typedef struct {
	char key[20];
	char value[20];
}localvarobj_t;

/*********************************************************************************************************/
/*===================================== Functions Prototype ====================================*/
/**
 * @description This function will parse the input command from user to an array of strings.
 * @param str -> char*
 * @return void
 * @complexity : O(n)
 */
void parseString(char* str);

/**
 * @description This function check if the string has equal or not 
 *              and if it has equal it well be considerd as local var.
 * @param str -> char*
 * @return void
 * @complexity : O(n)
 */
int is_string_has_equal(char* str);

/**
 * @description This function check if the string has a special char or not 
 *              and if it has special char it well do a specific command (<,>,2>,|).
 * @param str -> char*
 * @param string -> char* "array of strings"
 * @return int -> it will return if the this string contains this special char or symbol or not.
 * @complexity : O(1)
 */
int search_in_string_with_specific_symbol(char* str, char** string);

/**
 * @description This function used to set a local var in an global array contains 100 local var only.
 * @param str -> char*
 * @return void.
 * @complexity : O(1)
 */
void SetLocalVar(char *str);

/**
 * @description This function used to list all local var wich stored in the global array.
 * @param void.
 * @return coid.
 * @complexity : O(1)
 */
void ListAllLocalVar(void);

/**
 * @description This function used to search for a local var 
 *              when the user want to add this var to the env variables.
 * @param void.
 * @return int -> will return the position of this var in the array and in fail will return -1.
 * @complexity : O(1)
 */
int SearchForLcalVar(void);

/**
 * @description This function used to remove an env var.
 * @param var -> the name of this var.
 * @return int -> the status of this sys call (unsetenv).
 * @complexity : O(1)
 */
int RemoveEnvVar(char* var);

/**
 * @description This function used to list all info about this shell and its features till now.
 * @param void.
 * @return void.
 * @complexity : O(1)
 */
void help(void);
/***********************************************************************************************/

#endif