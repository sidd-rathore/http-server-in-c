#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#define DS_SB_IMPLEMENTATION
#define DS_SS_IMPLEMENTATION
#define DS_IO_IMPLEMENTATION
#include "ds.h"

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
    int clientSockfd;
    while(1) {
        addr_size = sizeof(clientAddr);
        clientSockfd = accept(sockfd,(struct sockaddr*)&clientAddr, &addr_size);
        if (clientSockfd == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            closesocket(sockfd);
            WSACleanup();
            return 1;
        }

        printf("Client connected.\n");

        
        
        // Read data from the client
        ssize_t bytesRead;
        bytesRead = recv(clientSockfd, buffer, sizeof(buffer), 0);
        buffer[bytesRead] = '\0'; 
        printf("%s", buffer); 
        unsigned int buffer_len = bytesRead;
        
        
        
        if (bytesRead == 0) {
            printf("\nClient disconnected.\n");
            continue;
            
        } else if (bytesRead == -1) {
            printf("\nRead failed: %d\n", WSAGetLastError());
           
        }
        
        
        // GET /home HTTP/1.1
        // Host: localhost:8080
        // User-Agent: curl/8.9.1
        // Accept: */*
        //
        ds_string_slice request, token;
        ds_string_slice_init(&request, buffer, buffer_len);

        // VERB
        ds_string_slice_tokenize(&request, ' ', &token);
        char *verb = NULL;
        ds_string_slice_to_owned(&token, &verb);
        if( strcmp(verb,"GET") != 0){
            DS_LOG_ERROR("not a get request");
            // TODO: send 400
            char *not_allowed = "HTTP/1.1 405 Method Not Allowed\nContent-Type: text/plain\nCContent-Length: 23\n\n405 Method Not Allowed";
            send(clientSockfd, not_allowed, strlen(not_allowed), 0);
            closesocket(clientSockfd);
            continue;
        }

        // PATH
        ds_string_slice_tokenize(&request, ' ', &token);
        char *path = NULL;
        ds_string_slice_to_owned(&token, &path);

        // TODO: if files do not exists return 404
        char *content = NULL;
        int content_len = ds_io_read_file(path + 1, &content);
        if (content_len == -1 || content == NULL) {
            char *not_found = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: 13\n\n404 Not Found";
            send(clientSockfd, not_found, strlen(not_found), 0);
            closesocket(clientSockfd);
            continue;
        }
        

        ds_string_builder response_builder;
        ds_string_builder_init(&response_builder);
        ds_string_builder_append(&response_builder,"HTTP/1.1 200 OK\n Content-Type: text/html\nContent-Length: %d\n\n%s",content_len ,content);
        char *response = NULL;
        ds_string_builder_build(&response_builder, &response);
        int response_len = strlen(response);
        // Send the response to the client
        int bytesSent = send(clientSockfd, response, response_len, 0);
        if (bytesSent == SOCKET_ERROR) {
            printf("Send failed: %d\n", WSAGetLastError());
            closesocket(clientSockfd);
        }

    }
    // Clean up
    closesocket(clientSockfd);
    closesocket(sockfd);
    WSACleanup();
    return 0;
}