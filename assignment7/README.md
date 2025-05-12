Part A - pre-optimization changes: (See initial_csynth.rpt)
- Changed values assigned A and B to random numbers so that when C is calculated it isn't already sorted. 
- With N changed to 64 and SORT_N remaining at 32, the resulting matrix C has 64 elements, but only the first 32 are sorted. 
- Additionally the pragma HLS PIPELINE was simply commented out and the prod and temp were changed to typ din_t.

Part B - optimization changes: (See final_csynth)
- Type definitions - created unassigned integers of bit length required to hold maximum values
- INTERFACE ap_memory - sets arrays as standard RAM
- INTERFACE ap_ctrl_hs - allows handshake with hardware, indicates when idle, done, and ready for new input
- ARRAY_PARTITION - breaks arrays to allow parallel access
- INLINE - increases parallelism, logic area
- PIPELINE - allows concurrent execution
- UNROLL - unrolls loop to allow parallel operations
- STABLE - keeps input/output behavior of buffer from changing

Attempted to put the matrix multiplication into it's own function so it can be paralleled with the bubble sort. Though latency was decreases slightly, FF and LUT were increase damatically. (see matrix_multiplication_csynth.rpt)