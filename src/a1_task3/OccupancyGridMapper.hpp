#ifndef OCCUPANCY_GRID_MAPPER_HPP
#define OCCUPANCY_GRID_MAPPER_HPP

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <lcm/lcm-cpp.hpp>
#include <signal.h>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>

#include "lcmtypes/maebot_motor_command_t.hpp"
#include "lcmtypes/maebot_targeting_laser_command_t.hpp"
#include "lcmtypes/maebot_leds_command_t.hpp"
#include "lcmtypes/maebot_sensor_data_t.hpp"
#include "lcmtypes/maebot_motor_feedback_t.hpp"
#include "lcmtypes/maebot_pose_t.hpp"
#include "lcmtypes/maebot_laser_scan_t.hpp"
#include "lcmtypes/maebot_occupancy_grid_t.hpp"

#include "mapping/occupancy_grid.hpp"
#include "mapping/occupancy_grid_utils.hpp"

#include "ApproxLaser.hpp"

#include "math/point.hpp"
#include "MagicNumbers.hpp"

class OccupancyGridMapper
{
    private:
        std::queue<maebot_laser_scan_t> laser_scans_;
        
        std::queue<maebot_pose_t> poses_;

        pthread_cond_t cv_;
        pthread_mutex_t mapper_mutex_; // lock used with cv to wait until poses_/motor_feedbacks_ and laser_scans_ are both nonempty
        eecs467::OccupancyGrid occupancy_grid_;
        eecs467::OccupancyGrid occupancy_grid_expanded_;
        lcm::LCM *lcm;
        
        ApproxLaser approx_laser_;
        MovingLaser moving_laser_;
        std::vector<maebot_pose_t> end_points_;

    public:
        OccupancyGridMapper(lcm::LCM *lcm_t);
        //OccupancyGridMapper(int height, int width, double cellSize);
        ~OccupancyGridMapper();

        void setLogOddsMapper(int x, int y, double logOdds);
        void expandOccupancyGrid();
        
        LaserScan calculateLaserOrigins();

        void updateGrid(LaserScan scan);
        void publishOccupancyGrid(maebot_pose_t pose);
        
        void drawLineMeters(double, double, double, double, double, eecs467::CellOdds, eecs467::CellOdds);
        void drawLineMeters(double, double, double, double, eecs467::CellOdds, eecs467::CellOdds);
        
        void addLaserScan(maebot_laser_scan_t input_scan);
        void addPose(maebot_pose_t input_pose);
        ApproxLaser getApproxLaser();
        MovingLaser getMovingLaser();
        eecs467::OccupancyGrid& getOccupancyGrid();

        bool laserScansEmpty();
        bool posesEmpty();

        // lock/unlock
        void lockMapperMutex();
        void unlockMapperMutex();

        void wait();
        void signal();

        double metersPerCellMapper();
};

#endif