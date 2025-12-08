#include "Orientation.h"
#include "math/FrameTransform.h"
#include <stdexcept>

Orientation::Orientation(Matrix3d const &ori) : orientation_(ori) {}

Matrix3d Orientation::in_frame(const Frame &source_frame, const Frame &target_frame) const {
    // This is a stub - actual transformation requires a FrameTransform
    // The user must provide a FrameTransform to define the relationship
    throw std::runtime_error("Orientation::in_frame() requires a FrameTransform to define frame relationship");
}
