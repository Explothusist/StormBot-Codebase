
#ifndef STORMBOT_ALIGN_AND_POUNCE_
#define STORMBOT_ALIGN_AND_POUNCE_

#include "../Automat/Command.h"
#include "../subsystems/Drivetrain.h"
#include "../subsystems/CameraReader.h"

class AlignAndPounce : public atmt::Command {
    public:
        AlignAndPounce(Drivetrain* drivetrain, CameraReader* cameras); // Put subsystems as parameters
        AlignAndPounce(AlignAndPounce& command); // Copy constructor
        ~AlignAndPounce();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Drivetrain* m_drivetrain;
        CameraReader* m_cameras;

        int m_check_dist_counter;
        double m_last_dist;
        int m_last_offset; // x
        int m_invisibility_count;
};

#endif