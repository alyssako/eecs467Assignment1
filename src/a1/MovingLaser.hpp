#ifndef MOVING_LASER_HPP
#define MOVING_LASER_HPP

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <lcm/lcm-cpp.hpp>
#include <signal.h>
#include <string>
#include <vector>

#include "lcmtypes/maebot_motor_command_t.hpp"
#include "lcmtypes/maebot_targeting_laser_command_t.hpp"
#include "lcmtypes/maebot_leds_command_t.hpp"
#include "lcmtypes/maebot_sensor_data_t.hpp"
#include "lcmtypes/maebot_motor_feedback_t.hpp"
#include "lcmtypes/maebot_pose_t.hpp"
#include "lcmtypes/maebot_laser_scan_t.hpp"

/* store lidar scans and associated poses where they originated */
struct LaserScan
{
    std::vector<maebot_pose_t> origins;
    maebot_laser_scan_t scan;
};

/* store the lidar scan and the two poses it originated between */
struct LaserScanApprox
{
    maebot_pose_t start_pose;
    maebot_pose_t end_pose;
    maebot_laser_scan_t scan;
};

/* functor that figure out where each individual laser originated from */
class MovingLaser
{
    public:
        LaserScan findOrigin(LaserScanApprox approx_scan);
        maebot_pose_t findOriginSingle(int64_t, maebot_pose_t, maebot_pose_t);
        float angle_diff(float, float);
};

#endif
