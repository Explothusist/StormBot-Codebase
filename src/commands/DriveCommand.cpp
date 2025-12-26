
#include "DriveCommand.h"

namespace frclib {

    DriveCommand::DriveCommand(Drivetrain* drivetrain, Joystick* driver_controller):
        Command(),
        m_drivetrain{ drivetrain },
        m_driver_controller{ driver_controller }
    {
        usesSubsystem(m_drivetrain);
    };
    DriveCommand::DriveCommand(DriveCommand& command):
        Command(command)
    {
        m_drivetrain = command.m_drivetrain;
    };
    DriveCommand::~DriveCommand() {
        // Will run ~Command() after this is complete
    };

    void DriveCommand::initialize() {

    };
    void DriveCommand::execute() {
        m_drivetrain->setDrive(
            m_driver_controller->getRawAxis(frclib::Axis1),
            m_driver_controller->getRawAxis(frclib::Axis2),
            m_driver_controller->getRawAxis(frclib::Axis4)
        );
    };
    void DriveCommand::end(bool interrupted) {
        m_drivetrain->stopDrive();
    };
    bool DriveCommand::is_finished() {
        return false;
    };

};