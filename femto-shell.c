/*
db      d888888b d8b   db db    db db    db 
88        `88'   888o  88 88    88 `8b  d8' 
88         88    88V8o 88 88    88  `8bd8'  
88         88    88 V8o88 88    88  .dPYb.  
88booo.   .88.   88  V888 88b  d88 .8P  Y8. 
Y88888P Y888888P VP   V8P ~Y8888P' YP    YP 
                                            
                                            
.d8888. db    db d8888b. d88888b d8888b. 
88'  YP 88    88 88  `8D 88'     88  `8D 
`8bo.   88    88 88oodD' 88ooooo 88oobY' 
  `Y8b. 88    88 88~~~   88~~~~~ 88`8b   
db   8D 88b  d88 88      88.     88 `88. 
`8888Y' ~Y8888P' 88      Y88888P 88   YD 
                                         
                                         
d8888b. db    db d8b   db d8b   db d88888b d8888b. .d8888. 
88  `8D 88    88 888o  88 888o  88 88'     88  `8D 88'  YP 
88oobY' 88    88 88V8o 88 88V8o 88 88ooooo 88oobY' `8bo.   
88`8b   88    88 88 V8o88 88 V8o88 88~~~~~ 88`8b     `Y8b. 
88 `88. 88b  d88 88  V888 88  V888 88.     88 `88. db   8D 
88   YD ~Y8888P' VP   V8P VP   V8P Y88888P 88   YD `8888Y' 
*/

#include "includes.h"
#include "myshellconfig.h"
#include "functions/functions.h"
#define _GNU_SOURCE		/* See feature_test_macros(7) */


/*====================================== GLOBAL VARIABLES ==========================================*/
extern int i;			/* this var contains the position of the "=" in the parsed array. */
extern int arrayofstrsize;	/* the size of array which contains the parsed command. */

extern char *command_parsed_holder[100];	/* array of strings which contains the parsed command */
extern localvarobj_t all_local_var_arr[100];	/* Array of struct has 100 element which is the maximum count of local var to this shell. */

extern int count;		/* global var which contains the number of local var in the "all_local_var_arr". */

/****************************************************************************************************/


/*==================================== Start of main Function ===================================*/

