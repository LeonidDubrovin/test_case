#ifdef __linux__
#include <arpa/inet.h>
#include <sys/socket.h>
#elif defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#include <unistd.h>
#include <iostream>

#define IP_ADDRESS "127.0.0.1"
#define PORT 8082

class Client {
public:
    Client();
    ~Client() {
        close(connectSocket);
    }

    void socketInit();
    void connectToServer();
    int exportData(const std::string& data) const {
        return send(connectSocket, data.data(), data.size(), 0);
    }
    int getErrorStatus() const {
        return errorStatus;
    }
    void setErrorStatus(int erStatus) {
        errorStatus = erStatus;
    }

private:
    int errorStatus;
    int connectSocket;
    sockaddr_in serverInfo;
    socklen_t serverInfoSize = sizeof(serverInfo);
};

