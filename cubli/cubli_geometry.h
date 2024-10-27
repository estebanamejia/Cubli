#include "math/Frame.h"
#include <set>
using namespace std;

class CubliFrameNames {
    public:
        FrameName WORLD() const { return FrameName("WORLD"); }
        FrameName CUBLI() const { return FrameName("CUBLI"); }
};