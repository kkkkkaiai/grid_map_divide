#pragma once

#ifndef READ_PCD_H
#define READ_PCD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include "yaml-cpp/yaml.h"

#define GRID_SIZE 
using namespace std;

static string config_name = {"../param/config.yaml"};
static const YAML::Node& node = YAML::LoadFile(config_name);

struct GridConfig{
    int grid_size;
    int net_num;
    double min_x = 100000000;
    double max_x = -100000000;
    double min_y = 100000000;
    double max_y = -100000000;
    int net_x = 0;
    int net_y = 0; // the num of net;
};

struct Grid{
    string filename;
    int grid_id;
    int grid_id_x;
    int gird_id_y;
    int lower_bound_x;
    int lower_bound_y;
    int upper_bound_x;
    int upper_bound_y;
    pcl::PointCloud<pcl::PointXYZI> cloud;
};

class readPcd{
public:
    readPcd();
    void loadConfig();
    string get_pcd_path();
    string get_scv_name();
    string get_scv_path();
    int getBound();           // obtain the bound according to pcd file
    int group();              // divide into group
    void organizeCloud();
    void writeCloud();
    void run();


    void print_debug();
    
private:
    string pcd_path;
    string write_path;
    string scv_path;
    string scv_name;
    pcl::PointCloud<pcl::PointXYZI> source_cloud;
    bool read_success = false;
    GridConfig grid_;
    vector<Grid> grid_sum;
};


#endif