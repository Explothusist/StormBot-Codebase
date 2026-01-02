
#ifndef STORMBOT_TELEOPDRIVECOMMAND_
#define STORMBOT_TELEOPDRIVECOMMAND_

#include "../Automat/automat.h"
#include "../subsystems/Drivetrain.h"

class TeleopDriveCommand : public atmt::Command {
    public:
        TeleopDriveCommand(Drivetrain* drivetrain, atmt::Joystick* driver_controller); // Put subsystems as parameters
        TeleopDriveCommand(TeleopDriveCommand& command); // Copy constructor
        ~TeleopDriveCommand();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Drivetrain* m_drivetrain;
        atmt::Joystick* m_driver_controller;
};

#endif