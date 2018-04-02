#include "camera.h"
#include "hitable_list.h"
#include "sphere.h"
#include <iostream>

vec3 color(ray& r, hitable* world) {
  hit_record rec;

  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5 *
           vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  int nx = 400;
  int ny = 200;
  std::cout << "P3" << std::endl
            << nx << " " << ny << std::endl
            << "255" << std::endl;

  hitable* list[3];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, 1, -1), 0.5);
  list[2] = new sphere(vec3(0, -100.5, -1), 100);
  hitable* world = new hitable_list(list, 3);
  camera cam;

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      ray r = cam.get_ray(u, v);
      vec3 col = color(r, world);
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);
      std::cout << ir << " " << ig << " " << ib << std::endl;
    }
  }
}