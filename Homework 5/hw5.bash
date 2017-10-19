#!/bin/bash
#
# File:     hw5.bash
# Author:   Mark Hutchinson
#
#PBS -N Ackerman_hutchimw
#PBS -l walltime=72:00:00
#PBS -l mem=4GB
#PBS -l nodes=1:ppn=1

cd $PBS_O_WORKDIR

echo "************C++ Standard -O3 Tests************"
/usr/bin/time -v ./ackermann 7
/usr/bin/time -v ./ackermann 7
/usr/bin/time -v ./ackermann 7

/usr/bin/time -v ./ackermann 10
/usr/bin/time -v ./ackermann 10
/usr/bin/time -v ./ackermann 10

/usr/bin/time -v ./ackermann 13
/usr/bin/time -v ./ackermann 13
/usr/bin/time -v ./ackermann 13

/usr/bin/time -v ./ackermann 15
/usr/bin/time -v ./ackermann 15
/usr/bin/time -v ./ackermann 15

echo "************C++ PGO Tests*********************"
/usr/bin/time -v ./ackermann_pgo 7
/usr/bin/time -v ./ackermann_pgo 7
/usr/bin/time -v ./ackermann_pgo 7

/usr/bin/time -v ./ackermann_pgo 10
/usr/bin/time -v ./ackermann_pgo 10
/usr/bin/time -v ./ackermann_pgo 10

/usr/bin/time -v ./ackermann_pgo 13
/usr/bin/time -v ./ackermann_pgo 13
/usr/bin/time -v ./ackermann_pgo 13

/usr/bin/time -v ./ackermann_pgo 15
/usr/bin/time -v ./ackermann_pgo 15
/usr/bin/time -v ./ackermann_pgo 15

echo "****************Java Runtime Tests**************"
/usr/bin/time -v java -Xss12m ackermann 7
/usr/bin/time -v java -Xss12m ackermann 7
/usr/bin/time -v java -Xss12m ackermann 7

/usr/bin/time -v java -Xss12m ackermann 10
/usr/bin/time -v java -Xss12m ackermann 10
/usr/bin/time -v java -Xss12m ackermann 10

/usr/bin/time -v java -Xss12m ackermann 13
/usr/bin/time -v java -Xss12m ackermann 13
/usr/bin/time -v java -Xss12m ackermann 13

/usr/bin/time -v java -Xss12m ackermann 15
/usr/bin/time -v java -Xss12m ackermann 15
/usr/bin/time -v java -Xss12m ackermann 15

echo "*****************Python Runtime Tests************"
/usr/bin/time -v python ackermann.py 7
/usr/bin/time -v python ackermann.py 7
/usr/bin/time -v python ackermann.py 7

/usr/bin/time -v python ackermann.py 10
/usr/bin/time -v python ackermann.py 10
/usr/bin/time -v python ackermann.py 10

/usr/bin/time -v python ackermann.py 13
/usr/bin/time -v python ackermann.py 13
/usr/bin/time -v python ackermann.py 13

# end of script
