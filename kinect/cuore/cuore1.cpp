#include <iostream>
#include <pcl/conversions.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

bool filterPass = false;

void showHelp()
{
	puts("\nHelp:\n\n");
	puts("a - show cloud");
}
 
class SimpleOpenNIViewer
{
   public:
     SimpleOpenNIViewer () : viewer ("PCL OpenNI Viewer") {}

     void cloud_cb_ (const pcl::PointCloud<pcl::PCLPointCloud2>::ConstPtr &cloud)
     {

  pcl::PointCloud<pcl::PCLPointCloud2>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PCLPointCloud2>);
	
	if (filterPass)
	{
	/*
		// Create the filtering object
	        pcl::PassThrough<pcl::PointXYZ> pass;
	        pass.setInputCloud (cloud);
	        pass.setFilterFieldName ("z");
	        pass.setFilterLimits (0.0, 1.4);
	        //pass.setFilterLimitsNegative (true);
	        pass.filter (*cloud_filtered);
	*/
        }

	if (!viewer.wasStopped())
	{
	  pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
	  //pcl::fromPCLPointCloud2(pcl_pc2,*temp_cloud);
	  sor.setInputCloud (cloud);
          sor.setLeafSize (0.01f, 0.01f, 0.01f);
          sor.filter (*cloud_filtered);
     
          viewer.showCloud (cloud_filtered);
	}
	pcl::PCDWriter writer;
	  writer.write("foto.pcd",*cloud,false);
	  std::cerr << "Saved: " << cloud->points.size ()<<" data points.\n";
     }

     void run ()
     {
       pcl::Grabber* interface = new pcl::OpenNIGrabber();
       boost::function<void (const pcl::PointCloud::<pcl::PCLPointCloud2>ConstPtr&)> f =
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


