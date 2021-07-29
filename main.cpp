#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
/*****************************WARNING*****************************************************
 *     THIS APPLICATION IS NOT SECURE AND IS HIGHLY VULNERABLE TO BUFFEROVERFLOW ATTACKS *
 *                NEVER USE THIS CODE IN A PRODUCTION ENVIRONMENT!                       *
 ****************************************************************************************/
const int PORT = 5000;
void rcvAndSendMsg(int,struct sockaddr_in ,const char*, char*);

int main(){
    const char* openingMessage = "\n\n\nVelkommen til S2G sin supersecure server!\nJeg bare sender tilbake det du skriver til meg...\nMade by mr ntnu developer\n";
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int socketS2G = socket(AF_INET, SOCK_STREAM, 0); //AF_INET is IPv4, SOCK_STREAM is TCP ,and Protocol value for Internet Protocol(IP), which is 0.
    if(socketS2G == -1){
        std::cout << "Something went wrong...\n";
    } else {
        //bind addresse to socket object
        if(bind(socketS2G, (struct sockaddr *)&address, sizeof(address)) < 0){
            std::cout << "Could not bind address and port\n";
        } else {
            std::cout << "Port now open\n";
            //listen to socket
            if (listen(socketS2G, 3) < 0){
                std::cout << "Can't lisent to socket\n";
            } else {
                std::cout << "Listening on socket...\n";
                //accept requests from clients
                char buffer[1024];
                while(true){
                    std::cout << "\n\nReady to accept connection\n";
                    rcvAndSendMsg(socketS2G, address, openingMessage, buffer);
                }
            }
        }
    }
    return 0;
}

void rcvAndSendMsg(int socketS2G, sockaddr_in address, const char *openingMessage, char *buffer){
    socklen_t addresslen = sizeof(address);
    char rcvMsg[256];

    int socket = accept(socketS2G,(struct sockaddr *)&address,&addresslen);
    send(socket, openingMessage, strlen(openingMessage), 0);
    read(socket, buffer, 1024);
    strcpy(rcvMsg, buffer);
    send(socket, buffer, strlen(buffer), 0);
    close(socket);
}
