
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

        void configure_bindings();

        atmt::Command* getAutonomousCommand();

        Drivetrain* m_drivetrain; // public because they are for Robot.cpp
        CameraReader* m_camera_reader;

        atmt::Joystick* m_driver_controller;
        atmt::Joystick* m_operator_controller;
    private:
};


#endif