#include "readPcd.h"

//s#define DEBUG_SUB_

readPcd::readPcd(){
    // load the config file
    loadConfig();

    // cout << get_pcd_path()  << endl;
  
}

void readPcd::run(){
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZI> ());
    source_cloud = *cloud;
    cloud = source_cloud.makeShared();

    cout << "Read pcd file " << pcd_path << ".\n";
    if(pcl::io::loadPCDFile(pcd_path, source_cloud) < 0){
        PCL_ERROR("Couldn't read the file which path is %s \n", pcd_path);
    }else{
        PCL_INFO("load pcd successfully, points is %d. \n", source_cloud.points.size());
        read_success = true;
    }

    if(getBound() < 0){
        PCL_ERROR("error occurs when get the PCD's bound.\n");
    }

    group();
    organizeCloud();
    writeCloud();
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

    grid_.net_x = (grid_.max_x-grid_.min_x)/grid_.grid_size+1;
    grid_.net_y = (grid_.max_y-grid_.min_y)/grid_.grid_size+1;
    grid_.net_num = grid_.net_x * grid_.net_y;

#ifdef DEBUG_SUB_
            cout << "--------------- bound --------------------" << endl;
            cout << "min_x  max_x min_y max_y" << endl;
            cout << grid_.min_x << " " << grid_.max_x << " "
                 << grid_.min_y << " " << grid_.max_y << endl;
#endif

    return 1;
}

int readPcd::group(){
    const int size = grid_.grid_size;
    int tmp_x = static_cast<int>(floor(grid_.min_x/size)*size);
    int tmp_y = static_cast<int>(floor(grid_.min_y/size)*size);
    int tmp_id = 0;

    for(int y = 0; y < grid_.net_y; y++){
        for(int x = 0; x < grid_.net_x; x++){
            Grid tmp_grid;
            tmp_grid.grid_id = tmp_id++;
            tmp_grid.filename = to_string(size)+"_"+to_string(tmp_x+x*size)
                                +"_"+to_string(tmp_y+y*size)+"_"+to_string(tmp_grid.grid_id)
                                +".pcd";
            tmp_grid.grid_id_x = x;
            tmp_grid.gird_id_y = y;
            tmp_grid.lower_bound_x = tmp_x + size * x;
            tmp_grid.lower_bound_y = tmp_y + size * y;
            tmp_grid.upper_bound_x = tmp_x + size * (x+1);
            tmp_grid.upper_bound_y = tmp_y + size * (y+1);

#ifdef DEBUG_SUB_
            cout << "--------------- group --------------------" << endl;
            cout << tmp_grid.grid_id << " " << tmp_grid.lower_bound_x << " "
                 << tmp_grid.lower_bound_y << endl;
#endif

            grid_sum.push_back(tmp_grid);
        }
    }

    return 1;
}

void readPcd::organizeCloud(){
    const int size = grid_.grid_size;
    int _min_x = static_cast<int>(floor(grid_.min_x/size)*size);
    int _min_y = static_cast<int>(floor(grid_.min_y/size)*size);
    
    for(auto p = source_cloud.begin(); p != source_cloud.end(); p++){
        int tmp_x = static_cast<int>(floor((p->x-_min_x)/size));
        int tmp_y = static_cast<int>(floor((p->y-_min_y)/size));
        int tmp_id = tmp_x  + tmp_y * grid_.net_x;

        if(tmp_id == grid_sum[tmp_id].grid_id){
            grid_sum[tmp_id].cloud.push_back(*p);
        }else{
#ifdef DEBUG_SUB_
            cout << p->x << " " << p->y << endl;
            cout << tmp_id << " " << grid_sum[tmp_id].grid_id << endl;
#endif
            PCL_ERROR("Get error grid_id, couldn't add the point\n");
        }
    }
}

void readPcd::writeCloud(){
    if(grid_sum.size() <=0){
        PCL_ERROR("Error occurs, there is no grid map!");
        return;
    }

    ofstream ofs(scv_path+scv_name);
    
    cout << "\n--------------------------------\n";
    for(int index = 0; index < grid_sum.size(); index++){
        if(grid_sum[index].cloud.size() > 0){
            if(pcl::io::savePCDFileASCII(write_path+grid_sum[index].filename, grid_sum[index].cloud) == -1){
                PCL_ERROR("Couldn't save %d pcd file!", index);
                break;
            }else{
                ofs << grid_sum[index].filename << endl;
                cout << "write " << grid_sum[index].filename << " successful.\n";
            }
        }
        
    }
    cout << "---------------------------------\n";    
}

void readPcd::print_debug(){
    cout << "--------------------------------------" << endl;
    cout << "min_x   min_y   max_x   max_y" << endl;
    cout << grid_.min_x << " " << grid_.min_y << " " << grid_.max_x << " " << grid_.max_y << endl;
    cout << "--------------------------------------" << endl;
    cout << "net_x   net_y   net_num" << endl;
    cout << grid_.net_x << "    " << grid_.net_y << "    " << grid_.net_num << endl;
    cout << "--------------------------------------" << endl;
    cout << "From x to y" << endl;
    for(int i = 0; i < grid_sum.size(); i++){
        cout << grid_sum[i].filename << endl;
    }
}

void readPcd::loadConfig(){
    pcd_path = node["pcd_path"].as<string>();
    grid_.grid_size = node["grid_size"].as<int>();
    write_path = node["write_path"].as<string>();
    scv_path = node["scv_path"].as<string>();
    scv_name = node["scv_name"].as<string>();
}

string readPcd::get_pcd_path(){
    return pcd_path;
}

string readPcd::get_scv_name(){
    return scv_path+scv_name;
}

string readPcd::get_scv_path(){
    return scv_path;
}

