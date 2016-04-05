#!/bin/bash

##############################
# Compile & Run Benchmark #3 #
##############################


# Directory of Benchmarks.
PEEPBENCHDIR=$PEEPDIR/PeepholeBenchmarks
# Benchmark #3 directory.
PEEPBENCH1DIR=$PEEPBENCHDIR/bench03

# Java compile.
cd $PEEPBENCHDIR/bench03 && make -f Makefile javac 
# Run.
cd $PEEPBENCHDIR/bench03 && make -f Makefile run
