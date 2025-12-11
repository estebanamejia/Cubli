#include <gtest/gtest.h>
#include "math/Pose.h"
#include "math/FrameID.h"

TEST(PoseEqualityTest, BasicAssertions) {
    FrameID frame_id("test_frame");
    Pose pose_a = Pose(RigidBodyDynamics::Math::Matrix3dIdentity, 0.0, 0.0, 0.0, frame_id);
    Pose pose_b = pose_a;
    EXPECT_EQ(pose_a, pose_b);
}

TEST(PoseEqualityTest, DifferentFrames) {
    FrameID frame_id_1("frame_1");
    FrameID frame_id_2("frame_2");
    Pose pose_a = Pose(RigidBodyDynamics::Math::Matrix3dIdentity, 1.0, 2.0, 3.0, frame_id_1);
    Pose pose_b = Pose(RigidBodyDynamics::Math::Matrix3dIdentity, 1.0, 2.0, 3.0, frame_id_2);
    EXPECT_NE(pose_a, pose_b);  // Same data but different frames
}

TEST(PoseFrameTest, FrameIDStorage) {
    FrameID frame_id("my_frame");
    Pose pose(RigidBodyDynamics::Math::Matrix3dIdentity, 1.0, 2.0, 3.0, frame_id);
    EXPECT_EQ(pose.frame_id(), frame_id);
}