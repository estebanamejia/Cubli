#pragma once

#include "math/Point.h"
#include "math/Frame.h"
#include "math/Pose.h"
#include <rbdl/rbdl.h>

class CubliState {
    private:
        Point center_of_mass_pos_;
        Point contact_corner_pos_;
        Matrix3d orientation_;
        Frame center_of_mass_frame_;
        Frame contact_corner_frame_;
    public:

                // Default construct points to zero; Pose/orientation uses identity.
                // Default source frames are WORLD so queries for WORLD return zero
                // without requiring a FrameTransform to be present.
                CubliState()
                        : center_of_mass_pos_(), contact_corner_pos_(), orientation_(Matrix3dIdentity),
                            center_of_mass_frame_(Frame(FrameIDs::WORLD)), contact_corner_frame_(Frame(FrameIDs::WORLD)) {}

                // Return positions expressed in the requested target frame.
                // The Point class is frame-less; we use `in_frame(source_frame, target_frame)`.
                Vector3d get_center_of_mass(const Frame &target_frame) {
                    if (center_of_mass_frame_ == target_frame) {
                        Vector3d v; v << center_of_mass_pos_.x(), center_of_mass_pos_.y(), center_of_mass_pos_.z();
                        return v;
                    }
                    return center_of_mass_pos_.in_frame(center_of_mass_frame_, target_frame);
                }

                Vector3d get_contact_corner(const Frame &target_frame) {
                    if (contact_corner_frame_ == target_frame) {
                        Vector3d v; v << contact_corner_pos_.x(), contact_corner_pos_.y(), contact_corner_pos_.z();
                        return v;
                    }
                    return contact_corner_pos_.in_frame(contact_corner_frame_, target_frame);
                }
                Pose get_cubli_pose(const Frame &target_frame);
};