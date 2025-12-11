#include <gtest/gtest.h>
#include <cmath>
#include "math/Point.h"
#include "math/Pose.h"
#include "math/Orientation.h"
#include "math/Frame.h"
#include "math/FrameID.h"
#include "math/FrameTransform.h"
#include "math/FrameTree.h"

using namespace RigidBodyDynamics::Math;

class FrameAwareGeometryTest : public ::testing::Test {
protected:
    // Create frame IDs with unique identifiers
    FrameID world_id{"WORLD_TEST_FRAME"};
    FrameID base_id{"BASE_TEST_FRAME"};
    FrameID tool_id{"TOOL_TEST_FRAME"};
    
    void SetUp() override {
        // Clear any existing transforms
        FrameTree::instance().clear();
        
        // Register transforms in the frame tree
        // base is translated 1 unit in X relative to world
        // This means: point_world = point_base + (1, 0, 0)
        // So the transform from base TO world is (I, 1, 0, 0)
        Pose base_to_world_pose(Matrix3dIdentity, 1.0, 0.0, 0.0, base_id);
        FrameTree::instance().add_transform(base_id, world_id, base_to_world_pose);
        
        // tool is translated 0.5 units in Y relative to base
        // This means: point_base = point_tool + (0, 0.5, 0)
        // So the transform from tool TO base is (I, 0, 0.5, 0)
        Pose tool_to_base_pose(Matrix3dIdentity, 0.0, 0.5, 0.0, tool_id);
        FrameTree::instance().add_transform(tool_id, base_id, tool_to_base_pose);
    }
    
    void TearDown() override {
        FrameTree::instance().clear();
    }
};

TEST_F(FrameAwareGeometryTest, FrameIDStorage) {
    FrameID frame_id("test_frame");
    Point point(0.5, 1.0, 2.0, frame_id);
    EXPECT_EQ(point.frame_id(), frame_id);
}

TEST_F(FrameAwareGeometryTest, PointInFrame) {
    // Create a point at origin in base frame
    Point point_in_base(0.0, 0.0, 0.0, base_id);
    
    // Transform to world frame
    Point point_in_world = point_in_base.in_frame(world_id);
    
    // Since base is translated (1, 0, 0) from world, origin of base should be at (1, 0, 0) in world
    EXPECT_DOUBLE_EQ(point_in_world.x(), 1.0);
    EXPECT_DOUBLE_EQ(point_in_world.y(), 0.0);
    EXPECT_DOUBLE_EQ(point_in_world.z(), 0.0);
    EXPECT_EQ(point_in_world.frame_id(), world_id);
}

TEST_F(FrameAwareGeometryTest, PointInFrameRoundTrip) {
    // Create a point in world frame
    Point point_in_world(1.0, 2.0, 3.0, world_id);
    
    // Transform to base frame
    Point point_in_base = point_in_world.in_frame(base_id);
    
    // Should be offset by -1.0 in X (inverse of the translation)
    EXPECT_DOUBLE_EQ(point_in_base.x(), 0.0);  // 1.0 - 1.0
    EXPECT_DOUBLE_EQ(point_in_base.y(), 2.0);
    EXPECT_DOUBLE_EQ(point_in_base.z(), 3.0);
    
    // Transform back to world
    Point point_back_in_world = point_in_base.in_frame(world_id);
    EXPECT_DOUBLE_EQ(point_back_in_world.x(), 1.0);
    EXPECT_DOUBLE_EQ(point_back_in_world.y(), 2.0);
    EXPECT_DOUBLE_EQ(point_back_in_world.z(), 3.0);
}

TEST_F(FrameAwareGeometryTest, PoseInFrame) {
    Pose pose_in_base(Matrix3dIdentity, 0.5, 0.0, 0.0, base_id);
    
    // Transform pose from base frame to world frame
    Pose pose_in_world = pose_in_base.in_frame(world_id);
    
    // Position should be (1.0 + 0.5, 0, 0) = (1.5, 0, 0) in world
    EXPECT_DOUBLE_EQ(pose_in_world.x(), 1.5);
    EXPECT_DOUBLE_EQ(pose_in_world.y(), 0.0);
    EXPECT_DOUBLE_EQ(pose_in_world.z(), 0.0);
    EXPECT_EQ(pose_in_world.frame_id(), world_id);
}

TEST_F(FrameAwareGeometryTest, OrientationInFrame) {
    // Create a 90-degree rotation around Z axis
    Matrix3d rotation;
    rotation << 0.0, -1.0, 0.0,
               1.0,  0.0, 0.0,
               0.0,  0.0, 1.0;
    
    Orientation ori_in_base(rotation, base_id);
    EXPECT_EQ(ori_in_base.frame_id(), base_id);
    
    // Transform orientation to world frame
    Orientation ori_in_world = ori_in_base.in_frame(world_id);
    EXPECT_EQ(ori_in_world.frame_id(), world_id);
}

TEST_F(FrameAwareGeometryTest, MultiHopTransform) {
    // Create a point at tool origin
    Point point_in_tool(0.0, 0.0, 0.0, tool_id);
    
    // Transform directly to world through the frame tree (should find path: tool -> base -> world)
    Point point_in_world = point_in_tool.in_frame(world_id);
    
    // tool origin in base is (0, 0.5, 0), base origin in world is (1, 0, 0)
    // So tool origin in world should be (1, 0.5, 0)
    EXPECT_DOUBLE_EQ(point_in_world.x(), 1.0);
    EXPECT_DOUBLE_EQ(point_in_world.y(), 0.5);
    EXPECT_DOUBLE_EQ(point_in_world.z(), 0.0);
    EXPECT_EQ(point_in_world.frame_id(), world_id);
}

TEST_F(FrameAwareGeometryTest, SameFrameTransform) {
    // Transform a point to its own frame should be a no-op
    Point point(1.0, 2.0, 3.0, base_id);
    Point point_same = point.in_frame(base_id);
    
    EXPECT_DOUBLE_EQ(point_same.x(), point.x());
    EXPECT_DOUBLE_EQ(point_same.y(), point.y());
    EXPECT_DOUBLE_EQ(point_same.z(), point.z());
}

