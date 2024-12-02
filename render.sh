#!/bin/bash

g++ -Iheaders/ src/*.cpp -o out/trace.elf 

./out/trace.elf > ./out/image.ppm
convert ./out/image.ppm ./out/image.png
rm -rf ./out/image.ppm
