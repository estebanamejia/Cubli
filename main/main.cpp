#include "cubli/cubli.h"

int main() {
    Cubli cubli = Cubli();
    cubli.start_cubli();
    cubli.balance_cubli();
    cubli.get_cubli_pose(FrameIDs::WORLD);
}