
#ifndef STORMBOT_CONSTANTS_
#define STORMBOT_CONSTANTS_

#include "vex.h"

namespace constants {

    // Robot
    int const AutonomousLength = 30; // Seconds

    // Drivetrain
    int const MotorBL_Port = vex::PORT1;
    int const MotorBR_Port = vex::PORT2;
    int const MotorFL_Port = vex::PORT3;
    int const MotorFR_Port = vex::PORT4;

    int const Gyro_Port = vex::PORT5;

    double const Drivetrain_Speed = 0.30; // Percent

    // Drivetrain Align
    double const Min_Speed_To_Move = 0.12; // Determine experimentally

    double const Align_Max_Speed_LR = 0.30; // Gradient, Left/Right
    double const Align_Min_Speed_FB = Min_Speed_To_Move + 0.4;
    double const Align_Max_Speed_FB = 0.30; // Gradient, Forward/Backward

    double const Align_Slow_At_Distance = 12; // in inches

    double const Align_Epsilon_LR = 20.0; // In camera pixels
    double const Align_Epsilon_FB = 2.0; // In inches

    // Camera
    int const CameraFront_Port = vex::PORT6;
    // int const CameraLeft_Port = vex::PORT2;
    // int const CameraRight_Port = vex::PORT3;

    int const Camera_Viewport_Width = 320; // In camera pixels
    int const Camera_Viewport_Height = 240; // In camera pixels

    double const Camera_FOV_Horizontal = 74.0; // In degrees
    double const Camera_FOV_Vertical = 63.0; // In degrees

    // Camera Apriltag
    // int const Apriltag_Apparent_Width = 30; // In pixels when against the scoring element
    // int const Apriltag_Apparent_Height = 30; // Determine experimentally
    
    double const Apriltag_Actual_Width = 2.0; // In inches
    double const Apriltag_Actual_Height = 2.0; // In inches

    double const ColorRect_Actual_Width = 8.0; // In inches
    double const ColorRect_Actual_Height = 2.0; // In inches

    double const ColorRect_Insignificant = 20; // In camera pixels

};

#endif