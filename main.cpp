#include "server.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong entry - usage : <port number> <password>" << std::endl;
        return 1;
    }

    Server s(atoi(argv[1]), std::string(argv[2]));
    
    s.start();
    s.handleConnections();

    return 0;
}