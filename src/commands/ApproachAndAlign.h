
#ifndef STORMBOT_APPROACH_AND_ALIGN_
#define STORMBOT_APPROACH_AND_ALIGN_

#include "../FRClib/Command.h"
#include "../subsystems/Drivetrain.h"
#include "../subsystems/CameraReader.h"

class ApproachAndAlign : public frclib::Command {
    public:
        ApproachAndAlign(Drivetrain* drivetrain, CameraReader* cameras); // Put subsystems as parameters
        ApproachAndAlign(ApproachAndAlign& command); // Copy constructor
        ~ApproachAndAlign();

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Drivetrain* m_drivetrain;
        CameraReader* m_cameras;

        int m_check_dist_counter;
        int m_last_dist;
};

#endif