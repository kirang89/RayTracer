#Ray Tracer

A simple and naive raytracer written solely for education and fun.

Here is the final output:
![](https://www.evernote.com/shard/s101/sh/9d32d7dd-a382-4b3a-b7ce-914bb0f9e745/9eea30783a75549e234a632fb5f5661e/res/53d07a99-bca8-4b56-8143-d1a87e35ff90/skitch.png?resizeSmall&width=832)

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
