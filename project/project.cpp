#include <ap_int.h>
#include <hls_stream.h>
#include "project.h"

void sort_cluster_energy(din16_t unsorted_cluster[GLOBAL_ETA][GLOBAL_PHI], din16_t sorted_list[GLOBAL_ETA * GLOBAL_PHI]) {
    din16_t flattened_array[GLOBAL_ETA * GLOBAL_PHI];
#pragma HLS INLINE off
#pragma HLS ARRAY_PARTITION variable=unsorted_cluster complete dim=2
#pragma HLS ARRAY_PARTITION variable=sorted_list complete dim=1
#pragma HLS ARRAY_PARTITION variable=flattened_array complete dim=1

    // Flatten
    int i = 0;
    for (int j = 0; j < GLOBAL_ETA; ++j) {
        for (int k = 0; k < GLOBAL_PHI; ++k) {
#pragma HLS UNROLL
            flattened_array[i] = unsorted_cluster[j][k];
            i++;
        }
    }

    // Bubble Sort
    for (int i = 0; i < GLOBAL_ETA * GLOBAL_PHI - 1; i++) {
        for (int j = 0; j < GLOBAL_ETA * GLOBAL_PHI - i - 1; j++) {
            #pragma HLS PIPELINE II=1
            if (flattened_array[j] < flattened_array[j + 1]) {
                din16_t temp = flattened_array[j];
                flattened_array[j] = flattened_array[j + 1];
                flattened_array[j + 1] = temp;
            }
        }
    }

    // Rebuild 2D
    for (int i = 0; i < GLOBAL_ETA*GLOBAL_PHI; ++i) {
#pragma HLS UNROLL
            sorted_list[i] = flattened_array[i];
    }
}

void calculate_cluster_energy(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
                    din16_t cluster_energy[GLOBAL_ETA][GLOBAL_PHI],
                    din2_t offset) {
#pragma HLS INLINE off
#pragma HLS ARRAY_PARTITION variable=crystal_energy complete dim=2
#pragma HLS ARRAY_PARTITION variable=cluster_energy complete dim=2

    for (int crystal_eta = offset; crystal_eta < GLOBAL_ETA - offset; crystal_eta++) {
        for (int crystal_phi = offset; crystal_phi < GLOBAL_PHI - offset; crystal_phi++) {
#pragma HLS PIPELINE II=1
#pragma HLS LATENCY min=3 max=10
            din16_t cluster_energy_value = 0;
            for (int i = -offset; i <= offset; i++) {
#pragma HLS UNROLL
                for (int j = -offset; j <= offset; j++) {
#pragma HLS UNROLL
                    cluster_energy_value += crystal_energy[crystal_eta + i][crystal_phi + j];;
                }
            }
            cluster_energy[crystal_eta][crystal_phi] = cluster_energy_value; /// ((2 * offset + 1) * (2 * offset + 1));
        }
    }
}

void calculate_tower_energy(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
                  din16_t tower_energy[TOWER_ETA][TOWER_PHI]) {
#pragma HLS INLINE off
#pragma HLS ARRAY_PARTITION variable=crystal_energy complete dim=2
#pragma HLS ARRAY_PARTITION variable=tower_energy complete dim=2

    for (int tower_eta = 0; tower_eta < TOWER_ETA; tower_eta++) {
        for (int tower_phi = 0; tower_phi < TOWER_PHI; tower_phi++) {
#pragma HLS PIPELINE II=1
#pragma HLS LATENCY min=3 max=10
            din16_t tower_energy_value = 0;
                for (int crystal_eta = 0; crystal_eta < CRYSTALS_ETA; crystal_eta++) {
#pragma HLS UNROLL
                    for (int crystal_phi = 0; crystal_phi < CRYSTALS_PHI; crystal_phi++) {
#pragma HLS UNROLL
                        tower_energy_value += crystal_energy[tower_eta * CRYSTALS_ETA + crystal_eta][tower_phi * CRYSTALS_PHI + crystal_phi];
                    }
                }
            tower_energy[tower_eta][tower_phi] = tower_energy_value;
        }
    }
}

void project(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
             din16_t tower_energy[TOWER_ETA][TOWER_PHI], 
             din16_t list_3x3_energy[GLOBAL_ETA * GLOBAL_PHI],
             din16_t list_5x5_energy[GLOBAL_ETA * GLOBAL_PHI],
             din16_t list_7x7_energy[GLOBAL_ETA * GLOBAL_PHI]) {
    din8_t crystal_energy_buffer1[GLOBAL_ETA][GLOBAL_PHI];
    din8_t crystal_energy_buffer2[GLOBAL_ETA][GLOBAL_PHI];
    din8_t crystal_energy_buffer3[GLOBAL_ETA][GLOBAL_PHI];
    din8_t crystal_energy_buffer4[GLOBAL_ETA][GLOBAL_PHI];
    din16_t cluster_3x3_buffer[GLOBAL_ETA][GLOBAL_PHI];
    din16_t cluster_5x5_buffer[GLOBAL_ETA][GLOBAL_PHI];
    din16_t cluster_7x7_buffer[GLOBAL_ETA][GLOBAL_PHI];
#pragma HLS STABLE variable=crystal_energy
#pragma HLS ARRAY_PARTITION variable=crystal_energy_buffer1 complete dim=2
#pragma HLS ARRAY_PARTITION variable=crystal_energy_buffer2 complete dim=2
#pragma HLS ARRAY_PARTITION variable=crystal_energy_buffer3 complete dim=2
#pragma HLS ARRAY_PARTITION variable=crystal_energy_buffer4 complete dim=2
#pragma HLS ARRAY_PARTITION variable=list_3x3_energy complete dim=1
#pragma HLS ARRAY_PARTITION variable=list_5x5_buffer complete dim=1
#pragma HLS ARRAY_PARTITION variable=list_7x7_buffer complete dim=1
#pragma HLS DATAFLOW

    for (int i = 0; i < GLOBAL_ETA; ++i) {
        for (int j = 0; j < GLOBAL_PHI; ++j) {
#pragma HLS PIPELINE II=1
            crystal_energy_buffer1[i][j] = crystal_energy[i][j];
            crystal_energy_buffer2[i][j] = crystal_energy[i][j];
            crystal_energy_buffer3[i][j] = crystal_energy[i][j];
            crystal_energy_buffer4[i][j] = crystal_energy[i][j];
        }
    }


    calculate_tower_energy(crystal_energy_buffer1, tower_energy);
    calculate_cluster_energy(crystal_energy_buffer2, cluster_3x3_buffer, 1);
    calculate_cluster_energy(crystal_energy_buffer3, cluster_5x5_buffer, 2);
    calculate_cluster_energy(crystal_energy_buffer4, cluster_7x7_buffer, 3);
    sort_cluster_energy(cluster_3x3_buffer, list_3x3_energy);
    sort_cluster_energy(cluster_5x5_buffer, list_5x5_energy);
    sort_cluster_energy(cluster_7x7_buffer, list_7x7_energy);
}
