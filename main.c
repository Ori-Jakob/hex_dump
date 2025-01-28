#include <stdio.h>
#include <stdlib.h>

#define WIDTH              0x20

void dump_file(FILE*);
void print_ascii(char*);
void columns();
void red ();
void yellow();
void purple();
void green();
void cyan();
void reset();


int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Too many argumnets. Only the file path is needed.");
        return -1;
    }
    else if(argc < 2) {
        printf("No file path was specified.");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("File could not be found.");
        return -1;
    }

    purple();
    printf("Printing hex dump of %s...\n\n", argv[1]);
    reset();

    dump_file(fp);

    purple();
    printf("\n\nDONE!");
    reset();

    return 1;

}

void red () {
  printf("\033[1;31m");
}

void green() {
  printf("\033[0;32m");
}

void yellow() {
  printf("\033[1;33m");
}

void purple() {
  printf("\033[0;35m");
}

void cyan() {
  printf("Offset:\t\t\033[0;36m");
}

void reset () {
  printf("\033[0m");
}

void columns() {
    cyan();
    for(int i = 0; i < WIDTH; i++)
        printf("%02X ", i);
    printf("\n\n");
}

void dump_file(FILE *file) {
    char bytes[WIDTH];
    size_t counter = 0;
    int c;

    columns();
    while((c = fgetc(file)) != EOF) {
        if (counter % WIDTH == 0){
            if (counter > 0) print_ascii(bytes);
            yellow();
            printf("0x%08x\t", counter);
        }
        reset();
        printf("%02X ", c);
        bytes[counter++ % WIDTH] = (char)c;
    }
}

void print_ascii(char *data) {
    printf("\t");
    for (int i = 0; i < WIDTH; i++){
        if (data[i] >= 0x20 && data[i] < 0x7F) {
            green();
            printf("%c", data[i]);
        }
        else {
            red();
            printf(".");
        }
    }
    printf("\n");
}

