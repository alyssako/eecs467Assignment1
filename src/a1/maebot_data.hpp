#ifndef MAEBOT_DATA
#define MAEBOT_DATA
#include <vector>
#include <math/point.hpp>
#include <deque>
class maebot_pose_data{
public:
    maebot_pose_data();
    maebot_pose_data(const maebot_pose_data& other);
    maebot_pose_data(int64_t utime,float x,float y,float theta);
    int64_t get_timestamp();
    float get_x_pos();
    float get_y_pos();
    float get_theta();
    ~maebot_pose_data(){}
private:
    int64_t pose_time;
    float pose_x_curr;
    float pose_y_curr;
    float pose_theta_curr;
};

//full laser scan
class maebot_laser_data{
public:
    maebot_laser_data();
    maebot_laser_data(int64_t utime,int32_t nranges,std::vector<float> rs,std::vector<float> ths,std::vector<int64_t> ts,std::vector<float> is);
    maebot_laser_data(int64_t utime,int32_t nranges,std::vector<float> rs,std::vector<float> ths,std::vector<int64_t> ts,std::vector<float> is,maebot_pose_data pose);
    void calc_end_points();
    int64_t get_timestamp();
    int32_t get_num_ranges();
    std::vector<float> get_ranges();
    std::vector<float> get_thetas();
    std::vector<int64_t> get_times();
    std::vector<float> get_intensities();
    maebot_pose_data get_curr_pose();
    std::vector<eecs467::Point<float>> get_end_points(); 
private:
    int64_t laser_time;
    int32_t num_ranges;
    std::vector<float> ranges;
    std::vector<float> thetas;
    std::vector<int64_t> times;
    std::vector<float> intensities;
    maebot_pose_data curr_pose;
    std::vector<eecs467::Point<float>> end_points;
};

//single laser
class maebot_laser{
public:    
    maebot_laser(){
        utime = 0;
        range = 0;
        theta = 0;
        intensity = 0;
        x_pos = 0;
        y_pos = 0;
    }
    maebot_laser(int64_t time, float r,float th,float inten,float x,float y){
        utime = time;
        range = r;
        theta = th;
        intensity = inten;
        x_pos = x;
        y_pos = y; 
    }
    int64_t get_timestamp(){
        return utime;
    }
    float get_range(){
        return range;
    }
    float get_theta(){
        return theta;
    }
    float get_intensity(){
        return intensity;
    }
    float get_x_pos(){
        return x_pos;
    }
    float get_y_pos(){
        return y_pos;
    }
    float get_x_end_pos(){
        return x_pos+cosf(theta)*range; 
    }
    float get_y_end_pos(){
        return y_pos+sinf(theta)*range;
    }
private:
    int64_t utime;
    float range;
    float theta;
    float intensity;
    float x_pos;
    float y_pos;
};

/*class maebot_matched_laser_data{
public:    
    maebot_matched_laser_data(){}
    void push_data(float range,float theta){
        range.push_back(range);
        theta.push_back(theta);
    }


private:
    std::deque<float> range;
    std::deque<float> theta;
};*/

class laser_array{
public:
    void add_ray(int64_t t, float th, float m)
    {
        times.push_back(t);
        thetas.push_back(th);
        ranges.push_back(m);
    }

    void pop()
    {
        times.pop_front();
        thetas.pop_front();
        ranges.pop_front();
    }

    int64_t front_time()
    {
        return times[0];
    }

    float front_theta()
    {
        return thetas[0];
    }

    float front_range()
    {
        return ranges[0];
    }

    int size()
    {
        return times.size();
    }

private:
    std::deque<int64_t> times;
    std::deque<float> thetas;
    std::deque<float> ranges;
};
#endif