#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#ifdef __linux__
#include <arpa/inet.h>
#include <sys/socket.h>
#elif defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#define IP_ADDRESS "127.0.0.1"
#define PORT 8082

class Server
{
public:
    Server();
    ~Server()
    {
        close(listenSocket);
        close(acceptSocket);
    }

    void socketInit();
    void socketBind();
    void socketListen();
    void socketAccept();
    int receiveData();
    void clearBuffer();
    std::string getData();
    int getReceivedBytes() const {
        return receivedBytes;
    }
    void clearReceivedBytes();
    void closeAcceptSocket() const;

private:
    const int BUFFER_SIZE = 100;
    int listenSocket;
    int acceptSocket;
    int errorStatus;
    int receivedBytes = 0;
    sockaddr_in serverAddress;
    sockaddr_in clientInfo;
    socklen_t clientInfoSize = sizeof(clientInfo);
    std::vector<char> buffer;
};
