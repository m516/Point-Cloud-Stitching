#include <iostream>
#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/io/ply_io.h>

// This function displays the help
void
showHelp(char* program_name)
{
    std::cout << std::endl;
    std::cout << "Usage: " << program_name << " cloud_source.[pcd|ply] cloud_target.[pcd|ply]" << std::endl;
    std::cout << "-h:  Show this help." << std::endl;
}


int
main(int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZ>(5, 1));
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_tr(new pcl::PointCloud<pcl::PointXYZ>);



    // Show help
    if (pcl::console::find_switch(argc, argv, "-h") || pcl::console::find_switch(argc, argv, "--help")) {
        showHelp(argv[0]);
        return 0;
    }
    // Fetch point cloud filename in arguments | Works with PCD and PLY files
    std::vector<int> filenames, t;
    bool file_is_pcd = false;
    filenames = pcl::console::parse_file_extension_argument(argc, argv, ".ply");
    t = pcl::console::parse_file_extension_argument(argc, argv, ".pcd");
    filenames.insert(filenames.end(), t.begin(), t.end());
    if (filenames.size() != 2) {
        std::cout << filenames.size() << " files were given. Expecting 2." << std::endl;
        showHelp(argv[0]);
        return -1;
    }
    // Load files | Works with PCD and PLY files
    if (pcl::io::loadPCDFile(argv[filenames[0]], *cloud_in) < 0) {
        if (pcl::io::loadPLYFile(argv[filenames[0]], *cloud_in) < 0) {
            std::cout << "Error loading point cloud " << argv[filenames[0]] << std::endl << std::endl;
            showHelp(argv[0]);
            return -1;
        }
    }
    if (pcl::io::loadPCDFile(argv[filenames[1]], *cloud_tr) < 0) {
        if (pcl::io::loadPLYFile(argv[filenames[1]], *cloud_tr) < 0) {
            std::cout << "Error loading point cloud " << argv[filenames[1]] << std::endl << std::endl;
            showHelp(argv[0]);
            return -1;
        }
    }
    // Get the number of iterations


    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(cloud_in);
    icp.setInputTarget(cloud_tr);

    pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);

    std::cout << "has converged:" << icp.hasConverged() << " score: " <<
        icp.getFitnessScore() << std::endl;
    std::cout << icp.getFinalTransformation() << std::endl;

    return (0);
}

