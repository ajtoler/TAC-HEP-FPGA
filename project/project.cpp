#include <ap_int.h>
#include <hls_stream.h>
#include "project.h"

void sort_cluster_energy(din16_t cluster_energy[GLOBAL_ETA][GLOBAL_PHI]) {
    // Sorts in descending order, to switch to ascending order, just switch the < to >
    for (int t = 1; t < GLOBAL_ETA * GLOBAL_PHI; t++) {
        // Sorts rows
        for (int i = 0; i < GLOBAL_ETA; i++){
            for (int j = 0; j < GLOBAL_PHI; j++){
                if (cluster_energy[i][j] < cluster_energy[i][j+1]){
                    din16_t temp = cluster_energy[i][j];
                    cluster_energy[i][j] = cluster_energy[i][j+1];
                    cluster_energy[i][j+1] = temp;
                }
            }
        }
        // Check for start/end of sequential rows
        for (int i = 0; i < GLOBAL_ETA - 1; i++){
            if (cluster_energy[i][GLOBAL_PHI - 1] < cluster_energy[i+1][0]){
                din16_t temp = cluster_energy[i][GLOBAL_PHI - 1];
                cluster_energy[i][GLOBAL_PHI - 1] = cluster_energy[i+1][0];
                cluster_energy[i+1][0] = temp;
            }
        }
    }
}

void calculate_cluster_energy(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
                    din16_t cluster_energy[GLOBAL_ETA][GLOBAL_PHI],
                    din2_t offset) {

    for (int crystal_eta = offset; crystal_eta < GLOBAL_ETA - offset; crystal_eta++) {
        for (int crystal_phi = offset; crystal_phi < GLOBAL_PHI - offset; crystal_phi++) {
            din16_t cluster_energy_value = 0;
            for (int i = -offset; i <= offset; i++) {
                for (int j = -offset; j <= offset; j++) {
                    din8_t crystal_energy_value = crystal_energy[crystal_eta + i][crystal_phi + j];
                    cluster_energy_value += crystal_energy_value;
                }
            }
            cluster_energy[crystal_eta][crystal_phi] = cluster_energy_value; /// ((2 * offset + 1) * (2 * offset + 1));
        }
    }
}

void calculate_tower_energy(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
                  din16_t tower_energy[TOWER_ETA][TOWER_PHI]) {

    for (int tower_eta = 0; tower_eta < TOWER_ETA; tower_eta++) {
        for (int tower_phi = 0; tower_phi < TOWER_PHI; tower_phi++) {
            din16_t tower_energy_value = 0;
                for (int crystal_eta = 0; crystal_eta < CRYSTALS_ETA; crystal_eta++) {
                    for (int crystal_phi = 0; crystal_phi < CRYSTALS_PHI; crystal_phi++) {
                        din8_t crystal_energy_value = crystal_energy[tower_eta * CRYSTALS_ETA + crystal_eta][tower_phi * CRYSTALS_PHI + crystal_phi];
                        tower_energy_value += crystal_energy_value;
                    }
                }
            tower_energy[tower_eta][tower_phi] = tower_energy_value;
        }
    }
}

void project(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
             din16_t tower_energy[TOWER_ETA][TOWER_PHI], 
             din16_t cluster_3x3_energy[GLOBAL_ETA][GLOBAL_PHI],
             din16_t cluster_5x5_energy[GLOBAL_ETA][GLOBAL_PHI],
             din16_t cluster_7x7_energy[GLOBAL_ETA][GLOBAL_PHI]) {
    

    calculate_tower_energy(crystal_energy, tower_energy);
    calculate_cluster_energy(crystal_energy, cluster_3x3_energy, 1);
    calculate_cluster_energy(crystal_energy, cluster_5x5_energy, 2);
    calculate_cluster_energy(crystal_energy, cluster_7x7_energy, 3);
    sort_cluster_energy(cluster_3x3_energy);
    sort_cluster_energy(cluster_5x5_energy);
    sort_cluster_energy(cluster_7x7_energy);
}