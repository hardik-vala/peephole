#!/bin/bash

################
# Build source #
################

cd $PEEPDIR/JOOSA-src/
make -f Makefile clean
make -f Makefile
