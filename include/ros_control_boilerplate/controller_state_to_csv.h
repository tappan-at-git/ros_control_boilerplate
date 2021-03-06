/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, University of Colorado, Boulder
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Univ of CO, Boulder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Dave Coleman
   Desc:   Records a ros_control ControllerState data to CSV for Matlab/etc analysis
*/

// ROS
#include <ros/ros.h>

// ros_control
#include <control_msgs/JointTrajectoryControllerState.h>

namespace ros_control_boilerplate
{

static const double RECORD_RATE_HZ = 100.0; // times per second to record

class ControllerStateToCSV
{
public:

  /**
   * \brief Constructor
   * \param verbose - run in debug mode
   * \param topic - ROS message to listen to from controller
   */
  ControllerStateToCSV(bool verbose, const std::string& topic);

  /** \brief Callback from ROS message */
  void stateCB(const control_msgs::JointTrajectoryControllerState::ConstPtr& state);

  /** \brief Start the data collection */
  void startRecording(const std::string& file_name);

  /** \brief Recieve data from controller via ROS message */
  void update(const ros::TimerEvent& e);

  /** \brief End recording */
  void stopRecording();

  /** \brief Send all resulting data to file */
  bool writeToFile();

private:

  // A shared node handle
  ros::NodeHandle nh_;

  // Listener to state of controller
  ros::Subscriber state_sub_;

  // Show more visual and console output, with general slower run time.
  bool verbose_;

  // Where to save the CSV
  std::string file_name_;

  // Buffer of controller state data
  std::vector<control_msgs::JointTrajectoryControllerState> controller_states_;
  std::vector<ros::Time> timestamps_;

  // Cache of last recieved state
  control_msgs::JointTrajectoryControllerState controller_state_;

  // Show status info on first update
  bool first_update_;

  // How often to sample the state
  ros::Timer non_realtime_loop_;

}; // end class

// Create boost pointers for this class
typedef boost::shared_ptr<ControllerStateToCSV> ControllerStateToCSVPtr;
typedef boost::shared_ptr<const ControllerStateToCSV> ControllerStateToCSVConstPtr;

} // end namespace
