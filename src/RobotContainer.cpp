
#include "RobotContainer.h"
#include "storm_serial_utils.h"

#include <vector>

#include "commands/DriveCommand.h"
#include "commands/TeleopDriveCommand.h"
#include "commands/ApproachAndAlign.h"
#include "commands/AlignAndPounce.h"
#include "commands/UpdateApriltag.h"

RobotContainer::RobotContainer():
    m_drivetrain{ new Drivetrain() },
    m_camera_reader{ new CameraReader() },
    m_driver_controller{ new atmt::Joystick(atmt::PrimaryJoystick) },
    // m_operator_controller{ new atmt::Joystick(atmt::PartnerJoystick) }
    m_camera_serial{ new atmt::SerialReader(constants::serial::SerialAddress, constants::serial::SerialCamerasPort) },
    m_esp_serial{ new atmt::SerialReader(constants::serial::SerialAddress, constants::serial::SerialEspPort) }
{

};
RobotContainer::~RobotContainer() { // Actually deleted by atmt::TimedRobot
};

void RobotContainer::configure_bindings() {
    m_driver_controller->bindKey(
        (new atmt::Trigger(atmt::R1Button, atmt::ButtonPressed))->setType(atmt::WhileTrigger),
        new AlignAndPounce(m_drivetrain, m_camera_reader)
    );

    m_camera_serial->bindToMessage(
        (new atmt::Trigger(atmt::SerialReceive, Serial_IsSingleDetection))->allowPartial()->fromSender(Address_Camera_1_Front),
        new UpdateApriltag(m_camera_serial, m_camera_reader, TagCamera_Front)
    );
    m_camera_serial->bindToMessage(
        (new atmt::Trigger(atmt::SerialReceive, Serial_IsSingleDetection))->allowPartial()->fromSender(Address_Camera_2_Right),
        new UpdateApriltag(m_camera_serial, m_camera_reader, TagCamera_Right)
    );
    m_camera_serial->bindToMessage(
        (new atmt::Trigger(atmt::SerialReceive, Serial_IsSingleDetection))->allowPartial()->fromSender(Address_Camera_3_Back),
        new UpdateApriltag(m_camera_serial, m_camera_reader, TagCamera_Back)
    );
    m_camera_serial->bindToMessage(
        (new atmt::Trigger(atmt::SerialReceive, Serial_IsSingleDetection))->allowPartial()->fromSender(Address_Camera_4_Left),
        new UpdateApriltag(m_camera_serial, m_camera_reader, TagCamera_Left)
    );
    m_camera_serial->bindToMessage(
        (new atmt::Trigger(atmt::SerialReceive, Serial_IsSingleDetection))->allowPartial()->fromSender(Address_Camera_5_Scoring),
        new UpdateApriltag(m_camera_serial, m_camera_reader, TagCamera_Scoring)
    );
    
    m_drivetrain->setDefaultCommand(new TeleopDriveCommand(m_drivetrain, m_driver_controller));
};

atmt::Command* RobotContainer::getAutonomousCommand() {
    return new atmt::SequentialCommandGroup({
        (new DriveCommand(m_drivetrain, 0.3, 0.0, 0.0))->withTimeout(2.0),
        new ApproachAndAlign(m_drivetrain, m_camera_reader)
    });
};