#ifndef MYBLUETOOTH_H
#define MYBLUETOOTH_H

#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <fstream>

#define COM "COM8"

extern HANDLE hSerial;

bool COMInit(const TCHAR*);
void COMEnd();
bool COMSend(const std::string&);
std::string COMRead();
bool BTInit();
//unsigned char COM_number_reader(const std::string&);

#endif 

