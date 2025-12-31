
#ifndef STORMBOT_
#define STORMBOT_

#include "Automat/automat.h"

class StormBot : public amt::TimedRobot {
    public:
        StormBot(); // No destructor because I don't want to override

        void robotPeriodic() override;
        
        void disabledInit() override;
        void disabledPeriodic() override;
        void disabledExit() override;
        
        void autonomousInit() override;
        void autonomousPeriodic() override;
        void autonomousExit() override;
        
        void teleopInit() override;
        void teleopPeriodic() override;
        void teleopExit() override;

    private:
};

#endif