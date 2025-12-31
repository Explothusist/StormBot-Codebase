
#include "DriveCommand.h"

DriveCommand::DriveCommand(Drivetrain* drivetrain, amt::Joystick* driver_controller):
    amt::Command(),
    m_drivetrain{ drivetrain },
    m_driver_controller{ driver_controller }
{
    usesSubsystem(m_drivetrain);
};
DriveCommand::DriveCommand(DriveCommand& command):
    amt::Command(command)
{
    m_drivetrain = command.m_drivetrain;
    m_driver_controller = command.m_driver_controller;
};
DriveCommand::~DriveCommand() {
    // Will run ~Command() after this is complete
};

void DriveCommand::initialize() {

};
void DriveCommand::execute() {
    int rotation = m_driver_controller->getRawAxis(amt::Axis4);

    if (m_driver_controller->getButtonState(amt::L2Button) != amt::ButtonPressed) {
        rotation = 0; // Lock rotation unless holding Z-target
    }

    m_drivetrain->setDrive(
        m_driver_controller->getRawAxis(amt::Axis1),
        m_driver_controller->getRawAxis(amt::Axis2),
        rotation
    );
};
void DriveCommand::end(bool interrupted) {
    m_drivetrain->stopDrive();
};
bool DriveCommand::is_finished() {
    return false;
};