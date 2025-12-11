#include "math/FrameTransform.h"
#include "math/Pose.h"
#include <typeinfo>
#include "math/Position.h"
#include "math/Orientation.h"

Position FrameTransform::transform_position(const Position &position_in_source) const {
    // Ensure the input position is expressed in the source frame
    Position pos_src = (position_in_source.frame_id() == source_frame_) ?
                        position_in_source : position_in_source.in_frame(source_frame_);

    // pos_in_target = R * pos_in_source + t
    Vector3d pos_in_target = transform_pose_.orientation() * pos_src.position() + transform_pose_.position();
    return Position(pos_in_target, target_frame_);
}

Orientation FrameTransform::transform_orientation(const Orientation &orientation_in_source) const {
    // Ensure the input orientation is expressed in the source frame
    Orientation ori_src = (orientation_in_source.frame_id() == source_frame_) ?
                          orientation_in_source : orientation_in_source.in_frame(source_frame_);

    // ori_in_target = R * ori_in_source
    Matrix3d ori_in_target = transform_pose_.orientation() * ori_src.orientation();
    return Orientation(ori_in_target, target_frame_);
}

Pose FrameTransform::transform_pose(const Pose &pose_in_source) const {
    // Convert Pose components to Position/Orientation and reuse new methods
    Orientation ori_src(pose_in_source.orientation(), pose_in_source.frame_id());
    Position pos_src(pose_in_source.position(), pose_in_source.frame_id());

    Orientation ori_in_target = transform_orientation(ori_src);
    Position pos_in_target = transform_position(pos_src);

    return Pose(ori_in_target.orientation(), pos_in_target.position(), target_frame_);
}

FrameTransform FrameTransform::inverse() const {
    // Inverse transform: T^-1 = [-R^T * t, R^T]
    Matrix3d R_inv = transform_pose_.orientation().transpose();
    Vector3d t_inv = -R_inv * transform_pose_.position();
    
    return FrameTransform(target_frame_, source_frame_, Pose(R_inv, t_inv, source_frame_));
}

bool operator==(const FrameTransform& lhs, const FrameTransform& rhs) {
    return typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs);
}

bool FrameTransform::isEqual(const FrameTransform& other) const {
    return (source_frame_ == other.source_frame_) && 
           (target_frame_ == other.target_frame_) && 
           (transform_pose_ == other.transform_pose_);
}
