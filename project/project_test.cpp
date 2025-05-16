#include "project.h"

// Should I be clustering (1x1, 3x3, 5x5, 7x7) and then find max or find max and cluster around that??

void print_cluster_energy(din16_t cluster_energy[GLOBAL_ETA][GLOBAL_PHI], int offset, int max_display=10) {
    int display_count = 0;
    for (int crystal_eta = 0; crystal_eta < GLOBAL_ETA; crystal_eta++) {
        for (int crystal_phi = 0; crystal_phi < GLOBAL_PHI; crystal_phi++) {
            display_count++;
            if (display_count <= max_display) {
                std::cout << cluster_energy[crystal_eta][crystal_phi] << " ";
            }
        }
        if (display_count <= max_display) std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {

    din8_t crystal_energy[GLOBAL_ETA][GLOBAL_PHI]; // Crystal Energy
    // Local to global crystal coordinate (local + (tower_number * crystals per tower) = global)
    din16_t tower_energy[TOWER_ETA][TOWER_PHI]; // Tower Energy
    din16_t cluster_3x3_energy[GLOBAL_ETA][GLOBAL_PHI]; // 3 x 3 Cluster Energy
    din16_t cluster_5x5_energy[GLOBAL_ETA][GLOBAL_PHI]; // 5 x 5 Cluster Energy
    din16_t cluster_7x7_energy[GLOBAL_ETA][GLOBAL_PHI]; // 7 x 7 Cluster Energy
    // Another index could be added to store energy value, and original eta and phi
    
    // Ensure input file
    std::ifstream input_file("input_energy.dat");
    if (!input_file) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    // Read input file, assign to crystal_energy
    for (size_t global_eta = 0; global_eta < GLOBAL_ETA; global_eta++) {
        for (size_t global_phi = 0; global_phi < GLOBAL_PHI; global_phi++) {
            din8_t crystal_energy_value;
            if (input_file >> crystal_energy_value) {
                crystal_energy[global_eta][global_phi] = crystal_energy_value;
            } else {
                std::cerr << "Error reading input energy value." << std::endl;
                return 1;
            }
            tower_energy[(int)(global_eta/CRYSTALS_ETA)][(int)(global_phi/CRYSTALS_PHI)] = 0;
            cluster_3x3_energy[global_eta][global_phi] = 0;
            cluster_5x5_energy[global_eta][global_phi] = 0;
            cluster_7x7_energy[global_eta][global_phi] = 0;
        }
    }

    // Call the project function
    project(crystal_energy, tower_energy, cluster_3x3_energy, cluster_5x5_energy, cluster_7x7_energy);
    input_file.close();

    // Print the crystal_energy
    // std::cout << "Crystal Energy: " << std::endl;
    // for (size_t global_eta = 0; global_eta < GLOBAL_ETA; global_eta++) {
    //     for (size_t global_phi = 0; global_phi < GLOBAL_PHI; global_phi++) {
    //         std::cout << (int)crystal_energy[global_eta][global_phi] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    // Print the tower_energy
    std::cout << "Tower Energy: " << std::endl;
    for (size_t tower_eta = 0; tower_eta < TOWER_ETA; tower_eta++) {
        for (size_t tower_phi = 0; tower_phi < TOWER_PHI; tower_phi++) {
            std::cout << (int) tower_energy[tower_eta][tower_phi] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Print the cluster energies
    std::cout << "Sorted 3x3 Cluster Energy: " << std::endl;
    print_cluster_energy(cluster_3x3_energy, 0);
    std::cout << "Sorted 5x5 Cluster Energy: " << std::endl;
    print_cluster_energy(cluster_5x5_energy, 0);
    std::cout << "Sorted 7x7 Cluster Energy: " << std::endl;
    print_cluster_energy(cluster_7x7_energy, 0);
}