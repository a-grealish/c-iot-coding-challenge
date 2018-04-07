#include <stdlib.h>
#include <stdio.h>
#include "file_parser.h"


float* parseFile(char* filename, float(*convert)(char*), size_t* return_len) {
    FILE* ptr_file;
    
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    float* results;
    size_t results_len = 1024;

    // Check that a function was correctly passed
    if (convert == NULL) {
        fprintf(stderr, "ERROR: Not appropriate convertion function passed\n");
        return NULL;
    }

    // Open the file
    ptr_file = fopen(filename, "r");
    if (!ptr_file) {
        perror("ERROR");
        return NULL;
    }

    // Allocate output buffer
    results = malloc(sizeof(float)*results_len);
    if (results == NULL) {
        perror("ERROR");
        fclose(ptr_file);
        return NULL;
    }

    // Read and convert one line at a time using the convert function pointer
    while((read = getline(&line, &len, ptr_file)) != -1) {
        
        // Expand the memory space for the returned list of floats
        if (*return_len >= results_len) {
            results_len *= 2;
            float* new_results = realloc(results, sizeof(float)*results_len);
            if (new_results == NULL) {
                perror("ERROR");
                free(results);
                fclose(ptr_file);
                return NULL;
            } else {
                results = new_results;
            }
        }
        
        // Convert the string and add to the list to return
        results[(*return_len)++] = convert(line);
    }

    fclose(ptr_file);
    if (line) {
        free(line);
    }

    // printf("Returning list of floats, size %i \n", *return_len);

    return results;
}

size_t strlen(char* input_str) {
    size_t len = 0;

    while (input_str[len++] != '\0') {}

    return len;
}

void strrev(char* input_str) {
    // Set the length of the string as one less to not reverse the null termination
    size_t len = strlen(input_str) - 1;

    for (int i=0; i<(len/2); i++){
        char temp = input_str[i];
        input_str[i] = input_str[len-1-i];
        input_str[len-1-i] = temp;
    }

}

float reverseStringToFloat(char* input_str) {
    strrev(input_str);
    return atof(input_str);
}
