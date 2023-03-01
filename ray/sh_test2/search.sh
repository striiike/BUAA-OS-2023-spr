#!/bin/bash
#First you can use grep (-n) to find the number of lines of string.
#Then you can use awk to separate the answer.

awk -v pat=$2 '$0~pat {print FNR}' $1 > $3


