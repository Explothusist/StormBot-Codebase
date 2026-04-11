
#ifndef STORMBOT_WHEEL_
#define STORMBOT_WHEEL_

#include "../Automat/command_based/Subsystem.h"
#include "vex.h"

class Wheel : public atmt::Subsystem {
    public:
        Wheel();
        ~Wheel() override;

        void init() override;
        void systemPeriodic() override;
        void disabledPeriodic() override;
        void autonomousPeriodic() override;
        void teleopPeriodic() override;

        void setDrive(int speed);
        void stopDrive();
        void lockDrive();


        int getSpeed();

    private:
        vex::motor* m_motor;
        int currentSpeed;

};

#endif