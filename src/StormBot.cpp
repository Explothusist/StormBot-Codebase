
#include "StormBot.h"

#include "Constants.h"

StormBot::StormBot():
    amt::TimedRobot(constants::AutonomousLength)
{
    setUsesCompetition(false); // VEX-specific, must be set before startLoop()
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