# Rasterizer
A simple real-time rasterizer written in C++. 
It saves renders to TGA, and displays them on the screen using OpenCV. It was optimized using Intel SSE.

By default, it works with multiple threads, rendering many frames simultaneously.

### Dependencies
The solution was created using Visual Studio 2017 and it requires OpenCV installed
(to run it out of the box, OpenCV should be placed in `C:\opencv` directory, so its dlls are in `C:\opencv\build\x64\vc14\bin`)
