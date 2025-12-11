#include "cubli/cubli_planning.h"
#include "cubli/cubli_geometry.h"


Pose CubliPlanner::calculate_balance_pose() {
    // TODO: Calculate balance pose using state information
    return Pose(RigidBodyDynamics::Math::Matrix3dIdentity, 0.0, 0.0, 0.0, FrameIDs::WORLD);
}