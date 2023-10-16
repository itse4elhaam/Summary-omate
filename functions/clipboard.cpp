#include <iostream>
#include <string>
#include <Windows.h>
#include "../functions.h"

using namespace std;

// this is windows specific
void copyToClipboard(const string &s)
{
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
        if (hg)
        {
            char *data = (char *)GlobalLock(hg);
            strcpy(data, s.c_str());
            GlobalUnlock(hg);
            SetClipboardData(CF_TEXT, hg);
            CloseClipboard();
            GlobalFree(hg);
            cout << "\n\nText copied to clipboard!." << endl;
        }
        else
        {
            cerr << "Failed to allocate memory for the clipboard." << endl;
        }
    }
    else
    {
        cerr << "Failed to open the clipboard." << endl;
    }
}