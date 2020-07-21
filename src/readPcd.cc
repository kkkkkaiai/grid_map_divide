#include "readPcd.h"

readPcd::readPcd(){
    loadConfig();

    // cout << get_pcd_path()  << endl;
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZI> ());
    source_cloud = *cloud;
    cloud = source_cloud.makeShared();

    if(pcl::io::loadPCDFile(pcd_path, source_cloud) < 0){
        PCL_ERROR("Couldn't read the file which path is %s \n", pcd_path);
    }else{
        PCL_INFO("load pcd successfully, points is %d. \n", source_cloud.points.size());
    }
    
}

void readPcd::loadConfig(){
    pcd_path = node["pcd_path"].as<string>();
}

string readPcd::get_pcd_path(){
    return pcd_path;
}

