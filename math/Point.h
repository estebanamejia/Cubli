#pragma once

#include <rbdl/rbdl.h>
#include <string>
#include "math/Position.h"

using namespace RigidBodyDynamics::Math;
using namespace std;

// Point is an object that holds a Position and a unique name.
// The Position type is the frame-aware 3D position; Points are named
// entities that reference a Position.
class Point {
    private:
        Position position_;
        string name_;
    public:
        // Construct from components and a frame identifier plus a name
        Point(double x, double y, double z, const FrameID& frame_id, const string& name);

        // Construct from a Position and a name
        Point(const Position& position, const string& name);

        // Accessors
        const string& name() const { return name_; }
        const Position& position() const { return position_; }
        FrameID frame_id() const { return position_.frame_id(); }

        // Return a new Point with the Position expressed in a different frame
        // Name is preserved.
        Point in_frame(const FrameID& target_frame_id) const;

        // Equality for Point objects is identity by name (names are unique)
        friend bool operator==(const Point& lhs, const Point& rhs) { return lhs.name_ == rhs.name_; }
        virtual bool isEqual(const Point& other) const { return name_ == other.name_; }
};