
#ifndef STORMBOT_CONTAINER_
#define STORMBOT_CONTAINER_

#include "Automat/automat.h"
#include "Constants.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/CameraReader.h"

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

        atmt::Joystick* m_driver_controller;
        // atmt::Joystick* m_operator_controller;
        atmt::SerialReader* m_camera_serial;
        atmt::SerialReader* m_esp_serial;
    private:
};


#endif