int main(int argc, char *argv[])
{

/*================================= NEOFETCH ======================================*/
    neofetch();  /*a welcome string appears at the first time you run the program*/

    while (1) {

/*================================= PROMPT =======================================*/
	char buf[100];
	char cwd_buf[100];
	char *cwd = getcwd(cwd_buf, 100);
	char *user_name = getenv("USER");
	char host_name[50];
	int gethostname_status = gethostname(host_name, 50);
	printf(GRN "[%s" YEL "@" GRN "%s" MAG " ~" BLU "%s" GRN "]" RESET"$ ", user_name, host_name, cwd);
	fgets(buf, 100, stdin);
	int len = strlen(buf);
	buf[len - 1] = 0;

/*============================= IF THE USER PRESS ENTER ===================================*/
	if ((strlen(buf)) == 0) {
	    continue;
	}

	parseString(buf);	/*parse string which the user enterd to a global array contain this string */
	int flag;
	flag = is_string_has_equal(command_parsed_holder[0]);	/* check if has equal to set a local var */
	if (flag == 1) {
	    /* parse and set a local var */
	    SetLocalVar(command_parsed_holder[0]);
		for(int i=1; i<arrayofstrsize;i++){
			flag = is_string_has_equal(command_parsed_holder[i]);
			if(flag == 1){
				SetLocalVar(command_parsed_holder[i]);
			}
		}
	    continue;
	} 
	else {

/*==================LIST ALL LOCAL VAR WITH "set" BUILT IN COMMAND==================*/
	    if (!(strcmp(command_parsed_holder[0], "set"))) {
		printf("\n\n******************"
		       "************************\n\n");

		ListAllLocalVar();

		printf("\n******************"
		       "************************\n\n");
			continue;
	    }
/*================ADD A LOCAL VAR TO ENV VAR BY USING "export var_name" BUILT IN COMMAND================*/
	    else if (!(strcmp(command_parsed_holder[0], "export"))) {
		int stat = SearchForLcalVar();
		if (stat >= 0) {
		    int X =
			setenv(all_local_var_arr[stat].key,all_local_var_arr[stat].value, 1);
		} 
		else if ((stat < 0) || ((strlen(buf) < 7))) {
		    printf("Can't export [%s], This var doesn't exist.\n",command_parsed_holder[1]);
		}
			continue;
	    }
/*============================== REMOVE A VAR FROM A ENV VARIABLES ================================*/
	    else if (!(strcmp(command_parsed_holder[0], "unset"))) {
		int stat = RemoveEnvVar(command_parsed_holder[1]);
		if (stat == 0) {
		    printf("(%s) is removed from env variables.\n",command_parsed_holder[1]);
		}
			continue;
	    }
/*============================== exit from the shell by using "exit" built in command ================================*/
		else if (!(strcmp(command_parsed_holder[0], "exit"))) {
			printf(".########..##....##.########\n"
				   ".##.....##..##..##..##......\n"
				   ".##.....##...####...##......\n"
				   ".########.....##....######..\n"
				   ".##.....##....##....##......\n"
				   ".##.....##....##....##......\n"
				   ".########.....##....########\n");
			break;
	    }
/*================= DISPLAY A MANUAL PAGE CALLED HELP BY USING "help" BUILT IN COMMAND =================*/
	    else if (!(strcmp(command_parsed_holder[0], "help"))) {
			help();
			continue;
	    }
/*============================ THIS SECTION BELONGS TO "cd" BUILT IN COMMNAD ===============================*/
	    else if (!(strcmp(command_parsed_holder[0], "cd"))) {
		if (!(strcmp(command_parsed_holder[1], "-"))) {
		    char *last_dir = getenv("OLDPWD");
		    int chdir_status = chdir(last_dir);
		} 
		else if (!(strcmp(command_parsed_holder[1], "/"))) {
		    int chdir_status = chdir("/");
		} 
		else if (!(strcmp(command_parsed_holder[1], ".."))) {
		    int chdir_status = chdir("../");
		} 
		else if (!(strcmp(command_parsed_holder[1], "~"))) {
		    char home_dis[50] = "/home/";
		    char *strcat_stat = strcat(home_dis, user_name);
		    int chdir_status = chdir(home_dis);
		} 
		else if (sizeof(command_parsed_holder[1])) {
		    int chdir_status = chdir(command_parsed_holder[1]);
		}
			continue;
	    } 
		else {
/*====================== THIS SECTION OF CODE IS BELONGS TO pipes "|" ONLY ======================*/
/*************************************************************************************************
 * 		because of pipe needs to fork(), I handled it by separating the pipe from othe commands  *
**************************************************************************************************/
		int flag;
		flag = search_in_string_with_specific_symbol("|",command_parsed_holder);
		char *first_command[flag + 1];
		char *second_command[arrayofstrsize - flag + 1];
		if (flag > 0) {
		    int i;
		    for (i = 0; i < flag; i++) {
			first_command[i] = command_parsed_holder[i];
		    }
		    for (i = flag + 1; i <= arrayofstrsize; i++) {
			second_command[i - flag - 1] =
			    command_parsed_holder[i];
		    }

		    int fd[2];
		    if ((pipe(fd)) == -1) {
				printf("pipe failed.\n");
		    }

		    int pid1 = fork();
		    if (pid1 < 0) {
				printf("fork failed.\n");
		    } 
			else if (pid1 == 0) {
				// Child process 1
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);

				if (flag == 2) {
					execlp(first_command[0], first_command[0],first_command[1], NULL);
				} 
				else if (flag == 3) {
					execlp(first_command[0], first_command[0],first_command[1], first_command[2],NULL);
				} 
				else if (flag == 1) {
					execlp(first_command[0], first_command[0],NULL);
				}

		    }

		    int pid2 = fork();
		    if (pid2 < 0) {
				printf("fork failed.\n");
		    } 
			else if (pid2 == 0) {
				// Child process 2 
				dup2(fd[0], 0);
				close(fd[0]);
				close(fd[1]);
				execlp(second_command[0], second_command[0],second_command[1], NULL);
		    }

		    close(fd[0]);
		    close(fd[1]);

		    int pid1_status;
		    int pid2_status;

		    int x = waitpid(pid1, &pid1_status, 0);
		    int y = waitpid(pid2, &pid2_status, 0);
		    continue;
		}
/*=============== ford when the user enter the command which is not a built in command or a pipe commnad ================*/
		int ret_pid = fork();

		if (ret_pid < 0) {
		    printf("Fork failed.\n");
		} 
		else if (ret_pid > 0) {	/* in parent */
		    int status;
		    wait(&status);
		    printf("The last command status = %d\n", status);
		} 
		else if (ret_pid == 0) {	/* in child */
/* ====================this section belongs to the redirection (<, >, 2>) only ========================*/
		    int flag;
		    flag = search_in_string_with_specific_symbol("<",command_parsed_holder);
		    if (flag > 0) {
				close(0);
				int source_dis = open(command_parsed_holder[flag - 1], O_RDONLY,0777);
				int x = dup2(0, source_dis);
		    }

		    flag = search_in_string_with_specific_symbol(">",command_parsed_holder);
		    if (flag > 0) {
				close(1);
				int source_dis = open(command_parsed_holder[flag + 1],O_CREAT | O_WRONLY, 0777);
				int x = dup2(1, source_dis);
				if (!(strcmp(command_parsed_holder[0], "echo"))) {
					command_parsed_holder[flag] = "\0";
					command_parsed_holder[flag + 1] = "\0";
				}

				if (flag == 1) {
					execlp(command_parsed_holder[0],command_parsed_holder[0], NULL);
				} 
				else if (flag == 2) {
					execlp(command_parsed_holder[0],command_parsed_holder[0],command_parsed_holder[1], NULL);
				} 
				else if (flag == 3) {
					execlp(command_parsed_holder[0],command_parsed_holder[0],command_parsed_holder[1],command_parsed_holder[2], NULL);
				}

		    }

		    flag = search_in_string_with_specific_symbol("2>",command_parsed_holder);
		    if (flag > 0) {
				close(2);
				int source_dis = open(command_parsed_holder[flag + 1],O_CREAT | O_WRONLY, 0777);
				int x = dup2(2, source_dis);
				command_parsed_holder[flag] = "\0";
				command_parsed_holder[flag + 1] = "\0";
		    }
/* =========================exec and replace the current process with specific program.===========================*/
		    execvp(command_parsed_holder[0],command_parsed_holder);
		    printf("execve failed.\n");
		}
	    }
	}
    }
    return 0;
}

/**************************************** end of main functions ********************************************/
