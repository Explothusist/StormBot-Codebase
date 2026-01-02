
#include "DriveCommand.h"

#include <cmath>

DriveCommand::DriveCommand(Drivetrain* drivetrain, double x_power, double y_power, double r_power):
    atmt::Command(),
    m_drivetrain{ drivetrain },
    m_x_power{ x_power },
    m_y_power{ y_power },
    m_r_power{ r_power }
{
    usesSubsystem(m_drivetrain);
};
DriveCommand::DriveCommand(DriveCommand& command):
    atmt::Command(command)
{
    m_drivetrain = command.m_drivetrain;
    m_x_power = command.m_x_power;
    m_y_power = command.m_y_power;
    m_r_power = command.m_r_power;
};
DriveCommand::~DriveCommand() {
    // Will run ~Command() after this is complete
};

void DriveCommand::initialize() {
    m_drivetrain->setDrive(
        static_cast<int>(std::round(m_x_power * 100)),
        static_cast<int>(std::round(m_y_power * 100)),
        static_cast<int>(std::round(m_r_power * 100))
    );
};
void DriveCommand::execute() {

};
void DriveCommand::end(bool interrupted) {
    m_drivetrain->stopDrive();
};
bool DriveCommand::is_finished() {
    return false;
};