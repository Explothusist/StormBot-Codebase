
#ifndef STORMBOT_DRIVETRAIN_
#define STORMBOT_DRIVETRAIN_

#include "../Automat/Subsystem.h"
#include "vex.h"

class Drivetrain : public amt::Subsystem {
    public:
        Drivetrain(); // No destructor because I don't want to override
        ~Drivetrain() override;

        void periodic() override;

        void setDrive(int x_power, int y_power, int r_power);
        void stopDrive();
        void lockDrive();

    private:
        vex::motor m_motor_bl;
        vex::motor m_motor_br;
        vex::motor m_motor_fl;
        vex::motor m_motor_fr;
};

#endif