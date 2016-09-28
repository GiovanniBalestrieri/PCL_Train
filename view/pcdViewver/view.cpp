#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
    
int user_data;
    
void 
viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor (1.0, 0.5, 0.7);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere (o, 0.5, "sphere", 0);
    std::cout << "Added Sphere" << std::endl;
    
}
    
void 
viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape ("text", 0);
    viewer.addText (ss.str(), 50, 400, "text", 0);
    
    //FIXME: possible race condition here:
    user_data++;
}
    
int 
main(int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ> cloud1;
  pcl::PCDReader reader;
  // Fill in the cloud data
  cloud1.width    = 100000;
  cloud1.height   = 1;
  cloud1.is_dense = false;
  cloud1.points.resize (cloud1.width * cloud1.height);

  for (size_t i = 0; i < cloud1.points.size (); ++i)
  {
    cloud1.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud1.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud1.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
  }

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
//    pcl::io::loadPCDFile ("foto.pcd", *cloud);
    reader.read("foto.pcd",*cloud);
    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
    //blocks until the cloud is actually rendered
    viewer.showCloud(cloud);
    
    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer
    
    //This will only get called once
    viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
    //This will get called once per visualization iteration
    viewer.runOnVisualizationThread (viewerPsycho);
    while (!viewer.wasStopped ())
    {
    //you can also do cool processing here
    //FIXME: Note that this is running in a separate thread from viewerPsycho
    //and you should guard against race conditions yourself...
    user_data++;
    }
    return 0;
}

