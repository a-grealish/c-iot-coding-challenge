#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "check_cluster.h"
#include "../src/cluster.h"

void setUp (float** data, int** cluster, int len, int k) {

	*data = malloc(sizeof(float)*len);
	if (data == NULL) {
		perror("ERROR");
	}

	*cluster = malloc(sizeof(int)*len);
	if (cluster == NULL) {
		perror("ERROR");
	}

	for (int i=0; i<len; i++) {
		int value = rand() % k;
		// Add some noise which is 0.1 magnitude of the value
		float noise = (float)(rand() % 1000) / 10000;
	
		(*data)[i] = (float)value + noise;
		(*cluster)[i] = value;
	}
}

void tearDown (float* data, int* cluster) {
	free(data);
	free(cluster);
}

void test_differnt_k (int k) {
	float* data;
	int* cluster;
	int* cluster_results;
	int len = 10000;
	
	setUp(&data, &cluster, len, k);

	cluster_results = malloc(sizeof(int)*len);
	if (cluster_results == NULL) {
		perror("ERROR");
	}

	k_MeansCluster1d(data, cluster_results, len, k);

	// Check the cluster values
	for (int i=0; i<len; i++) {
		if (cluster[i] != cluster_results[i])
			printf("%i, %i, %i \n", i, cluster[i], cluster_results[i] );
		ck_assert_int_eq(cluster[i], cluster_results[i]);
	}

	// Clean up
	tearDown(data, cluster);
}

START_TEST (testk_MeansCluster1d_2) {
	test_differnt_k(2);
}
END_TEST

START_TEST (testk_MeansCluster1d_1) {
	test_differnt_k(1);
}
END_TEST

START_TEST (testk_MeansCluster1d_5) {
	test_differnt_k(5);
}
END_TEST

START_TEST (testTwoGroupMidpointCluster) {
	float* data;
	int* cluster;
	int* cluster_results;
	int len = 10000;
	
	setUp(&data, &cluster, len, 2);

	cluster_results = malloc(sizeof(int)*len);
	if (cluster_results == NULL) {
		perror("ERROR");
	}

	twoGroupMidpointCluster(data, cluster_results, len);

	// Check the cluster values
	for (int i=0; i<len; i++) {
		ck_assert_int_eq(cluster[i], cluster_results[i]);
	}

	// Clean up
	tearDown(data, cluster);	

}
END_TEST

Suite * ClusterSuite(void) {
	Suite *s;
	TCase *tc_k_means;
	TCase *tc_midpoint;

	s = suite_create("Cluster");

	// ---------------------------------------------------

	tc_k_means = tcase_create("k_menas");

	tcase_add_test(tc_k_means, testk_MeansCluster1d_1);
	tcase_add_test(tc_k_means, testk_MeansCluster1d_2);
	tcase_add_test(tc_k_means, testk_MeansCluster1d_5);
	suite_add_tcase(s, tc_k_means);

	// ---------------------------------------------------

	tc_midpoint = tcase_create("midpoint_cluster");

	tcase_add_test(tc_midpoint, testTwoGroupMidpointCluster);
	suite_add_tcase(s, tc_midpoint);

	return s;
}