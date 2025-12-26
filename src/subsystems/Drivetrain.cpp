
#include "Drivetrain.h"

#include "../Constants.h"

Drivetrain::Drivetrain():
    frclib::Subsystem(),
    m_motor_bl{ vex::motor(constants::MotorBL_Port, vex::gearSetting::ratio18_1, false) },
    m_motor_br{ vex::motor(constants::MotorBR_Port, vex::gearSetting::ratio18_1, false) },
    m_motor_fl{ vex::motor(constants::MotorFL_Port, vex::gearSetting::ratio18_1, false) },
    m_motor_fr{ vex::motor(constants::MotorFR_Port, vex::gearSetting::ratio18_1, false) }
{

};
Drivetrain::~Drivetrain() {
    
};

void Drivetrain::periodic() {

};

void Drivetrain::setDrive(int x_power, int y_power, int r_power) {
    int power_fl =  y_power +  x_power + r_power;
    int power_fr = -y_power +  x_power + r_power;
    int power_bl =  y_power + -x_power + r_power;
    int power_br = -y_power + -x_power + r_power;

    power_fl = std::min((power_fl / 200.0) * 100.0 * constants::Drivetrain_Speed, 100.0);
    power_fr = std::min((power_fr / 200.0) * 100.0 * constants::Drivetrain_Speed, 100.0);
    power_bl = std::min((power_bl / 200.0) * 100.0 * constants::Drivetrain_Speed, 100.0);
    power_br = std::min((power_br / 200.0) * 100.0 * constants::Drivetrain_Speed, 100.0);

    m_motor_fl.spin(vex::directionType::fwd, power_fl, vex::velocityUnits::pct);
    m_motor_fr.spin(vex::directionType::fwd, power_fr, vex::velocityUnits::pct);
    m_motor_bl.spin(vex::directionType::fwd, power_bl, vex::velocityUnits::pct);
    m_motor_br.spin(vex::directionType::fwd, power_br, vex::velocityUnits::pct);
};
void Drivetrain::stopDrive() {
    m_motor_fl.stop(vex::brakeType::coast);
    m_motor_fr.stop(vex::brakeType::coast);
    m_motor_bl.stop(vex::brakeType::coast);
    m_motor_br.stop(vex::brakeType::coast);
};
void Drivetrain::lockDrive() {
    m_motor_fl.stop(vex::brakeType::brake);
    m_motor_fr.stop(vex::brakeType::brake);
    m_motor_bl.stop(vex::brakeType::brake);
    m_motor_br.stop(vex::brakeType::brake);
};