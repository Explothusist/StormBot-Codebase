
#include "Trigger.h"

namespace frclib {

    Trigger::Trigger() {};
    Trigger::~Trigger() {};
    bool Trigger::matchesEvent(StickIndicator stick, StickEvent event) { return false; };
    bool Trigger::matchesEvent(ButtonIndicator button, ButtonEvent event) { return false; };
    Command* Trigger::getCommand() { return nullptr; };
    TriggerType Trigger::getTriggerType() { return OnTrigger; };

    StickTrigger::StickTrigger(StickIndicator stick, StickEvent event, Command* command):
        m_stick{ stick },
        m_event{ event },
        m_type{ OnTrigger },
        m_command{ command }
    {

    };
    StickTrigger::StickTrigger(StickIndicator stick, StickEvent event, TriggerType type, Command* command):
        m_stick{ stick },
        m_event{ event },
        m_type{ type },
        m_command{ command }
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
    TriggerType StickTrigger::getTriggerType() {
        return m_type;
    };

    ButtonTrigger::ButtonTrigger(ButtonIndicator button, ButtonEvent event, Command* command):
        m_button{ button },
        m_event{ event },
        m_type{ OnTrigger },
        m_command{ command }
    {

    };
    ButtonTrigger::ButtonTrigger(ButtonIndicator button, ButtonEvent event, TriggerType type, Command* command):
        m_button{ button },
        m_event{ event },
        m_type{ type },
        m_command{ command }
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
    TriggerType ButtonTrigger::getTriggerType() {
        return m_type;
    };



    EndingTrigger::EndingTrigger(int command_id):
        m_command_id{ command_id }
    {

    };
    EndingTrigger::~EndingTrigger() {};
    bool EndingTrigger::matchesEvent(StickIndicator stick, StickEvent event) { return false; };
    bool EndingTrigger::matchesEvent(ButtonIndicator button, ButtonEvent event) { return false; };

    int EndingTrigger::getCommandId() {
        return m_command_id;
    };



    StickEndingTrigger::StickEndingTrigger(StickIndicator stick, StickEvent event, int command_id):
        EndingTrigger(command_id),
        m_stick{ stick },
        m_event{ event }
    {

    };
    StickEndingTrigger::~StickEndingTrigger() {};

    bool StickEndingTrigger::matchesEvent(StickIndicator stick, StickEvent event) {
        if (m_stick == stick && m_event != event) { // != is the key to ending trigger
            return true;
        }
        return false;
    };
    bool StickEndingTrigger::matchesEvent(ButtonIndicator button, ButtonEvent event) {
        return false;
    };

    ButtonEndingTrigger::ButtonEndingTrigger(ButtonIndicator button, ButtonEvent event, int command_id):
        EndingTrigger(command_id),
        m_button{ button },
        m_event{ event }
    {

    };
    ButtonEndingTrigger::~ButtonEndingTrigger() {};

    bool ButtonEndingTrigger::matchesEvent(StickIndicator stick, StickEvent event) {
        return false;
    };
    bool ButtonEndingTrigger::matchesEvent(ButtonIndicator button, ButtonEvent event) {
        if (m_button == button && m_event != event) { // != is the key to ending trigger
            return true;
        }
        return false;
    };


};