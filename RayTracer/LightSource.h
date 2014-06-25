//
//  LightSource.h
//  RayTracer
//
//  Created by Kiran Gangadharan on 20/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#ifndef RayTracer_LightSource_h
#define RayTracer_LightSource_h

#include "Vector.h"
#include "Colour.h"

class LightSource {
public:
    Vector position;
    Colour intensity;
    
    LightSource(): position(Vector()), intensity(Colour()) {}
    LightSource(Vector pos, Colour c): position(pos), intensity(c) {}
};

#endif
