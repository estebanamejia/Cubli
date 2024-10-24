#include <gtest/gtest.h>
#include "main/cubli.h"

TEST(StabilityTest, BasicAssertions) {
    start_cubli();
    cubli_pose = get_cubli_pose();
    start_pose;
    EXPECT_EQ(cubli_pose, start_pose);
}