#!/bin/bash

# ./dcompose 300 out.RGB_color.%04d.exr out.VRayZDepth.%04d.exr out.RGB_color.%04d.exr out.VRayZDepth.%04d.exr out_%d.png

cd build
./dcompose 15 ../data/out.RGB_color.%04d.exr ../data/out.VRayZDepth.%04d.exr ../data/frame_color%07d.exr ../data/frame_depth%07d.exr out_%d.png
