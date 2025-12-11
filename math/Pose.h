#pragma once

#include <rbdl/rbdl.h>
#include "math/FrameID.h"

using namespace RigidBodyDynamics::Math;

// Forward declaration
class FrameTree;

// Pose represents a rigid body transformation (orientation + position) in a specific coordinate frame.
// Each pose is tied to a frame via its frame ID. To get the pose in a different frame,
// use in_frame(target_frame_id).
class Pose {
    private:
        Matrix3d orientation_;
        Vector3d position_;
        FrameID frame_id_;
        
    public:
        // Prefer initializing position explicitly with x, y, z components.
        Pose(const Matrix3d& orientation, double tx, double ty, double tz, const FrameID& frame_id);

        // Constructor accepting a Vector3d for internal uses and compatibility.
        Pose(const Matrix3d& orientation, const Vector3d& position, const FrameID& frame_id);

        Matrix3d orientation() const { return orientation_; }
        Vector3d position() const { return position_; }
        
        // Get the frame ID this pose is expressed in
        FrameID frame_id() const { return frame_id_; }

        // Explicit position component accessors
        double x() const { return position_(0); }
        double y() const { return position_(1); }
        double z() const { return position_(2); }
        
        // Return a new Pose representing the same transformation but in a different frame
        // Throws if no transform path exists between the current frame and target_frame_id
        Pose in_frame(const FrameID& target_frame_id) const;
        
    protected:
        friend bool operator==(const Pose&, const Pose&);
        friend bool operator!=(const Pose&, const Pose&);
        virtual bool isEqual(const Pose& pose) const;
        virtual bool oriIsEqual(const Pose& pose) const { return pose.orientation() == orientation_; }
        virtual bool positionIsEqual(const Pose& pose) const { return pose.position() == position_; }
        virtual bool frameIdIsEqual(const Pose& pose) const { return pose.frame_id() == frame_id_; }
};




