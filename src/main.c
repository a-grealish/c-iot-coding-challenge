#include "main.h"
#include <stdio.h>
#include <math.h>

#include "file_parser.h"


int main (void) {

    char in_file[] = "./data/test_file.txt";
    char out_file[] = "./data/out_file.txt";
    float* out;
    size_t readings_len = 0;
    float total = 0;

    float min = INFINITY;
    float max = -INFINITY;
    float threshold = 0;
    
    out = parseFile(in_file, reverseStringToFloat, &readings_len);

    printf("Output[0]: %f, Output[1]: %f, list size: %i \n", out[0], out[1], readings_len);

    for (int i=0; i<readings_len; i++){
        if (out[i] < min)
            min = out[i];
        if (out[i] > max)
            max = out[i];

        total += out[i];
    }
    threshold = min + ((max-min)/2.0);
    printf("Total: %f Min: %f, Max: %f, Threshold: %f \n", total, min, max, threshold);

    int on = 0;
    for (int i=0; i<readings_len; i++) {
        if (out[i] > threshold)
            on++;
    }
    float on_ratio = (float)on / (float)readings_len;

    printf("On time: %f \n", on_ratio);

    // Open the file
    FILE* ptr_file;
    ptr_file = fopen(out_file, "w");
    if (!ptr_file) {
        printf("Could not open output file\n");
        return -1;
    }
    fprintf(ptr_file, "%f\n", on_ratio);
    fclose(ptr_file);


    return 0;

}