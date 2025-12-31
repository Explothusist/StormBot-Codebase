
#ifndef STORMBOT_DRIVECOMMAND_
#define STORMBOT_DRIVECOMMAND_

#include "../Automat/automat.h"
#include "../subsystems/Drivetrain.h"

class DriveCommand : public atmt::Command {
    public:
        DriveCommand(Drivetrain* drivetrain, atmt::Joystick* driver_controller); // Put subsystems as parameters
        DriveCommand(DriveCommand& command); // Copy constructor
        ~DriveCommand();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Drivetrain* m_drivetrain;
        atmt::Joystick* m_driver_controller;
};

#endif