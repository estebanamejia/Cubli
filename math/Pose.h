#pragma once

#include <rbdl/rbdl.h>

using namespace RigidBodyDynamics::Math;

// Forward declaration
class Frame;

// Pose represents a rigid body transformation: orientation (rotation) + translation
// A Pose is data-only and has no intrinsic frame context.
// To transform between frames, use in_frame(source_frame, target_frame)
class Pose {
    private:
        Matrix3d orientation_;
        Vector3d translation_;
    public:
        Pose(const Matrix3d &orientation = Matrix3dIdentity, const Vector3d &translation = Vector3dZero) 
            : orientation_(orientation), translation_(translation) {}
        Matrix3d orientation() const {return orientation_;}
        Vector3d translation() const {return translation_;}
        
        // Transform this pose from source_frame to target_frame
        // Requires the transform relationship between frames to be specified
        Pose in_frame(const Frame &source_frame, const Frame &target_frame) const;
        
    protected:
        friend bool operator==(const Pose&, const Pose&);
        virtual bool isEqual(const Pose& pose) const { return oriIsEqual(pose) && translationIsEqual(pose); }
        virtual bool oriIsEqual(const Pose& pose) const { return pose.orientation() == orientation_; }
        virtual bool translationIsEqual(const Pose& pose) const { return pose.translation() == translation_; }

};




