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
   Desc:   Example ros_control hardware interface that performs a perfect control loop for simulation
*/

#ifndef GENERIC_ROS_CONTROL__GENERIC_HARDWARE_INTERFACE_H
#define GENERIC_ROS_CONTROL__GENERIC_HARDWARE_INTERFACE_H

#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>
#include <controller_manager/controller_manager.h>
#include <boost/scoped_ptr.hpp>
#include <ros/ros.h>

namespace ros_control_boilerplate
{

// For simulation only - determines how fast a trajectory is followed
static const double POSITION_STEP_FACTOR = 1;
static const double VELOCITY_STEP_FACTOR = 1;

/// \brief Hardware interface for a robot
class GenericHardwareInterface: public hardware_interface::RobotHW
{
public:

  /**
   * \brief Constructor
   * \param nh - Node handle for topics.
   * \param joint_mode - method to control joints by: 0 - position, 1 - velocity, or 2 - effort
   */ 
  GenericHardwareInterface(ros::NodeHandle& nh, int joint_mode);

  /// \brief Initialize the hardware interface
  virtual void init();

  /// \brief Read the state from the robot hardware.
  virtual void read(ros::Duration elapsed_time);

  /// \brief write the command to the robot hardware.
  virtual void write(ros::Duration elapsed_time);

protected:

  // Startup and shutdown of the internal node inside a roscpp program
  ros::NodeHandle                              nh_;

  // Interfaces
  hardware_interface::JointStateInterface      joint_state_interface_;
  hardware_interface::PositionJointInterface   position_joint_interface_;
  hardware_interface::VelocityJointInterface   velocity_joint_interface_;
  hardware_interface::EffortJointInterface     effort_joint_interface_;

  // Shared memory
  std::vector<std::string>                     joint_names_;
  std::vector<double>                          joint_position_;
  std::vector<double>                          joint_velocity_;
  std::vector<double>                          joint_effort_;
  std::vector<double>                          joint_position_command_;
  std::vector<double>                          joint_velocity_command_;
  std::vector<double>                          joint_effort_command_;
  std::size_t                                  num_joints_;
  std::size_t                                  joint_mode_; // 0 - position, 1 - velocity, or 2 - effort

  // Simulated controller
  double                                       p_error_, v_error_, e_error_;

}; // class

} // namespace

#endif
