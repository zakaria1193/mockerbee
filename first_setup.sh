#!/bin/bash

PACKAGES="ninja-build cppcheck"

apt-get update

apt-get install -y $PACKAGES

# Install LLVM
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
yes | ./llvm.sh 17
