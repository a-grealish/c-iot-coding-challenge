#include "cluster.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_ITERATIONS 20

void twoGroupMidpointCluster(float* data, int* cluster, int len){
    float min = INFINITY;
    float max = -INFINITY;
    float threshold = 0;

    for (int i=0; i<len; i++){
        if (data[i] < min)
            min = data[i];
        if (data[i] > max)
            max = data[i];
    }
    threshold = min + ((max-min)/2.0);
    // printf("Min: %f, Max: %f, Threshold: %f \n", min, max, threshold);

    for (int i=0; i<len; i++) {
        if (data[i] > threshold)
            cluster[i] = 1;
        else
            cluster[i] = 0;
    }
}

// Used be the qsort algo to compare two floats
int compare (const void * a, const void * b)
{
  float fa = *(const float*) a;
  float fb = *(const float*) b;
  return (fa > fb) - (fa < fb);
}

void k_MeansCluster1d(float* data, int* cluster, int len, int k) {
    float* means;
    float* prev_means;
    float* k_sums;
    float* k_count;

    int itterations = 0;

    if (k < 1) {
        fprintf(stderr, "ERROR: there must be at least 1 cluster\n");
        return;
    }

    means = malloc(sizeof(float)*k);
    if (means == NULL) {
        perror("ERROR");
        return;
    }

    prev_means = malloc(sizeof(float)*k);
    if (prev_means == NULL) {
        perror("ERROR");
        return;
    }

    k_sums = calloc(k, sizeof(float));
    if (k_sums == NULL) {
        perror("ERROR");
        return;
    }

    k_count = calloc(k, sizeof(float));
    if (k_count == NULL) {
        perror("ERROR");
        return;
    }

    // Initilise the means by choosing random value from 
    // data - Forgy  Init. Doesn't matter if this isn't truely random
    for (int i=0; i<k; i++)
        means[i] = data[rand() % len];


    // Loop through the iterations of k-means until it converges
    while (itterations++ < MAX_ITERATIONS) {

        // Order the means to make the clusters numbers increase
        // from smallest mean to largest
        qsort(means, k, sizeof(float), compare);

        // Copy the means to the prev_means memory
        // Zero out the counts and sums
        for (int i=0; i<k; i++) {   
            prev_means[i] = means[i];
            k_sums[i] = 0;
            k_count[i] = 0;
        }

        // For each value in data assign it to the nearest k
        for (int i=0; i<len; i++) {
            float closest_k_dist = INFINITY;

            for (int j=0; j<k; j++) {
                float k_dist = fabs(data[i] - means[j]);
                // printf("%i, %f < %f \n", i, k_dist, closest_k_dist);
                if (k_dist < closest_k_dist) {
                    closest_k_dist = k_dist;
                    cluster[i] = j;
                }
            }

            // Add the data point to the sum and count to later find means
            k_sums[cluster[i]] += data[i];
            k_count[cluster[i]] += 1;
        }

        // Calculate the new means
        for (int i=0; i<k; i++) {
            if (k_count[i] != 0) {
                means[i] = k_sums[i] / k_count[i];
            }
        }

        // Exit the loop if the means have converged
        short converged = 1;
        for (int i=0; i<k; i++) {
            if (means[i] != prev_means[i]) {
                converged = 0;
                break;
            }
        }
        if (converged) 
            break;

    }

    free(means);
    free(prev_means);
    free(k_count);
    free(k_sums);
}
