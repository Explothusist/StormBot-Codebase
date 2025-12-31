
#ifndef STORMBOT_DRIVECOMMAND_
#define STORMBOT_DRIVECOMMAND_

#include "../Automat/automat.h"
#include "../subsystems/Drivetrain.h"

class DriveCommand : public amt::Command {
    public:
        DriveCommand(Drivetrain* drivetrain, amt::Joystick* driver_controller); // Put subsystems as parameters
        DriveCommand(DriveCommand& command); // Copy constructor
        ~DriveCommand();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Drivetrain* m_drivetrain;
        amt::Joystick* m_driver_controller;
};

#endif