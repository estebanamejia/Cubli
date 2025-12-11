#include "math/Pose.h"
#include "math/FrameTree.h"
#include "math/FrameTransform.h"
#include <typeinfo>
#include <stdexcept>

Pose::Pose(const Matrix3d& orientation, double tx, double ty, double tz, const FrameID& frame_id)
    : orientation_(orientation), frame_id_(frame_id) {
    position_ << tx, ty, tz;
}

Pose::Pose(const Matrix3d& orientation, const Vector3d& position, const FrameID& frame_id)
    : orientation_(orientation), position_(position), frame_id_(frame_id) {}

bool operator==(const Pose& lhs, const Pose& rhs) {
    return typeid(lhs) == typeid(rhs) // Allow compare only instances of the same dynamic type
           && lhs.isEqual(rhs);       // If types are the same then do the comparision.
}

bool operator!=(const Pose& lhs, const Pose& rhs) {
    return !(lhs == rhs);
}

bool Pose::isEqual(const Pose& pose) const {
    return oriIsEqual(pose) && positionIsEqual(pose) && frameIdIsEqual(pose);
}

Pose Pose::in_frame(const FrameID& target_frame_id) const {
    if (frame_id_ == target_frame_id) {
        // Already in target frame
        return Pose(orientation_, position_, frame_id_);
    }
    
    // Query the frame tree for the transform
    FrameTree& tree = FrameTree::instance();
    FrameTransform transform = tree.get_transform_or_throw(frame_id_, target_frame_id);
    
    // Transform the pose
    Pose transformed_pose_data = transform.transform_pose(Pose(orientation_, position_, frame_id_));
    
    return Pose(transformed_pose_data.orientation(), transformed_pose_data.position(), target_frame_id);
}
