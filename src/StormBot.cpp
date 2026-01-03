
#include "StormBot.h"

#include "Automat/automat.h"

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
    atmt::platform_print("Robot Periodic...");
};

void StormBot::disabledInit() {
    atmt::platform_print("Disabled Init!");
};
void StormBot::disabledPeriodic() {
    atmt::platform_print("Disabled Periodic...");
};
void StormBot::disabledExit() {
    atmt::platform_print("Disabled Exit");
};

void StormBot::autonomousInit() {
    atmt::platform_print("Autonomous Init!");
};
void StormBot::autonomousPeriodic() {
    atmt::platform_print("Autonomous Periodic...");
};
void StormBot::autonomousExit() {
    atmt::platform_print("Autonomous Exit");
};

void StormBot::teleopInit() {
    atmt::platform_print("Teleop Init!");
};
void StormBot::teleopPeriodic() {
    atmt::platform_print("Teleop Periodic...");
};
void StormBot::teleopExit() {
    atmt::platform_print("Teleop Exit");
};