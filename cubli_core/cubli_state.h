#pragma once

#include "math/Point.h"
#include "math/FrameID.h"
#include "math/Pose.h"
#include <rbdl/rbdl.h>

class CubliState {
    private:
        Point center_of_mass_pos_;
        Point contact_corner_pos_;
        Matrix3d orientation_;
    public:
        // Default construct points to zero; Pose/orientation uses identity.
        // Default source frames are WORLD so queries for WORLD return zero
        // without requiring a FrameTransform to be present.
        CubliState()
                : center_of_mass_pos_(0.0, 0.0, 0.0, FrameIDs::WORLD), 
                  contact_corner_pos_(0.0, 0.0, 0.0, FrameIDs::WORLD), 
                  orientation_(Matrix3dIdentity) {}

        // Return positions expressed in the requested target frame.
        // Points are now frame-aware; use in_frame(target_frame_id) to transform.
        Vector3d get_center_of_mass(const FrameID &target_frame_id) {
            return center_of_mass_pos_.in_frame(target_frame_id).position();
        }

        Vector3d get_contact_corner(const FrameID &target_frame_id) {
            return contact_corner_pos_.in_frame(target_frame_id).position();
        }
        
        Pose get_cubli_pose(const FrameID &target_frame_id);
};