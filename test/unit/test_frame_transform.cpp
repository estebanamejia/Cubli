#include <gtest/gtest.h>
#include <cmath>
#include "math/Point.h"
#include "math/Pose.h"
#include "math/Orientation.h"
#include "math/Frame.h"
#include "math/FrameID.h"
#include "math/FrameTransform.h"

using namespace RigidBodyDynamics::Math;

class ExplicitFrameTransformTest : public ::testing::Test {
protected:
    // Create frame IDs with unique identifiers
    FrameID world_id{"WORLD_TEST_FRAME"};
    FrameID base_id{"BASE_TEST_FRAME"};
    FrameID tool_id{"TOOL_TEST_FRAME"};
    
    // Create frames from IDs
    Frame world_frame;
    Frame base_frame;
    Frame tool_frame;
    
    // Create explicit transforms between frames
    FrameTransform world_to_base;
    FrameTransform base_to_tool;
    
    void SetUp() override {
        // Frames are now identified by unique FrameIDs
        world_frame = Frame(world_id);
        base_frame = Frame(base_id);
        tool_frame = Frame(tool_id);
        
        // Explicit transform: base is translated 1 unit in X relative to world
        Vector3d base_translation;
        base_translation << 1.0, 0.0, 0.0;
        Pose world_to_base_pose(Matrix3dIdentity, base_translation);
        world_to_base = FrameTransform(world_frame, base_frame, world_to_base_pose);
        
        // Explicit transform: tool is translated 0.5 units in Y relative to base
        Vector3d tool_translation;
        tool_translation << 0.0, 0.5, 0.0;
        Pose base_to_tool_pose(Matrix3dIdentity, tool_translation);
        base_to_tool = FrameTransform(base_frame, tool_frame, base_to_tool_pose);
    }
};

TEST_F(ExplicitFrameTransformTest, FrameIdentifiers) {
    EXPECT_EQ(world_frame.id(), world_id);
    EXPECT_EQ(base_frame.id(), base_id);
    EXPECT_EQ(tool_frame.id(), tool_id);
    
    // Verify IDs are different
    EXPECT_NE(world_frame.id(), base_frame.id());
    EXPECT_NE(base_frame.id(), tool_frame.id());
}

TEST_F(ExplicitFrameTransformTest, PureData) {
    Vector3d point_pos;
    point_pos << 0.5, 0.0, 0.0;
    Point point(point_pos);
    EXPECT_DOUBLE_EQ(point.position()(0), 0.5);
    EXPECT_DOUBLE_EQ(point.position()(1), 0.0);
    EXPECT_DOUBLE_EQ(point.position()(2), 0.0);
}

TEST_F(ExplicitFrameTransformTest, PoseIsPureData) {
    Vector3d pose_translation;
    pose_translation << 1.0, 1.0, 1.0;
    Pose pose(Matrix3dIdentity, pose_translation);
    
    Vector3d trans = pose.translation();
    EXPECT_DOUBLE_EQ(trans(0), 1.0);
    EXPECT_DOUBLE_EQ(trans(1), 1.0);
    EXPECT_DOUBLE_EQ(trans(2), 1.0);
}

TEST_F(ExplicitFrameTransformTest, OrientationIsPureData) {
    Orientation orientation(Matrix3dIdentity);
    
    Matrix3d ori = orientation.orientation();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(ori(i, j), Matrix3dIdentity(i, j));
        }
    }
}

TEST_F(ExplicitFrameTransformTest, FrameTransformPosition) {
    // Create a point at origin in base frame
    Vector3d point_in_base;
    point_in_base << 0.0, 0.0, 0.0;
    
    // Transform using explicit FrameTransform
    Vector3d point_in_world = world_to_base.transform_position(point_in_base);
    
    // Since base_frame is translated (1, 0, 0) from world, origin of base should be at (1, 0, 0) in world
    EXPECT_DOUBLE_EQ(point_in_world(0), 1.0);
    EXPECT_DOUBLE_EQ(point_in_world(1), 0.0);
    EXPECT_DOUBLE_EQ(point_in_world(2), 0.0);
}

TEST_F(ExplicitFrameTransformTest, FrameTransformPose) {
    Vector3d pose_translation;
    pose_translation << 0.5, 0.0, 0.0;
    Pose pose_in_base(Matrix3dIdentity, pose_translation);
    
    // Transform pose from base frame to world frame using explicit transform
    Pose pose_in_world = world_to_base.transform_pose(pose_in_base);
    
    // Position should be (1.0 + 0.5, 0, 0) = (1.5, 0, 0) in world
    Vector3d trans_in_world = pose_in_world.translation();
    EXPECT_DOUBLE_EQ(trans_in_world(0), 1.5);
    EXPECT_DOUBLE_EQ(trans_in_world(1), 0.0);
    EXPECT_DOUBLE_EQ(trans_in_world(2), 0.0);
}

TEST_F(ExplicitFrameTransformTest, InverseTransform) {
    FrameTransform base_to_world = world_to_base.inverse();
    
    // Inverse should swap source and target frames
    EXPECT_TRUE(base_to_world.source_frame() == base_frame);
    EXPECT_TRUE(base_to_world.target_frame() == world_frame);
    
    // The original transform (world_to_base) translates by (1, 0, 0)
    // So the inverse should translate by (-1, 0, 0)
    Vector3d point_in_base;
    point_in_base << 0.0, 0.0, 0.0;
    
    Vector3d point_in_world = base_to_world.transform_position(point_in_base);
    
    // Origin of base in world coordinates should be (-1, 0, 0)
    // because base is translated (+1, 0, 0) FROM world
    EXPECT_DOUBLE_EQ(point_in_world(0), -1.0);
    EXPECT_DOUBLE_EQ(point_in_world(1), 0.0);
    EXPECT_DOUBLE_EQ(point_in_world(2), 0.0);
}

TEST_F(ExplicitFrameTransformTest, FrameTransformComposition) {
    // Compose transforms: world -> base -> tool
    Vector3d point_in_tool;
    point_in_tool << 0.0, 0.0, 0.0;
    
    // Transform from tool to base
    Vector3d point_in_base = base_to_tool.transform_position(point_in_tool);
    EXPECT_DOUBLE_EQ(point_in_base(0), 0.0);
    EXPECT_DOUBLE_EQ(point_in_base(1), 0.5);
    EXPECT_DOUBLE_EQ(point_in_base(2), 0.0);
    
    // Transform from base to world
    Vector3d point_in_world = world_to_base.transform_position(point_in_base);
    EXPECT_DOUBLE_EQ(point_in_world(0), 1.0);
    EXPECT_DOUBLE_EQ(point_in_world(1), 0.5);
    EXPECT_DOUBLE_EQ(point_in_world(2), 0.0);
}

TEST_F(ExplicitFrameTransformTest, RotationTransform) {
    // Create a 90-degree rotation around Z axis
    Matrix3d rotation;
    rotation << 0.0, -1.0, 0.0,
               1.0,  0.0, 0.0,
               0.0,  0.0, 1.0;
    
    Pose rotation_pose(rotation, Vector3dZero);
    FrameTransform rotation_transform(world_frame, base_frame, rotation_pose);
    
    // Transform a point (1, 0, 0) by 90 degree rotation
    Vector3d point;
    point << 1.0, 0.0, 0.0;
    Vector3d rotated = rotation_transform.transform_position(point);
    
    // Should become (0, 1, 0) within tolerance
    EXPECT_NEAR(rotated(0), 0.0, 1e-10);
    EXPECT_NEAR(rotated(1), 1.0, 1e-10);
    EXPECT_NEAR(rotated(2), 0.0, 1e-10);
}

