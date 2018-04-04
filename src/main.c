#include "main.h"
#include <stdio.h>
#include <math.h>

#include "file_parser.h"

/**
 * A function which takes a lists of floats, finds the midpoint between mid and 
 * max and uses this to classify each point. > the midpoint is classified as on.
 * @param values a pointer to an array of floats
 * @param len the number of floats in the array
 * @returns float which is the proportion of time the unit is on
 */
float calculateOnTime(float* values, size_t len) {
    float min = INFINITY;
    float max = -INFINITY;
    float threshold = 0;

    for (int i=0; i<len; i++){
        if (values[i] < min)
            min = values[i];
        if (values[i] > max)
            max = values[i];
    }
    threshold = min + ((max-min)/2.0);
    // printf("Min: %f, Max: %f, Threshold: %f \n", min, max, threshold);

    int on = 0;
    for (int i=0; i<len; i++) {
        if (values[i] > threshold)
            on++;
    }
    float on_ratio = (float)on / (float)len;

    return on_ratio;
}


int main (int argc, char *argv[]) {

    char* in_file;
    char* out_file;

    float* out;
    size_t readings_len = 0;
    float on_time;

    // Check the passed in arguments
    if (argc == 3) {
        in_file = argv[1];
        out_file = argv[2];
    } else {
        printf("Please pass in both input and output path \n");
        return 1;
    }

    // Load the file and parse it to an array of floats
    out = parseFile(in_file, reverseStringToFloat, &readings_len);
    // printf("Output[0]: %f, Output[1]: %f, list size: %i \n", out[0], out[1], readings_len);

    // Calculate the on_time ratio
    on_time = calculateOnTime(out, readings_len);
    printf("On time: %f, reult written to %s \n", on_time, out_file);

    // Open the file and save the on_time result
    FILE* ptr_file;
    ptr_file = fopen(out_file, "w");
    if (!ptr_file) {
        printf("Could not open output file\n");
        return 1;
    }
    fprintf(ptr_file, "%f\n", on_time);
    fclose(ptr_file);


    return 0;

}