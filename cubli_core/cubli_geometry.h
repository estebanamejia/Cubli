#include "math/FrameID.h"
#include <set>
using namespace std;

class CubliFrameNames {
    public:
        // Return well-known frame IDs
        FrameID WORLD() const { return FrameIDs::WORLD; }
        FrameID CUBLI() const { return FrameID("CUBLI"); }
};