#!/bin/bash

###############################################
# JOOS Compile Benchmarks & Report Statistics #
###############################################

# Path to benchmark directory
BENCHDIR=$PEEPDIR/PeepholeBenchmarks

# Code lengths WITHOUT optimizations (Hard-coded) for each benchmark.
bench1=1148
bench2=571
bench3=3382
bench4=3906
bench5=1258
bench6=4348
bench7=6372

# Total code length without optimizations.
total=$(expr $bench1 + $bench2 + $bench3 + $bench4 + $bench5 + $bench6 + $bench7)

# JOOS compile each benchmark WITH optimizations and store the code lengths.
bench1o=`cd $BENCHDIR/bench01 && make -f Makefile joosco | grep code_length | awk '{sum += $3} END {print sum}'`
bench2o=`cd $BENCHDIR/bench02 && make -f Makefile joosco | grep code_length | awk '{sum += $3} END {print sum}'`
bench3o=`cd $BENCHDIR/bench03 && make -f Makefile joosco | grep code_length | awk '{sum += $3} END {print sum}'`
bench4o=`cd $BENCHDIR/bench04 && make -f Makefile joosco | grep code_length | awk '{sum += $3} END {print sum}'`
bench5o=`cd $BENCHDIR/bench05 && make -f Makefile joosco | grep code_length | awk '{sum += $3} END {print sum}'`
bench6o=`cd $BENCHDIR/bench06 && make -f Makefile joosco | grep code_length | awk '{sum += $3} END {print sum}'`
bench7o=`cd $BENCHDIR/bench07 && make -f Makefile joosco | grep code_length | awk '{sum += $3} END {print sum}'`

# Total code length with optimizations.
totalo=$(expr $bench1o + $bench2o + $bench3o + $bench4o + $bench5o + $bench6o + $bench7o)

echo -e "----- CODE LENGTH REPORT -----"

echo -e "B1, NO OPT.: $bench1"
if [[ $bench1 -ge $bench1o ]]
then
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench1 - $bench1o)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench1 * 100)" | python`
	echo -e "B1, OUR OPT.: $bench1o ( -$diff NO OPT. (-$perc%) )"
else
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench1o - $bench1)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench1 * 100)" | python`
	echo -e "B1, OUR OPT.: $bench1o ( +$diff NO OPT. (+$perc%) )"
fi
echo -e "B2, NO OPT.: $bench2"
if [[ $bench2 -ge $bench2o ]]
then
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench2 - $bench2o)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench2 * 100)" | python`
	echo -e "B2, OUR OPT.: $bench2o ( -$diff NO OPT. (-$perc%) )"
else
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench2o - $bench2)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench2 * 100)" | python`
	echo -e "B2, OUR OPT.: $bench2o ( +$diff NO OPT. (+$perc%) )"
fi
echo -e "B3, NO OPT.: $bench3"
if [[ $bench3 -ge $bench3o ]]
then
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench3 - $bench3o)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench3 * 100)" | python`
	echo -e "B3, OUR OPT.: $bench3o ( -$diff NO OPT. (-$perc%) )"
else
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench3o - $bench3)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench3 * 100)" | python`
	echo -e "B3, OUR OPT.: $bench3o ( +$diff NO OPT. (+$perc%) )"
fi
echo -e "B4, NO OPT.: $bench4"
if [[ $bench4 -ge $bench4o ]]
then
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench4 - $bench4o)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench4 * 100)" | python`
	echo -e "B4, OUR OPT.: $bench4o ( -$diff NO OPT. (-$perc%) )"
else
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench4o - $bench4)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench4 * 100)" | python`
	echo -e "B4, OUR OPT.: $bench4o ( +$diff NO OPT. (+$perc%) )"
fi
echo -e "B5, NO OPT.: $bench5"
if [[ $bench5 -ge $bench5o ]]
then
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench5 - $bench5o)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench5 * 100)" | python`
	echo -e "B5, OUR OPT.: $bench5o ( -$diff NO OPT. (-$perc%) )"
else
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench5o - $bench5)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench5 * 100)" | python`
	echo -e "B5, OUR OPT.: $bench5o ( +$diff NO OPT. (+$perc%) )"
fi
echo -e "B6, NO OPT.: $bench6"
if [[ $bench6 -ge $bench6o ]]
then
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench6 - $bench6o)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench6 * 100)" | python`
	echo -e "B6, OUR OPT.: $bench6o ( -$diff NO OPT. (-$perc%) )"
