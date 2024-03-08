#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <thread>

#define SOCKET_CREATION_ERROR -1
#define BIND_ERROR -2
#define LISTEN_ERROR -3
#define EXIT_SUCCESS 0

using namespace std;
const int PORT = 8888;
const int BUFFER_SIZE = 1024;

void handle_client(int client_socket) {
    while (true) {
        
        char buffer[BUFFER_SIZE] = {0};
        long valread = read(client_socket, buffer, BUFFER_SIZE);
        if (valread == 0) {
            cout << "Client disconnected" << endl;
            close(client_socket);
            break;
        } else if (valread < 0) {
            cout << "Read error" << endl;
            close(client_socket);
            break;
        }
        cout << "Message received: " << buffer << endl;

        
        string response;
        cout << "Enter response: ";
        getline(cin, response);
        if (response.empty()) {
            cout << "No response sent." << endl;
            continue;
        }
        send(client_socket, response.c_str(), response.length(), 0);
        cout << "Response sent." << endl;
    }
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cout << "Socket creation failed" << endl;
        exit(SOCKET_CREATION_ERROR);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        cout << "Bind failed" << endl;
        exit(BIND_ERROR);
    }
    int yes = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    if (listen(server_fd, 10) < 0) {
        cout << "Listen failed" << endl;
        exit(LISTEN_ERROR);
    }
    cout << "Listening on port: " << PORT << endl;

    while (true) {
        cout << "Waiting for new connection ..." << endl;
        client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            cout << "Accept error" << endl;
            continue;
        }
        cout << "New connection, socket fd is " << client_socket << endl;

        thread t(handle_client, client_socket);
        t.detach();
    }
    return EXIT_SUCCESS;
}
