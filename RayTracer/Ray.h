//
//  Ray.h
//  RayTracer
//
//  Created by Kiran Gangadharan on 20/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#ifndef RayTracer_Ray_h
#define RayTracer_Ray_h

#include "Vector.h"

class Ray {
public:
    Vector origin;
    Vector direction;
    
    Ray(){
        origin = Vector(0,0,0);
        direction = Vector(0,0,0);
    }
    
    Ray(Vector start, Vector dir): origin(start), direction(dir){}
    
    ~Ray(){}
};


#endif
