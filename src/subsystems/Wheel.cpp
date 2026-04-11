
#include "Wheel.h"

#include <cmath>
#include "../Automat/utils.h" // Printing
#include "../Automat/utilities/Vector2.h"
#include "../Constants.h"

Wheel::Wheel():
    atmt::Subsystem(),
    m_motor{ nullptr },
    currentSpeed{ 0 }
{

};
Wheel::~Wheel() {
    delete m_motor;
    
};

void Wheel::init() {
    m_motor = new vex::motor(constants::ports::Wheel_Port, vex::gearSetting::ratio18_1, false);

};
void Wheel::systemPeriodic() {

};
void Wheel::disabledPeriodic() {};
void Wheel::autonomousPeriodic() {};
void Wheel::teleopPeriodic() {};

void Wheel::setDrive(int speed) {

    currentSpeed = speed;

    m_motor->spin(vex::directionType::fwd, currentSpeed, vex::velocityUnits::pct);

};
void Wheel::stopDrive() {
    m_motor->stop(vex::brakeType::coast);

};
void Wheel::lockDrive() {
    m_motor->stop(vex::brakeType::brake);

};

int Wheel::getSpeed() {
    return currentSpeed;
};