#ifndef CONSOLE_H
#define CONSOLE_H
#include <windows.h>
#include <iostream>
using namespace std;

HANDLE console;

#define green 10
#define red 12
#define yellow 14 
#define white 15
#define blue 9

class Console
{
public:
    Console()
    {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTitleW(L"Rummy");
    }

    static void clean_screen()
    {
        system("CLS");
    }

    static void pause_console()
    {
        cout << endl;
        system("pause");
    }

    static void setConsoleColour(int k)
    {
        SetConsoleTextAttribute(console, k);
    }
};

#endif
#pragma once
