#include <stdio.h> //printf(), fprintf(), perror(), getc()
#include <sys/socket.h> //socket(), bind(), sendto(), recvfrom()
#include <arpa/inet.h> // struct sockaddr_in, struct sockaddr, inet_ntoa(), inet_aton()
#include <stdlib.h> //atoi(), exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <string.h> //memset(), strcmp()
#include <unistd.h> //close()

#define MSG_FAILURE -1

#define MAX_MSGSIZE 1024
#define MAX_BUFSIZE (MAX_MSGSIZE + 1)

int  get_socket();
void sockaddr_init (unsigned short, struct sockaddr *);
int  udp_send(int, const char *, int, struct sockaddr *);
int  udp_receive(int, char *, int, struct sockaddr *);

int main(int argc, char* argv[]) {

    unsigned short port = (unsigned short)atoi(argv[1]);
    struct sockaddr servSockAddr, clitSockAddr;
    char recvBuffer[MAX_BUFSIZE];

    int server_sock = get_socket();
    sockaddr_init(port, &servSockAddr);

    if (bind(server_sock, &servSockAddr, sizeof(servSockAddr)) < 0) {
        perror("bind() failed.");
        exit(EXIT_FAILURE);
    }

    while(1) {
        int recvMsgSize = udp_receive(server_sock, recvBuffer, MAX_BUFSIZE, &clitSockAddr);
        if (recvMsgSize == MSG_FAILURE) continue;

        printf("message received from %s.\n", inet_ntoa(((struct sockaddr_in *)&clitSockAddr)->sin_addr));

        int sendMsgSize = udp_send(server_sock, recvBuffer, recvMsgSize, &clitSockAddr);
        if (sendMsgSize == MSG_FAILURE) continue;
    }
}

int get_socket() {
    int sock;

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock < 0){
        perror("socket() failed.");
        exit(EXIT_FAILURE);
    }

    return sock;
}

void sockaddr_init (unsigned short port, struct sockaddr *sockaddr) {

    struct sockaddr_in sockaddr_in;
    sockaddr_in.sin_family = AF_INET;

    if (inet_aton("", &sockaddr_in.sin_addr) == 0) {
        sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    if (port == 0) {
        fprintf(stderr, "invalid port number.\n");
        exit(EXIT_FAILURE);
    }
    sockaddr_in.sin_port = htons(port);

    *sockaddr = *((struct sockaddr *)&sockaddr_in);
}

int udp_send(int sock, const char *data, int size, struct sockaddr *sockaddr) {
    int sendSize;
    sendSize = sendto(sock, data, size, 0, sockaddr, sizeof(*sockaddr));
    if (sendSize != size) {
        perror("sendto() failed.");
        return MSG_FAILURE;
    }
    return sendSize;
}

int udp_receive(int sock, char *buffer, int size, struct sockaddr *sockaddr) {
    unsigned int sockaddrLen = sizeof(*sockaddr);
    int receivedSize = recvfrom(sock, buffer, size, 0, sockaddr, &sockaddrLen);
    if (receivedSize < 0) {
        perror("recvfrom() failed.");
        return MSG_FAILURE;
    }

    return receivedSize;
}
