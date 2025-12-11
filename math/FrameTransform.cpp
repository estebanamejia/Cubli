#include "math/FrameTransform.h"
#include "math/Pose.h"
#include <typeinfo>

Vector3d FrameTransform::transform_position(const Vector3d &position_in_source) const {
    // pos_in_target = R * pos_in_source + t
    Vector3d pos_in_target = transform_pose_.orientation() * position_in_source + transform_pose_.position();
    return pos_in_target;
}

Pose FrameTransform::transform_pose(const Pose &pose_in_source) const {
    // ori_in_target = R * ori_in_source
    Matrix3d ori_in_target = transform_pose_.orientation() * pose_in_source.orientation();
    
    // pos_in_target = R * pos_in_source + t
    Vector3d pos_in_target = transform_pose_.orientation() * pose_in_source.position() + transform_pose_.position();
    
    return Pose(ori_in_target, pos_in_target);
}

FrameTransform FrameTransform::inverse() const {
    // Inverse transform: T^-1 = [-R^T * t, R^T]
    Matrix3d R_inv = transform_pose_.orientation().transpose();
    Vector3d t_inv = -R_inv * transform_pose_.position();
    
    return FrameTransform(target_frame_, source_frame_, Pose(R_inv, t_inv));
}

bool operator==(const FrameTransform& lhs, const FrameTransform& rhs) {
    return typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs);
}

bool FrameTransform::isEqual(const FrameTransform& other) const {
    return (source_frame_ == other.source_frame_) && 
           (target_frame_ == other.target_frame_) && 
           (transform_pose_ == other.transform_pose_);
}
