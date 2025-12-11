#include "Orientation.h"
#include "math/FrameTree.h"
#include "math/FrameTransform.h"
#include <stdexcept>

Orientation::Orientation(const Matrix3d& ori, const FrameID& frame_id)
    : quat_(ori), frame_id_(frame_id) {}

Orientation::Orientation(const Eigen::Quaterniond& q, const FrameID& frame_id)
    : quat_(q), frame_id_(frame_id) {}

Orientation Orientation::fromRPY(double roll, double pitch, double yaw, const FrameID& frame_id) {
    // Construct from roll, pitch, yaw (Tait-Bryan angles).
    //
    // Convention:
    // - These are intrinsic (body-fixed) rotations applied in the order:
    //     1) roll  about body X-axis
    //     2) pitch about (body) Y-axis (after roll)
    //     3) yaw   about (body) Z-axis (after roll and pitch)
    //
    // The composed rotation matrix equals R = Rz(yaw) * Ry(pitch) * Rx(roll).
    // This matches how the angles are recovered below using
    // `eulerAngles(0,1,2)`, which returns angles a0,a1,a2 such that
    // R = Rz(a2) * Ry(a1) * Rx(a0).
    //
    // Angles are in radians.
    Eigen::AngleAxisd rx(roll, Eigen::Vector3d::UnitX());
    Eigen::AngleAxisd ry(pitch, Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd rz(yaw, Eigen::Vector3d::UnitZ());
    Eigen::Quaterniond q = rz * ry * rx; // yaw * pitch * roll (intrinsic / body-fixed sequence)
    return Orientation(q, frame_id);
}

Eigen::Vector3d Orientation::rpy() const {
    // Return roll, pitch, yaw following the intrinsic (body-fixed)
    // Z (yaw) - Y (pitch) - X (roll) composition used in `fromRPY`.
    // We compute them explicitly from the rotation matrix to ensure the
    // same convention/ordering as `fromRPY` (R = Rz(yaw) * Ry(pitch) * Rx(roll)).
    Eigen::Matrix3d R = quat_.toRotationMatrix();
    double roll, pitch, yaw;

    // pitch = asin(-R(2,0)) with clamping to [-1,1] for numerical safety
    double sp = -R(2, 0);
    if (sp <= -1.0) {
        pitch = -M_PI/2.0;
    } else if (sp >= 1.0) {
        pitch = M_PI/2.0;
    } else {
        pitch = std::asin(sp);
    }

    // roll = atan2(R(2,1), R(2,2))
    roll = std::atan2(R(2, 1), R(2, 2));

    // yaw = atan2(R(1,0), R(0,0))
    yaw = std::atan2(R(1, 0), R(0, 0));

    Eigen::Vector3d out;
    out << roll, pitch, yaw;
    return out;
}

Orientation Orientation::in_frame(const FrameID& target_frame_id) const {
    // Query the frame tree for the transform
    FrameTree& tree = FrameTree::instance();
    FrameTransform transform = tree.get_transform_or_throw(frame_id_, target_frame_id);
    
    // Transform the orientation
    return transform.transform_orientation(*this);
    }

bool operator==(const Orientation& lhs, const Orientation& rhs) {
    return lhs.isEqual(rhs);
}

bool Orientation::isEqual(const Orientation& other) const {
    return (frame_id_ == other.frame_id_) && (quaternion() == other.quaternion());
}

