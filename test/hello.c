#include <stdio.h>

int main(int argc, char **argv) {
    printf("hello world\n");
    int cnt = 0;
    while (cnt < argc) {
        printf("arg%d: %s\n", cnt++, *argv);
        argv++;
    }
    return 0;
}