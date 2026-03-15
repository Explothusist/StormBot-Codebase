
#include "RobotContainer.h"

#include <vector>

#include "commands/DriveCommand.h"
#include "commands/TeleopDriveCommand.h"
#include "commands/ApproachAndAlign.h"
#include "commands/AlignAndPounce.h"

RobotContainer::RobotContainer():
    m_drivetrain{ new Drivetrain() },
    m_camera_reader{ new CameraReader() },
    m_driver_controller{ new atmt::Joystick(atmt::PrimaryJoystick) }//,
    // m_operator_controller{ new atmt::Joystick(atmt::PartnerJoystick) }
{

};
RobotContainer::~RobotContainer() { // Actually deleted by atmt::TimedRobot
};

void RobotContainer::configure_bindings() {
    m_driver_controller->bindKey(
        (new atmt::Trigger(atmt::R1Button, atmt::ButtonPressed))->setType(atmt::WhileTrigger),
        new AlignAndPounce(m_drivetrain, m_camera_reader)
    );
    
    m_drivetrain->setDefaultCommand(new TeleopDriveCommand(m_drivetrain, m_driver_controller));
};

atmt::Command* RobotContainer::getAutonomousCommand() {
    return new atmt::SequentialCommandGroup({
        (new DriveCommand(m_drivetrain, 0.3, 0.0, 0.0))->withTimeout(2.0),
        new ApproachAndAlign(m_drivetrain, m_camera_reader)
    });
};