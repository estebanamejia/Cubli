#pragma once

#include <rbdl/rbdl.h>
#include "math/FrameID.h"

using namespace RigidBodyDynamics::Math;
using namespace std;

// Forward declaration
class FrameTree;

// Point represents a 3D position in a specific coordinate frame.
// Each point is tied to a frame via its frame ID. To get the coordinates
// of this point in a different frame, use in_frame(target_frame_id).
class Point {
    private:
        Vector3d position_;
        FrameID frame_id_;
        
    public:
        // Initialize with x, y, z components and a frame identifier
        Point(double x, double y, double z, const FrameID& frame_id);
        
        // Initialize with a Vector3d and frame identifier
        Point(const Vector3d& position, const FrameID& frame_id);

        // Explicit component accessors — these are relative to the point's current frame
        double x() const { return position_(0); }
        double y() const { return position_(1); }
        double z() const { return position_(2); }
        
        // Get the underlying position vector in the current frame
        Vector3d position() const { return position_; }
        
        // Get the frame ID this point is expressed in
        FrameID frame_id() const { return frame_id_; }
        
        // Return a new Point representing the same location but in a different frame
        // Throws if no transform path exists between the current frame and target_frame_id
        Point in_frame(const FrameID& target_frame_id) const;
        
        friend bool operator==(const Point&, const Point&);
        virtual bool isEqual(const Point& other) const;
};