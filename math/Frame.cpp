#include "Frame.h"
#include <typeinfo>

bool operator==(const Frame& lhs, const Frame& rhs) {
    return typeid(lhs) == typeid(rhs) // Allow compare only instances of the same dynamic type
           && lhs.isEqual(rhs);       // If types are the same then do the comparision.
}

