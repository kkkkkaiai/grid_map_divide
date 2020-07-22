#include "readPcd.h"

readPcd::readPcd(){
    // load the config file
    loadConfig();

    // cout << get_pcd_path()  << endl;

    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZI> ());
    source_cloud = *cloud;
    cloud = source_cloud.makeShared();

    if(pcl::io::loadPCDFile(pcd_path, source_cloud) < 0){
        PCL_ERROR("Couldn't read the file which path is %s \n", pcd_path);
    }else{
        PCL_INFO("load pcd successfully, points is %d. \n", source_cloud.points.size());
        read_success = true;
    }

    if(getBound() < 0){
        PCL_ERROR("error occurs when get the PCD's bound.\n");
    }
}

int readPcd::getBound(){
    if(!read_success){
        return -1;
    }

    for(auto p = source_cloud.begin(); p != source_cloud.end(); p++){
        if(p->x < grid_.min_x) grid_.min_x = p->x;
        if(p->x > grid_.max_x) grid_.max_x = p->x;
        if(p->y < grid_.min_y) grid_.min_y = p->y;
        if(p->y > grid_.max_y) grid_.max_y = p->y;
    }

    grid_.net_x = (grid_.max_x-grid_.min_x)/grid_.all_size+1;
    grid_.net_y = (grid_.max_y-grid_.min_y)/grid_.all_size+1;
    grid_.net_num = grid_.net_x * grid_.net_y;

    return 1;
}

void readPcd::print_test(){

    cout << "min_x      min_y       max_x       max_y" << endl;
    cout << grid_.min_x << " " << grid_.min_y << " " << grid_.max_x << " " << grid_.max_y << endl;

    cout << "net_x      net_y       net_num" << endl;
    cout << grid_.net_x << " " << grid_.net_y << " " << grid_.net_num << endl;

}

void readPcd::loadConfig(){
    pcd_path = node["pcd_path"].as<string>();
    grid_.all_size = node["grid_size"].as<int>();
}

string readPcd::get_pcd_path(){
    return pcd_path;
}

