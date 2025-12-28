
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
            virtual ~Trigger();

            virtual bool matchesEvent(StickIndicator stick, StickEvent event);
            virtual bool matchesEvent(ButtonIndicator stick, ButtonEvent event);
            virtual Command* getCommand();

            virtual TriggerType getTriggerType();
        private:
    };
    class StickTrigger : public Trigger {
        public:
            StickTrigger(StickIndicator stick, StickEvent event, Command* command);
            StickTrigger(StickIndicator stick, StickEvent event, TriggerType type, Command* command);
            ~StickTrigger();

            bool matchesEvent(StickIndicator stick, StickEvent event) override;
            bool matchesEvent(ButtonIndicator button, ButtonEvent event) override;
            Command* getCommand() override;

            TriggerType getTriggerType() override;
        private:
            StickIndicator m_stick;
            StickEvent m_event;
            TriggerType m_type;

            Command* m_command;
    };
    class ButtonTrigger : public Trigger {
        public:
            ButtonTrigger(ButtonIndicator button, ButtonEvent event, Command* command);
            ButtonTrigger(ButtonIndicator button, ButtonEvent event, TriggerType type, Command* command);
            ~ButtonTrigger();

            bool matchesEvent(StickIndicator stick, StickEvent event) override;
            bool matchesEvent(ButtonIndicator button, ButtonEvent event) override;
            Command* getCommand() override;

            TriggerType getTriggerType() override;
        private:
            ButtonIndicator m_button;
            ButtonEvent m_event;
            TriggerType m_type;

            Command* m_command;
    };


    class EndingTrigger {
        public:
            EndingTrigger(int command_id);
            virtual ~EndingTrigger();

            virtual bool matchesEvent(StickIndicator stick, StickEvent event);
            virtual bool matchesEvent(ButtonIndicator stick, ButtonEvent event);
            int getCommandId();
        private:
            int m_command_id;
    };
    class StickEndingTrigger : public EndingTrigger {
        public:
            StickEndingTrigger(StickIndicator stick, StickEvent event, int command_id);
            ~StickEndingTrigger();

            bool matchesEvent(StickIndicator stick, StickEvent event) override;
            bool matchesEvent(ButtonIndicator button, ButtonEvent event) override;
        private:
            StickIndicator m_stick;
            StickEvent m_event;
    };
    class ButtonEndingTrigger : public EndingTrigger {
        public:
            ButtonEndingTrigger(ButtonIndicator button, ButtonEvent event, int command_id);
            ~ButtonEndingTrigger();

            bool matchesEvent(StickIndicator stick, StickEvent event) override;
            bool matchesEvent(ButtonIndicator button, ButtonEvent event) override;
        private:
            ButtonIndicator m_button;
            ButtonEvent m_event;
    };

}

#endif