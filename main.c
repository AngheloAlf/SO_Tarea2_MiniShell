#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "strParse.h"

int foregroundExecution(char *input){
    pid_t pid = fork();

    if(pid<0){
        printf("Error forking: %d", pid);
        exit(EXIT_FAILURE);
    }
    else if(!pid){

        char **parsed = split(input, " ");
        char *program = parsed[0];
        // execvp(program, (const char**) parsed);
        int notFound = execvp(program, parsed);
        freeSplitted(parsed);
        exit(notFound);
    }
    else{
        int exitCodeChild;
        pid_t endID = waitpid(pid, &exitCodeChild, WUNTRACED);
        if(endID == -1){
            printf("ERROR");
            exit(EXIT_FAILURE);
        }
        return exitCodeChild;

    }
    // strerror(errno); child
    // return 2;
}

void backgroundExecution(char *input) {
    pid_t pid = fork();

    if(pid<0){
        printf("Error forking: %d", pid);
        exit(EXIT_FAILURE);
    }
    else if(!pid){

        char **parsed = split(input, " ");
        char *program = parsed[0];
        // execvp(program, (const char**) parsed);
        execvp(program, parsed);
        freeSplitted(parsed);
        // exit(0);
    }

    // strerror(errno); child
}

int main(int argc, char* argv[]){
    /*printf("%d\n", argc);
    for(int i = 0; i < argc; i++){
        printf("\t%s\n", argv[i]);
    }
    */
    printf("---- Welcome to miniShell ----\n");
    printf("type 'exit' to exit\n\n");

    /*
    pid_t pid = fork();

    if(pid<0){
        printf("Error forking: %d", pid);
    }
    else if(!pid){
        printf("Soy un hijo y retorno 42");
        return 42;
    }
    else{
        printf("Soy un padre y mi hijo tiene PID: %d", pid);
    }
    */

    char *input;
    int exit_code, exitCodeChild;
    pid_t endID;
    do{
        input = raw_input("> ");
        if(input == NULL){
            exit(EXIT_FAILURE);
        }
        if(!strcmp(input, "exit")){
            break;
        }

        endID = waitpid(-1, &exitCodeChild, WUNTRACED|WNOHANG);
        if(endID != -1 && !endID){
            if(exitCodeChild){
                printf("\nThe background proccess, PID: %d, has ended with ERROR code: %d\n", endID, exitCodeChild);
                printf("%s\n\n", strerror(errno));
            }
            else{
                printf("\nThe background proccess, PID: %d, has ended with exit code: %d\n\n", endID, exitCodeChild);
            }
        }

        if(!strcmp(input, "")){
            continue;
        }
        if(strchr(input, '&') == NULL){ // Ejecucion en primer plano
            exit_code = foregroundExecution(input);
            if(exit_code){
                printf("\nProccess finished with ERROR code: %d.\n", exit_code);
                printf("%s\n\n", strerror(errno));
            }
            else{
                printf("\nProccess finished with exit code: %d.\n\n", exit_code);
            }
        }
        else{ // Ejecucion en segundo plano
            backgroundExecution(input);
        }
        free(input);
    } while(1);

    printf("Bye c:");
    return 0;
}
