Initial DSP = 4, see initial_csynth.rpt

With submitted alterations DSP = 0.

Added HLS Pipeline II=2, Allocation instances=mul limit=0 operation, and Inline pragmas to compute_blur function. Changed variable types to din9_t, in addition to setting the sum in compute_blue to type din9_t before dividing by 3.