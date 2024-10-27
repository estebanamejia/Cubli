#include "Point.h"

Point::Point(Vector3d const &pos, Frame const &frame) {
    set_pos_frame(pos, frame);
};

void Point::set_pos_frame(Vector3d const &pos, Frame const &frame) {
    bool frame_not_in_map = pos_frame_map_.find(frame.name()) == pos_frame_map_.end();
    if (frame_not_in_map) {
        pair<Frame, Vector3d> frame_pos (frame, pos);
        pos_frame_map_.insert({frame.name(), frame_pos});
    };
};

Vector3d Point::pos_in_frame(const FrameName &name) const {
    pair<Frame, Vector3d> frame_pos = pos_frame_map_.at(name);
    return frame_pos.second;
};