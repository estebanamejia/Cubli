#include "cubli/cubli_state.h"

Pose CubliState::get_cubli_pose(const Frame &target_frame) {
    Vector3d cubli_com = get_center_of_mass(target_frame);
    Pose cubli_pose = Pose(orientation_, cubli_com);
    return cubli_pose;
}
