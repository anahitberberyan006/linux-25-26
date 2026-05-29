#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>

unsigned short checksum(void* b, int len)
{
    unsigned short* buf = (unsigned short*)b;
    unsigned int sum = 0;

    while (len > 1)
    {
        sum += *buf++;
        len -= 2;
    }

    if (len == 1)
    {
        sum += *(unsigned char*)buf;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);

    return (unsigned short)(~sum);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <IPv4>\n";
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0)
    {
        perror("socket");
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;

    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) != 1)
    {
        std::cerr << "Invalid IPv4 address\n";
        return 1;
    }

    char packet[64];
    memset(packet, 0, sizeof(packet));

    icmphdr* icmp = (icmphdr*)packet;

    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = getpid();
    icmp->un.echo.sequence = 1;

    icmp->checksum = 0;
    icmp->checksum = checksum(packet, sizeof(icmphdr));

    ssize_t sent = sendto(
        sockfd,
        packet,
        sizeof(icmphdr),
        0,
        (sockaddr*)&addr,
        sizeof(addr)
    );

    if (sent < 0)
    {
        perror("sendto");
        return 1;
    }

    char buffer[1024];

    sockaddr_in reply_addr{};
    socklen_t reply_len = sizeof(reply_addr);

    ssize_t received = recvfrom(
        sockfd,
        buffer,
        sizeof(buffer),
        0,
        (sockaddr*)&reply_addr,
        &reply_len
    );

    if (received < 0)
    {
        perror("recvfrom");
        return 1;
    }

    iphdr* ip = (iphdr*)buffer;
    icmphdr* reply =
        (icmphdr*)(buffer + (ip->ihl * 4));

    if (reply->type == ICMP_ECHOREPLY &&
        reply->un.echo.id == getpid())
    {
        char ipstr[INET_ADDRSTRLEN];

        inet_ntop(
            AF_INET,
            &reply_addr.sin_addr,
            ipstr,
            sizeof(ipstr)
        );

        std::cout << "Echo reply from "
                  << ipstr << '\n';
    }
    else
    {
        std::cout << "Unexpected ICMP packet\n";
    }

    close(sockfd);

    return 0;
}
