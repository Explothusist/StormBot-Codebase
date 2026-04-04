
#include "UpdateJoystick.h"

#include <cmath>
#include "../Constants.h"

UpdateJoystick::UpdateJoystick(atmt::SerialReader* serial, atmt::Joystick* controller):
    atmt::Command(),
    m_serial{ serial },
    m_controller{ controller }
{
    // Does not use CameraReader* at the moment (somewhat risky)
    usesSubsystem(serial);
};
UpdateJoystick::UpdateJoystick(UpdateJoystick& command):
    atmt::Command(command)
{
    m_serial = command.m_serial;
    m_controller = command.m_controller;
};
UpdateJoystick::~UpdateJoystick() {
    // Will run ~Command() after this is complete
};
atmt::Command* UpdateJoystick::clone() const {
    return new UpdateJoystick(m_serial, m_controller);
};

void UpdateJoystick::initialize() {
    uint8_t prefix;
    uint8_t message[atmt::kMaxPacketSize];
    uint8_t length;
    bool success = m_serial->popMessagePrefixed(getSerialMessageId(), prefix, message, length);
    if (!success || length != sizeof(atmt::JoystickState)) {
        return;
    }
    atmt::JoystickState* state = reinterpret_cast<atmt::JoystickState*>(message);
    m_controller->updateState(*state);
};
void UpdateJoystick::execute() {
    
};
void UpdateJoystick::end(bool interrupted) {
    
};
bool UpdateJoystick::is_finished() {
    return true;
};