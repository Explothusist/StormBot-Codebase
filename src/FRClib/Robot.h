
#ifndef FRCLIB_ROBOT_
#define FRCLIB_ROBOT_

#include <vector>

#include "vex.h"

// using namespace vex;

#include "Subsystem.h"
#include "Command.h"
#include "Joystick.h"

namespace frclib {

    typedef enum {
        Disabled,
        Autonomous,
        Teleop
    } RobotState;

    class TimedRobot {
        public:
            TimedRobot();
            TimedRobot(bool use_vex_competition);
            TimedRobot(bool use_vex_competition, int autonomous_length);
            ~TimedRobot();

            // void robotInit(); // Use constructor instead
            virtual void robotPeriodic(); // User-made
            // void robotExit(); // Use destructor instead

            virtual void disabledInit(); // User-made
            virtual void disabledPeriodic(); // User-made
            virtual void disabledExit(); // User-made

            virtual void autonomousInit(); // User-made
            virtual void autonomousPeriodic(); // User-made
            virtual void autonomousExit(); // User-made 

            virtual void teleopInit(); // User-made
            virtual void teleopPeriodic(); // User-made
            virtual void teleopExit(); // User-made

            void handleState(RobotState state);
            void pollState();

            void runCommand(Command* command);
            void registerSubsystem(Subsystem* subsystem);
            void addJoystick(Joystick* joystick);

            void endCommand(int command_id); // Use the global Id assigned by Joystick

            void startLoop();
        private:
            std::vector<Subsystem*> m_subsystems;
            std::vector<Command*> m_commands;
            std::vector<Joystick*> m_joysticks;
            Command* m_autonomous_command;

            vex::brain m_brain;

            RobotState m_state;
            RobotState m_old_state;
            bool m_reseting_state_loop;
            bool m_had_state_chage;

            int m_frame_delay;

            bool m_uses_vex_competition;
            bool m_first_auto_trigger;
            int m_autonomous_length;
            bool m_start_of_auto;

            // int m_command_id_counter;

            // void robotInternal(bool is_original);
            void robotInternal();
            void disabledInternal();
            void autonomousInternal();
            void teleopInternal();

            void commandScheduler();
            void clearCommands();
            void runDefaultCommands();
            void pollJoystickEvents();

            bool robotHasSubsystem(Subsystem* subsystem);
            bool robotHasJoystick(Joystick* joystick);
            bool subsystemHasCommand(Subsystem* subsystem);
    };

    void InstigateRobot(TimedRobot* robot);

    void translateAutonomous();
    void translateTeleop();

}

#endif