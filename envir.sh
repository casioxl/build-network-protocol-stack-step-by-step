#!/bin/sh
sudo mknod /dev/net/tap c 10 200
sudo chmod 0666 /dev/net/tap
sysctl -w net.ipv4.ip_forward=1
iptables -I INPUT --source 10.0.0.4/24 -j ACCEPT
iptables -t nat -I POSTROUTING --out-interface ens33 -j MASQUERADE
iptables -I FORWARD --in-interface ens33 --out-interface tap0 -j ACCEPT
iptables -I FORWARD --in-interface tap0 --out-interface ens33 -j ACCEPT