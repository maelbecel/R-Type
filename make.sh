#!/usr/bin/env bash

# This script is used to build the project.

echo "Command to execute (make, make re, make examples, make clean, make fclean)"
echo "Please enter the command to execute :"

read command

make() {
    mkdir build ; cd build ; cmake .. -G Ninja ; ninja ; cd ..
}

makeexamples() {
    mkdir build ; cd build ; cmake .. -DCOMPILE_EXAMPLES=ON -G Ninja ; ninja ; cd ..
}

makeclean() {
    rm -rf *.log
}

makefclean() {
    makeclean
    rm -rf build
    rm -rf lib
    rm -rf bin_examples
    rm -rf r-type_client
    rm -rf r-type_server
}

makere() {
    makefclean
    make
}

if [ "$command" = "make" ]
then
    make
elif [ "$command" = "make re" ]
then
    makere
elif [ "$command" = "make examples" ]
then
    makeexamples
elif [ "$command" = "make clean" ]
then
    makeclean
elif [ "$command" = "make fclean" ]
then
    makefclean
fi
