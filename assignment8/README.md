| Version Number         | Latency (cycles) | Latency (absolute) [ms] | BRAM | DSP  | FF    | LUT    | URAM |
| ---------------------- | ---------------- | ----------------------- | ---- | ---- | ----- | ------ | ---- |
| 1 - initial_csynth.rpt | 532609           | 13.315                  | 0    | 3    | 105   | 269    | 0    |
| 2                      | 131137           | 3.278                   | 0    | 2048 | 25971 | 81464  | 0    |
| 3                      | 4098             | 0.102                   | 0    | 37   | 53    | 1109   | 0    |
| 4                      | 16387            | 0.41                    | 0    | 37   | 340   | 2174   | 0    |
| 5                      | 16387            | 0.41                    | 0    | 37   | 340   | 2174   | 0    |
| 6                      | 8194             | 0.205                   | 0    | 37   | 454   | 1165   | 0    |
| 7 - final_csynth.rpt   | 8194             | 0.205                   | 0    | 37   | 454   | 1165   | 0    |

1. Initial provided code
2. Changed typedef from 32 bit signed int to 4, 5, and 15 bit unsigned int for elements of martices A, B, and C to minimize memory while holding max possible value.
3. Added following pragmas. Added new temp variable to reduce memory access and allow for better loop unrolling.
    - Inline
    - Stable variable=<A, B> 
    - Array_partition variable=<A, B, C> complete dim=<2, 1, 0>
    - Interface ap_ctrl_hs port=return
    - Interface ap_memory port=<A, B, C>
    - Dataflow
    - Pipeline II=2
    - Unroll
4. Added and changed following pragma options
    - Loop_Flatten
    - Loop_tripcount min=64 max=64
    - Array_partition complete -> Array_partition cyclic factor=8
    - Unroll -> Unroll factor=8
    - Interface ap_ctrl_hs -> Interface s_axilite
    - Interface ap_memory -> Interface ap_vld
5. Removed Loop_flatten and Loop_tripcount. Changed Interface ap_vld port=<A, B> -> Interface ap_memory port=<A, B>
6. Changed Array_partition cyclic factor=8 -> Array_partition complete
7. Changed Unroll factor=8 -> Unroll

- Can't figure out how to get back to version 3 stats, the only difference between version 3 and 7 should be Interface ap_ctrl_hs -> Interface s_axilite, which was changed at request of Vivado warning.
- No restraints on specific memory type so didn't test pragmas like Bind_storage, Bind_op, Resource