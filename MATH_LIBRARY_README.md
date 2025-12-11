# Robotics Math Library - Explicit Frame Foundation

## Design Philosophy

**No implicit frames.** All frame relationships are explicit. Users must provide Frame context when transforming data. This eliminates "magic" coordinate frames and makes code intent clear and testable.

## Overview

A robotics mathematics library supporting explicit frame transformations for positions, orientations, and poses. Data objects (Point, Pose, Orientation) are frame-agnostic. Frame relationships are defined using FrameTransform objects.

## Core Concepts

### Pure Data Objects vs Frame Relationships

- **Data Objects** (Point, Pose, Orientation): Store ONLY the data itself, no frame context
- **Frame Relationships** (FrameTransform): Explicitly define how to convert data between coordinate frames

This separation ensures clarity about what depends on which frame.

### FrameID: Robust Frame Identification

Instead of error-prone string-based frame names, all frames are identified by **FrameID** - a hash-based, collision-resistant unique identifier:

- **Type-safe**: Compile-time type checking prevents frame ID confusion
- **Hash-based**: Generates unique IDs from descriptor strings, with negligible collision risk
- **Comparable**: Supports hashing for use in maps/sets
- **Debug-friendly**: Stores original descriptor for logging

**Example:**
```cpp
// Create unique frame identifiers
FrameID world_id("WORLD_COORDINATE_FRAME_ROOT");
FrameID base_id("BASE_ROBOT_FRAME");
FrameID tool_id("TOOL_END_EFFECTOR_FRAME");

// Or use predefined common frames
using namespace FrameIDs;
Frame world(FrameIDs::WORLD);
Frame camera(FrameIDs::CAMERA);
Frame sensor(FrameIDs::SENSOR);
```

## Core Classes

### 1. **FrameID** (`math/FrameID.h`)
The library uses `FrameID` as the canonical frame identifier type. `FrameID` is a small, hash-based identifier constructed
from a unique debug string. It is the type returned by `Position::frame_id()` and used throughout the APIs.

**Key features:**
- Type-safe identifier for frames
- Hashable and comparable for maps/sets
- Stores debug name for logging

**Example:**
```cpp
FrameID world_id("WORLD_COORDINATE_FRAME_ROOT");
FrameID base_id("BASE_ROBOT_FRAME");
EXPECT_EQ(world_id.name(), std::string("WORLD_COORDINATE_FRAME_ROOT"));
```

### 2. **FrameID** (`math/FrameID.h`)
Robust, hash-based unique identifier for coordinate frames.

**Key Features:**
- Hash-based ID generation from unique descriptors
- Collision-resistant (uses std::hash<string>)
- Supports use in maps/sets via std::hash specialization
- Debug info: stores original descriptor name
- Comparison operators: ==, !=, < for sorting

**Common Predefined IDs:**
```cpp
namespace FrameIDs {
    static const FrameID WORLD("WORLD_COORDINATE_FRAME_ROOT");
    static const FrameID BASE("BASE_ROBOT_FRAME");
    static const FrameID TOOL("TOOL_END_EFFECTOR_FRAME");
    static const FrameID CAMERA("CAMERA_OPTICAL_FRAME");
    static const FrameID SENSOR("SENSOR_MOUNTING_FRAME");
}
```

### 2. **Point** (`math/Point.h` & `math/Point.cpp`)
Represents a pure 3D position with no frame context.

**Key Features:**
- Stores ONLY a Vector3d position
- No frame affinity or assumptions
- Pure data object

**Example:**
```cpp
Vector3d position; position << 1.0, 2.0, 3.0;
Point point(position);
Vector3d p = point.position();  // Just returns the data
```

### 3. **Pose** (`math/Pose.h` & `math/Pose.cpp`)
Represents a rigid body transformation (rotation + translation) with no frame context.

**Key Features:**
- Stores rotation (3x3 Matrix3d) and translation (Vector3d)
- Pure data - no implicit frame reference
- Requires explicit frame parameters for transformations

**Example:**
```cpp
Pose pose(Matrix3dIdentity, Vector3d(1, 2, 3));
Vector3d translation = pose.translation();
Matrix3d orientation = pose.orientation();
```

### 4. **Orientation** (`math/Orientation.h` & `math/Orientation.cpp`)
Represents a pure 3D rotation with no frame context.

**Key Features:**
- Stores only a Matrix3d rotation
- Pure data object with no frame assumptions
- Cannot transform without explicit FrameTransform

**Example:**
```cpp
Orientation orientation(Matrix3dIdentity);
Matrix3d ori = orientation.orientation();
```

### 5. **FrameTransform** (`math/FrameTransform.h` & `math/FrameTransform.cpp`)
**The key class for all frame operations.** Explicitly defines the rigid transformation from one frame to another.

**Key Features:**
- Stores source frame, target frame, and the pose that transforms between them
- Methods to transform Point, Pose, and Orientation objects
- Supports inverse transforms
- Makes frame relationships crystal clear in code

**Methods:**
- `transform_position(position_in_source)` - Transform position from source to target frame
- `transform_pose(pose_in_source)` - Transform complete pose between frames
- `inverse()` - Get the inverse transform (target to source)

