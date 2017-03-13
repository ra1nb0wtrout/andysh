#ifndef ANDYSH_BUILTINS_H
#define ANDYSH_BUILTINS_H

#pragma once

#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

int andysh_environ(char ** args);
int andysh_clear(char ** args);
int andysh_cd(char ** args);
int andysh_dir(char ** args);
int andysh_help(char ** args);
int andysh_exit(char ** args);

char * command_str[] ={
	"environ",
	"clr",
	"cd",
	"dir",
	"help",
	"quit",
};
int (*command_func[]) (char **) = {

	&andysh_environ,
	&andysh_clear,
	&andysh_cd,
	&andysh_dir,
	&andysh_help,
	&andysh_exit,

};

int andysh_environ(char ** args){
	int i = 0;
	while(environ[i] != NULL){
		printf("%s\n", environ[i++]);
	}
}
int andysh_clear(char ** args){
	system("clear");
}

int andysh_cd(char ** args){
	if(args[1] != NULL){ 
		chdir(args[1]);
	}
	else{
		int i = 0;
		while( environ[i] != NULL){
			printf("Not NULL\n");
			if(!strncmp("HOME=",environ[i],5)){
				char * path = strchr(environ[i],'/');
				chdir(path);
				break;
			}
			i++;
		}
		printf("Unable to find $HOME");
	}
}
int andysh_dir(char ** args){
	system("ls -alh");
}
int andysh_help(char ** args){
}
int andysh_exit(char ** args){
	free(args);
	exit(0);
}

#endif
