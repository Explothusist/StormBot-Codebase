
#include "Drivetrain.h"

#include <cmath>
#include "../Constants.h"

Drivetrain::Drivetrain():
    atmt::Subsystem(),
    m_motor_bl{ nullptr },
    m_motor_br{ nullptr },
    m_motor_fl{ nullptr },
    m_motor_fr{ nullptr },
    m_gyro{ vex::inertial(constants::ports::Gyro_Port, vex::turnType::right) } // Calibrates on program launch
{

};
Drivetrain::~Drivetrain() {
    
};

void Drivetrain::init() {
    m_motor_bl = new vex::motor(constants::ports::MotorBL_Port, vex::gearSetting::ratio18_1, false);
    m_motor_br = new vex::motor(constants::ports::MotorBR_Port, vex::gearSetting::ratio18_1, false);
    m_motor_fl = new vex::motor(constants::ports::MotorFL_Port, vex::gearSetting::ratio18_1, false);
    m_motor_fr = new vex::motor(constants::ports::MotorFR_Port, vex::gearSetting::ratio18_1, false);
};
void Drivetrain::periodic() {

};

void Drivetrain::setDrive(int x_power, int y_power, int r_power) {
    atmt::Vector_2D vector{ atmt::Vector_2D(static_cast<double>(x_power), static_cast<double>(y_power)) };
    vector.rotate( // Add some offset, probably
        atmt::degreesToRadians(
            -m_gyro.heading(vex::rotationUnits::deg) // Direction correct IF increases CCW
        )
    );
    double x_amt = vector.getX();
    double y_amt = vector.getY();

    double power_fl =  y_amt +  x_amt + r_power; // -300.0 to 300.0
    double power_fr = -y_amt +  x_amt + r_power; // (-200.0 to 200.0 ignoring r_power)
    double power_bl =  y_amt + -x_amt + r_power;
    double power_br = -y_amt + -x_amt + r_power;

    double maxMag = std::abs(power_fl);
    maxMag = std::max(maxMag, std::abs(power_fr));
    maxMag = std::max(maxMag, std::abs(power_bl));
    maxMag = std::max(maxMag, std::abs(power_br));

    if (maxMag > 100.0) {
        double scale = 100.0 / maxMag;
        power_fl *= scale;
        power_fr *= scale;
        power_bl *= scale;
        power_br *= scale;
    }

    power_fl *= constants::drivetrain::Drivetrain_Speed;
    power_fr *= constants::drivetrain::Drivetrain_Speed;
    power_bl *= constants::drivetrain::Drivetrain_Speed;
    power_br *= constants::drivetrain::Drivetrain_Speed;

    auto applyMotor = [&](vex::motor* motor, double velocity) {
        int int_velocity = static_cast<int>(std::round(std::abs(velocity)));
        if (int_velocity == 0) {
            motor->stop(vex::brakeType::coast);
        }else if (velocity >= 0) {
            motor->spin(vex::directionType::fwd, int_velocity, vex::velocityUnits::pct);
        }else {
            motor->spin(vex::directionType::rev, int_velocity, vex::velocityUnits::pct);
        }
    };

    applyMotor(m_motor_fl, power_fl);
    applyMotor(m_motor_fr, power_fr);
    applyMotor(m_motor_bl, power_bl);
    applyMotor(m_motor_br, power_br);
};
void Drivetrain::stopDrive() {
    m_motor_fl->stop(vex::brakeType::coast);
    m_motor_fr->stop(vex::brakeType::coast);
    m_motor_bl->stop(vex::brakeType::coast);
    m_motor_br->stop(vex::brakeType::coast);
};
void Drivetrain::lockDrive() {
    m_motor_fl->stop(vex::brakeType::brake);
    m_motor_fr->stop(vex::brakeType::brake);
    m_motor_bl->stop(vex::brakeType::brake);
    m_motor_br->stop(vex::brakeType::brake);
};