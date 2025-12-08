#pragma once

#include "math/FrameID.h"

// Frame is a pure identifier/reference - it has no position or orientation
// All position/orientation data is stored separately from frame references
class Frame {
    private:
        FrameID id_;
    public:
        Frame(FrameID const &id = FrameID()) : id_(id) {}
        FrameID id() const { return id_; }
        
        friend bool operator==(const Frame&, const Frame&);
        virtual bool isEqual(const Frame& frame) const { return frame.id_ == id_; }
};
