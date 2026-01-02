
#include "TeleopDriveCommand.h"

TeleopDriveCommand::TeleopDriveCommand(Drivetrain* drivetrain, atmt::Joystick* driver_controller):
    atmt::Command(),
    m_drivetrain{ drivetrain },
    m_driver_controller{ driver_controller }
{
    usesSubsystem(m_drivetrain);
};
TeleopDriveCommand::TeleopDriveCommand(TeleopDriveCommand& command):
    atmt::Command(command)
{
    m_drivetrain = command.m_drivetrain;
    m_driver_controller = command.m_driver_controller;
};
TeleopDriveCommand::~TeleopDriveCommand() {
    // Will run ~Command() after this is complete
};

void TeleopDriveCommand::initialize() {

};
void TeleopDriveCommand::execute() {
    int rotation = m_driver_controller->getRawAxis(atmt::Axis4);

    if (m_driver_controller->getButtonState(atmt::L2Button) != atmt::ButtonPressed) {
        rotation = 0; // Lock rotation unless holding Z-target
    }

    m_drivetrain->setDrive(
        m_driver_controller->getRawAxis(atmt::Axis1),
        m_driver_controller->getRawAxis(atmt::Axis2),
        rotation
    );
};
void TeleopDriveCommand::end(bool interrupted) {
    m_drivetrain->stopDrive();
};
bool TeleopDriveCommand::is_finished() {
    return false;
};