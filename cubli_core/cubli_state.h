#pragma once

#include "math/Point.h"
#include <rbdl/rbdl.h>

class CubliState {
    private: 
        Point center_of_mass_pos_;
        Point contact_corner_pos_;
        Matrix3d orientation_;
    public:

        CubliState() : center_of_mass_pos_(Vector3dZero, Frame()), contact_corner_pos_(Vector3dZero, Frame()), orientation_(Matrix3dIdentity) {}    

        Vector3d get_center_of_mass(const FrameName &name) { return center_of_mass_pos_.pos_in_frame(name); }
        Vector3d get_contact_corner(const FrameName &name) { return contact_corner_pos_.pos_in_frame(name); }
        Pose get_cubli_pose(FrameName name);
};