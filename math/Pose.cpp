#include "math/Pose.h"

bool operator==(const Pose& lhs, const Pose& rhs) {
    return typeid(lhs) == typeid(rhs) // Allow compare only instances of the same dynamic type
           && lhs.isEqual(rhs);       // If types are the same then do the comparision.
}