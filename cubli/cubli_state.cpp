#include "cubli/cubli_state.h"

Pose CubliState::get_cubli_pose(FrameName name) {
    Vector3d cubli_com = get_center_of_mass(name);
    Pose cubli_pose = Pose(orientation_, cubli_com);
    return cubli_pose;
};
