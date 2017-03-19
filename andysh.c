#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "builtins.h"

#define TOKENBUFFERSIZE 64
#define TOKENDELIM " \r\n\t\a"

//Function Declarations
void init();
void andysh_loop();
char ** andysh_tokenize(char * msg);
void andysh_do(char ** tokens);
void writeOut();
char * getInput();




//MAIN FUNCTION, SHOULD DO NOTHING EXCEPT SETUP< THEN LOOP
int main(){
	init();
	andysh_loop();
	return 0;
}

//INIT: ENTRY VECTOR, ONLY EXEC ONCE
void init(){	
	printf("====================\n");
	printf("Andy's Shell\n");
	printf("PID:  \%d\n", getpid());
	printf("USER: ");
	printf("andy\n");
	printf("====================\n");
}

//LOOP: SHOULD ONLY RETURN ON PROGRAM EXIT
void andysh_loop(){

	int cwdsize = 64;
	while(1){
		char * cwd = getcwd(NULL, cwdsize);
		//Request Input
		printf("\n%s\n>|>", cwd);
		free(cwd);
		char * input = getInput();

		//Tokenize Input
		char ** iTokens = andysh_tokenize(input);

		//if it's not an empty command, do it
		(iTokens[0] != NULL) ? 
			andysh_do(iTokens) : printf("No Operation\n");
		free(input);
		free(iTokens);

	}

}

//DO: TAKE ACTION BASED ON TOKENIZED INPUTS
void andysh_do(char ** tokens){

	//If first Token is a builtin, Execute it.
	{
		/* 	 Array Size
			 ------------	= number of elements
			 Element Size
		 */
		int numCommands = sizeof(command_str) / sizeof(char*);

		//Check each builtin against first token
		for(int i = 0; i < numCommands; i++){

			// If Matches One of our builtins,
			if(!strcmp(tokens[0], command_str[i])){
				command_func[i](tokens);
				return;
			}
		}
	}

	//Otherwise, Fork, and Exec the New Process
	{
		// GO Back Through, and replace the '/0's with ' '
		for(int i = 1; tokens[i] != NULL; i++){
			char * j = tokens[i] - sizeof(char);
			*j = ' ';
		}

		//Pass to system shell, eventually should be replaced with fork,
		//exec, however that isn't how the exercise tells us to do it.
		system(tokens[0]);
	}
}

char ** andysh_tokenize(char * msg){
	int position = 0;
	int bufferSize = TOKENBUFFERSIZE;

	char ** tokens = malloc(bufferSize * sizeof(char *));
	char * token = strtok(msg, TOKENDELIM);
	while(token != NULL){
		tokens[position] = token;

		position++;
		if(position >= TOKENBUFFERSIZE){
			bufferSize += TOKENBUFFERSIZE;
			tokens = realloc(
					tokens,
					bufferSize *
					sizeof(char *)
					);
		}
		token = strtok(NULL, TOKENDELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

char * getInput(){
	char * msg = NULL;
	ssize_t buffersize= 0;
	getline(&msg, &buffersize, stdin);
	return msg;
}

void writeOut(char * msg){

}
