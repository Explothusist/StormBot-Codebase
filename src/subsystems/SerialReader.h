#ifndef STORMBOT_SERIAL_READER_
#define STORMBOT_SERIAL_READER_

#include <string>
#include "../Automat/Subsystem.h"
#include "vex.h"

class SerialReader : atmt::Subsystem {
    public:
        SerialReader();
        ~SerialReader() override;

        void init() override;
        void periodic() override;

        std::string readData();
        void sendData(std::string data);
        bool hasData();

    private:
        vex::motor* m_serial_link;
};

#endif