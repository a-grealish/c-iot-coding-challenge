#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "file_parser.h"
#include "cluster.h"

/**
 * Takes input list, clusters the data and calculates the ratio of on time
 * @params values - list of raw data readings
 * @params len length of the input list
 * @return float that is the ratios of time on
 */
float calculateOnTime(float* values, int len) {
    int* cluster;
    int on = 0;

    cluster = malloc(sizeof(int)*len);
    if (cluster == NULL) {
        perror("ERROR");
        return 0;
    }

    // Cluster with data with one of the two algos
    // twoGroupMidpointCluster(values, cluster, len);
    k_MeansCluster1d(values, cluster, len, 2);

    for (int i=0; i<len; i++) {
        if (cluster[i] != 0)
            on += 1;
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
        fprintf(stderr, "ERROR: Please pass in both input and output path \n");
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
        perror("ERROR");
        return 1;
    }
    fprintf(ptr_file, "%f\n", on_time);
    fclose(ptr_file);


    return 0;

}