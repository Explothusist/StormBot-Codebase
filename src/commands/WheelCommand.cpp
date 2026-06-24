
#include "WheelCommand.h"

#include <cmath>

WheelCommand::WheelCommand(Wheel* wheel, double rpm):
    atmt::Command(),
    m_wheel{ wheel },
    m_rpm{ rpm }
{
    usesSubsystem(m_wheel);
};
WheelCommand::WheelCommand(WheelCommand& command):
    atmt::Command(command)
{
    m_wheel = command.m_wheel;
    m_rpm = command.m_rpm;
};
WheelCommand::~WheelCommand() {
    // Will run ~Command() after this is complete
};
atmt::Command* WheelCommand::cloneSelf() const {
    return new WheelCommand(m_wheel, m_rpm);
};

void WheelCommand::initialize() {
    m_wheel->setDrive(m_rpm);
};
void WheelCommand::execute() {

};
void WheelCommand::end(bool interrupted) {
    m_wheel->stopDrive();
};
bool WheelCommand::is_finished() {
    return false;
};