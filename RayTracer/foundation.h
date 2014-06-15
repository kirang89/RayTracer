//
//  foundation.h
//  RayTracer
//
//  Created by Kiran Gangadharan on 14/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#ifndef RayTracer_foundation_h
#define RayTracer_foundation_h

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define BYTES_PER_PIXEL 3
#define min(a,b) a < b ? a : b

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

};

class LightSource {
public:
    Vector position;
    Colour intensity;
    
    LightSource(): position(Vector()), intensity(Colour()) {}
    LightSource(Vector pos, Colour c): position(pos), intensity(c) {}
};

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
    
    bool intersect(Ray ray, float *t0=NULL, float *t1=NULL){
        bool retval = false;
        Vector l = center - ray.origin;
        float tca = l.dot(ray.direction);
        if (tca < 0) retval = false;
        
        float dsquare = l.dot(l) - tca * tca;
        if (dsquare > radius_square()) retval = false;
        
        float thc = sqrtf(radius_square() - dsquare);
        if (t0 != NULL && t1 != NULL) {
            *t0 = tca - thc;
            *t1 = tca + thc;
            retval = true;
        }
        
        return retval;
    }
    
    bool intersect1(Ray ray, float *p){
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
        int pos = (x + y * width) * 3;
        buffer[pos + 0] = (unsigned char) min(c.red * 255.0f, 255.0f);
        buffer[pos + 1] = (unsigned char) min(c.green * 255.0f, 255.0f);
        buffer[pos + 2] = (unsigned char) min(c.blue * 255.0f, 255.0f);
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
