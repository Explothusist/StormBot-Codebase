
#include "StormBot.h"

#include "Automat/automat.h"

#include "Constants.h"

StormBot::StormBot():
    atmt::TimedRobot(constants::robot::AutonomousLength),
    m_bot_cont{ new RobotContainer() }
{

};
StormBot::~StormBot() {
    delete m_bot_cont;
    m_bot_cont = nullptr;
};

void StormBot::environmentInit() {
    setUsesCompetition(false); // VEX-specific, must be set before startLoop()

    // Register all Subsystems
    registerSubsystem(m_bot_cont->m_drivetrain);
    registerSubsystem(m_bot_cont->m_camera_reader);

    // Add all Joysticks
    addJoystick(m_bot_cont->m_driver_controller);
    // addJoystick(m_bot_cont->m_operator_controller);

    // Set up Autonomous
    // setAutonomousCommand(m_bot_cont->getAutonomousCommand(0, m_bot_cont));
    setAutonomousCommandGetter(RobotContainer::getAutonomousCommand, RobotContainer::getWhichAutonomousRoutine, m_bot_cont);

#ifdef STORMBOT_STATE_MATCHED_
    addHeartbeat(m_bot_cont->m_heartbeat);
#endif

    // Configure bindings
    m_bot_cont->configure_auto_triggers();
    m_bot_cont->configure_bindings();
};

void StormBot::robotInit() {
    atmt::platform_print("Robot Init!           ");
};
void StormBot::robotPeriodic() {
    atmt::platform_print("Robot Periodic...     ");
};
void StormBot::robotExit() {
    atmt::platform_print("Robot Exit            ");
};

void StormBot::disabledInit() {
    atmt::platform_println("Disabled Init!");
};
void StormBot::disabledPeriodic() {
    atmt::platform_println("Disabled Periodic...");
};
void StormBot::disabledExit() {
    atmt::platform_println("Disabled Exit");
};

void StormBot::autonomousInit() {
    atmt::platform_println("Autonomous Init!");
};
void StormBot::autonomousPeriodic() {
    atmt::platform_println("Autonomous Periodic...");
};
void StormBot::autonomousExit() {
    atmt::platform_println("Autonomous Exit");
};

void StormBot::teleopInit() {
    atmt::platform_println("Teleop Init!");
};
void StormBot::teleopPeriodic() {
    atmt::platform_println("Teleop Periodic...");
};
void StormBot::teleopExit() {
    atmt::platform_println("Teleop Exit");
};