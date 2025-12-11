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
        // Initialize explicitly with x, y, z components. Internal storage remains a Vector3d.
        Point(double x = 0.0, double y = 0.0, double z = 0.0);

        // Explicit component accessors — prefer these instead of exposing the internal Vector3d.
        double x() const { return position_(0); }
        double y() const { return position_(1); }
        double z() const { return position_(2); }
        
        // Transform this position from source_frame to target_frame
        // Requires a FrameTransform that defines the relationship between frames
        Vector3d in_frame(const Frame &source_frame, const Frame &target_frame) const;
};