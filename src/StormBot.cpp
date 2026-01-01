
#include "StormBot.h"

#include "Constants.h"

StormBot::StormBot():
    atmt::TimedRobot(constants::AutonomousLength),
    m_bot_cont{ new RobotContainer() }
{
    setUsesCompetition(false); // VEX-specific, must be set before startLoop()

    // Register all Subsystems
    registerSubsystem(m_bot_cont->m_drivetrain);
    registerSubsystem(m_bot_cont->m_camera_reader);

    // Add all Joysticks
    addJoystick(m_bot_cont->m_driver_controller);
    addJoystick(m_bot_cont->m_operator_controller);

    // Configure bindings
    m_bot_cont->configure_bindings();
};
StormBot::~StormBot() {
    delete m_bot_cont;
    m_bot_cont = nullptr;
};

void StormBot::robotPeriodic() {

};

void StormBot::disabledInit() {

};
void StormBot::disabledPeriodic() {

};
void StormBot::disabledExit() {

};

void StormBot::autonomousInit() {

};
void StormBot::autonomousPeriodic() {

};
void StormBot::autonomousExit() {

};

void StormBot::teleopInit() {

};
void StormBot::teleopPeriodic() {

};
void StormBot::teleopExit() {

};