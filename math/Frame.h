#pragma once
#include "Pose.h"

using namespace std;

class FrameName {
    private:
        string name_;
    public:
        FrameName() { name_ = "UNKNOWN"; }
        FrameName(string name) : name_(name) {}
        friend bool operator==(const FrameName&, const FrameName&);
        virtual bool isEqual(const FrameName& frame_name) const { return frame_name.name_ == name_; }
};

class Frame {
    private:
        Pose pose_frame_;
        FrameName name_;
    public:
        Frame(Pose const &pose_in_world = Pose(), FrameName const &name = FrameName()) : pose_frame_(pose_in_world), name_(name) {}
        FrameName name() const { return name_; }
        friend bool operator==(const Frame&, const Frame&);
        virtual bool isEqual(const Frame& frame) const { return poseIsEqual(frame) && nameIsEqual(frame); }
        virtual bool poseIsEqual(const Frame& frame) const { return frame.pose_frame_ == pose_frame_; }
        virtual bool nameIsEqual(const Frame& frame) const { return frame.name_  == name_; }
};