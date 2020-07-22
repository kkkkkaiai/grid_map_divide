#include "readPcd.h"
#include <random>

class Visualize{
public:
    void loadPcd();
    void show();
    void print_test();

private:
    readPcd rP;
    pcl::PointCloud<pcl::PointXYZI> cloud;
    vector<string> filenames;
};