#include <iostream>
#include <string>
#include <vector>
#include <errno.h>
#include <unistd.h>
#include <condition_variable>
#include <mutex>
#include <algorithm>
#include <thread>

#include "Client.h"

#define THREAD_INVALID -1
#define THREAD_ENTER	1
#define THREAD_EXPORT   2

class ProgramOne {
public:
    ProgramOne();
    void readStringThread();
    void exportStringThread();
    bool isActiveThread(int threadId);
    void setActiveThread(int threadId);


private:
    Client socketClient;
    std::vector<std::string> buffer;
    std::mutex mtx;
    std::condition_variable conditionVariable;
    int activeThread = 0;
};

std::string enterString();
void sortString(std::string &str);
std::string changeEvenToKB(const std::string& str);
