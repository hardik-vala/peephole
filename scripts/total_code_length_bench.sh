#!/bin/bash

############################################################
# Calculates total code length of JOOS compiled benchmarks #
############################################################

# Run with -O to include optimizations.

total=`$PEEPDIR/scripts/joosc_bench.sh $1 | grep code_length | awk '{sum += $3} END {print sum}'`

# Calculate the code length difference against no optimizations.
diff=$(expr 20814 - $total)

if [[ $diff -ge 0 ]]
then
	echo -e "TOTAL CODE LENGTH: $total (-$diff)"
else
	echo -e "TOTAL CODE LENGTH: $total (+$diff)"
fi
