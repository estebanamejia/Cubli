#pragma once

#include <rbdl/rbdl.h>

using namespace RigidBodyDynamics::Math;

// Forward declaration
class Frame;

// Pose represents a rigid body transformation: orientation (rotation) + position
// A Pose is data-only and has no intrinsic frame context.
// To transform between frames, use in_frame(source_frame, target_frame)
class Pose {
    private:
        Matrix3d orientation_;
        Vector3d position_;
    public:
        // Prefer initializing position explicitly with x, y, z components.
        Pose(const Matrix3d &orientation = Matrix3dIdentity, double tx = 0.0, double ty = 0.0, double tz = 0.0)
            : orientation_(orientation), position_() {
                position_ << tx, ty, tz;
        }

        // Keep an overload that accepts a Vector3d for internal uses and compatibility.
        Pose(const Matrix3d &orientation, const Vector3d &position)
            : orientation_(orientation), position_(position) {}

        Matrix3d orientation() const { return orientation_; }
        Vector3d position() const { return position_; }

        // Explicit position component accessors
        double x() const { return position_(0); }
        double y() const { return position_(1); }
        double z() const { return position_(2); }
        
        // Transform this pose from source_frame to target_frame
        // Requires the transform relationship between frames to be specified
        Pose in_frame(const Frame &source_frame, const Frame &target_frame) const;
        
    protected:
        friend bool operator==(const Pose&, const Pose&);
        virtual bool isEqual(const Pose& pose) const { return oriIsEqual(pose) && translationIsEqual(pose); }
        virtual bool oriIsEqual(const Pose& pose) const { return pose.orientation() == orientation_; }
        virtual bool translationIsEqual(const Pose& pose) const { return pose.position() == position_; }

};




