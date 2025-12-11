#include "math/FrameTree.h"
#include "math/FrameTransform.h"
#include <queue>
#include <set>

FrameTree* FrameTree::instance_ = nullptr;

FrameTree& FrameTree::instance() {
    if (instance_ == nullptr) {
        instance_ = new FrameTree();
    }
    return *instance_;
}

void FrameTree::add_transform(const FrameID& source, const FrameID& target, const FrameTransform& transform) {
    // Use insert or emplace instead of [] to avoid default construction
    frame_transforms_[source].insert({target, transform});
    // Also add the inverse transform for bidirectional querying
    frame_transforms_[target].insert({source, transform.inverse()});
}

void FrameTree::add_transform(const FrameID& source, const FrameID& target, const Pose& pose) {
    FrameTransform transform(source, target, pose);
    add_transform(source, target, transform);
}

bool FrameTree::get_transform(const FrameID& source, const FrameID& target, FrameTransform& result) const {
    if (source == target) {
        // Identity transform
        result = FrameTransform(source, source, Pose(RigidBodyDynamics::Math::Matrix3dIdentity, 0.0, 0.0, 0.0, source));
        return true;
    }
    
    std::vector<FrameTransform> path;
    if (!find_path(source, target, path)) {
        return false;
    }
    
    result = compose_transforms(path);
    return true;
}

FrameTransform FrameTree::get_transform_or_throw(const FrameID& source, const FrameID& target) const {
    std::vector<FrameTransform> path;
    if (source == target) {
        // Identity transform
        Pose identity_pose(RigidBodyDynamics::Math::Matrix3dIdentity, 0.0, 0.0, 0.0, source);
        return FrameTransform(source, source, identity_pose);
    }
    
    if (!find_path(source, target, path)) {
        throw std::runtime_error(
            "No transform path found between frames " + 
            source.name() + " (" + source.hex() + ") and " + 
            target.name() + " (" + target.hex() + ")"
        );
    }
    
    return compose_transforms(path);
}

void FrameTree::clear() {
    frame_transforms_.clear();
}

bool FrameTree::find_path(
    const FrameID& source, 
    const FrameID& target,
    std::vector<FrameTransform>& path
) const {
    if (source == target) {
        path.clear();
        return true;
    }
    
    // BFS to find shortest path
    std::queue<FrameID> queue;
    std::map<FrameID, FrameID> parent_map;
    std::set<FrameID> visited;
    
    queue.push(source);
    visited.insert(source);
    
    while (!queue.empty()) {
        FrameID current = queue.front();
        queue.pop();
        
        if (current == target) {
            // Reconstruct path
            std::vector<FrameTransform> result_path;
            FrameID node = target;
            
            while (parent_map.find(node) != parent_map.end()) {
                FrameID parent = parent_map[node];
                // Get the direct transform from parent to node
                auto it = frame_transforms_.find(parent);
                if (it != frame_transforms_.end()) {
                    auto jt = it->second.find(node);
                    if (jt != it->second.end()) {
                        result_path.push_back(jt->second);
                    }
                }
                node = parent;
            }
            
            // Reverse to get source -> target order
            std::reverse(result_path.begin(), result_path.end());
            path = result_path;
            return true;
        }
        
        // Explore neighbors
        auto it = frame_transforms_.find(current);
        if (it != frame_transforms_.end()) {
            for (const auto& neighbor_pair : it->second) {
                FrameID neighbor = neighbor_pair.first;
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    parent_map[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }
    }
    
    return false;
}

FrameTransform FrameTree::compose_transforms(const std::vector<FrameTransform>& transforms) {
    if (transforms.empty()) {
        // Return identity transform
        FrameID identity_id("identity");
        return FrameTransform(identity_id, identity_id, Pose(RigidBodyDynamics::Math::Matrix3dIdentity, 0.0, 0.0, 0.0, identity_id));
    }
    
    if (transforms.size() == 1) {
        return transforms[0];
    }
    
    // Compose transforms: T_total = T_n * ... * T_2 * T_1
    Pose composed_pose = transforms[0].pose();
    
    for (size_t i = 1; i < transforms.size(); ++i) {
        // Apply the next transform
        composed_pose = transforms[i].transform_pose(composed_pose);
    }
    
    // The source is from the first transform, target is from the last
    FrameID target_id = transforms.back().target_frame();
    FrameID source_id = transforms.front().source_frame();

    // Create final pose with correct target frame ID
    Pose result_pose(composed_pose.orientation(), composed_pose.position(), target_id);

    return FrameTransform(source_id, target_id, result_pose);
}

