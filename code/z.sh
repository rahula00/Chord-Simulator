#!/bin/bash
make
clear
./nodeClient > output.txt
cat output.txt
make