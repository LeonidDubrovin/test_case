#include "Server.h"

void checkData(std::string str);

int main() {
    std::string str;
    Server server;

    int receivedBytes;
    while (true)
    {
        server.socketAccept();
        server.clearBuffer();
        server.clearReceivedBytes();

        while (server.getReceivedBytes() >= 0)
        {
            receivedBytes = server.receiveData();
            if (receivedBytes > 0) {
                checkData(server.getData());
            } else if (receivedBytes <= 0) {
                std::cout << "Data retrieval error" << std::endl;
                server.closeAcceptSocket();
            }
        }
    }

    return EXIT_SUCCESS;
}

void checkData(std::string str) {
    int number = stoi(str);
    if (str.length() <= 2) {
        std::cout << "Length of number <= 2, given: " << str << std::endl;
    } else if (number % 32 != 0) {
        std::cout << "The number is not a multiple of 32, given: " << str << std::endl;
    } else {
        std::cout << "The number is OK: " << str << std::endl;
    }
}