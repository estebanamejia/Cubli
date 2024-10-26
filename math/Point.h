#include <rbdl/rbdl.h>
#include "math/Frame.h"
using namespace RigidBodyDynamics::Math;
using namespace std;

class Point {
    private:
        map<FrameName, pair<Frame, Vector3d>, equal_to<Frame>> pos_frame_map_;
        void set_pos_frame(Vector3d const &pos, Frame const &frame);
    public:
        Point(Vector3d const &pos = Vector3dZero, Frame const &frame = Frame());
        Vector3d pos_in_frame(FrameName &name) const;
};