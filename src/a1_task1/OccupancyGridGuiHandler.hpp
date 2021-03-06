#ifndef OCCUPANCY_GRID_GUI_HANDLER_HPP
#define OCCUPANCY_GRID_GUI_HANDLER_HPP

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <lcm/lcm-cpp.hpp>
#include <signal.h>
#include <string>

#include "maebot_handlers.hpp"
#include "lcmtypes/maebot_motor_command_t.hpp"
#include "lcmtypes/maebot_targeting_laser_command_t.hpp"
#include "lcmtypes/maebot_leds_command_t.hpp"
#include "lcmtypes/maebot_sensor_data_t.hpp"
#include "lcmtypes/maebot_motor_feedback_t.hpp"
#include "lcmtypes/maebot_pose_t.hpp"
#include "lcmtypes/maebot_laser_scan_t.hpp"
#include "lcmtypes/maebot_occupancy_grid_t.hpp"

#include "state.hpp"
#include "mapping/occupancy_grid.hpp"
#include "mapping/occupancy_grid_utils.hpp"

class OccupancyGridGuiHandler
{
    public:
		eecs467::OccupancyGrid *grid;
		
        OccupancyGridGuiHandler(eecs467::OccupancyGrid* _grid){
        	grid = _grid;
        }
        
        ~OccupancyGridGuiHandler(){}

        void handleMessage(const lcm::ReceiveBuffer *rbuf,
                           const std::string& channel,
                           const maebot_occupancy_grid_t *msg)
        {   
            std::cout << "gui received grid" << std::endl;
            
            grid->reset();
            grid->fromLCM(*msg);
        }
};

class LocationHandler
{
    public:
        state_t *state;
        LocationHandler(state_t *state_t) : state(state_t) {}

        ~LocationHandler(){}

        void handlePose(const lcm::ReceiveBuffer *rbuf,
                        const std::string& channel,
                        const maebot_pose_t *msg)
        {
            state->poses.push_back(*msg);
        }
};

#endif
