#!/bin/bash

# Lines beginning with # are comments Only lines beginning #PBS are
# processed by qsub

#PBS -N bit_count 
#PBS -l walltime=5:00:00
#PBS -l mem=1GB
#PBS -S /bin/bash
#PBS -j oe

cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=$PBS_NP

echo "Number of Threads = $PBS_NP"

# Run the program 3 times to get measure consistent timings
/usr/bin/time -v ./hutchimw_NumberCheck 100000 100100 > /dev/null
/usr/bin/time -v ./hutchimw_NumberCheck 100000 100100 > /dev/null
/usr/bin/time -v ./hutchimw_NumberCheck 100000 100100 > /dev/null
/usr/bin/time -v ./hutchimw_NumberCheck 100000 100100 > /dev/null
/usr/bin/time -v ./hutchimw_NumberCheck 100000 100100 > /dev/null

#end of script
