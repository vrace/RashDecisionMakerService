#!/bin/sh
rm -r Build
mkdir Build
cd Build
clang++ -Wall -c ../RashDecisionMaker/*.cpp
clang -Wall -c ../RashDecisionMaker/mongoose/*.c
clang++ -o RashDecisionMakerService *.o
rm *.o
cp ../RashDecisionMaker/*.html .
