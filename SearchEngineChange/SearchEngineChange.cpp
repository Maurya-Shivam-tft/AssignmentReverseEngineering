// SearchEngineChange.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <ShlObj.h>

#pragma comment(lib,"Shell32.lib")

std::string GetLogPath()
{
    char path[MAX_PATH];

    SHGetFolderPathA(
        NULL,
        CSIDL_APPDATA,
        NULL,
        0,
        path
    );

    std::string folder =
        std::string(path) +
        "\\SearchEngineChange";

    CreateDirectoryA(
        folder.c_str(),
        NULL
    );

    return folder + "\\log.txt";
}

typedef bool(*ChangeFunction)();

int main()
{
    auto start =
        std::chrono::steady_clock::now();

    auto startTime =
        std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );

    bool success = false;

    HMODULE dll =
        LoadLibrary(
            L"DllSerachEngineChange.dll"
        );

    if (dll)
    {
        ChangeFunction func =
            (ChangeFunction)
            GetProcAddress(
                dll,
                "ChangeSearchEngine"
            );

        if (!func) {
            std::cout << "func not found";
        }

        if (func)
        {
            success = func();
        }

        FreeLibrary(dll);
    }
    if (!dll) {
        std::cout << "Dll not found";
    }

    auto end =
        std::chrono::steady_clock::now();

    auto endTime =
        std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );

    auto duration =
        std::chrono::duration_cast
        <
        std::chrono::milliseconds
        >
        (
            end - start
            );

    std::ofstream log(
        GetLogPath(),
        std::ios::app
    );

    log << "----------------\n";

    char startBuffer[100];

    ctime_s(
        startBuffer,
        sizeof(startBuffer),
        &startTime
    );

    log << "Start: "
        << startBuffer;

    char endBuffer[100];

    ctime_s(
        endBuffer,
        sizeof(endBuffer),
        &endTime
    );

    log << "End: "
        << endBuffer;

    log << "Status: "
        << (success ? "Success" : "Failure")
        << "\n";

    log << "Duration(ms): "
        << duration.count()
        << "\n";

    log.close();

    return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
