//
//  Image.h
//  RayTracer
//
//  Created by Kiran Gangadharan on 20/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#ifndef RayTracer_Image_h
#define RayTracer_Image_h

#include <stdio.h>

const int BYTES_PER_PIXEL = 3;
inline int min(int a,int b) { return a < b ? a : b; }

class Image {
public:
    int width;
    int height;
    unsigned char *buffer;

    Image(){
        width = 0;
        height = 0;
    }

    Image(float w, float h){
        width = w;
        height = h;
        buffer = new unsigned char[BYTES_PER_PIXEL * width * height]();
    }

    void set_colour_for_pixel(int x, int y, Colour c){
        c.clamp();
        int pos = (x + y * width) * 3;
        buffer[pos + 0] = static_cast<unsigned char>(c.red * 255.0f);
        buffer[pos + 1] = static_cast<unsigned char>(c.green * 255.0f);
        buffer[pos + 2] = static_cast<unsigned char>(c.blue * 255.0f);
    }

    void renderPPM(char *filename){
        FILE *file;
        file = fopen(filename, "w");
        fprintf(file, "P6 %d %d %d\n", width, height, 255);
        fwrite(buffer, BYTES_PER_PIXEL, (width * height), file);
        fclose(file);
    }

    ~Image(){
        delete[] buffer;
    }
};

#endif
