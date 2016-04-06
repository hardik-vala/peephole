#!/bin/bash

##############################
# Compile & Run Benchmark #4 #
##############################


# Directory of Benchmarks.
PEEPBENCHDIR=$PEEPDIR/PeepholeBenchmarks
# Benchmark #4 directory.
PEEPBENCH1DIR=$PEEPBENCHDIR/bench04

# Java compile.
cd $PEEPBENCHDIR/bench04 && make -f Makefile javac 
# Run.
cd $PEEPBENCHDIR/bench04 && make -f Makefile run
