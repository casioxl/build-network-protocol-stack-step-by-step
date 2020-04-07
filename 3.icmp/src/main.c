#include "syshead.h"
#include "basic.h"
#include "utils.h"
#include "tuntap_if.h"
#include "ethernet.h"
#include "arp.h"
#include "netdev.h"
#include "ipv4.h"


#define BUFLEN 100

void handle_frame(struct netdev *netdev, struct eth_hdr *hdr)
{
    switch (hdr->ethertype) {
    case ETH_P_ARP:
        printf("--------arp_incoming----------\n");
        arp_incoming(netdev, hdr);
        break;
    case ETH_P_IP:
        printf("Found IPv4\n");
		ipv4_incoming(netdev, hdr);
        break;
    default:
        printf("Unrecognized ethertype %x\n", hdr->ethertype);
        break;
    }
}




int main(int argc, char** argv)
{

    char buf[BUFLEN];
    char *dev = calloc(10, 1);
    struct netdev netdev;
    CLEAR(buf);


    system("sudo mknod /dev/net/tap c 10 200");
    system("sudo chmod 0666 /dev/net/tap");

    tun_init(dev);
    netdev_init(&netdev, "10.0.0.4", "00:0c:29:6d:50:25");
    arp_init();

    while(1) {
        if (tun_read(buf, BUFLEN) < 0) {
            print_error("ERR: Read from tun_fd: %s\n", strerror(errno));
        }


        struct eth_hdr *eth_hdr;
        eth_hdr=init_eth_hdr(buf);
        //print_eth_hdr(eth_hdr);
        handle_frame(&netdev, eth_hdr);

    }
    free(dev);
}
