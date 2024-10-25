#include <gtest/gtest.h>
#include "cubli/cubli.h"

TEST(StabilityTest, BasicAssertions) {
    start_cubli();
    Pose cubli_pose = get_cubli_pose();
    Pose start_pose = Pose();
    EXPECT_EQ(cubli_pose, start_pose);
}