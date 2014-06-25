//
//  Colour.h
//  RayTracer
//
//  Created by Kiran Gangadharan on 20/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#ifndef RayTracer_Colour_h
#define RayTracer_Colour_h

class Colour {
public:
    float red;
    float green;
    float blue;

    Colour(): red(0), green(0), blue(0) {}
    Colour(float r, float g, float b): red(r), green(g), blue(b) {}
    Colour operator += (const Colour c) const {
        return Colour(red + c.red, green + c.green, blue + c.blue);
    }
    Colour operator * (const float value) const {
        return Colour(red * value, green * value, blue * value);
    }
    Colour operator * (const Colour value) const {
        return Colour(red * value.red, green * value.green, blue * value.blue);
    }
    void clamp(){
        red = (red < 0) ? 0 : (red > 1) ? 1: red;
        green = (green < 0) ? 0 : (green > 1) ? 1: green;
        blue = (blue < 0) ? 0 : (blue > 1) ? 1: blue;
    }


};


#endif
