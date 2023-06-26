#!/bin/bash

declare local_1=111 local_2=22222222222
declare local_3=3333"; ls"
declare -r local_4="44 4444;echo 4"
declare -x var_3="33 ;echo 33 > ok.txt"
declare -x var_4=44444444
declare -x var_5=55
declare -x -r var_6=6
declare -x -r var_7=7";; ; cat ok.txt"
declare name=hello"; echo hi"

echo $local_1 $local_2
echo $local_3
echo $local_4
echo $var_3 
echo $var_4  
echo $var_5  
echo $var_6  
echo $var_7
echo $father_1  
echo $father_2
echo $name

declare local_1=aaaaa
declare local_2=bbbbbbb
declare local_3=ccccc"; tree"
declare -r local_4="ddd dddd;d"
declare -x var_3="cc ;c c"
declare -x var_4=ddddddddd
declare -x var_5=ee
declare -x -r var_6=f
declare -x -r var_7=g";; ; &g ; ggg ;"

echo $local_1
echo $local_2
echo $local_3
echo $local_4
echo $var_3
echo $var_4 
echo $var_5 
echo $var_6 
echo $var_7 
echo $father_1 
echo $father_2
declare
echo over!
