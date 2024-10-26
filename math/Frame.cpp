#include "Frame.h"

bool operator==(const Frame& lhs, const Frame& rhs) {
    return typeid(lhs) == typeid(rhs) // Allow compare only instances of the same dynamic type
           && lhs.isEqual(rhs);       // If types are the same then do the comparision.
}

bool operator==(const FrameName& lhs, const FrameName& rhs) {
    return typeid(lhs) == typeid(rhs) // Allow compare only instances of the same dynamic type
           && lhs.isEqual(rhs);       // If types are the same then do the comparision.
}