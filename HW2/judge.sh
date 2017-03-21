#!/bin/bash

#
#   Author: 404410030 - Kuang-Yu Jeng
#   2017/03/21
#   All Rights Reserved
#
JUDGE_SCALE=200000
echo "Stand by..."
make all
./build_judge $JUDGE_SCALE
./gen
echo "There are $JUDGE_SCALE cases"
# note: /dev/null , a biiiiiig black hooooooooole
if time ./hw2.bin < testfile.txt 1>/dev/null ; then 
    echo "Self test passed!"
    echo "Executed $JUDGE_SCALE test cases"
else
    echo "Failed"
fi


rm -f gen
