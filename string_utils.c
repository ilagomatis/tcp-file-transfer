#include "string_utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char** split(char *string, char separator, int* size){
    char** words = (char**)malloc(0);
    int numWords = 0;
    int startingPoint = 0;

    for(int i=0; ; i++){
        
        if(string[i] == '\0'){
            words = realloc(words, (numWords + 1) * sizeof(char*));
            words[numWords] = (char*)malloc((1 + (i-startingPoint)) * sizeof(char));
            strcpy(words[numWords], &string[startingPoint]);
            numWords++;
            break;
        }

        if(string[i] == separator){
            words = realloc(words, (numWords + 1) * sizeof(char*));
            words[numWords] = (char*)malloc((1 + (i-startingPoint)) * sizeof(char));
            strncpy(words[numWords], &string[startingPoint], i - startingPoint);
            strcat(words[numWords], "\0");
            startingPoint = i + 1;
            numWords++;
        }
    }

    *size = numWords;
    return words;
}

unsigned char* getBinaryContent(char* path, int* bytes)
{
    FILE* fd;
    fd = fopen(path, "rb");
    fseek(fd, 0L, SEEK_END);

    *bytes = ftell(fd);
    
    fseek(fd, 0L, SEEK_SET);
    
    unsigned char* buffer = (unsigned char*) malloc(*bytes * sizeof(unsigned char));
    fread(buffer, *bytes, 1, fd);
    fclose(fd);
    return buffer;
}