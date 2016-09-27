#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>



 class SimpleOpenNIViewer
 {
   public:
     SimpleOpenNIViewer () : viewer ("PCL OpenNI Viewer") {}

     void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
     {
	//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered( new pcl::PointCloud<pcl::PointXYZ>);
	//pcl::PCLPointCloudConstPtr cloudPtr(cloud1);
	//pcl_conversions::toPCL(*cloud,*cloud1)
	//pcl::VoxelGrid<pcl::PointXYZ> sor;
	//sor.setInputCloud (cloud);
	//sor.setLeafSize (0.01f, 0.01f, 0.01f);
	//sor.filter (*cloud_filtered);

       if (!viewer.wasStopped())
       {  // Create the filtering object
 	viewer.showCloud (cloud);
	}
     }

     void run ()
     {
       pcl::Grabber* interface = new pcl::OpenNIGrabber();

       boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f =  boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

       interface->registerCallback (f);
       interface->start ();

       while (!viewer.wasStopped())
       {
         boost::this_thread::sleep (boost::posix_time::seconds (1));
       }
       interface->stop ();
     }
     pcl::visualization::CloudViewer viewer;
 };

 int main ()
 {
   SimpleOpenNIViewer v;
   v.run ();
   return 0;
 }
