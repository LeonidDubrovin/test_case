#include "Client.h"

Client::Client() {
    in_addr ip_address{};
    socketInit();
    inet_pton(AF_INET, IP_ADDRESS, &ip_address);
    serverInfo.sin_port = htons(PORT);
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr = ip_address;
    connectToServer();
}

void Client::socketInit() {
    #if defined(_WIN32)
    WSADATA wsaData = {0};
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        wprintf(L"WSAStartup failed: %d\n", iResult);
        exit(1);
    }
    #endif

    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (connectSocket < 0) {
        perror("Error initialization: socket failed");
        std::cout << std::endl;
        close(connectSocket);
    } else {
        std::cout << "connectSocket initialization is OK\n";
    }
}

void Client::connectToServer() {
    errorStatus = connect(connectSocket, (sockaddr *) &serverInfo, serverInfoSize);
    if (errorStatus != 0) {
        perror("Error connection to server");
        std::cout << std::endl;
        close(connectSocket);
    } else {
        std::cout << "Client connected to server" << std::endl;
    }
}
