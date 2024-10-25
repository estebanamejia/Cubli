#include <gtest/gtest.h>
#include "math/Pose.h"

TEST(PoseEqualityTest, BasicAssertions) {
    Pose pose_a = Pose();
    Pose pose_b = pose_a;
    EXPECT_EQ(pose_a, pose_b);
}