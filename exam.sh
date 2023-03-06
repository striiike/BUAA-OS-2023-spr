#!/bin/bash

# Orz

mkdir mydir
chmod a+rwx mydir
echo 2023 > myfile
mv moveme ./mydir/
cp copyme ./mydir/copied
cat readme
gcc bad.c &> err.txt
mkdir gen

if [ $# -le 0 ]
then
	cd gen
	touch 1.txt 2.txt 3.txt 4.txt 5.txt
	touch 6.txt 7.txt 8.txt 9.txt 10.txt
	cd ..

elif [ 1 -le 1 ]
then
	a=1
	while [ $a -le $1 ]
	do
			touch ./gen/${a}.txt
			a=$[$a+1]
	done
fi
