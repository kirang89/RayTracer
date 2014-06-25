#Ray Tracer

A simple and naive raytracer written solely for education and fun.

*Note: Only object reflections are handled for now.*

###Usage

- First compile the program using:
```
c++ -o rtracer -O3 -Wall main.cpp
```
- Next, run the executable. Doing so, generates a [PPM](http://www.fileinfo.com/extension/ppm) image of the scene generated:
```
./rtracer
```
- Finally open the scene image created using a PPM Viewer
    - ToyViewer/Photoshop for Mac
    - GIMP for Linux
    - GIMP/Photoshop for Windows

###Todo
- Show object shadows on scene
- Anti-aliasing
- Object refractions
- Loading scene from files
