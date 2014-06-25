//
//  main.cpp
//  RayTracer
//
//  Created by Kiran Gangadharan on 14/06/14.
//  Copyright (c) 2014 kiran. All rights reserved.
//

#include "Vector.h"
#include "Colour.h"
#include "Ray.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Image.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_DEPTH = 15;
const double _INFINITY = 20000.0f;
const int OBJECT_COUNT = 5;
const int LIGHT_SOURCE_COUNT = 3;
const double GAMMA_CORRECTION = 1/2.2;

void render_scene(LightSource *sources, Sphere *spheres){
    Image image = Image(WIDTH, HEIGHT);

    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            Colour pixel_colour = Colour();
            Ray ray = Ray(Vector(x, y, -100), Vector(0, 0, 1));
            int depth = 0;
            bool d = false;
            float transmittivity = 1.0;

            do {
                Sphere currentSphere;
                int index = -1;
                float tnear = _INFINITY;

                for (int i=0; i<OBJECT_COUNT; i++)
                    if (spheres[i].findIntersection(ray, &tnear)) index = i;

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
                for (int l=0; l<LIGHT_SOURCE_COUNT; l++) {
                    LightSource ls = sources[l];
                    Vector lightSourceDirection = ls.position - incidentRay;
                    if (normal.dot(lightSourceDirection) <= 0.0f) continue;

                    lightSourceDirection.normalize();

                    Ray lightRay = Ray(ls.position, lightSourceDirection);

                    float ndotls = normal.dot(lightSourceDirection);

                    pixel_colour.red += currentSphere.colour.red * transmittivity * sources[l].intensity.red * ndotls;

                    pixel_colour.green += currentSphere.colour.green * transmittivity * sources[l].intensity.green * ndotls;

                    pixel_colour.blue += currentSphere.colour.blue * transmittivity * sources[l].intensity.blue * ndotls;
                }

                d = true;

                // Change light intensity according to the
                // reflectivity of object
                transmittivity = transmittivity * currentSphere.reflectivity;

                // The new ray starts at the point of intersection
                // and travels along the direction of the
                // reflected ray
                ray = Ray(incidentRay, reflectedRay);

                depth++;

            } while ((transmittivity > 0.0f) && (depth < MAX_DEPTH));

            //Applying Gamma Correction
            pixel_colour.red = pow(pixel_colour.red, GAMMA_CORRECTION);
            pixel_colour.green = pow(pixel_colour.green, GAMMA_CORRECTION);
            pixel_colour.blue = pow(pixel_colour.blue, GAMMA_CORRECTION);

            //Setting the colour of pixel in the final image
            if (d)
            {
                image.set_colour_for_pixel(x, y, pixel_colour);
            } else {
                image.set_colour_for_pixel(x, y, Colour(0.65, 0.65, 0.65));
            }

        }
    }

    //Write image to file
    image.renderPPM("scene.ppm");
}

int main(int argc, const char * argv[])
{
    LightSource *sources = new LightSource[3];
    sources[0] = LightSource(Vector(500, -1000, -1000), Colour(0.6,0.7,1));
    sources[1] = LightSource(Vector(520, -1000, -1000), Colour(0.3,0.5,1));
    sources[2] = LightSource(Vector(550, -1000, -1000), Colour(1,1,1));

    Sphere *spheres = new Sphere[OBJECT_COUNT];
    spheres[0] = Sphere(Vector(500,200.8,81.6), 20);
    spheres[0].set_surface_properties(Colour(.75,.25,.25), 0);

    spheres[1] = Sphere(Vector(100,300,81.6), 50);
    spheres[1].set_surface_properties(Colour(.75,.25,.25), 0);

    spheres[2] = Sphere(Vector(600,500, 320.6), 200);
    spheres[2].set_surface_properties(Colour(.58,.74,.80), 1);

    spheres[3] = Sphere(Vector(327,360.5,47), 10);
    spheres[3].set_surface_properties(Colour(1.00, 0.57, 0.38), 0);

    spheres[4] = Sphere(Vector(373,160.5,78), 50);
    spheres[4].set_surface_properties(Colour(1.00, 0.57, 0.38), 0.7);


    render_scene(sources, spheres);

    // Cleaning up
    delete [] sources;
    delete [] spheres;

    return 0;
}

