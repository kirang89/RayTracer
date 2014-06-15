//
//  main.cpp
//  RayTracer
//
//  Created by Kiran Gangadharan on 14/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#include "foundation.h"

#define WIDTH 800
#define HEIGHT 600
#define MAX_DEPTH 15
#define _INFINITY 20000.0f

void render_scene(LightSource *sources, Sphere *spheres){
    Image image = Image(WIDTH, HEIGHT);
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            Colour pixel_colour = Colour();
            Ray ray = Ray(Vector(x, y, -100), Vector(0, 0, 1));
            int depth = 0;
            float transmittivity = 1.0;
            
            do {
                Sphere currentSphere;
                int index = -1;
                float tnear = _INFINITY;
                
                for (int i=0; i<3; i++)
                    if (spheres[i].intersect1(ray, &tnear)) index = i;
                
                if (index == -1)
                    break;
                else
                    currentSphere = spheres[index];
                
                // Now we need to find the reflection vector
                Vector incidentRay = ray.origin + ray.direction * tnear;
                Vector normal = (incidentRay - currentSphere.center);
                normal.normalize();

                Vector reflectedRay = (ray.direction - normal * 2 * ray.direction.dot(normal));
                reflectedRay.normalize();
                
                // Now to find colour of surface of sphere at intersection point
                for (int l=0; l<3; l++) {
                    LightSource ls = sources[l];
                    Vector lightSourceDirection = ls.position - incidentRay;
                    if (normal.dot(lightSourceDirection) <= 0.0f) continue;
                    
                    lightSourceDirection.normalize();
                    
                    float temp = normal.dot(lightSourceDirection);
                    
                    pixel_colour.red += currentSphere.colour.red * transmittivity * sources[l].intensity.red * temp;
                    
                    pixel_colour.green += currentSphere.colour.green * transmittivity * sources[l].intensity.green * temp;
                    
                    pixel_colour.blue += currentSphere.colour.blue * transmittivity * sources[l].intensity.blue * temp;
                }
                
                // Change light intensity according to the
                // reflectivity of object
                transmittivity = transmittivity * currentSphere.reflectivity;
                
                // The new ray starts at the point of intersection
                // and travels along the direction of the
                // reflected ray
                ray = Ray(incidentRay, reflectedRay);
                
                depth++;
                
            } while ((transmittivity > 0.0f) && (depth < MAX_DEPTH));
            
            //Setting the colour of pixel in the final image
            image.set_colour_for_pixel(x, y, pixel_colour);
        }
    }
    
    //Write image to file
    image.renderPPM("scene.ppm");
}


int main(int argc, const char * argv[])
{
    LightSource *sources = new LightSource[3];
    sources[0] = LightSource(Vector(0, 240, -100), Colour(1, 1, 1));
    sources[1] = LightSource(Vector(6200, 3000, -1000), Colour(0.6, 0.7, 1));
    sources[2] = LightSource(Vector(600, 200, -100), Colour(0.3, 0.5, 1));
    
    Sphere *spheres = new Sphere[3];
    spheres[0] = Sphere(Vector(200, 300, 0), 100);
    spheres[0].set_surface_properties(Colour(1, 0, 0), 0.2);
    
    spheres[1] = Sphere(Vector(450, 450, 0), 100);
    spheres[1].set_surface_properties(Colour(0, 1, 0), 0.5);
    
    spheres[2] = Sphere(Vector(500, 120, 0), 100);
    spheres[2].set_surface_properties(Colour(0, 0, 1), 0.9);
    
    render_scene(sources, spheres);
    
    // Cleaning up
    delete [] sources;
    delete [] spheres;
    
    return 0;
}

