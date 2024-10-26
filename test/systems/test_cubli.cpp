#include <gtest/gtest.h>
#include "cubli/cubli.h"
#include "planning/planning.h"

TEST(StabilityTest, BasicAssertions) {
    start_cubli();
    Pose cubli_pose = get_cubli_pose();
    Pose start_pose = Pose();
    EXPECT_EQ(cubli_pose, start_pose);

    balance_cubli();
    Pose balanced_pose = calculate_balance_pose();
    cubli_pose = get_cubli_pose();
    EXPECT_EQ(cubli_pose, balanced_pose);
}