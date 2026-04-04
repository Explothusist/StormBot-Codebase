
#include "RobotContainer.h"
#include "storm_serial_utils.h"

#include <vector>

#include "commands/DriveCommand.h"
#include "commands/TeleopDriveCommand.h"
#include "commands/ApproachAndAlign.h"
#include "commands/AlignAndPounce.h"
#include "commands/UpdateApriltag.h"
#include "commands/UpdateJoystick.h"

RobotContainer::RobotContainer():
    m_drivetrain{ new Drivetrain() },
    m_camera_reader{ new CameraReader() },
#ifdef STORMBOT_USE_VEX_CONTROLLER_
    m_driver_controller{ new atmt::Joystick(atmt::PollMode_Continuous, atmt::PrimaryJoystick) },
#endif
#ifdef STORMBOT_USE_SERIAL_ESP_CONTROLLER_
    m_driver_controller{ new atmt::Joystick(atmt::PollMode_Manual) },
#endif
    // m_operator_controller{ new atmt::Joystick(atmt::PartnerJoystick) }
    m_camera_serial{ new atmt::SerialReader(constants::serial::SerialAddress, constants::ports::SerialCameras_Port) },
    m_esp_serial{ new atmt::SerialReader(constants::serial::SerialAddress, constants::ports::SerialEsp_Port) }
#ifdef STORMBOT_STATE_MATCHED_
    ,m_heartbeat{ new atmt::Heartbeat_StateMatcher(constants::heartbeat::TimeoutMS, m_esp_serial, Serial_Heartbeat) }
#endif
{
    
};
RobotContainer::~RobotContainer() { // Actually deleted by atmt::TimedRobot
};


void RobotContainer::configure_auto_triggers() {
    m_driver_controller->bindAutoTrigger(new atmt::Trigger(atmt::AButton, atmt::ButtonPressed));
};
void RobotContainer::configure_bindings() {
    m_driver_controller->bindKey(
        (new atmt::Trigger(atmt::R1Button, atmt::ButtonPressed))->setType(atmt::WhileTrigger),
        new AlignAndPounce(m_drivetrain, m_camera_reader)
    );
    m_driver_controller->bindKey(
        (new atmt::Trigger(atmt::L1Button, atmt::ButtonPressed))->setType(atmt::WhileTrigger),
        new ApproachAndAlign(m_drivetrain, m_camera_reader, m_camera_serial)
    );

    // Serial
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
    
#ifdef STORMBOT_USE_SERIAL_ESP_CONTROLLER_
    m_esp_serial->bindToMessage(
        (new atmt::Trigger(atmt::SerialReceive, Serial_JoystickPacket))->allowPartial()->fromSender(Address_EspBot),
        new UpdateApriltag(m_camera_serial, m_camera_reader, TagCamera_Scoring)
    );
#endif
    
    // Default Commands
    m_drivetrain->setDefaultCommand(new TeleopDriveCommand(m_drivetrain, m_driver_controller));
};

atmt::Command* RobotContainer::getAutonomousCommand(int indicator, void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    switch (indicator) {
        case 0:
            return new atmt::EmptyCommand();

        case 1:
            return new atmt::SequentialCommandGroup({
                (new DriveCommand(self->m_drivetrain, 0.3, 0.0, 0.0))->withTimeout(2.0),
                new ApproachAndAlign(self->m_drivetrain, self->m_camera_reader, self->m_camera_serial)
            });
        
        default:
            return new atmt::EmptyCommand();
    }
};
int RobotContainer::getWhichAutonomousRoutine(void* robot_container) {
    RobotContainer* self = static_cast<RobotContainer*>(robot_container);
    return 0;
};