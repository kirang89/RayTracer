//
//  Sphere.h
//  RayTracer
//
//  Created by Kiran Gangadharan on 20/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#ifndef RayTracer_Sphere_h
#define RayTracer_Sphere_h

#include "Vector.h"
#include "Colour.h"

class Sphere {
public:
    Vector center;
    Colour colour;
    float reflectivity;
    float radius;
    
    Sphere(): center(Vector()), radius(0) {}
    Sphere(Vector c, float r): center(c), radius(r) {}
    
    void set_surface_properties(Colour c, float refl){
        colour = c;
        reflectivity = refl;
    }
    
    //    bool intersect(Ray ray, float *t0=NULL, float *t1=NULL){
    //        bool retval = false;
    //        Vector l = center - ray.origin;
    //        float tca = l.dot(ray.direction);
    //        if (tca < 0) retval = false;
    //
    //        float dsquare = l.dot(l) - tca * tca;
    //        if (dsquare > radius_square()) retval = false;
    //
    //        float thc = sqrtf(radius_square() - dsquare);
    //        if (t0 != NULL && t1 != NULL) {
    //            *t0 = tca - thc;
    //            *t1 = tca + thc;
    //            retval = true;
    //        }
    //
    //        return retval;
    //    }
    
    bool findIntersection(Ray ray, float *p){
        bool retval = false;
        float A = ray.direction.dot(ray.direction);
        
        Vector distance = ray.origin - center;
        float B = 2 * ray.direction.dot(distance);
        float C = distance.dot(distance) - radius_square();
        
        float discriminant = (B * B) - 4 * A * C;
        
        if(discriminant < 0)
            retval = false;
        else {
            float sqrtDiscriminant = sqrtf(discriminant);
            float point1 = (-B + sqrtDiscriminant)/(2);
            float point2 = (-B - sqrtDiscriminant)/(2);
            
            point1 = (point1 > point2)? point2: point1;
            
            if ((point1 > 0.001f) && (point1 < *p)){
                *p = point1;
                retval = true;
            } else {
                retval = false;
            }
            
        }
        
        return retval;
    }
    
    float radius_square(){
        return radius * radius;
    }
    
};

#endif
