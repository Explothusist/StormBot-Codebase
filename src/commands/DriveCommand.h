
#ifndef STORMBOT_DRIVECOMMAND_
#define STORMBOT_DRIVECOMMAND_

#include "../Automat/automat.h"
#include "../subsystems/Drivetrain.h"

class DriveCommand : public atmt::Command {
    public:
        DriveCommand(Drivetrain* drivetrain, double x_power, double y_power, double r_power); // Put subsystems as parameters
        DriveCommand(DriveCommand& command); // Copy constructor
        ~DriveCommand();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Drivetrain* m_drivetrain;
        double m_x_power;
        double m_y_power;
        double m_r_power;
};

#endif