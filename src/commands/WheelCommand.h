
#ifndef STORMBOT_WheelCommand_
#define STORMBOT_WheelCommand_

#include "../Automat/automat.h"
#include "../subsystems/Wheel.h"

class WheelCommand : public atmt::Command {
    public:
        WheelCommand(Wheel* wheel, double rpm); // Put subsystems as parameters
        WheelCommand(WheelCommand& command); // Copy constructor
        ~WheelCommand();
        atmt::Command* cloneSelf() const override;

        void initialize() override; // User-made
        void execute() override; // User-made
        void end(bool interrupted) override; // User-made
        bool is_finished() override; // User-made
        
    private:
        Wheel* m_wheel;
        double m_rpm;
};

#endif