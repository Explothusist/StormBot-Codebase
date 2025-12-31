/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cedric Serio                                              */
/*    Created:      12/20/2025, 2:52:29 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "Automat/automat.h"
#include "StormBot.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/CameraReader.h"

#include "commands/DriveCommand.h"


StormBot* m_robot{ new StormBot() };
Drivetrain* m_drivetrain{ new Drivetrain() };
CameraReader* m_camera_reader{ new CameraReader() };

atmt::Joystick* m_driver_controller{ new atmt::Joystick(atmt::PrimaryJoystick) };
atmt::Joystick* m_operator_controller{ new atmt::Joystick(atmt::PartnerJoystick) };


int main() {

    m_drivetrain->setDefaultCommand(new DriveCommand(m_drivetrain, m_driver_controller));

    m_robot->registerSubsystem(m_drivetrain);
    m_robot->registerSubsystem(m_camera_reader);

    m_robot->addJoystick(m_driver_controller);
    m_robot->addJoystick(m_operator_controller);



    m_robot->startLoop();

};
