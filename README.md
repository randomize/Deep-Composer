# Deep-Composer
Simple tool that deep-composes two EXR images into a single PNG file. Uses OpenEXR and OpenMP for processing, can batch process multiple frames.

Usage:
 `dcompose <num-frames> <pat-1-color>  <pat-1-depth>  <pat-2-color>  <pat-2-depth> <pat-out>`
 
First four patterns define input file names, color and depth exr for first deep image and same for the second. Last pattern defines output image name. Pattens must contain one `%d` symbol to define index in batch processing. 
