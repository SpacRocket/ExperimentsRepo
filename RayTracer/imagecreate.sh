#!/bin/zsh
rm ./pic.ppm;
cd build;
./raytracer > pic.ppm;
mv pic.ppm ../pic.ppm;