**Example:**
```cpp
// Define frames
Frame world = Frame(FrameName("world"));
Frame base = Frame(FrameName("base"));

// Define explicit transform: base is 1 unit in X from world
Pose base_relative_to_world(Matrix3dIdentity, Vector3d(1, 0, 0));
FrameTransform world_to_base(world, base, base_relative_to_world);

// Transform a position (use `Position` which carries its frame)
Position point_in_base(Vector3d(0, 0, 0), base.id());
Position point_in_world = world_to_base.transform_position(point_in_base);
// Result: Position(Vector3d(1, 0, 0), world.id()) — expressed in `world`
```

### 6. **FrameName**
(Deprecated) Earlier drafts used a `Frame` wrapper type; the current implementation uses `FrameID` directly. Examples and APIs
in this README use `FrameID` and the `FrameIDs` namespace.

## Usage Patterns

### Pattern 1: Pure Data
```cpp
Point point(Vector3d(1, 2, 3));        // Just a position
Pose pose(rot_mat, trans_vec);         // Just a transformation
Orientation ori(rot_mat);              // Just a rotation
```

### Pattern 2: Define Frame Identifiers
```cpp
// Create unique frame identifiers (use descriptive names)
FrameID world_id("WORLD_COORDINATE_FRAME_ROOT");
FrameID base_id("BASE_ROBOT_FRAME_ORIGIN");
FrameID tool_id("TOOL_TIP_FRAME");

// Or use predefined frames
using namespace FrameIDs;
FrameID camera_id = FrameIDs::CAMERA;
```

### Pattern 3: Explicit Frame Transformation
```cpp
// Define your frames using robust IDs
FrameID world_id("WORLD_COORDINATE_FRAME_ROOT");
FrameID camera_id("CAMERA_OPTICAL_FRAME");

// Define the relationship
Pose camera_pose(rotation, translation);
FrameTransform world_to_camera(world_id, camera_id, camera_pose);

// Use it to transform data
Point point(position);
// Wrap the point data with a `Position` tied to its frame (example uses `base_id`), then transform
FrameID base_id("BASE_ROBOT_FRAME_ORIGIN");
Position point_in_base(point.position(), base_id);
Position point_in_camera = world_to_camera.transform_position(point_in_base);
```

### Pattern 4: Chain Transformations
```cpp
// Frame hierarchy: world -> base -> tool
FrameID world_id("WORLD_COORDINATE_FRAME_ROOT");
FrameID base_id("BASE_ROBOT_FRAME_ORIGIN");
FrameID tool_id("TOOL_TIP_FRAME");

// FrameTransform examples expect `FrameID` values for source/target
FrameTransform world_to_base = /* ... */;
FrameTransform base_to_tool = /* ... */;

// Transform step by step
Position in_tool(Vector3d(/* ... */), tool_id);
Position in_base = base_to_tool.transform_position(in_tool);
Position in_world = world_to_base.transform_position(in_base);
```

## Transformation Mathematics

### Position Transform
```
p_target = R * p_source + t
where R is rotation, t is translation from source to target frame
```

### Pose Transform  
```
R_target = R * R_source
p_target = R * p_source + t
```

### Inverse Transform
```
T^-1 = [R^T * (-t), R^T]
```

## Architecture Notes

### No Circular Dependencies
- `FrameID` is just an identifier used throughout the math library
- Pose has no frame references (it stores a frame id for conversions)
- Point/Orientation are pure data with frame-aware wrappers
- FrameTransform brings frame relationships and conversions together

### Explicit > Implicit
Every place code accesses frame-relative data, the frames are explicit:
```cpp
// Bad (implicit assumption about frames):
// Vector3d pos = point.position_in_world();

// Good (explicit frames):
Vector3d pos = world_to_base.transform_position(point.position());
```

## Testing

Comprehensive tests in `test/unit/test_frame_transform.cpp`:
- ✅ Frame identifiers  
- ✅ Pure data objects (no frame coupling)
- ✅ FrameTransform position transformations
- ✅ FrameTransform pose transformations
- ✅ Inverse transforms
- ✅ Transform composition
- ✅ Rotation transforms
- ✅ Round-trip transformations

**All 9 tests passing!**

## Dependencies

- **RBDL** (Rigid Body Dynamics Library): For matrix/vector math
  - Eigen: Underlying linear algebra  
  - Matrix3d, Vector3d types
  - Matrix3dIdentity, Vector3dZero constants

## Build Configuration

```starlark
cc_library(
    name = "math",
    hdrs = ["Pose.h", "Frame.h", "FrameID.h", "Point.h", "Orientation.h", "FrameTransform.h"],
    srcs = ["Pose.cpp", "Frame.cpp", "Point.cpp", "Orientation.cpp", "FrameTransform.cpp"],
    deps = ["@rbdl//:rbdl"]
)
```

## Future Enhancements

1. **FrameGraph**: Automatically resolve transformations between arbitrary frames
2. **Velocity/Acceleration**: Extend to motion vectors with frame semantics
3. **Serialization**: JSON/binary support for transforms
4. **Interpolation**: Pose SLERP and trajectory interpolation
5. **Validation**: Frame graph consistency checking
6. **Performance**: Transform caching and composition optimization

