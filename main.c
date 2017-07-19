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
        int notFound = execvp(program, parsed);
        // freeSplitted(parsed);
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
}

void backgroundExecution(char *input) {
    pid_t pid = fork();

    if(pid<0){
        printf("Error forking: %d", pid);
        exit(EXIT_FAILURE);
    }
    else if(!pid){
        char *ret = strchr(input, '&');
        input[ret-input] = '\0';
        char **parsed = split(input, " ");
        char *program = parsed[0];
        // execvp(program, (const char**) parsed);
        int notFound = execvp(program, parsed);
        //freeSplitted(parsed);
        exit(notFound);
    }

    // strerror(errno); child
}

int main(int argc, char* argv[]){
    printf("---- Welcome to miniShell ----\n");
    printf("type 'exit' to exit\n\n");

    char *input;
    int exit_code; //, exitCodeChild;
    //pid_t endID;
    do{
        input = raw_input("> ");
        if(input == NULL){
            exit(EXIT_FAILURE);
        }
        if(!strcmp(input, "exit")){
            break;
        }

        if(!strcmp(input, "")){
            continue;
        }
        if(strchr(input, '&') == NULL){ // Ejecucion en primer plano
            exit_code = foregroundExecution(input);
            if(exit_code){
                printf("\nProccess finished with ERROR code: %d.\n", exit_code);
                if(exit_code==65280){
                    printf("El programa no existe o no es ejecutable.\n\n");
                }
                // printf("%s\n\n", strerror(errno));
            }
            else{
                printf("\nProccess finished with exit code: %d.\n\n", exit_code);
            }
        }
        else{ // Ejecucion en segundo plano
            backgroundExecution(input);
        }

        /*
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
        */

        free(input);
    } while(1);

    printf("Bye c:\n");
    return 0;
}
