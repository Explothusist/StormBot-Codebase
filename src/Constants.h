
#ifndef STORMBOT_CONSTANTS_
#define STORMBOT_CONSTANTS_

#include "vex.h"
#include "storm_serial_utils.h"

namespace constants {

    namespace robot {
        // int const AutonomousLength = 30; // Seconds
        int const AutonomousLength = 3; // Seconds
    };

    namespace serial {
        int const SerialAddress = Address_VexBot;
    };

    namespace ports {
        int const MotorBL_Port = vex::PORT2;
        int const MotorBR_Port = vex::PORT20;
        int const MotorFL_Port = vex::PORT10;
        int const MotorFR_Port = vex::PORT1;
        int const Gyro_Port = vex::PORT3;
        
        int const Wheel_Port = vex::PORT4;

        int const SerialCameras_Port = vex::PORT15;
        // int const SerialEsp_Port = vex::PORT16;
        int const SerialEsp_Port = 15;

        int const CameraFront_Port = vex::PORT19;
    }

    namespace drivetrain {
        double const Drivetrain_Speed = 1.0; // Percent

        double const RotationCorrect_Threshold = 1.0; // Degrees
        double const RotationCorrect_MinSpeed = 0.02;
        double const RotationCorrect_MaxSpeed = 0.18;
        double const RotationCorrect_Range = 30.0; // Degrees

        namespace align {
            double const Min_Speed_To_Move = 0.03; // Determine experimentally

            double const Align_Max_Speed_LR = 0.20; // Gradient, Left/Right
            double const Align_Min_Speed_FB = Min_Speed_To_Move + 0.0;
            double const Align_Max_Speed_FB = 0.20; // Gradient, Forward/Backward

            double const Align_Slow_At_Distance = 12.0; // in inches

            double const Align_Epsilon_LR = 20.0; // In camera pixels
            double const Align_Epsilon_FB = 2.0; // In inches

            double const Pounce_Max_Speed_LR = 0.50;
            double const Pounce_Min_Speed_FB = Min_Speed_To_Move;
            double const Pounce_Max_Speed_FB = 0.20;

            double const Pounce_Slow_At_Distance = 12.0;
            double const Pounce_Stop_At_Distance = 2.0;
            double const Pounce_Epsilon_LR = 20.0;
            double const Pounce_Epsilon_FB = 2.0;
        };
    };
    
    namespace camera {
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

        double const Battery_Actual_Width = 1.66; // In inches
        double const Battery_Actual_Height = 6.0; // In inches

        double const ColorRect_Insignificant = 20; // In camera pixels
        double const AprilTag_Insignificant = 10; // In camera pixels
        double const Battery_Insignificant = 20; // In camera pixels
    };

    namespace serial {
        int const Serial_Baudrate = 115200;
    };

    namespace heartbeat {
        int const TimeoutMS = 750;
    };

};

#endif