else
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench6o - $bench6)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench6 * 100)" | python`
	echo -e "B6, OUR OPT.: $bench6o ( +$diff NO OPT. (+$perc%) )"
fi
echo -e "B7, NO OPT.: $bench7"
if [[ $bench7 -ge $bench7o ]]
then
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench7 - $bench7o)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench7 * 100)" | python`
	echo -e "B7, OUR OPT.: $bench7o ( -$diff NO OPT. (-$perc%) )"
else
	# Absolute difference of opt. vs. no opt.
	diff=$(expr $bench7o - $bench7)
	# Percentage difference of opt. vs. no opt.
	perc=`echo "print '%.2f' % (float($diff) / $bench7 * 100)" | python`
	echo -e "B7, OUR OPT.: $bench7o ( +$diff NO OPT. (+$perc%) )"
fi
echo ""

echo -e "TOTAL, NO OPT.: $total"
echo -e "TOTAL, A- OPT.: (TODO)"
echo -e "TOTAL, A+ OPT.: (TODO)"

# The file containing the last total code length with optimizations exists.
if [[ -f $PEEPDIR/scripts/.last_total_opt_code_length ]]
then
	last_totalo=`head -1 $PEEPDIR/scripts/.last_total_opt_code_length`

	echo -e "LAST OPT.: $last_totalo"
	echo ""

	# Calculate code length differences and output.
	if [[ $total -ge $totalo ]]
	then
		# Absolute difference of opt. vs. no opt.
		diff1=$(expr $total - $totalo)
		# Percentage difference of opt. vs. no opt.
		perc1=`echo "print '%.2f' % (float($diff1) / $total * 100)" | python`
		if [[ $totalo -ge $last_totalo ]]
		then
			# Absolute difference of opt. vs. last opt.
			diff2=$(expr $totalo - $last_totalo)
			# Percentage difference of opt. vs. last opt.
			perc2=`echo "print '%.2f' % (float($diff2) / $last_totalo * 100)" | python`
			echo -e "TOTAL, OUR OPT.: $totalo ( -$diff1 NO OPT. (-$perc1%), +$diff2 LAST OPT. (+$perc2%) )"
		else
			diff2=$(expr $last_totalo - $totalo)
			# Percentage difference of opt. vs. last opt.
			perc2=`echo "print '%.2f' % (float($diff2) / $last_totalo * 100)" | python`
			echo -e "TOTAL, OUR OPT.: $totalo ( -$diff1 NO OPT. (-$perc1%), -$diff2 LAST OPT. (-$perc2%) )"
		fi 
	else
		# Absolute difference of opt. vs. no opt.
		diff1=$(expr $totalo - $total)
		# Percentage difference of opt. vs. no opt.
		perc1=`echo "print '%.2f' % (float($diff1) / $total * 100)" | python`
		if [[ $totalo -ge $last_totalo ]]
		then
			# Absolute difference of opt. vs. last opt.
			diff2=$(expr $totalo - $last_totalo)
			# Percentage difference of opt. vs. last opt.
			perc2=`echo "print '%.2f' % (float($diff2) / $last_totalo * 100)" | python`
			echo -e "TOTAL, OUR OPT.: $totalo ( +$diff1 NO OPT. ($perc1%), +$diff2 LAST OPT. (+$perc2%) )"
		else
			# Absolute difference of opt. vs. last opt.
			diff2=$(expr $last_totalo - $totalo)
			# Percentage difference of opt. vs. last opt.
			perc2=`echo "print '%.2f' % (float($diff2) / $last_totalo * 100)" | python`
			echo -e "TOTAL, OUR OPT.: $totalo ( +$diff1 NO OPT. ($perc1%), -$diff2 LAST OPT. (-$perc2%) )"
		fi
	fi
else
	echo ""

	# Calculate the code length difference and output.
	if [[ $total -ge $totalo ]]
	then
		# Absolute difference of opt. vs. no opt.
		diff=$(expr $total - $totalo)
		# Percentage difference of opt. vs. last opt.
		perc=`echo "print '%.2f' % (float($diff) / $total * 100)" | python`
		echo -e "OUR OPT.: $totalo ( -$diff NO OPT. (-$perc%) )"
	else
		# Absolute difference of opt. vs. no opt.
		diff=$(expr $totalo - $total)
		# Percentage difference of opt. vs. last opt.
		perc=`echo "print '%.2f' % (float($diff) / $total * 100)" | python`
		echo -e "OUR OPT.: $totalo ( +$diff NO OPT. (+$perc%) )"
	fi
fi

# Store the newly calculated total.
[[ $totalo != "" ]] && echo $totalo > $PEEPDIR/scripts/.last_total_opt_code_length