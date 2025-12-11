#pragma once

#include <rbdl/rbdl.h>
#include "math/FrameID.h"
#include "math/Pose.h"
#include "math/Position.h"
#include "math/Orientation.h"

using namespace RigidBodyDynamics::Math;

// FrameTransform explicitly defines the relationship between two frames
// It stores the pose (rotation + translation) that transforms from source_frame to target_frame
class FrameTransform {
    private:
        FrameID source_frame_;
        FrameID target_frame_;
        Pose transform_pose_;  // Pose that transforms from source to target
        
    public:
        // Constructor with explicit frames and transform
        FrameTransform(
            const FrameID &source_frame, 
            const FrameID &target_frame, 
            const Pose &transform_pose
        ) : source_frame_(source_frame), target_frame_(target_frame), transform_pose_(transform_pose) {}
        
        FrameID source_frame() const { return source_frame_; }
        FrameID target_frame() const { return target_frame_; }
        Pose pose() const { return transform_pose_; }
        
        // Transform a position from source frame to target frame
        Position transform_position(const Position &position_in_source) const;
        
        // Transform an orientation from source frame to target frame
        Orientation transform_orientation(const Orientation &orientation_in_source) const;

        // Transform a pose from source frame to target frame
        Pose transform_pose(const Pose &pose_in_source) const;
        
        // Get the inverse transform (target to source)
        FrameTransform inverse() const;
        
        friend bool operator==(const FrameTransform&, const FrameTransform&);
        virtual bool isEqual(const FrameTransform& other) const;
};
