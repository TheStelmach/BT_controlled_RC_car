#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>

#include "mybluetooth.h"

HANDLE hSerial;

//unsigned char COM_number_reader(std::string &port_name) {
//    std::ifstream fin;
//    fin.open("serial_setting.txt");
//    if (!fin) {
//        return 1;
//    }
//    char COM_number[10];
//    fin >> COM_number;
//    fin.close();
//    switch (COM_number[3]) {
//        case '1':
//            if (COM_number[4] == '1') { 
//                port_name = "COM11";
//                return 11; }
//            else if (COM_number[4] == '2') {
//                port_name = "COM12";
//                return 12; 
//            }
//            else if (COM_number[4] == '3') {
//                port_name = "COM13";
//                return 13;
//            }
//            else if (COM_number[4] == '4') { 
//                port_name = "COM14";
//                return 14; }
//            else
//            {
//                port_name = "COM1";
//                return 1;
//            }
//            break;
//        case '2': 
//            port_name = "COM2";
//            return 2; break;
//        case '3': 
//            port_name = "COM3";
//            return 3; break;
//        case '4': 
//            port_name = "COM4";
//            return 4; break;
//        case '5': 
//            port_name = "COM5";
//            return 5; break;
//        case '6': 
//            port_name = "COM6";
//            return 6; break;
//        case '7': 
//            port_name = "COM7";
//            return 7; break;
//        case '8': 
//            port_name = "COM8";
//            return 8; break;
//        case '9': 
//            port_name = "COM9";
//            return 9; break;
//        default: return 0;
//    }
//
//};

bool COMInit(const TCHAR* portName) {
    hSerial = CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Unable to open COM port\n";
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: Unable to get COM port state\n";
        CloseHandle(hSerial);
        return false;
    }
    dcbSerialParams.BaudRate = CBR_38400;  // Set your desired baud rate here
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = 0; // Set stop bits to 0
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error: Unable to set COM port state\n";
        CloseHandle(hSerial);
        return false;
    }

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error: Unable to set COM port timeouts\n";
        CloseHandle(hSerial);
        return false;
    }

    return true;
}

void COMEnd() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
    }
}

bool COMSend(const std::string& data) {
    DWORD bytesWritten;
    if (!WriteFile(hSerial, data.c_str(), data.length(), &bytesWritten, NULL)) {
        std::cerr << "Error: Unable to write to COM port\n";
        return false;
    }
    return true;
}

std::string COMRead() {
    const int BUFFER_SIZE = 128;
    char buffer[BUFFER_SIZE];
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
        std::cerr << "Error: Unable to read from COM port\n";
        return "";
    }
    return std::string(buffer, bytesRead);
}

bool BTInit() {
    std::string command1 = "AT\r\n";
    std::string command2 = "AT+INQ\r\n";
    std::string command3 = "AT+CONN1\r\n";
    std::string answer1;
    std::string answer2;
    //std::string answer2_sub;
    std::string answer3;
    //std::string answer3_sub;
    bool condition1 = false;
    bool condition2 = false;
    bool condition3 = false;

    //////////////////////////////////////////////////////////////////////////
    Sleep(50);
    if (COMSend(command1)) {
        std::cout << "AT Checking!\n";
    }
    else {
        std::cout << "Failed to send data to master\n";
        return false;
    }
    Sleep(50);
    answer1 = COMRead();
    if (!answer1.empty()) {
        std::cout << "Received Response\n" << answer1;
    }
    else {
        std::cout << "Master module is not responding\n";
        return false;
    }
    if (answer1.find("OK") != std::string::npos) {
        condition1 = true;
    }
    else {
        std::cout << "There is an error in the first initiation command\n";
        return false;
    }
    /////////////////////////////////////////////////////////////////////////////
    Sleep(50);
    if (COMSend(command2)) {
        std::cout << "AT Inquiring slave devices!\n";
    }
    else {
        std::cout << "Failed to send data to master\n";
        return false;
    }
    Sleep(50);
    answer2 = COMRead();
    if (!answer2.empty()) {
        std::cout << "Received Response\n" << answer2;
    }
    else {
        std::cout << "Master module is not responding\n";
        return false;
    }
    Sleep(500);
    if (answer2.find("1") != std::string::npos) {
        condition2 = true;
    }
    else {
        std::cout << "There is an error in the seccond initiation command\n";
        return false;
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    Sleep(50);
    if (COMSend(command3)) {
        std::cout << "AT connecting to the device number1 !\n";
    }
    else {
        std::cout << "Failed to send data to master\n";
        return false;
    }
    Sleep(700);
    answer3 = COMRead();
    if (!answer3.empty()) {
        std::cout << "Received Response\n" << answer3;
    }
    else {
        std::cout << "Master module is not responding\n";
        return false;
    }
    if ((answer3.find("CONNECTED") != std::string::npos) || (answer3.find("Connected") != std::string::npos)) {
        condition3 = true;
    }
    else {
        std::cout << "There is an error in the third initiation command\n";
        return false;
    }
    std::cout << "BT SUCCESSFULLY INITIATED\n";
    Sleep(2000);
    return condition1 && condition2 && condition3;

}