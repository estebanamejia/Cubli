#include "math/FrameID.h"
#include "cubli/cubli_state.h"

class Cubli {
    private:
        CubliState state_;
    public:
        void start_cubli();
        void balance_cubli();
        Pose get_cubli_pose(const FrameID &target_frame_id);
};

