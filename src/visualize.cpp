#include "visualize.h"

// #define DEBUG_SUB_

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> rand_(0,255);


void Visualize::loadPcd(){
    string scv_name = rP.get_scv_name(); 
    ifstream ifs(scv_name);

    if(!ifs.is_open()){
        cout << "fail to open the file!" << endl;
    }

    string tmp_str;
    while(ifs >> tmp_str){
        filenames.push_back(rP.get_scv_path()+tmp_str);
    }

}

void Visualize::show(){
    // pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_ptr (new pcl::PointCloud<pcl::PointXYZI> ());
    // cloud = *cloud_ptr;
    // cloud_ptr = cloud.makeShared();

    int cnt = 0;
    pcl::PointCloud<pcl::PointXYZI>::Ptr tmp_cloud(new pcl::PointCloud<pcl::PointXYZI> ());
    pcl::visualization::PCLVisualizer viewer ("map viewer");

    for(int i=0; i < filenames.size(); i++){
        if(pcl::io::loadPCDFile(filenames[i], *tmp_cloud) < 0){
            PCL_ERROR("Load pointcloud file %s error!", filenames[i]);
            continue;
        }else{
            PCL_INFO("load pcd successfully, points is %d. \n", tmp_cloud->points.size());
        }
        pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZI> cloud_color_handler (tmp_cloud, rand_(gen), rand_(gen), rand_(gen));
        viewer.addPointCloud<pcl::PointXYZI>(tmp_cloud, cloud_color_handler, "cloud"+to_string(cnt));
        viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1.0, "cloud"+to_string(cnt));
        cnt++;
    }
    while (!viewer.wasStopped ()) { // 在按下 "q" 键之前一直会显示窗口
        viewer.spinOnce ();
    }
}


void Visualize::print_test(){

#ifdef DEBUG_SUB_
    for(int i=0; i < filenames.size(); i++){
        cout << filenames[i] << endl;
    }
#endif
}