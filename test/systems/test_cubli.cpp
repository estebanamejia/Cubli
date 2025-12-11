#include <gtest/gtest.h>
#include "cubli/cubli.h"
#include "cubli/cubli_geometry.h"
#include "cubli/cubli_planning.h"
#include "math/Pose.h"
#include "math/FrameID.h"

TEST(StabilityTest, BasicAssertions) {
    CubliPlanner cubli_planner = CubliPlanner();
    Cubli cubli = Cubli();
    CubliFrameNames names = CubliFrameNames();
    cubli.start_cubli();
    Pose cubli_pose = cubli.get_cubli_pose(names.WORLD());
    Pose start_pose = Pose(RigidBodyDynamics::Math::Matrix3dIdentity, 0.0, 0.0, 0.0, FrameIDs::WORLD);
    EXPECT_EQ(cubli_pose, start_pose);

    cubli.balance_cubli();
    Pose balanced_pose = cubli_planner.calculate_balance_pose();
    cubli_pose = cubli.get_cubli_pose(names.WORLD());
    EXPECT_EQ(cubli_pose, balanced_pose);
}