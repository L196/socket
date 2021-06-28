#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <cstring>

class Socket_addr
{
    private:
        struct sockaddr_storage address;

    private:
        Socket_addr(struct sockaddr_storage addr)
            :
            address(addr)
        {
            //memcpy(&address, &addr, sizeof(struct sockaddr_in));
        }
/*        Socket_addr(inetaddr_in6 addr)
        {
            memcpy(&address, &addr, sizeof(struct sockaddr_in6));
        }*/

    public:
        Socket_addr()
        {
        }

        Socket_addr set_address(const char *addr, int port, int fm)
        {
            struct sockaddr_storage address;

            switch(fm)
            {
                case AF_INET:
                    struct sockaddr_in *address_4;
                    address_4 = (struct sockaddr_in *)&address;
                    address_4->sin_family = AF_INET;
                    address_4->sin_port = htons(port);
                    //address.sin_addr.s_addr = inet_addr(addr);
                    //address.sin_addr.s_addr = INADDR_ANY;
                    //inet_aton(addr, &address_4->sin_addr);
                    inet_pton(AF_INET, addr, &address_4->sin_addr);
                    break;

                case AF_INET6:
                    struct sockaddr_in6 *address_6 = (struct sockaddr_in6 *)&address;
                    address_6->sin6_family = AF_INET6;
                    address_6->sin6_port = htons(port);
                    //inet_aton(addr, &address_6->sin6_addr);
                    inet_pton(AF_INET6, addr, &address_6->sin6_addr);
                    break;
            }

            Socket_addr a(address);
            return a;
        }

        void get_address(void)
        {
            std::cout << address.ss_family << ' ' << AF_INET6 << std::endl;
        }
};

int main(void)
{
    Socket_addr a;

    a = a.set_address("127.0.0.1", 80, AF_INET6);
    a.get_address();

    return 0;
}
