#include "math/Position.h"
#include "cubli/cubli_state.h"

using namespace std;

class CubliPlanner {
    
    CubliState state_;
    
    public:
        Pose calculate_balance_pose();
};

