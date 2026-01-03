
#include "RobotContainer.h"

#include <vector>

#include "commands/DriveCommand.h"
#include "commands/TeleopDriveCommand.h"
#include "commands/ApproachAndAlign.h"
#include "commands/AlignAndPounce.h"

RobotContainer::RobotContainer():
    m_drivetrain{ new Drivetrain() },
    m_camera_reader{ new CameraReader() },
    m_driver_controller{ new atmt::Joystick(atmt::PrimaryJoystick) },
    m_operator_controller{ new atmt::Joystick(atmt::PartnerJoystick) }
{

};
RobotContainer::~RobotContainer() {
    delete m_drivetrain;
    m_drivetrain = nullptr;
    delete m_camera_reader;
    m_camera_reader = nullptr;
    delete m_driver_controller;
    m_driver_controller = nullptr;
    delete m_operator_controller;
    m_operator_controller = nullptr;
};

void RobotContainer::configure_bindings() {
    m_driver_controller->bindKey(atmt::R2Button, atmt::ButtonPressed, atmt::WhileTrigger, new ApproachAndAlign(m_drivetrain, m_camera_reader));
    m_driver_controller->bindKey(atmt::R1Button, atmt::ButtonPressed, atmt::WhileTrigger, new AlignAndPounce(m_drivetrain, m_camera_reader));
    
    m_drivetrain->setDefaultCommand(new TeleopDriveCommand(m_drivetrain, m_driver_controller));
};

atmt::Command* RobotContainer::getAutonomousCommand() {
    // std::vector<atmt::Command*> commands = 
    return new atmt::SequentialCommandGroup({
        (new DriveCommand(m_drivetrain, 0.3, 0.0, 0.0))->withTimeout(2.0),
        new ApproachAndAlign(m_drivetrain, m_camera_reader)
    });
};