/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Cedric Serio                                              */
/*    Created:      12/20/2025, 2:52:29 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include "FRClib/frclib_vex.h"
#include "StormBot.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/CameraReader.h"

#include "commands/DriveCommand.h"


StormBot* m_robot{ new StormBot() };
Drivetrain* m_drivetrain{ new Drivetrain() };
CameraReader* m_camera_reader{ new CameraReader() };

frclib::Joystick* m_driver_controller{ new frclib::Joystick(frclib::PrimaryJoystick) };
frclib::Joystick* m_operator_controller{ new frclib::Joystick(frclib::PartnerJoystick) };


int main() {

    m_drivetrain->setDefaultCommand(new DriveCommand(m_drivetrain, m_driver_controller));

    m_robot->registerSubsystem(m_drivetrain);
    m_robot->registerSubsystem(m_camera_reader);

    m_robot->addJoystick(m_driver_controller);
    m_robot->addJoystick(m_operator_controller);



    m_robot->startLoop();

};
