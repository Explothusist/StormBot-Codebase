
# include toolchain options
include vex/mkenv.mk

Robot.o: Robot.h Robot.cpp Subsystem.o Joystick.o
	g++ -Wall -c Robot.cpp -o Robot.o

Subsystem.o: Subsystem.h Subsystem.cpp Command.o
	g++ -Wall -c Subsystem.cpp -o Subsystem.o

Command.o: Command.h Command.cpp
	g++ -Wall -c Command.cpp -o Command.o

Joystick.o: Joystick.h Joystick.cpp Trigger.o
	g++ -Wall -c Joystick.cpp -o Joystick.o

Trigger.o: Trigger.h Trigger.cpp
	g++ -Wall -c Trigger.cpp -o Trigger.o