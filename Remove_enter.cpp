#include<iostream>
#include<string>
#include<Windows.h>
#include<vector>

using namespace std;

std::wstring Acsi2WideByte(std::string& strascii)  
{  
    int widesize = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
    std::vector<wchar_t> resultstring(widesize);  
    int convresult = MultiByteToWideChar (CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
    return std::wstring(&resultstring[0]);  
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    while(true) {
        cout << "Enter sentenses (ctrl+z to finish):啊\n";
        string s, total;
        while(getline(cin, s)){
            total += s;
        }
        cout << total << endl;
        if(OpenClipboard(NULL)){
            wstring t = Acsi2WideByte(total);
            HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (t.length() + 1) * sizeof(wchar_t));
            if (hMem == NULL) {
                CloseClipboard();
                cout << "复制到粘贴板失败, 无法分配全局内存." << endl;
            }else {
                LPTSTR lpStr = (LPTSTR)GlobalLock(hMem);
                memcpy(lpStr, t.c_str(), t.length() * sizeof(wchar_t));
                lpStr[t.length()] = (wchar_t) 0;
                GlobalUnlock(hMem);
                SetClipboardData(CF_UNICODETEXT, hMem);
                CloseClipboard();
                cout << "已经结果复制到粘贴板中." << endl;
            }
        }else {
            cout << "粘贴板打开失败." << endl;
        }

        
        cin.clear();
    }

    return 0;
}