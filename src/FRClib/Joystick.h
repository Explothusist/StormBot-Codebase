
#ifndef FRCLIB_JOYSTICK_
#define FRCLIB_JOYSTICK_

#include <vector>

#include "vex.h"

#include "Trigger.h"

namespace frclib {

    class Command;

    typedef enum {
        PrimaryJoystick,
        PartnerJoystick
    } JoystickType;

    class Joystick {
        public:
            Joystick(JoystickType type);
            ~Joystick();

            std::vector<Command*> pollEvents();
            std::vector<int> pollEventTerminations();

            void bindKey(StickIndicator stick, StickEvent event, Command* command);
            void bindKey(StickIndicator stick, StickEvent event, TriggerType type, Command* command);
            void bindKey(ButtonIndicator button, ButtonEvent event, Command* command);
            void bindKey(ButtonIndicator button, ButtonEvent event, TriggerType type, Command* command);

            void triggerEvent(StickIndicator stick, StickEvent event);
            void triggerEvent(ButtonIndicator button, ButtonEvent event);

            void setAxis12(int axis1, int axis2);
            void setAxis34(int axis3, int axis4);

            StickEvent getStickState(StickIndicator stick);
            ButtonEvent getButtonState(ButtonIndicator button);
            int getRawAxis(AxisIndicator axis);
        private:
            vex::controller m_controller;

            std::vector<Trigger*> m_triggers;
            std::vector<EndingTrigger*> m_temp_triggers;
            std::vector<Command*> m_triggered_commands;
            std::vector<int> m_command_terminations;

            StickEvent m_stick_state[2];
            int m_axis_position[4];
            ButtonEvent m_button_state[12];
    };

}

#endif