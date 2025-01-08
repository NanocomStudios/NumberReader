#include <stdio.h>

#include "files.h"

long int fileSize(const char file_name[]) {

    // opening the file in read mode 
    FILE* fp;
    fopen_s(&fp, file_name, "r");

    // checking if the file exist or not 
    if (fp == NULL) {
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file 
    long int res = ftell(fp);

    // closing the file 
    fclose(fp);

    return res;
}