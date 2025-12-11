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
    Frame world_frame = Frame(world_id);
    Frame base_frame = Frame(base_id);
    Frame tool_frame = Frame(tool_id);
    
    // Create explicit transforms between frames
    FrameTransform world_to_base;
    FrameTransform base_to_tool;
    
    void SetUp() override {
        // Explicit transform: base is translated 1 unit in X relative to world
        Pose world_to_base_pose(Matrix3dIdentity, 1.0, 0.0, 0.0);
        world_to_base = FrameTransform(world_frame, base_frame, world_to_base_pose);
        
        // Explicit transform: tool is translated 0.5 units in Y relative to base
        Pose base_to_tool_pose(Matrix3dIdentity, 0.0, 0.5, 0.0);
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
    Point point(0.5, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(point.x(), 0.5);
    EXPECT_DOUBLE_EQ(point.y(), 0.0);
    EXPECT_DOUBLE_EQ(point.z(), 0.0);
}

TEST_F(ExplicitFrameTransformTest, PoseIsPureData) {
    Pose pose(Matrix3dIdentity, 1.0, 1.0, 1.0);
    EXPECT_DOUBLE_EQ(pose.x(), 1.0);
    EXPECT_DOUBLE_EQ(pose.y(), 1.0);
    EXPECT_DOUBLE_EQ(pose.z(), 1.0);
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
    Pose pose_in_base(Matrix3dIdentity, 0.5, 0.0, 0.0);
    // Transform pose from base frame to world frame using explicit transform
    Pose pose_in_world = world_to_base.transform_pose(pose_in_base);
    
    // Position should be (1.0 + 0.5, 0, 0) = (1.5, 0, 0) in world
    EXPECT_DOUBLE_EQ(pose_in_world.x(), 1.5);
    EXPECT_DOUBLE_EQ(pose_in_world.y(), 0.0);
    EXPECT_DOUBLE_EQ(pose_in_world.z(), 0.0);
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
    
    Pose rotation_pose(rotation, 0.0, 0.0, 0.0);
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

