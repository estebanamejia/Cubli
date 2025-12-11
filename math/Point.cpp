
#include "math/Point.h"

#include "math/FrameTree.h"
#include "math/FrameTransform.h"

Point::Point(double x, double y, double z, const FrameID& frame_id, const string& name)
    : position_(Position(x, y, z, frame_id)), name_(name) {}

Point::Point(const Position& position, const string& name)
    : position_(position), name_(name) {}

Point Point::in_frame(const FrameID& target_frame_id) const {
    Position p_in_target = position_.in_frame(target_frame_id);
    return Point(p_in_target, name_);
}


