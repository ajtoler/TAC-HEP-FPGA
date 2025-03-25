############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project assignment3p2
set_top assignment3p2
add_files assignment3p2.c
add_files assignment3p2.h
open_solution "solution1"
set_part {xcvu9p-flga2104-1-i}
create_clock -period 10 -name default
#source "./assignment3p2/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
