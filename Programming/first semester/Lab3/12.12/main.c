#include <stdio.h>

int main (int argc, char *argv[]) {
    FILE* file1 = fopen(argv[1], "r");
    char cfile1[256];
    int i = 0;
    while (!feof(file1)) {
            if (i == 0) {
                fgets(cfile1, sizeof(cfile1), file1);
                i = 1;
            } else {
                printf("%s", fgets(cfile1, sizeof(cfile1), file1));
                i = 0;
            }
        }
    printf("\n");
    return 0;
}
