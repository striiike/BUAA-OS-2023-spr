#!/bin/bash

# change file string
# $1 for file
# $3 substitute $2

sed -i "s%$2%$3%g" $1


