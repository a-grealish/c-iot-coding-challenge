#ifndef CLUSTER_H
#define CLUSTER_H
#include <stddef.h>

/**
 * A function which takes a lists of floats, finds the midpoint between mid and 
 * max and uses this to classify each point. > the midpoint is classified as on.
 * @param data a pointer to an array of floats
 * @param cluster an int array of length len to return the cluster for each point
 * @param len the number of floats in the array
 * @returns void
 */
void twoGroupMidpointCluster(float* data, int* cluster, int len);

/** 
 * Clusters the list of floats in data into k categories using
 * a simplified k-means algorithm for 1D data
 * The cluster numbers are order so the lowest cluster corresponds to the
 * lowest cluster mean.
 * @param data pointer to the list of input values to cluster
 * @param cluster pointer to list of ints to store the cluster for each data point
 * @param len the number of data points and sizeof data and cluster
 * @param k the number of clusters to group the data into
 * @returns void
 */
void k_MeansCluster1d(float* data, int* cluster, int len, int k);

#endif