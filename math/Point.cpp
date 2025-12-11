#include "Point.h"
#include "math/FrameTree.h"
#include "math/FrameTransform.h"
#include <stdexcept>

Point::Point(double x, double y, double z, const FrameID& frame_id)
    : frame_id_(frame_id) {
    position_ << x, y, z;
}

Point::Point(const Vector3d& position, const FrameID& frame_id)
    : position_(position), frame_id_(frame_id) {}

Point Point::in_frame(const FrameID& target_frame_id) const {
    if (frame_id_ == target_frame_id) {
        // Already in target frame
        return Point(position_, frame_id_);
    }
    
    // Query the frame tree for the transform
    FrameTree& tree = FrameTree::instance();
    FrameTransform transform = tree.get_transform_or_throw(frame_id_, target_frame_id);
    
    // Transform the position
    Vector3d transformed_position = transform.transform_position(position_);
    
    return Point(transformed_position, target_frame_id);
}

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.isEqual(rhs);
}

bool Point::isEqual(const Point& other) const {
    return (frame_id_ == other.frame_id_) && (position_ == other.position_);
}

