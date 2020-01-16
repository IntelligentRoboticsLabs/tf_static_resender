#include "ros/ros.h"
#include <tf2_msgs/TFMessage.h>

class TFStaticResender
{
public:
	TFStaticResender(): n_()
	{
		tf_static_sub_ = n_.subscribe("/tf_static", 1, &TFStaticResender::tfStaticCallback, this);
    tf_static_pub_ = n_.advertise<tf2_msgs::TFMessage>("/tf", 1);
    tf_ready = false;
	}

	void tfStaticCallback(const tf2_msgs::TFMessage::ConstPtr& msg)
	{
    tf_ready = true;
    tf_list_.push_back(*msg);
	}

  void step()
	{
    if (tf_ready)
    {
      for(auto & tf : tf_list_)
      {
        for(auto & msg : tf.transforms)
          msg.header.stamp = ros::Time::now();
        tf_static_pub_.publish(tf);
      }
    }
	}

private:
	ros::NodeHandle n_;
	ros::Subscriber tf_static_sub_;
  ros::Publisher tf_static_pub_;
  bool tf_ready;
  std::vector<tf2_msgs::TFMessage> tf_list_;

};

int main(int argc, char **argv)
{

  ros::init(argc, argv, "tf_static_resender");
  ros::NodeHandle n;

  TFStaticResender tf_static_resender;
  ros::Rate loop_rate(100);

  while (ros::ok())
  {
    tf_static_resender.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
 }
