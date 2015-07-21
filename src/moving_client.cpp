#include <ros/ros.h>
#include <fstream>
#include <string>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main (int argc, char** argv)
{
    std::ifstream file(argv[1]);
    std::string line;
    double numbers[21];
    int count = 0;
    while(std::getline(file,line))
    {
        numbers[count] = atof(line.c_str());
        count++;
    }

    ros::init(argc, argv, "test_movement");

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0)) && ros::ok())
    {
        ROS_INFO("Waiting");
    }

    while(ros::ok())
    {

        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = numbers[0];
        goal.target_pose.pose.position.y = numbers[1];
        goal.target_pose.pose.position.z = numbers[2];
        goal.target_pose.pose.orientation.x = numbers[3];
        goal.target_pose.pose.orientation.y = numbers[4];
        goal.target_pose.pose.orientation.z = numbers[5];
        goal.target_pose.pose.orientation.w = numbers[6];

        ROS_INFO("Sending First Goal");
        ac.sendGoal(goal);

        ac.waitForResult();

        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            goal.target_pose.pose.position.x = numbers[7];
            goal.target_pose.pose.position.y = numbers[8];
            goal.target_pose.pose.position.z = numbers[9];
            goal.target_pose.pose.orientation.x = numbers[10];
            goal.target_pose.pose.orientation.y = numbers[11];
            goal.target_pose.pose.orientation.z = numbers[12];
            goal.target_pose.pose.orientation.w = numbers[13];

            ROS_INFO("Sending Second Goal");
            ac.sendGoal(goal);

            ac.waitForResult();

            if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            {
                ROS_INFO("Success");
            }
            else
            {
                ROS_INFO("Error");
            }
        }
        else
        {
            ROS_INFO("Error");
        }
    }
    return 0;
}
