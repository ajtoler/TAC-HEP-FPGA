#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /afs/hep.wisc.edu/user/atoler/fpga/assignment3p2/assignment3p2/solution1/.autopilot/db/a.g.bc ${1+"$@"}
