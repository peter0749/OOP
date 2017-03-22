#!/bin/bash

ARR=( cin cerr cout endl string list vector numeric_limits runtime_error out_of_range )

#slow, can I do it better by using awk? Mmm... No, I'm lazy :P
for v in ${ARR[@]}; do
    sed "s/$v/std::$v/g" $1 > ./tmp
    mv ./tmp $1
done
