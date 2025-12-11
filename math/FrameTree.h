#pragma once

#include <map>
#include <vector>
#include <stdexcept>
#include "math/FrameID.h"
#include "math/Pose.h"

// Forward declaration
class FrameTransform;

// FrameTree manages a tree/graph of coordinate frame relationships.
// It stores transforms between frames and enables querying transforms
// between any two frames by composing transforms along a path.
class FrameTree {
private:
    // Adjacency structure: for each frame, stores transforms to neighboring frames
    // Key: source frame ID, Value: map of (target frame ID -> FrameTransform)
    std::map<FrameID, std::map<FrameID, FrameTransform>> frame_transforms_;
    
    // Singleton pattern for global frame tree
    static FrameTree* instance_;
    
    FrameTree() = default;
    
public:
    // Delete copy/move constructors to enforce singleton
    FrameTree(const FrameTree&) = delete;
    FrameTree(FrameTree&&) = delete;
    FrameTree& operator=(const FrameTree&) = delete;
    FrameTree& operator=(FrameTree&&) = delete;
    
    // Get singleton instance
    static FrameTree& instance();
    
    // Register a direct transform from source to target frame
    // This overwrites any existing transform between these two frames
    void add_transform(const FrameID& source, const FrameID& target, const FrameTransform& transform);
    
    // Register a direct transform from source to target frame using a Pose
    // Convenience method that creates a FrameTransform internally
    void add_transform(const FrameID& source, const FrameID& target, const Pose& pose);
    
    // Query transform from source to target frame
    // Returns true if transform found, false otherwise
    // Result is populated if found
    bool get_transform(const FrameID& source, const FrameID& target, FrameTransform& result) const;
    
    // Query transform from source to target frame, throws if not found
    FrameTransform get_transform_or_throw(const FrameID& source, const FrameID& target) const;
    
    // Clear all transforms (for testing or reset)
    void clear();
    
private:
    // Helper: Find path between two frames using BFS
    // Returns true if path found, false otherwise
    // Result is populated if found
    bool find_path(
        const FrameID& source, 
        const FrameID& target,
        std::vector<FrameTransform>& path
    ) const;
    
    // Helper: Compose a sequence of transforms into a single transform
    static FrameTransform compose_transforms(const std::vector<FrameTransform>& transforms);
};
