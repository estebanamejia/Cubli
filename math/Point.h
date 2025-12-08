#pragma once

#include <rbdl/rbdl.h>
#include "math/Frame.h"
using namespace RigidBodyDynamics::Math;
using namespace std;

// Point represents a 3D position with no intrinsic frame context
// To work with positions in different frames, use in_frame() with explicit frame parameters
class Point {
    private:
        Vector3d position_;
        
    public:
        Point(Vector3d const &pos = Vector3dZero);
        Vector3d position() const { return position_; }
        
        // Transform this position from source_frame to target_frame
        // Requires a FrameTransform that defines the relationship between frames
        Vector3d in_frame(const Frame &source_frame, const Frame &target_frame) const;
};