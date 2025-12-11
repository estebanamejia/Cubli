#include "math/Frame.h"
#include "math/FrameID.h"
#include <set>
using namespace std;

class CubliFrameNames {
    public:
        // Return well-known frames as `Frame` objects using `FrameID` constants
        Frame WORLD() const { return Frame(FrameIDs::WORLD); }
        Frame CUBLI() const { return Frame(FrameID("CUBLI")); }
};