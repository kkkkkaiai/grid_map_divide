#include "readPcd.h"

readPcd::readPcd(){
    loadConfig();
}

void readPcd::loadConfig(){
    pcd_path = node["pcd_path"].as<string>();
}

string readPcd::get_pcd_path(){
    return pcd_path;
}