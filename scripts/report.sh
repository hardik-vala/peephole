#!/bin/bash

################################################
# JOOS Compiles Benchmarks & Report Statistics #
################################################

# Run with -O to include optimizations (which is usually what you want to do,
# but you can run it without for debugging).

if [[ -z $1 ]]
then	
	total=`$PEEPDIR/scripts/joosc_bench.sh | grep code_length | awk '{sum += $3} END {print sum}'`
	echo -e "TOTAL CODE LENGTH: $total"
	exit 0
fi

# Total code length without optimizations (Hard-coded).
total=20814
# Total code length with optimizations.
totalo=`$PEEPDIR/scripts/joosc_bench.sh -O | grep code_length | awk '{sum += $3} END {print sum}'`

echo -e "----- CODE LENGTH REPORT -----"
echo -e "NO OPT.: $total"
echo -e "A- OPT.: (TODO)"
echo -e "A+ OPT.: (TODO)"
echo ""

# Calculate the code length difference.
if [[ $total -ge $totalo ]]
then
	diff=$(expr $total - $totalo)
	echo -e "OUR OPT.: $totalo (-$diff NO OPT.)"
else
	diff=$(expr $totalo - $total)
	echo -e "OUR OPT.: $totalo (+$diff NO OPT.)"
fi
