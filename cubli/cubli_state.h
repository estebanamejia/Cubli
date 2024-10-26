#include "math/Point.h"
#include <rbdl/rbdl.h>

class CubliState {
    private: 
        Point center_of_mass_pos_;
        Point contact_corner_pos_;
        Matrix3d orientation_;
    public:
        Vector3d get_center_of_mass(FrameName &name) { return center_of_mass_pos_.pos_in_frame(name); }
        Vector3d get_contact_corner(FrameName &name) { return contact_corner_pos_.pos_in_frame(name); }
        Pose get_cubli_pose(FrameName name);
};