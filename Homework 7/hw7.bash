#!/bin/bash

# Lines beginning with # are comments Only lines beginning #PBS are
# processed by qsub

#PBS -N ImageSearch 
#PBS -l walltime=5:00:00
#PBS -l mem=1GB
#PBS -S /bin/bash
#PBS -j oe

cd $PBS_O_WORKDIR

./ImageSearch star.png star_mask.png result.png true 75 16

#end of script
