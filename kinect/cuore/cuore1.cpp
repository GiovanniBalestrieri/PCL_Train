#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

void showHelp()
{
	puts("\nHelp:\n\n");
	puts("a - show cloud");
}
 
class SimpleOpenNIViewer
{
   public:
     SimpleOpenNIViewer () : viewer ("PCL OpenNI Viewer") {}

     void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud)
     {

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
	// Create the filtering object
        pcl::PassThrough<pcl::PointXYZ> pass;
        pass.setInputCloud (cloud);
        pass.setFilterFieldName ("z");
        pass.setFilterLimits (0.0, 1.0);
        //pass.setFilterLimitsNegative (true);
        pass.filter (*cloud_filtered);
        
	if (!viewer.wasStopped())
          viewer.showCloud (cloud);
	  pcl::io::savePCDFileASCII( "foto.pcd" , *cloud );
	  std::cerr << "Saved: " << cloud->points.size ()<<" data points.\n";
     }

     void run ()
     {
       pcl::Grabber* interface = new pcl::OpenNIGrabber();
       boost::function<void (const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f =
         boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

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
  pcl::PointCloud <pcl::PointXYZ> cloudDump;
  
	
  int c;
  puts ("\t\t_..::| Welcome StickAround |::.._\n");
  showHelp();
  do {
    c=getchar();
  } while (c != 'a');

   SimpleOpenNIViewer v;
   v.run ();
   
   return 0;
}


