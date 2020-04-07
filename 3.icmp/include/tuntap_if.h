#ifndef TUNTAP_IF_H
#define TUNTAP_IF_H


int set_if_route(char *dev, char *cidr);

int set_if_address(char *dev, char *cidr);

int set_if_up(char *dev);

int tun_alloc(char *dev);

void tun_init(char *dev);

int tun_read(char *buf, int len);

int tun_write(char *buf, int len);

#endif

