#pragma once

#include <functional>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>

// FrameID provides a type-safe, unique identifier for coordinate frames.
// Uses hash of a unique string to ensure collision-resistant IDs.
class FrameID {
private:
    uint64_t id_;
    std::string name_;  // For debugging/logging only, not used in comparison
    
public:
    // Constructor from unique string identifier
    // Note: String is used only to generate hash; two different strings can produce same hash (rare collision)
    explicit FrameID(const std::string& unique_name) 
        : id_(std::hash<std::string>()(unique_name)), name_(unique_name) {}
    
    // Constructor from raw ID (for testing/advanced use)
    explicit FrameID(uint64_t id, const std::string& debug_name = "")
        : id_(id), name_(debug_name) {}
    
    // Default constructor creates invalid frame (id = 0)
    FrameID() : id_(0), name_("INVALID") {}
    
    uint64_t id() const { return id_; }
    const std::string& name() const { return name_; }
    
    // For debugging: get hex representation of ID
    std::string hex() const {
        std::stringstream ss;
        ss << "0x" << std::hex << std::setw(16) << std::setfill('0') << id_;
        return ss.str();
    }
    
    // Comparison operators
    friend bool operator==(const FrameID& lhs, const FrameID& rhs) {
        return lhs.id_ == rhs.id_;
    }
    
    friend bool operator!=(const FrameID& lhs, const FrameID& rhs) {
        return lhs.id_ != rhs.id_;
    }
    
    friend bool operator<(const FrameID& lhs, const FrameID& rhs) {
        return lhs.id_ < rhs.id_;
    }
    
    // For use in maps/sets
    friend struct std::hash<FrameID>;
};

// Hash specialization for std::unordered_map support
namespace std {
    template<>
    struct hash<FrameID> {
        size_t operator()(const FrameID& frame_id) const {
            return std::hash<uint64_t>()(frame_id.id_);
        }
    };
}

// Common frame IDs - define these once and reuse
// Use globally unique naming to minimize hash collisions
namespace FrameIDs {
    static const FrameID WORLD("WORLD_COORDINATE_FRAME_ROOT");
    static const FrameID BASE("BASE_ROBOT_FRAME");
    static const FrameID TOOL("TOOL_END_EFFECTOR_FRAME");
    static const FrameID CAMERA("CAMERA_OPTICAL_FRAME");
    static const FrameID SENSOR("SENSOR_MOUNTING_FRAME");
}
