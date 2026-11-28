#include <iostream> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <ctime>

using namespace std;

void log(ostream& out, const string& msg) {
    time_t t = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));
    out << "[" << buf << "] " << msg << "\n";
}

int main(){

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);


    int bind_addr = bind(server_socket,reinterpret_cast<sockaddr*>(&server_address),sizeof(server_address));
    if (bind_addr == -1){
        perror("bind");
        return 1;
    }

    int listen_addr = listen(server_socket,5);

    if (listen_addr == -1) {
        perror("listen");
        return 1;
    }

    int client_socket = accept(server_socket, nullptr, nullptr);

    if( client_socket ==-1 ){
        perror("accept");
        return 1;
    }
    else{
        cout << "Client connected!\n";
    }

    
    while(true){
        char buffer[1024]{};
        ofstream file("history.txt", ios::app);
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        string s(buffer, bytes_received);
        if (bytes_received > 0){
            cout << "Client's message:\n" << s << "\n";
            log(file, "Client's message: " + s);
        }
        else if(bytes_received == 0){
            cout << "Client disconnected!!" << "\n";
            break;
        }
        else{
            perror("recv");
            break;
        }                                     
           
        string message;
        cout << "Send a message:\n";
        getline(cin, message);
        if(message=="End"){
            break;
        }
        log(file, "Server's message: " + message);
        send(client_socket, message.data(), message.size(),0);
    }
    close(client_socket);
    close(server_socket);



}