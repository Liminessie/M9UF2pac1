#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Enlazar librería

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in serv_addr;
    const char* message = "Hola servidor!";
    char buffer[1024] = {0};

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, message, strlen(message), 0);
    recv(sock, buffer, 1024, 0);

    std::cout << "Servidor: " << buffer << "\n";
    closesocket(sock);
    WSACleanup();

    return 0;
}
