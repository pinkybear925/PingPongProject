#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>

using namespace std;

int main(){

    string message; 
    int client_socket = socket(AF_INET,  SOCK_STREAM, 0);

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    int server_connection = connect(client_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));


    if(server_connection!=0){
        perror("connect");
        return 1;
    }

    while(true){
        cout << "Send a message:\n";
        getline(cin, message);
        send(client_socket, message.data(),message.size(),0);
        char buffer[1024]{};
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer)-1,0);
        if (bytes_received > 0) {
        cout << "Sthvers message:\n" << string(buffer, bytes_received) << endl;
        }
        else if (bytes_received == 0) {
            cout << "Server disconnected\n";
            break;
        }
        else {
            perror("recv");
            break;
        }
        }
    close(client_socket);
}
