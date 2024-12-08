#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET server_fd, client_socket;
    sockaddr_in address;
    char buffer[1024] = {0};
    const char* response = "Hola desde el servidor!";

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 1);
    std::cout << "Esperando conexión...\n";

    client_socket = accept(server_fd, nullptr, nullptr);
    recv(client_socket, buffer, 1024, 0);
    std::cout << "Cliente: " << buffer << "\n";

    send(client_socket, response, strlen(response), 0);
    closesocket(client_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
