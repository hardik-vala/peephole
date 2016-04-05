#!/bin/bash

############################################################
# Calculates total code length of JOOS compiled benchmarks #
############################################################


# Run with -O to include optimizations.
$PEEPDIR/scripts/joosc_bench.sh $1 | grep code_length | awk '{sum += $3} END {print sum}'
