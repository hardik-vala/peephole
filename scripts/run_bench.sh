#!/bin/bash

##################
# Run Benchmarks #
##################

for i in {1..7}
do
	cd $PEEPDIR/PeepholeBenchmarks/bench0$i && make -f Makefile run
done
