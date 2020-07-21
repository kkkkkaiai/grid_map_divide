#pragma once

#ifndef READ_PCD_H
#define READ_PCD_H

#include <iostream>
#include <string>
#include <fstream>
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
};


#endif