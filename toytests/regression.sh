#!/bin/bash

checkCommand() { # $1: command name
    if [ $? -ne 0 ]; then
        echo "${1}" fails!
        exit 1
    else
        echo "${1}" succeeds!
    fi
}

if [ "${TOY_EMULATOR_PATH}" == "" ]; then
    echo "Please set TOY_EMULATOR_PATH first!"
    exit 1
fi

test_base_dir=`pwd`
echo "${test_base_dir}"
tests=("basic")
 
for ((i=0; i < ${#tests[@]}; i++))
do
    cd ${test_base_dir}/${tests[$i]}
    ${TOY_EMULATOR_PATH}/emulator ${tests[$i]}.o ${tests[$i]}_memory.bin
    checkCommand ${TOY_EMULATOR_PATH}/emulator
    ./${tests[$i]}_verifier ${tests[$i]}_memory.bin
    checkCommand  ./${tests[$i]}_verifier
    cd ${test_base_dir}
done
