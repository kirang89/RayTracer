//
//  Vector.h
//  RayTracer
//
//  Created by Kiran Gangadharan on 20/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#ifndef RayTracer_Vector_h
#define RayTracer_Vector_h

#include <math.h>

class Vector {
public:
    float x;
    float y;
    float z;
    
    Vector() {
        x = 0;
        y = 0;
        z = 0;
    }
    
    Vector(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {}
    
    Vector operator * (const float &val) const {
        return Vector(x * val, y * val, z * val);
    }
    
    Vector operator - (const Vector &v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    }
    
    Vector operator + (const Vector &v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }
    
    Vector& normalize() {
        float minverse = 1;
        float m = magnitude();
        
        if (m) minverse = 1/m;
        x *= minverse;
        y *= minverse;
        z *= minverse;
        
        return *this;
    }
    
    float magnitude() {
        return sqrt(x * x + y * y + z * z);
    }
    
    Vector& scale(float &factor) {
        x *= factor;
        y *= factor;
        z *= factor;
        
        return *this;
    }
    
    Vector difference(Vector &v){
        return Vector(x-v.x, y-v.y, z-v.z);
    }
    
    Vector add(Vector &v){
        return Vector(x+v.x, y+v.y, z+v.z);
    }
    
    float dot(const Vector &v) {
        return x * v.x + y * v.y + z * v.z;
    }
    
    ~Vector(){}
    
};


#endif
