#include "Point.h"
#include "math/FrameTransform.h"
#include <stdexcept>

Point::Point(double x, double y, double z) : position_() {
    position_ << x, y, z;
}

Vector3d Point::in_frame(const Frame &source_frame, const Frame &target_frame) const {
    // This is a stub - actual transformation requires a FrameTransform
    // The user must provide a FrameTransform to define the relationship
    throw std::runtime_error("Point::in_frame() requires a FrameTransform to define frame relationship");
}
