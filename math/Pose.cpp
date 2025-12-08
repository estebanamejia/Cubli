#include "math/Pose.h"
#include "math/Frame.h"
#include "math/FrameTransform.h"
#include <typeinfo>
#include <stdexcept>

bool operator==(const Pose& lhs, const Pose& rhs) {
    return typeid(lhs) == typeid(rhs) // Allow compare only instances of the same dynamic type
           && lhs.isEqual(rhs);       // If types are the same then do the comparision.
}

Pose Pose::in_frame(const Frame &source_frame, const Frame &target_frame) const {
    // This is a stub - actual transformation requires a FrameTransform
    // The user must provide a FrameTransform to define the relationship
    throw std::runtime_error("Pose::in_frame() requires a FrameTransform to define frame relationship");
}
