
#ifndef STORMBOT_UPDATEJOYSTICKCOMMAND_
#define STORMBOT_UPDATEJOYSTICKCOMMAND_

#include "../Automat/automat.h"

class UpdateJoystick : public atmt::Command {
    public:
        UpdateJoystick(atmt::SerialReader* serial, atmt::Joystick* controller); // Put subsystems as parameters
        UpdateJoystick(UpdateJoystick& command); // Copy constructor
        ~UpdateJoystick();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        atmt::SerialReader* m_serial;
        atmt::Joystick* m_controller;
};

#endif