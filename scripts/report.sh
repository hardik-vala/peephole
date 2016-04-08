#!/bin/bash

###############################################
# JOOS Compile Benchmarks & Report Statistics #
###############################################

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
			echo -e "OUR OPT.: $totalo ( -$diff1 NO OPT. (-$perc1%), +$diff2 LAST OPT. (+$perc2%) )"
		else
			diff2=$(expr $last_totalo - $totalo)
			# Percentage difference of opt. vs. last opt.
			perc2=`echo "print '%.2f' % (float($diff2) / $last_totalo * 100)" | python`
			echo -e "OUR OPT.: $totalo ( -$diff1 NO OPT. (-$perc1%), -$diff2 LAST OPT. (-$perc2%) )"
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
			echo -e "OUR OPT.: $totalo ( +$diff1 NO OPT. ($perc1%), +$diff2 LAST OPT. (+$perc2%) )"
		else
			# Absolute difference of opt. vs. last opt.
			diff2=$(expr $last_totalo - $totalo)
			# Percentage difference of opt. vs. last opt.
			perc2=`echo "print '%.2f' % (float($diff2) / $last_totalo * 100)" | python`
			echo -e "OUR OPT.: $totalo ( +$diff1 NO OPT. ($perc1%), -$diff2 LAST OPT. (-$perc2%) )"
		fi
	fi
else
	echo ""

	# Calculate the code length difference and output.
	if [[ $total -ge $totalo ]]
	then
		diff=$(expr $total - $totalo)
		echo -e "OUR OPT.: $totalo (-$diff NO OPT.)"
	else
		diff=$(expr $totalo - $total)
		echo -e "OUR OPT.: $totalo (+$diff NO OPT.)"
	fi
fi

# Store the newly calculated total.
echo $totalo > $PEEPDIR/scripts/.last_total_opt_code_length
