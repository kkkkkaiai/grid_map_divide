#pragma once

#ifndef READ_PCD_H
#define READ_PCD_H

#include <iostream>
#include <string>
#include <fstream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include "yaml-cpp/yaml.h"

using namespace std;

static string config_name = {"../param/config.yaml"};
static const YAML::Node& node = YAML::LoadFile(config_name);


class readPcd{
public:
    readPcd();
    void loadConfig();
    string get_pcd_path();
private:
    string pcd_path;
    pcl::PointCloud<pcl::PointXYZI> source_cloud;
};


#endif