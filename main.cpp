//
// Created by jacky on 2019/4/6.
//

#ifdef _WIN32
#include <windows.h>
#endif
#include "src/ACGMain.h"

int main(){
#ifdef _WIN32
//Change the Console Font to display Chinese
//Reference: http://m.blog.csdn.net/article/details?id=52789570
//system("chcp 65001"); //设置字符集（使用SetConsoleCP(65001)设置无效，原因未知）
    SetConsoleOutputCP(65001);
    CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = 16; // leave X as zero
    info.FontWeight = FW_NORMAL;
    wcscpy(info.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
#endif

    ACGMain mainProgram = ACGMain();
    mainProgram.run();
    return 0;
}