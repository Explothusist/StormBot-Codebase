
#include "TeleopDriveCommand.h"

#include <cmath>
#include "../Constants.h"

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
atmt::Command* TeleopDriveCommand::cloneSelf() const {
    return new TeleopDriveCommand(m_drivetrain, m_driver_controller);
};

void TeleopDriveCommand::initialize() {

};
void TeleopDriveCommand::execute() {
    int rotation = 0;

    if (m_driver_controller->getButtonState(atmt::L2Button) != atmt::ButtonPressed) {
        // rotation = 0; // Lock rotation unless holding Z-target
        double heading = m_drivetrain->getHeading();
        if (heading > 180) {
            heading -= 360;
        }
        if (std::abs(heading) > constants::drivetrain::RotationCorrect_Threshold) {
            // double min_speed = constants::drivetrain::RotationCorrect_MinSpeed;
            // double obj_percent_pos = std::min(std::abs(heading) / constants::drivetrain::RotationCorrect_Range, 1.0);
            // double bonus_speed = constants::drivetrain::RotationCorrect_MaxSpeed - constants::drivetrain::RotationCorrect_MinSpeed;
            // double sign = heading != 0 ? -heading / std::abs(heading) : 1;

            // rotation = (min_speed + (obj_percent_pos * bonus_speed)) * 100 * sign; // in percentage
            rotation = static_cast<int>(atmt::getProportional(
                heading, 
                constants::drivetrain::RotationCorrect_Threshold, 
                constants::drivetrain::RotationCorrect_Range,
                constants::drivetrain::RotationCorrect_MinSpeed,
                constants::drivetrain::RotationCorrect_MaxSpeed
            ) * -1 * 100);
#ifdef AUTOMAT_VEX_ // DEBUG
        atmt::m_brain.Screen.print("Rotation: %d ", rotation);
#endif
        }
    }else {
        rotation = m_driver_controller->getRawAxis(atmt::RXAxis) * 100;
    }

    m_drivetrain->setDrive(
        m_driver_controller->getRawAxis(atmt::LXAxis) * 100,
        m_driver_controller->getRawAxis(atmt::LYAxis) * 100,
        rotation
    );
};
void TeleopDriveCommand::end(bool interrupted) {
    m_drivetrain->stopDrive();
};
bool TeleopDriveCommand::is_finished() {
    return false;
};