
#include "pch.h"
#include "EdgeChanger.h"
#include <string>
#include <winuser.h>
#pragma comment(lib, "user32.lib")

void PressKey(WORD vk)
{
    keybd_event(vk, 0, 0, 0);
    Sleep(50);
    keybd_event(vk, 0, KEYEVENTF_KEYUP, 0);
    Sleep(150);
}

void TypeText(const char* text)
{
    for (int i = 0; text[i]; i++)
    {
        SHORT vk = VkKeyScanA(text[i]);
        BYTE keyCode = LOBYTE(vk);
        BYTE shiftState = HIBYTE(vk);

        // Press Shift if needed
        if (shiftState & 1)
            keybd_event(VK_SHIFT, 0, 0, 0);

        keybd_event(keyCode, 0, 0, 0);
        Sleep(50);
        keybd_event(keyCode, 0, KEYEVENTF_KEYUP, 0);
        Sleep(50);

        // Release Shift if it was pressed
        if (shiftState & 1)
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);

        Sleep(20);
    }
}

bool LaunchEdgeToSettings()
{
    const wchar_t* edgePaths[] = {
        L"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe",
        L"C:\\Program Files\\Microsoft\\Edge\\Application\\msedge.exe"
    };
    const wchar_t* url =
        L"edge://settings/privacy/services/search/searchEngines";

    for (auto edgePath : edgePaths)
    {
        if (GetFileAttributesW(edgePath) == INVALID_FILE_ATTRIBUTES)
            continue;

        std::wstring cmd = L"\"";
        cmd += edgePath;
        cmd += L"\" --new-window ";
        cmd += url;

        STARTUPINFOW si = {};
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_SHOW;
        PROCESS_INFORMATION pi = {};

        BOOL ok = CreateProcessW(
            NULL, (LPWSTR)cmd.c_str(),
            NULL, NULL, FALSE,
            0, NULL, NULL, &si, &pi);

        if (ok)
        {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            return true;
        }
    }
    return false;
}

bool ChangeSearchEngine()
{
    try
    {
        // 1. Kill Edge
        system("taskkill /IM msedge.exe /F >nul 2>&1");
        Sleep(2000);

        // 2. Launch Edge to search engines page
        if (!LaunchEdgeToSettings())
            return false;

        // 3. Wait for page to load
        Sleep(5000);

        // 4. Find Edge window
        HWND hEdge = NULL;
        for (int i = 0; i < 20; i++)
        {
            hEdge = FindWindowW(L"Chrome_WidgetWin_1", NULL);
            if (hEdge) break;
            Sleep(500);
        }
        if (!hEdge) return false;

        SetForegroundWindow(hEdge);
        Sleep(1000);

        // 5. Navigate to correct URL via address bar
        keybd_event(VK_CONTROL, 0, 0, 0);
        keybd_event('L', 0, 0, 0);
        keybd_event('L', 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
        Sleep(500);

        TypeText("edge://settings/privacy/services/search/searchEngines");
        Sleep(2000);
        PressKey(VK_RETURN);
        Sleep(4000);

        // 6. Tab 4 times to reach search box
        PressKey(VK_TAB);
        Sleep(300);
        PressKey(VK_TAB);
        Sleep(300);
        PressKey(VK_TAB);
        Sleep(300);
        PressKey(VK_TAB);
        Sleep(300);

        // 7. Press Enter to focus search
        PressKey(VK_RETURN);
        Sleep(500);

        // 8. Type search engine name
        // =============================================
        // PATCH TARGET: change "yahoo" to "duckduckgo"
        // in Ghidra to change search engine
        // =============================================
        TypeText("yahoo");

        Sleep(500);

        // 9. Press Enter to confirm search
        PressKey(VK_RETURN);
        Sleep(1000);

        // 10. Tab twice to reach the result row
        PressKey(VK_TAB);
        Sleep(300);
        PressKey(VK_TAB);
        Sleep(300);

        // 11. Right arrow 3 times to reach Make Default
        PressKey(VK_RIGHT);
        Sleep(300);
        PressKey(VK_RIGHT);
        Sleep(300);
        PressKey(VK_RIGHT);
        Sleep(300);

        // 12. Press Enter twice to confirm
        PressKey(VK_RETURN);
        Sleep(500);
        PressKey(VK_RETURN);
        Sleep(3000);

        // 13. Close Edge gracefully
        SetForegroundWindow(hEdge);
        Sleep(500);
        keybd_event(VK_MENU, 0, 0, 0);
        keybd_event(VK_F4, 0, 0, 0);
        keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
        Sleep(3000);

        // 14. Force kill if still running
        system("taskkill /IM msedge.exe /F >nul 2>&1");
        Sleep(1000);

        return true;
    }
    catch (...)
    {
        return false;
    }
}
















































