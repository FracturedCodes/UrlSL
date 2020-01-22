#pragma once
enum ServerThreadType {
    Tls,
    Http
}

class ServerThread {
private:
    SOCKET _listenSocket;
    ServerThreadType _type;
    HANDLE _hThread;
    std::mutex* _acceptMutex;
    SSL_CTX* _tlsCtx;
    bool _continueThread;

    static void handleTls(void* s);
    //static void handleHttp(void* s); TODO
public:
    ServerThread(SOCKET listenSocket, ServerThreadType type, std::mutex* acceptMutex, SSL_CTX* tlsCtx);

    ServerThreadType GetType() const { return _type; }

    bool StopThread(bool forciblyStop=false);
};

class Server {
private:
    SOCKET _tlsListenSocket;
    std::list<ServerThread> _serverThreads;
    std::mutex _tlsAcceptMutex;

    SOCKET createListenSocket(int port);
    SSL_CTX* createTlsCtx();
public:
    Server(unsigned int TlsThreadCount, unsigned int HttpThreadCount);

    bool StopAllThreads(bool forciblyStop=false);
}