#ifndef CAMERA_H
#define CAMERA_H

#include "utility_functions.h"

#include "colour.h"
#include "hittable.h"
#include "material.h"

#include <iostream>
#include <omp.h>

//Create a camera class to render the image
class camera {
 public:

  //Public variables to edit
  double aspect_ratio = 1.0;
  int image_width = 100;
  double focal_length = 1.0;
  double viewport_height = 2.0;
  point3 center = point3(0,0,0);
  int samples_per_pixels = 10;
  int max_depth = 50;
  colour background_col = colour(0.02, 0.02, 0.05) * 20;

  camera() {}
  camera(double _aspect_ratio, int _image_width, double _focal_length, double _viewport_height) : 
  aspect_ratio(_aspect_ratio), image_width(_image_width), focal_length(_focal_length), viewport_height(_viewport_height) {}


  //Given the camera object, define a world to 
  void render(const hittable& world) {

    //Define the rest of the constants
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    for (int j = 0; j < image_height; ++j) {
      std::clog << "\rPercent Done: " << static_cast<int>((double)j / (double)image_height * 100) << "%";
      for (int i = 0; i < image_width; ++i) {
	      colour pixel_colour(0,0,0);
	      for (int sample = 0; sample < samples_per_pixels; ++sample) {
	        // cast the ray to the world, each if it hits any objects in the world
	        ray r = get_ray(i, j);
	        pixel_colour += ray_colour(r, world, max_depth);
	      }

	      return_colour(std::cout, pixel_colour, samples_per_pixels);
      }
    }
    std::clog << "\rFinished.\n";
  }
 
 private:
  int image_height;
 
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;

  point3 pixel00_loc;
  double sample_square_radius = 0.5;

  void initialize() {

    // Calculate the height, ensure it is at least one
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Define what the camera will see
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    
    // Calculate the vectors of the corner that the camera can acutally see
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    
    //Space between each ray in porportion to the pixels
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    //Using the center of the camera, find the top left of the viewport as a vector
    auto viewport_upper_left = center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    
  }

  ray get_ray (int i, int j) const {
    auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
    auto pixel_sample = pixel_center - pixel_sample_square();

    auto ray_origin = center;
    auto ray_direction = pixel_sample - center;

    return ray(ray_origin, ray_direction);
  }

  vec3 pixel_sample_square() const {
    auto px = -sample_square_radius + random_double();
    auto py = -sample_square_radius + random_double();
    return (px * pixel_delta_u) + (py * pixel_delta_u);
  }
  
  //return the colour of a given ray
  colour ray_colour(ray &r, const hittable& world, int depth) {
    if (depth <= 0)
      return colour(0,0,0);
    hit_record rec;
    if (world.hit(r, interval(0.001, infinity), rec)) {
      ray scattered;
      colour attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered))
        return attenuation * ray_colour(scattered, world, depth-1);
      return colour(0,0,0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    return background_col;
  }

};

#endif