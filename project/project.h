#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ap_int.h"

using namespace std;

#define TOWER_ETA 17
#define TOWER_PHI 2
#define CRYSTALS_ETA 5
#define CRYSTALS_PHI 5 
#define GLOBAL_ETA (TOWER_ETA*CRYSTALS_ETA)
#define GLOBAL_PHI (TOWER_PHI*CRYSTALS_PHI)

typedef ap_uint<2> din2_t; // matrix offset
typedef ap_uint<8> din8_t; // energy in crystal
typedef ap_uint<16> din16_t; // energy in cluster

void project(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
             din16_t tower_energy[TOWER_ETA][TOWER_PHI], 
             din16_t list_3x3_energy[GLOBAL_ETA * GLOBAL_PHI],
             din16_t list_5x5_energy[GLOBAL_ETA * GLOBAL_PHI],
             din16_t list_7x7_energy[GLOBAL_ETA * GLOBAL_PHI]);
void calculate_tower_energy(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
                  din16_t tower_energy[TOWER_ETA][TOWER_PHI]);
void calculate_cluster_energy(din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI],
                    din16_t cluster_energy[GLOBAL_ETA][GLOBAL_PHI],
                    din2_t offset);
void sort_cluster_energy(din16_t unsorted_cluster[GLOBAL_ETA][GLOBAL_PHI], din16_t sorted_list[GLOBAL_ETA * GLOBAL_PHI]);

#endif