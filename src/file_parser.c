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
        printf("Not appropriate convertion function passed\n");
        return NULL;
    }

    // Open the file
    ptr_file = fopen(filename, "r");
    if (!ptr_file) {
        printf("Could not open file\n");
        return NULL;
    }

    // Allocate output buffer
    results = malloc(sizeof(float)*results_len);
    if (results == NULL) {
        printf("Out of memory\n");
        return NULL;
    }

    // Read and convert one line at a time using the convert function pointer
    // ToDo: fix this and reduce the number of floats allocated initally
    while((read = getline(&line, &len, ptr_file)) != -1) {
        
        if (*return_len >= results_len) {
            results_len *= 2;
            float* new_results = realloc(results, sizeof(float)*results_len);
            if (new_results == NULL) {
                printf("Out of memory\n");
                free(results);
                return NULL;
            } else {
                results = new_results;
            }
        }
        
        results[(*return_len)++] = convert(line);
    }

    fclose(ptr_file);
    if (line) {
        free(line);
    }

    printf("Returning list of floats, size %i \n", *return_len);

    return results;
}


float reverseStringToFloat(char* input_str) {
    int i = 0;
    int j = 0;
    char* reversed_string;
    float converted;

    // Find the size of the input string and make an appropriatly sized buffer
    while (input_str[i++] != '\n' || input_str[i] != '\0'); 
    reversed_string = malloc(sizeof(char)*(i+1));

    // Cycle through the string and reverse it, ending with a null
    while (--i >= 0) {
        reversed_string[j++] = input_str[i];
    }
    reversed_string[j] = '\0';

    // Convert to a float
    converted = atof(reversed_string);

    // Free up the memory
    free(reversed_string);

    // Convert to float and return
    return converted;
}