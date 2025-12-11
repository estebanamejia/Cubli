#include "Orientation.h"
#include "math/FrameTransform.h"
#include <stdexcept>

Orientation::Orientation(Matrix3d const &ori) : quat_(ori) {}

Orientation::Orientation(const Eigen::Quaterniond &q) : quat_(q) {}

Orientation Orientation::fromRPY(double roll, double pitch, double yaw) {
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
    return Orientation(q);
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

Matrix3d Orientation::in_frame(const Frame &source_frame, const Frame &target_frame) const {
    // This is a stub - actual transformation requires a FrameTransform
    // The user must provide a FrameTransform to define the relationship
    throw std::runtime_error("Orientation::in_frame() requires a FrameTransform to define frame relationship");
}
