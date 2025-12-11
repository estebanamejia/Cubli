#include <gtest/gtest.h>
#include <random>
#include "math/Orientation.h"
#include <cmath>

// Helper to normalize angle to [-pi, pi]
double normalize_angle(double a) {
    const double TWO_PI = 2.0 * M_PI;
    a = fmod(a + M_PI, TWO_PI);
    if (a < 0) a += TWO_PI;
    return a - M_PI;
}

TEST(OrientationTest, RpyRoundTripRandom) {
    std::mt19937_64 gen(12345);
    std::uniform_real_distribution<double> dist_roll(-M_PI, M_PI);
    std::uniform_real_distribution<double> dist_yaw(-M_PI, M_PI);
    // Keep pitch away from exact +/- pi/2 to avoid gimbal singularities
    const double eps = 1e-3;
    std::uniform_real_distribution<double> dist_pitch(-M_PI/2 + eps, M_PI/2 - eps);

    for (int i = 0; i < 1000; ++i) {
        double roll = dist_roll(gen);
        double pitch = dist_pitch(gen);
        double yaw = dist_yaw(gen);

        Orientation o = Orientation::fromRPY(roll, pitch, yaw);

        // Recover angles and reconstruct orientation; compare rotations (not raw angles)
        Eigen::Vector3d out = o.rpy();
        // Reconstruct a rotation using the same composition used in `fromRPY`:
        Eigen::AngleAxisd rx(out[0], Eigen::Vector3d::UnitX());
        Eigen::AngleAxisd ry(out[1], Eigen::Vector3d::UnitY());
        Eigen::AngleAxisd rz(out[2], Eigen::Vector3d::UnitZ());
        Eigen::Quaterniond q_out = rz * ry * rx; // yaw * pitch * roll

        // Compare rotation matrices (more robust to Euler non-uniqueness)
        Eigen::Matrix3d R1 = o.orientation();
        Eigen::Matrix3d R2 = q_out.toRotationMatrix();
        double err = (R1 - R2).norm();

        const double tol = 1e-10;
        EXPECT_LT(err, tol);
    }
}
