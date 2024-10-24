#include <gtest/gtest.h>
#include "math/Pose.h"

TEST(PoseEqualityTest, BasicAssertions) {
    Matrix3d ori_a = Matrix3d();
    Vector3d translation_a = Vector3d();
    Pose pose_a = Pose(ori_a, translation_a);
    Pose pose_b = pose_a;
    EXPECT_EQ(pose_a, pose_b);
}