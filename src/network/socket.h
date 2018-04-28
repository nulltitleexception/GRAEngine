#ifndef GRAE_ENGINE_SOCKET_H
#define GRAE_ENGINE_SOCKET_H

#include <string>
#include <memory>

namespace GRAE {
class Address {
public:
    class Address_Impl;

    Address_Impl *Impl;
public:
    Address(std::string ip, int port);

    Address(Address_Impl *impl);

    Address(const Address &address);

    ~Address();
};

class Message {
public:
    void *data;
    int size;
    Address sender;
public:
    Message(void *d, int s, Address from) : data(d), size(s), sender(from) {}

    std::string toString(int len) {
        return std::string(static_cast<const char *>(data), len);
    }

    std::string toString() {
        return toString(size);
    }

    void removePrefixBytes(int num) {
        data = static_cast<char *>(data) + num;
        size -= num;
    }

    ~Message() {
        char *buf = (char *) data;
        delete buf;
    }
};

class Socket {
private:
    class Socket_Impl;

    std::unique_ptr <Socket_Impl> Impl;
public:
    Socket(int port);

    ~Socket();

    void bind();

    Message *receive();

    void send(Address, void *, int);

    void send(Address a, std::string s) {
        send(a, (void *) s.c_str(), s.length());
    }
};
}

#endif //GRAE_ENGINE_SOCKET_H
