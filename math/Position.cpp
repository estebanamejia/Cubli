#include "math/Position.h"
#include "math/FrameTree.h"
#include "math/FrameTransform.h"
#include <stdexcept>

Position::Position(double x, double y, double z, const FrameID& frame_id)
    : frame_id_(frame_id) {
    position_ << x, y, z;
}

Position::Position(const Vector3d& position, const FrameID& frame_id)
    : position_(position), frame_id_(frame_id) {}

Position Position::in_frame(const FrameID& target_frame_id) const {
    if (frame_id_ == target_frame_id) {
        // Already in target frame
        return Position(position_, frame_id_);
    }
    
    // Query the frame tree for the transform
    FrameTree& tree = FrameTree::instance();
    FrameTransform transform = tree.get_transform_or_throw(frame_id_, target_frame_id);
    
    // Transform the position using the FrameTransform API that operates on Position
    Position transformed = transform.transform_position(Position(position_, frame_id_));
    return transformed;
}

bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.isEqual(rhs);
}

bool Position::isEqual(const Position& other) const {
    return (frame_id_ == other.frame_id_) && (position_ == other.position_);
}
