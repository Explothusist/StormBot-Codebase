
#include "DriveCommand.h"

DriveCommand::DriveCommand(Drivetrain* drivetrain, frclib::Joystick* driver_controller):
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
    m_driver_controller = command.m_driver_controller;
};
DriveCommand::~DriveCommand() {
    // Will run ~Command() after this is complete
};

void DriveCommand::initialize() {

};
void DriveCommand::execute() {
    int rotation = m_driver_controller->getRawAxis(frclib::Axis4);

    if (m_driver_controller->getButtonState(frclib::L2Button) != frclib::ButtonPressed) {
        rotation = 0; // Lock rotation unless holding Z-target
    }

    m_drivetrain->setDrive(
        m_driver_controller->getRawAxis(frclib::Axis1),
        m_driver_controller->getRawAxis(frclib::Axis2),
        rotation
    );
};
void DriveCommand::end(bool interrupted) {
    m_drivetrain->stopDrive();
};
bool DriveCommand::is_finished() {
    return false;
};