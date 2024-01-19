#ifndef MATERIAL_H
#define MATERIAL_H

#include "utility_functions.h"

class hit_record;

class material {
 public:
  virtual ~material() = default;
  
  virtual bool scatter(const ray& ray_in, const hit_record& rec, colour& attenuation, ray& scattered) const = 0;

  virtual bool emitted(colour& attenuation) const = 0;
};

class diffuse : public material {
 public:
   diffuse(const colour& a) : col(a) {}

  bool scatter (const ray& ray_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
    auto scattered_direction = rec.normal + random_unit_vector();
    if (scattered_direction.near_zero())
      scattered_direction = rec.normal;
    scattered = ray(rec.p, scattered_direction);
    attenuation = col;
    return true;
  }

  bool emitted(colour& attenuation) const override {
    return false;
  }

 private:
  colour col;
};

class metallic : public material {
  public:
   metallic(const colour& a) : col(a) {}

  bool scatter (const ray& ray_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
    vec3 reflected_vec = reflect(ray_in.direction(), rec.normal);
    scattered = ray(rec.p, reflected_vec);
    attenuation = col;
    return true;
  }

  bool emitted(colour& attenuation) const override {
    return false;
  }

 private:
  colour col;
};

class dielectrics : public material {
  public:
   dielectrics(const colour& a) : col(a) {}

  bool scatter (const ray& ray_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
    vec3 reflected_vec = reflect(ray_in.direction(), rec.normal);
    scattered = ray(rec.p, reflected_vec);
    attenuation = col;
    return true;
  }

  bool emitted(colour& attenuation) const override {
    return false;
  }

 private:
  colour col;
};

class diffuse_light : public material {
 public:
  diffuse_light(const colour& a) : col(a) {}

  bool scatter (const ray& ray_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
    return false;
  }

  bool emitted(colour& attenuation) const override {
    attenuation = col;
    return true;
  }
 private:
    colour col;
};

#endif
