#include <min/visual/accel.h>

namespace min {

class NaiveAccelerator : public Accelerator {
  std::vector<std::shared_ptr<Shape>> primitives;
  Bounds3f bounds;
 public:
  void AddShape(const std::vector<std::shared_ptr<Shape>> &shape) override {
    primitives.insert(primitives.end(), shape.begin(), shape.end());
  }
  void Build() override {
    for (auto shape : primitives) {
      bounds = Union(bounds, shape->WorldBound());
    }
  }
  bool Intersect(const Ray &ray, SurfaceIntersection &isect) const override {
    bool found_intersection = false;
    for (auto shape : primitives) {
      if (shape->Intersect(ray, isect)) {
        found_intersection = true;
      }
    }
    return found_intersection;
  }

  Bounds3f WorldBound() const override {
    return bounds;
  }
};
MIN_IMPLEMENTATION(Accelerator, NaiveAccelerator, "naive");

}

