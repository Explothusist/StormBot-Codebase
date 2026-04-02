
// #include "SerialReader.h"

// #include <cmath>
// #include "../Constants.h"

// SerialReader::SerialReader():
//     atmt::Subsystem(),
//     m_serial_link{ nullptr }
// {

// };
// SerialReader::~SerialReader() {
//     delete m_serial_link;
//     m_serial_link = nullptr;
// };

// void SerialReader::init() {
//     m_serial_link = new vex::motor(constants::ports::Serial_Port);

//     vexGenericSerialEnable(m_serial_link->index(), 0);
//     vexGenericSerialBaudrate(m_serial_link->index(), constants::serial::Serial_Baudrate);
// };
// void SerialReader::periodic() {

// };

// std::string SerialReader::readData() {
//     std::string data;
//     while (vexGenericSerialReceiveAvail(m_serial_link->index()) > 0) {
//         data.push_back(static_cast<char>(vexGenericSerialReadChar(m_serial_link->index())));
//     }
//     return data;
// };
// void SerialReader::sendData(std::string data) {
//     vexGenericSerialTransmit(m_serial_link->index(), (uint8_t*)(data.c_str()), data.size());
// };
// bool SerialReader::hasData() {
//     return (vexGenericSerialReceiveAvail(m_serial_link->index()) > 0);
// };
