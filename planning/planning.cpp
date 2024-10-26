#include "planning.h"
#include "cubli/cubli_geometry.h"


Pose CubliPlanner::calculate_balance_pose() {
    Vector3d contact_corner = state_.get_center_of_mass(CubliFrameNames::WORLD);
    Vector3d center_of_mass = state_.get_contact_corner(CubliFrameNames::WORLD);
}