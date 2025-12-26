
#ifndef FRCLIB_COMMAND_
#define FRCLIB_COMMAND_

#include <vector>

// #include "Subsystem.h"

namespace frclib {

    class Subsystem;

    class Command {
        public:
            Command(); // Put subsystems as parameters
            Command(Command& command); // Copy constructor
            ~Command();

            bool runLoop();

            virtual void initialize(); // User-made
            virtual void execute(); // User-made
            virtual void end(bool interrupted); // User-made
            virtual bool is_finished(); // User-made
            
            std::vector<Subsystem*> getSubsystems();
            bool hasMatchingSubsystems(Command* command);
            bool hasSubsystem(Subsystem* subsystem);

            void usesSubsystem(Subsystem* subsystem); // Call repeatedly for each subsystem used
        private:
            bool m_is_first_run;
            bool m_was_interrupted;

            std::vector<Subsystem*> m_subsystems;
    };

}

#endif