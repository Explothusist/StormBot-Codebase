
#include "Trigger.h"

namespace frclib {

    Trigger::Trigger() {};
    Trigger::~Trigger() {};
    bool Trigger::matchesEvent(StickIndicator stick, StickEvent event) { return false; };
    bool Trigger::matchesEvent(ButtonIndicator button, ButtonEvent event) { return false; };
    Command* Trigger::getCommand() { return nullptr; };

    StickTrigger::StickTrigger(StickIndicator stick, StickEvent event, Command* command):
        m_stick{ stick },
        m_event{ event },
        m_command{ command },
        m_type{ OnTrigger }
    {

    };
    StickTrigger::StickTrigger(StickIndicator stick, StickEvent event, TriggerType type, Command* command):
        m_stick{ stick },
        m_event{ event },
        m_command{ command },
        m_type{ type }
    {

    };
    StickTrigger::~StickTrigger() {
        delete m_command;
        m_command = nullptr;
    };

    bool StickTrigger::matchesEvent(StickIndicator stick, StickEvent event) {
        if (m_stick == stick && m_event == event) {
            return true;
        }
        return false;
    };
    bool StickTrigger::matchesEvent(ButtonIndicator button, ButtonEvent event) {
        return false;
    };
    Command* StickTrigger::getCommand() {
        return m_command;
    };

    ButtonTrigger::ButtonTrigger(ButtonIndicator button, ButtonEvent event, Command* command):
        m_button{ button },
        m_event{ event },
        m_command{ command },
        m_type{ OnTrigger }
    {

    };
    ButtonTrigger::ButtonTrigger(ButtonIndicator button, ButtonEvent event, TriggerType type, Command* command):
        m_button{ button },
        m_event{ event },
        m_command{ command },
        m_type{ type }
    {

    };
    ButtonTrigger::~ButtonTrigger() {
        delete m_command;
        m_command = nullptr;
    };

    bool ButtonTrigger::matchesEvent(StickIndicator stick, StickEvent event) {
        return false;
    };
    bool ButtonTrigger::matchesEvent(ButtonIndicator button, ButtonEvent event) {
        if (m_button == button && m_event == event) {
            return true;
        }
        return false;
    };
    Command* ButtonTrigger::getCommand() {
        Command* copy { new Command(*m_command) };
        return copy;
    };

};