
#ifndef FRCLIB_TRIGGER_
#define FRCLIB_TRIGGER_

#include <vector>

#include "vex.h"

#include "Command.h"

namespace frclib {

    // class Command; // Forward declare because it never actually uses it

    typedef enum {
        LeftStick,
        RightStick
    } StickIndicator;
    typedef enum {
        StickUp,
        StickDown,
        StickLeft,
        StickRight,
        StickCenter
    } StickEvent;
    typedef enum {
        AButton,
        BButton,
        XButton,
        YButton,
        UpButton,
        LeftButton,
        DownButton,
        RightButton,
        L1Button,
        L2Button,
        R1Button,
        R2Button
    } ButtonIndicator;
    typedef enum {
        ButtonPressed,
        ButtonReleased,
    } ButtonEvent;
    typedef enum {
        OnTrigger,
        WhileTrigger
    } TriggerType;
    typedef enum {
        Axis1,
        Axis2,
        Axis3,
        Axis4
    } AxisIndicator;

    class Trigger {
        public:
            Trigger();
            ~Trigger();

            bool matchesEvent(StickIndicator stick, StickEvent event);
            bool matchesEvent(ButtonIndicator stick, ButtonEvent event);
            Command* getCommand();
        private:
    };
    class StickTrigger : public Trigger {
        public:
            StickTrigger(StickIndicator stick, StickEvent event, Command* command);
            StickTrigger(StickIndicator stick, StickEvent event, TriggerType type, Command* command);
            ~StickTrigger();

            bool matchesEvent(StickIndicator stick, StickEvent event);
            bool matchesEvent(ButtonIndicator button, ButtonEvent event);
            Command* getCommand();
        private:
            StickIndicator m_stick;
            StickEvent m_event;
            TriggerType m_type;

            Command* m_command;
    };
    class ButtonTrigger : public Trigger {
        public:
            ButtonTrigger(ButtonIndicator stick, ButtonEvent event, Command* command);
            ButtonTrigger(ButtonIndicator stick, ButtonEvent event, TriggerType type, Command* command);
            ~ButtonTrigger();

            bool matchesEvent(StickIndicator stick, StickEvent event);
            bool matchesEvent(ButtonIndicator button, ButtonEvent event);
            Command* getCommand();
        private:
            ButtonIndicator m_button;
            ButtonEvent m_event;
            TriggerType m_type;

            Command* m_command;
    };

}

#endif