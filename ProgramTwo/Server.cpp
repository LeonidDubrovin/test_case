#include "Server.h"

Server::Server() {
    buffer = std::vector<char>(BUFFER_SIZE);

    socketInit();

    in_addr ip_address{};
    errorStatus = inet_pton(AF_INET, IP_ADDRESS,&ip_address);
    if (errorStatus <= 0) {
        std::cout << "Error in IP translation to special numeric format" << std::endl;
        return;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr = ip_address;

    socketBind();
    socketListen();
}

void Server::socketInit() {

    #if defined(_WIN32)
    WSADATA wsaData = {0};
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        perror("WSAStartup failed: \n");
        exit(EXIT_FAILURE);
    }
    #endif

    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket < 0) {
        perror("Error at socket(): ");
        std::cout << std::endl;
        close(listenSocket);
    } else {
        std::cout << "Server socket created" << std::endl;
    }
}

void Server::socketBind() {
    errorStatus = bind(listenSocket, (sockaddr *) &serverAddress, sizeof(serverAddress));
    if (errorStatus != 0) {
        perror("Error socket binding to server address");
        close(listenSocket);
    } else {
        std::cout << "Socket binding completed" << std::endl;
    }
}

void Server::socketListen() {
    errorStatus = listen(listenSocket, 1);
    if (errorStatus != 0) {
        perror("Can't start to listen");
        close(listenSocket);
    } else {
        std::cout << "Listening..." << std::endl;
    }
}

void Server::socketAccept() {
    acceptSocket = accept(listenSocket, (sockaddr *) &clientInfo, &clientInfoSize);
    if (acceptSocket < 0) {
        perror("Can't connect to a client");
        close(listenSocket);
        close(acceptSocket);
    } else {
        std::cout << "Connection with client is established" << std::endl;
    }
}

int Server::receiveData() {
    if (receivedBytes > 0)
        clearReceivedBytes();
    if (!buffer.empty())
        clearBuffer();

    receivedBytes = recv(acceptSocket, buffer.data(), buffer.size(), 0);
    return receivedBytes;
}

std::string Server::getData() {
    return buffer.data();
}

void Server::clearBuffer() {
    std::fill(buffer.begin(), buffer.end(), 0);
}

void Server::closeAcceptSocket() const {
    close(acceptSocket);
}

void Server::clearReceivedBytes() {
    receivedBytes = 0;
}