#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
  private:
    point3 center;
    double radius;

  public:
    
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {};

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& h_record) const override
    {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c;

        if (discriminant < 0)
        {
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        h_record.t = root;
        h_record.p = r.at(h_record.t);
        h_record.normal = (h_record.p - center) / radius;

        vec3 outward_normal = (h_record.p - center) / radius;
        
        h_record.set_face_normal(r, outward_normal);
        
        return true;
    }

};


#endif