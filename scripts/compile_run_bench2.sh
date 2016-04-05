#!/bin/bash

##############################
# Compile & Run Benchmark #2 #
##############################


# Directory of Benchmarks.
PEEPBENCHDIR=$PEEPDIR/PeepholeBenchmarks
# Benchmark #2 directory.
PEEPBENCH1DIR=$PEEPBENCHDIR/bench02

# Java compile.
cd $PEEPBENCHDIR/bench02 && make -f Makefile javac 
# Run.
cd $PEEPBENCHDIR/bench02 && make -f Makefile run
