#include <gtest/gtest.h>
#include "main/cubli.h"

TEST(StabilityTest, BasicAssertions) {
    start_cubli();
    SpatialTransform cubli_pose = get_cubli_pose();
    SpatialTransform start_pose = SpatialTransform();
    EXPECT_EQ(cubli_pose, start_pose);
}