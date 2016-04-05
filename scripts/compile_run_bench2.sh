#!/bin/bash

##############################
# Compile & Run Benchmark #2 #
##############################


# Directory of Benchmarks.
PEEPBENCHDIR=$PEEPDIR/PeepholeBenchmarks
# Benchmark #2 directory.
PEEPBENCH1DIR=$PEEPBENCHDIR/bench01

# Java compile.
cd $PEEPBENCHDIR/bench01 && make -f Makefile javac 
# Run.
cd $PEEPBENCHDIR/bench01 && make -f Makefile run
