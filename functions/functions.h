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
void parseString(char* str);
int is_string_has_equal(char* str);
int search_in_string_with_specific_symbol(char* str, char** string);
void SetLocalVar(char *str);
void ListAllLocalVar(void);
int SearchForLcalVar(void);
int RemoveEnvVar(char* var);
void help(void);
/***********************************************************************************************/

#endif