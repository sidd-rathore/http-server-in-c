#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
int main(){
    WSADATA wsaData;
    int result;

    // Initialize Winsock
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
        return 1;
    }
    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Define server address
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    serverAddr.sin_family = AF_INET; 
    serverAddr.sin_port = htons(8080); 
    serverAddr.sin_addr.s_addr = INADDR_ANY; 

    // Connect to the server
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Start listening
    if (listen(sockfd, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("Server listening on port 8080...\n");

    // Accept incoming connections
    addr_size = sizeof(clientAddr);
    int clientSockfd = accept(sockfd,(struct sockaddr*)&clientAddr, &addr_size);
    if (clientSockfd == INVALID_SOCKET) {
        printf("Accept failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Client connected.\n");

    // Send data to the client
    const char *msg = "Hello, client!\n";
    int bytesSent = send(clientSockfd, msg, strlen(msg), 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("Send failed: %d\n", WSAGetLastError());
        closesocket(clientSockfd);
    }
    
    // Read data from the client
    ssize_t bytesRead;
    while ((bytesRead = recv(clientSockfd, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesRead] = '\0'; 
        printf("%s", buffer); 
    }
    if (bytesRead == 0) {
        printf("Client disconnected.\n");
    } else if (bytesRead == -1) {
        printf("Read failed: %d\n", WSAGetLastError());
    }
    // Clean up
    closesocket(clientSockfd);
    closesocket(sockfd);
    WSACleanup();
    return 0;
}