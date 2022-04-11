#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CWD_MAX_LENGTH 100
#define CMDLINE_MAX_LENGTH 200
#define ARGS_MAX_NUM 100
#define DELIM " \n\t\r"

char *cwd;
char *cmdline;
char **args;

int main() {
    cwd = malloc(CWD_MAX_LENGTH);
    cmdline = malloc(CMDLINE_MAX_LENGTH);
    args = malloc(ARGS_MAX_NUM * sizeof(char *));
    while (1) {
        // cwd$ prompt
        printf("%s$ ", getcwd(cwd, CWD_MAX_LENGTH));
        // reset memory
        memset(cwd, 0, CWD_MAX_LENGTH);
        memset(cmdline, 0, CMDLINE_MAX_LENGTH);
        memset(args, 0, ARGS_MAX_NUM);
        // get cmdline from stdin
        if (scanf("%[^\n]", cmdline) != 1) {};
        // rm \n from stdin
        getc(stdin);
        // arg counter
        int argcnt = 0;
        // get args and argcnt from cmdline
        char *arg = strtok(cmdline, DELIM);
        while (arg != NULL) {
            if (argcnt == ARGS_MAX_NUM) {
                fprintf(stderr, "too many args\n");
            }
            args[argcnt++] = arg;
            arg = strtok(NULL, DELIM);
        }
        // no arg
        if (argcnt == 0) {
            continue;
        }
        // cd
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "no arg to cd\n");
            }
            if (chdir(args[1]) != 0) {
                perror("");
            }
        } else if (strcmp(args[0], "exit") == 0) { // exit
            break;
        } else { // exec another process
            pid_t pid = fork();
            if (pid < 0) { // fork error
                perror("");
            } else if (pid == 0) { // child process
                // exec arg
                if (execvp(args[0], args) == -1) {
                    perror("");
                }
                return 0;
            } else { // father process
                // wait child process
                waitpid(pid, NULL, 0);
            }
        }
    }
    free(args);
    free(cmdline);
    free(cwd);
    return 0;
}