#include "socket.h"

#include <iostream>

#define MAX_PACKET_BYTES 1024

#ifdef _WIN32
//Use winsock2 sockets
#include <winsock2.h>

namespace GRAE {
class WSAHandler {
private:
    WSADATA WSAData;
public:
    WSAHandler() {
        WSAStartup(MAKEWORD(2, 0), &WSAData);
    }

    ~WSAHandler() {
        WSACleanup();
    }
};

class Address::Address_Impl {
public:
    SOCKADDR_IN address;
public:
    Address_Impl(std::string ip, int port) {
        address.sin_addr.s_addr = inet_addr(ip.c_str());
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
    }

    Address_Impl(SOCKADDR_IN addr) : address(addr) {}

    Address_Impl(const Address_Impl &other) {
        address = other.address;
    }

    ~Address_Impl() {}
};

class Socket::Socket_Impl {
private:
    WSAHandler *wsa;
    SOCKET sock;
    SOCKADDR_IN sockAddr;
public:
    Socket_Impl(int port) {
        wsa = new WSAHandler();
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        memset(&sockAddr, 0, sizeof(sockAddr));
        sockAddr.sin_addr.s_addr = INADDR_ANY;
        sockAddr.sin_family = AF_INET;
        sockAddr.sin_port = htons(port);
    }

    ~Socket_Impl() {
        closesocket(sock);
        delete wsa;
    }

    void bind() {
        ::bind(sock, (SOCKADDR *) &sockAddr, sizeof(sockAddr));
    }

    void send(Address address, void *data, int len) {
        if (sendto(sock, (const char *) data, len, 0, (SOCKADDR *) &(address.Impl->address),
                   sizeof(address.Impl->address)) == SOCKET_ERROR) {
            printf("sendto() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
    }

    Message *receive() {
        SOCKADDR_IN si_other;
        int slen = sizeof(si_other);
        char *buf = new char[MAX_PACKET_BYTES];
        //clear the buffer by filling null, it might have previously received data
        memset(buf, '\0', MAX_PACKET_BYTES);

        //try to receive some data, this is a blocking call
        int recv_len;
        recv_len = recvfrom(sock, buf, MAX_PACKET_BYTES, 0, (struct sockaddr *) &si_other, &slen);
        if (recv_len == SOCKET_ERROR) {
            printf("recvfrom() failed with error code : %d", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
        Address from(new Address::Address_Impl(si_other));
        return new Message(buf, recv_len, from);
    }

};
}

#else
//Assume linux and use linux sockets (add mac support eventually?)

#endif

namespace GRAE {
Address::Address(std::string ip, int port) : Impl(new Address::Address_Impl(ip, port)) {}

Address::Address(Address_Impl *impl) {
    Impl = impl;
}

Address::Address(const Address &address) {
    Impl = new Address_Impl(*address.Impl);
}

Address::~Address() {
    delete Impl;
}

Socket::Socket(int port) : Impl(std::make_unique<Socket::Socket_Impl>(port)) {}

Socket::~Socket() {}

void Socket::bind() {
    Impl->bind();
}

Message *Socket::receive() {
    return Impl->receive();
}

void Socket::send(Address addr, void *data, int size) {
    Impl->send(addr, data, size);
}
}