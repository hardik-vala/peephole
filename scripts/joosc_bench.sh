#!/bin/bash

###########################
# JOOS compile benchmarks #
###########################

## Run with -O to include optimizations.

# Path to benchmark directory
BENCHDIR=$PEEPDIR/PeepholeBenchmarks

# List of bench directories.
bench_dirs=(
	$BENCHDIR/bench01
	$BENCHDIR/bench02
	$BENCHDIR/bench03
	$BENCHDIR/bench04
	$BENCHDIR/bench05
	$BENCHDIR/bench06
	$BENCHDIR/bench07
)

# Joos compile each benchmark.

# With optimizations.
if [[ $1 == "-O" ]]
then
	for bd in ${bench_dirs[@]}
	do
		cd $bd
		make -f Makefile joosc_opt
	done
# Without optimizations.
else
	for bd in ${bench_dirs[@]}
	do
		cd $bd
		make -f Makefile joosc
	done
fi
