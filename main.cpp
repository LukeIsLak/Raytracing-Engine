#include <iostream>
#include <chrono>
#include "camera.h"
#include "colour.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {

  //Create a list of objects
  auto material_d_r = make_shared<diffuse>(colour(1, 0, 0));
  auto material_d_g = make_shared<diffuse>(colour(0, 1, 0));
  auto material_d_b = make_shared<diffuse>(colour(0, 0, 1));

  auto material_d_l = make_shared<diffuse_light>(colour(1, 0.2, 0.2));

  auto material_met_r = make_shared<metallic>(colour(1, 0.6, 0.6));
  auto material_met_g = make_shared<metallic>(colour(0.6, 1, 0.6));
  auto material_met_b = make_shared<metallic>(colour(0.6, 0.6, 1));

  hittable_list world;
  world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_d_g));
  world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_d_b));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_met_r));
  world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_met_g));

  //Set up the camera
  int image_width = 1920;
  auto aspect_ratio = 16.0 / 9.0;
  auto focal_length = 1.0;
  auto viewport_height = 2.0;

  camera cam(aspect_ratio, image_width, focal_length, viewport_height);
  cam.samples_per_pixels = 100;

  //Render a list of objects
  auto start_time = std::chrono::high_resolution_clock::now();
  cam.render(world);
  auto end_time = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> dur = end_time-start_time;

  std::clog << "The total time it took to render was: " << dur.count() << " second\n";
 
}
