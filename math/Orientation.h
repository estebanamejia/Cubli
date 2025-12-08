#pragma once

#include <rbdl/rbdl.h>
#include "math/Frame.h"
using namespace RigidBodyDynamics::Math;
using namespace std;

// Orientation represents a 3D rotation with no intrinsic frame context
// To transform orientations between frames, use in_frame() with explicit frame parameters
class Orientation {
    private:
        Matrix3d orientation_;
        
    public:
        Orientation(Matrix3d const &ori = Matrix3dIdentity);
        Matrix3d orientation() const { return orientation_; }
        
        // Transform this orientation from source_frame to target_frame
        // Requires a FrameTransform that defines the relationship between frames
        Matrix3d in_frame(const Frame &source_frame, const Frame &target_frame) const;
};
