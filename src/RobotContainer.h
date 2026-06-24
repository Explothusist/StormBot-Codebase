
#ifndef STORMBOT_CONTAINER_
#define STORMBOT_CONTAINER_

#include "stormbot_type.h"

#include "Automat/automat.h"
#include "Constants.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/CameraReader.h"
#include "subsystems/Wheel.h"

class RobotContainer {
    public:
        RobotContainer();
        ~RobotContainer();

        void configure_auto_triggers();
        void configure_bindings();

        static atmt::Command* getAutonomousCommand(int indicator, void* robot_container);
        static int getWhichAutonomousRoutine(void* robot_container);

        Drivetrain* m_drivetrain; // public because they are for Robot.cpp
        CameraReader* m_camera_reader;
        Wheel* m_wheel;

        atmt::Joystick* m_driver_controller;
        // atmt::Joystick* m_operator_controller;
        atmt::SerialReader* m_camera_serial;
        atmt::SerialReader* m_esp_serial;
        
#ifdef STORMBOT_STATE_MATCHED_
        atmt::Heartbeat_StateMatcher* m_heartbeat;
#endif
    private:
};


#endif