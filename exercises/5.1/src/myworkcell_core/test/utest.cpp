#include <ros/time.h>
#include <ros/ros.h>
#include <gtest/gtest.h>
#include <iostream>

#include <fake_ar_publisher/ARMarker.h>

class BaseTest
{
public:
    BaseTest(ros::NodeHandle& nh)
    {
        ar_sub_ = nh.subscribe<fake_ar_publisher::ARMarker>("ar_pose_marker", 1,
        &BaseTest::ar_callback, this);
    }

    void ar_callback(const fake_ar_publisher::ARMarkerConstPtr& msg)
    {
        last_msg_ = msg;
    }

    ros::Subscriber ar_sub_;
    fake_ar_publisher::ARMarkerConstPtr last_msg_;
};

TEST(TestSuite, ar_z_position_test)
{
  ros::NodeHandle nh;
  ros::Duration(10).sleep();
  BaseTest basetester(nh);
  if(basetester.ar_sub_.getNumPublishers()==0){
    ASSERT_FALSE(true);
  }
  else{
    ROS_INFO_STREAM(basetester.last_msg_->pose.pose.position.z);
    ASSERT_TRUE(basetester.last_msg_->pose.pose.position.z==0.5);
  }
  ros::spin();
}

int main(int argc, char **argv){
  ros::init(argc, argv, "myworkscell_test_node");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
