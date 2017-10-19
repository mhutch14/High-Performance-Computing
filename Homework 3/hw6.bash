#!/bin/bash

#PBS -N ex5_O3_profilers
#PBS -l walltime=0:30:00
#PBS -l mem=128MB
#PBS -l nodes=1:ppn=1
#PBS -S /bin/bash
#PBS -j oe

# Change to directory from where PBS job was submitted
cd $PBS_O_WORKDIR

#echo "----------------[ Output from callgrind for lambda ]---------------------"
/usr/bin/time -v ./main lambda 30000000
/usr/bin/time -v ./main lambda 30000000
/usr/bin/time -v ./main lambda 30000000
/usr/bin/time -v ./main lambda 30000000
/usr/bin/time -v ./main lambda 30000000
#echo "----------------[ Output from callgrind for function ]-------------------"
/usr/bin/time -v ./main standard 30000000
/usr/bin/time -v ./main standard 30000000
/usr/bin/time -v ./main standard 30000000
/usr/bin/time -v ./main standard 30000000
/usr/bin/time -v ./main standard 30000000

#echo "----------------[ Output from callgrind for lambda ]---------------------"
#valgrind --tool=callgrind ./main lambda 30000000
#echo "----------------[ Output from callgrind for function ]-------------------"
#valgrind --tool=callgrind ./main standard 30000000
#end of script

