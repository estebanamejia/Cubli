#pragma once

#include <rbdl/rbdl.h>
#include <Eigen/Geometry>
#include "math/Frame.h"
using namespace RigidBodyDynamics::Math;
using namespace std;

// Orientation represents a 3D rotation with no intrinsic frame context
// Internally this uses a quaternion for robust computations. External
// callers may construct or retrieve a rotation matrix as before.
class Orientation {
    private:
        Eigen::Quaterniond quat_;

    public:
        // Construct from rotation matrix (keeps the old API)
        Orientation(Matrix3d const &ori = Matrix3dIdentity);

        // Construct directly from a quaternion
        Orientation(const Eigen::Quaterniond &q);

        // Retrieve as a rotation matrix (same as previous `orientation()`)
        Matrix3d orientation() const { return quat_.toRotationMatrix(); }

        // Retrieve the underlying quaternion
        Eigen::Quaterniond quaternion() const { return quat_; }

        // Construct from roll, pitch, yaw (radians)
        static Orientation fromRPY(double roll, double pitch, double yaw);

        // Return roll, pitch, yaw (radians) in the order: roll, pitch, yaw
        Eigen::Vector3d rpy() const;

        // Transform this orientation from source_frame to target_frame
        // Requires a FrameTransform that defines the relationship between frames
        Matrix3d in_frame(const Frame &source_frame, const Frame &target_frame) const;
};
