#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <thread>

using namespace std;

int PORT = 8888;
const int BUFFER_SIZE = 1024;

void read_messages(int sock) {
    while (true) {
        char buffer[BUFFER_SIZE] = {0};
        long valread = read(sock, buffer, BUFFER_SIZE);
        if (valread == 0) {
            cout << "Server disconnected" << endl;
            close(sock);
            exit(0);
        } else if (valread < 0) {
            cout << "Read error" << endl;
            close(sock);
            exit(1);
        }
        cout << "Message Received: " << buffer << endl;
    }
}

void write_messages(int sock) {
    while (true) {
        string message;
        cout << "Enter message: ";
        getline(cin, message);
        
        if (message.empty()) continue;
        
        send(sock, message.c_str(), message.length(), 0);
        cout << "Message sent" << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        PORT = atoi(argv[1]);
    }

    int sock;
    struct sockaddr_in serv_address;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_address.sin_addr) <= 0) {
        cout << "Invalid address" << endl;
        close(sock);
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_address, sizeof(serv_address)) < 0) {
        cout << "Connection Failed" << endl;
        close(sock);
        return -1;
    }

    thread read_thread(read_messages, sock);
    thread write_thread(write_messages, sock);

    read_thread.join();
    write_thread.join();

    return 0;
}
