#pragma once

#include <rbdl/rbdl.h>
#include <Eigen/Geometry>
#include "math/FrameID.h"

using namespace RigidBodyDynamics::Math;
using namespace std;

// Forward declaration
class FrameTree;

// Orientation represents a 3D rotation in a specific coordinate frame.
// Each orientation is tied to a frame via its frame ID. To get the orientation
// in a different frame, use in_frame(target_frame_id).
// Internally this uses a quaternion for robust computations.
class Orientation {
    private:
        Eigen::Quaterniond quat_;
        FrameID frame_id_;

    public:
        // Construct from rotation matrix and frame ID
        Orientation(const Matrix3d& ori, const FrameID& frame_id);

        // Construct from a quaternion and frame ID
        Orientation(const Eigen::Quaterniond& q, const FrameID& frame_id);

        // Retrieve as a rotation matrix
        Matrix3d rotation_matrix() const { return quat_.toRotationMatrix(); }

        // Retrieve the underlying quaternion
        Eigen::Quaterniond quaternion() const { return quat_; }
        
        // Get the frame ID this orientation is expressed in
        FrameID frame_id() const { return frame_id_; }

        // Construct from roll, pitch, yaw (radians) in a specified frame
        static Orientation fromRPY(double roll, double pitch, double yaw, const FrameID& frame_id);

        // Return roll, pitch, yaw (radians) in the order: roll, pitch, yaw
        Eigen::Vector3d rpy() const;

        // Return a new Orientation representing the same rotation but in a different frame
        // Throws if no transform path exists between the current frame and target_frame_id
        Orientation in_frame(const FrameID& target_frame_id) const;
        
        friend bool operator==(const Orientation&, const Orientation&);
        virtual bool isEqual(const Orientation& other) const;
};
