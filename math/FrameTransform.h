#pragma once

#include <rbdl/rbdl.h>
#include "math/Frame.h"
#include "math/Pose.h"

using namespace RigidBodyDynamics::Math;

// FrameTransform explicitly defines the relationship between two frames
// It stores the pose (rotation + translation) that transforms from source_frame to target_frame
class FrameTransform {
    private:
        Frame source_frame_;
        Frame target_frame_;
        Pose transform_pose_;  // Pose that transforms from source to target
        
    public:
        // Default constructor
        FrameTransform() : source_frame_(Frame()), target_frame_(Frame()), transform_pose_() {}
        
        // Constructor with explicit frames and transform
        FrameTransform(
            const Frame &source_frame, 
            const Frame &target_frame, 
            const Pose &transform_pose
        ) : source_frame_(source_frame), target_frame_(target_frame), transform_pose_(transform_pose) {}
        
        Frame source_frame() const { return source_frame_; }
        Frame target_frame() const { return target_frame_; }
        Pose pose() const { return transform_pose_; }
        
        // Transform a position from source frame to target frame
        Vector3d transform_position(const Vector3d &position_in_source) const;
        
        // Transform a pose from source frame to target frame
        Pose transform_pose(const Pose &pose_in_source) const;
        
        // Get the inverse transform (target to source)
        FrameTransform inverse() const;
        
        friend bool operator==(const FrameTransform&, const FrameTransform&);
        virtual bool isEqual(const FrameTransform& other) const;
};
