#include "ProgramOne.h"

ProgramOne::ProgramOne() {
    setActiveThread(THREAD_ENTER);
}

void ProgramOne::readStringThread()
{
    std::string str;
    while (isActiveThread(THREAD_ENTER))
    {
        str = enterString();
        sortString(str);
        std::string tmp_str = changeEvenToKB(str);
        buffer.push_back(tmp_str);

        setActiveThread(THREAD_EXPORT);
    }
}

void ProgramOne::exportStringThread()
{
    while (isActiveThread(THREAD_EXPORT))
    {
        std::string str;
        int bytesExported = 0;

        while (bytesExported >= 0 && !buffer.empty()) {
            int number = 0;

            str = buffer.back();
            buffer.pop_back();

            std::cout << "Changed string: " << str << std::endl;

            for (char ch: str) {
                if (std::isdigit(ch))
                    number += int(ch - '0');
            }

            if (socketClient.getErrorStatus() != 0)
            {
                socketClient.socketInit();
                socketClient.connectToServer();
            }

            std::cout << "Sending number: " << std::to_string(number) << std::endl;

            bytesExported = socketClient.exportData(std::to_string(number));

            std::cout << "Bytes exported: " << bytesExported << std::endl;
            if (bytesExported == -1) {
                buffer.push_back(str);
                socketClient.setErrorStatus(-1);
            }
        }
        setActiveThread(THREAD_ENTER);
    }
}

bool ProgramOne::isActiveThread(int threadId)
{
    std::unique_lock<std::mutex> lk(mtx);
    while (activeThread != THREAD_INVALID)
    {
        if (activeThread == threadId)
            return true;
        conditionVariable.wait(lk);
    }
    return false;
}

void ProgramOne::setActiveThread(int threadId)
{
    std::unique_lock<std::mutex> lk(mtx);
    activeThread = threadId;
    conditionVariable.notify_all();
}

std::string enterString() {
    std::string str;
    bool validString = false;

    do {
        std::cout << "Enter string: ";
        std::cin >> str;

        if (str.length() > 64) {
            std::cout << "Error: The length of the string should be no more than 64 characters" << std::endl;
            continue;
        }
        if (str.empty()) {
            std::cout << "Error: Empty string" << std::endl;
            continue;
        }
        if (!std::all_of(str.begin(), str.end(), ::isdigit)) {
            std::cout << "Error: Bad numeric string" << std::endl;
            continue;
        }

        validString = true;
    } while (validString == false);

    return str;
}

void sortString(std::string &str) {
    std::sort(str.begin(), str.end(), std::greater<int>());
}

std::string changeEvenToKB(const std::string& str) {
    std::string tmp_str = "";
    for (char ch: str)
    {
        if ((int(ch - '0') % 2) == 0)
        {
            tmp_str += "KB";
        }
        else {
            tmp_str += ch;
        }
    }
    return tmp_str;
}