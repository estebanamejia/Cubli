#include "cubli/cubli_state.h"

Pose CubliState::get_cubli_pose(const FrameID &target_frame_id) {
    Vector3d cubli_com = get_center_of_mass(target_frame_id);
    Pose cubli_pose = Pose(orientation_, cubli_com, target_frame_id);
    return cubli_pose;
}
