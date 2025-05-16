**Calorimeter Level-1 trigger system in real HEP experiment.**  
Process calorimeter data to cluster energy deposits, perform the sorting of these clusters, make triggerable objects (photons, jet candidates, MET).
1. Input Data:
    - Simulate a grid of calorimeter cells or a QCD sample
        - e.g. 2D array of energy desposits, eta vs phi 
    - Optionally, use already simulated samples contianing CMS or ATLAS HCAL/ECAl
2. Clustering Algorithm:
    - Perform sliding window clustering:
        - Identify local maxima in calorimeter grid,
        - Build clusters (3 x 3, 5 x 5, 7 x 7) by summing nearby cells (why would different sizes be needed?)
        - Compare thresholds for seed and sum
        - Keep seed positions
3. Sorting:
    - Sort clusters by transverse energy or position
    - Output top-N clusters
        - e.g. for jet candiates, photon/electron candidates, MET
4. Trigger Object Creation and Send Out:
    - Use cluster properties to generate trigger candidates
        - e.g. total transverse energy, missing transverse energy using vector sum, jet or EM candidates  

Submitted Work:  
1.  - Converted the example data shown on lecture 24, slide 8 into input_crystal_energy.dat which has the corresponding crystal energies.
    - project_test.cpp reads in input.dat and assigns the values to elements of matrix crystal_energy of size (towers in eta x crystals in eta per tower) x (towers in phi x crystals in phi per tower) = (17 x 5) x (2 x 5) = 85 x 10.
2.  - Matrix input is passed to project function in project.cpp, where the sliding window cluster algorithm is performed.
    - Clustering into towers and 3 x 3, 5 x 5, and 7 x 7 regions is performed and saved to  respective matricies (tower_energy, cluster_3x3_energy, cluster_5x5_energy, cluster_7x7_energy).
3.  - Energy deposit clusters are sorted via bubble sort.
    - Sorted energy desposits are sent back to project_test.cpp and top-N = 10 displayed.

HLS Pragma Implementation:
| Version Number         | Latency (cycles) | Latency (absolute) [ms] | BRAM | DSP  | FF    | LUT    | URAM |
| ---------------------- | ---------------- | ----------------------- | ---- | ---- | ----- | ------ | ---- |
| 1 - initial_csynth.rpt | ?                | ?                       | 10   | 0    | 1512  | 4229   | 0    |
| 2                      | 2279411          | 56.985                  | 60   | 0    | 2170  | 8089   | 0    |
1. No pragmas used
2. Added following pragmas  
    - project function:
        - STABLE variable=crystal_energy
        - ARRAY_PARTITION variable=crystal_energy_buffer1 complete dim=2
        - ARRAY_PARTITION variable=crystal_energy_buffer2 complete dim=2
        - ARRAY_PARTITION variable=crystal_energy_buffer3 complete dim=2
        - ARRAY_PARTITION variable=crystal_energy_buffer4 complete dim=2
        - ARRAY_PARTITION variable=cluster_3x3_buffer complete dim=2
        - ARRAY_PARTITION variable=cluster_5x5_buffer complete dim=2
        - ARRAY_PARTITION variable=cluster_7x7_buffer complete dim=2
        - DATAFLOW
        - PIPELINE II=1  
    - calculate_tower_energy and calculate_cluster_energy function:
        - INLINE off
        - ARRAY_PARTITION variable=crystal_energy complete dim=2
        - ARRAY_PARTITION variable=tower_energy complete dim=2
        - PIPELINE II=1
        - LATENCY min=3 max=10
        - UNROLL
    - sort_cluster_energy function:
        - INLINE off
        - ARRAY_PARTITION variable=unsorted_cluster complete dim=2
        - ARRAY_PARTITION variable=sorted_cluster complete dim=2
        - ARRAY_PARTITION variable=buffer complete dim=2
        - PIPELINE II=1
        - LOOP_TRIPCOUNT min=1 max=850
3. Restructed sort_cluster_energy to map 2D unsorted_cluster to 1D flattened_array to be sorted. Converted all sorted cluster_energy to 1D lists of energy.
