//
//  packet_handle.h
//  jw
//
//  Created by 李毓琪 on 2021/7/12.
//  Copyright © 2021 李毓琪. All rights reserved.
//

#ifndef packet_handle_h
#define packet_handle_h
#include "header.h"
// 以太网协议格式的定义
int tp;
void tcp_protocol_packet_handle(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    tcp_header *tcp_protocol;
    tcp_protocol = (tcp_header*)(pkt_content + 14 + 20);
    int sport_tmp = ntohs(tcp_protocol->sport);
    int dport_tmp = ntohs(tcp_protocol->dport);
    if( sport_tmp == 20 || sport_tmp == 21 || dport_tmp == 21 || dport_tmp == 21){
        printf("FTP   ");
    }else if(dport_tmp == 80 || sport_tmp == 80){
        printf("HTTP ");
    }
    else{
    printf("TCP  ");
    }
    printf("%5i ->", ntohs(tcp_protocol->sport));//源端口号 端口号范围0-65535
    printf("%-5i\t", ntohs(tcp_protocol->dport));//目的端口号
    printf("seq: %-15u", ntohl(tcp_protocol->sequence));//序号
    printf("ack: %-15u", ntohl(tcp_protocol->ack));//确认号
    if (tcp_protocol->flags & 0x08) printf("[PSH]");//六个表示符表示
    if (tcp_protocol->flags & 0x10) printf("[ACK]");
    if (tcp_protocol->flags & 0x02) printf("[SYN]");
    if (tcp_protocol->flags & 0x20) printf("[URG]");
    if (tcp_protocol->flags & 0x01) printf("[FIN]");
    if (tcp_protocol->flags & 0x04) printf("[RST]");
    printf("\n");
}


void udp_protocol_packet_handle(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    printf("UDP\t");
    udp_header *udp_protocol;
    udp_protocol = (udp_header*)(pkt_content + 14 + 20);
    printf("%5i ->", ntohs(udp_protocol->sport));//源端口
    printf("%-5i\n", ntohs(udp_protocol->dport));//目的端口

}

void icmp_protocol_packet_handle(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    printf("ICMP\t");
    icmp_header *icmp_protocol;
    icmp_protocol = (icmp_header*)(pkt_content + 14 + 20);
    switch (icmp_protocol->type)
    {
    case 11:
        printf("(Time out)\n");
        break;
    case 8:
        printf("(request)\n");
        break;
    case 0:
        printf("(reply)\n");
        break;
    default:
        printf("\n");
        break;
    }
}

void arp_protocol_packet_handle(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    printf("\tARP\t");
    arp_header *arp_protocol;
    arp_protocol = (arp_header*)(pkt_content + 14);
switch (ntohs(arp_protocol->operation_code))
    {
    case 1:
        printf("\tASK\n");
        break;
    case 2:
        printf("\tRECALL\n");
        break;
    default:
        break;
    }
}

void ip_protocol_packet_handle(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    ip_header *ip_protocol;
    sockaddr_in source, dest;
    char sourceIP[MAX_ADDR_LEN], destIP[MAX_ADDR_LEN];
    ip_protocol = (ip_header*)(pkt_content + 14);
    source.sin_addr.s_addr = ip_protocol->saddr;
    dest.sin_addr.s_addr = ip_protocol->daddr;
    strncpy(sourceIP, inet_ntoa(source.sin_addr), MAX_ADDR_LEN);
    strncpy(destIP, inet_ntoa(dest.sin_addr), MAX_ADDR_LEN);
    printf("%15s ->\t", sourceIP);
    printf("%-15s\t", destIP);
    if (ip_protocol->proto == htons(0x0600))
    {
        tp = 11;
        tcp_protocol_packet_handle(arg, pkt_header, pkt_content);
    }
    else if (ip_protocol->proto == htons(0x1100))
    {
        tp = 12;
        udp_protocol_packet_handle(arg, pkt_header, pkt_content);
    }
    else if (ip_protocol->proto == htons(0x0100))
    {
        tp = 13;
        icmp_protocol_packet_handle(arg, pkt_header, pkt_content);
    }
}

int ethernet_protocol_packet_handle(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    ether_header *ethernet_protocol;//以太网协议
    u_short ethernet_type;            //以太网类型
    ethernet_protocol = (ether_header*)pkt_content;
    ethernet_type = ntohs(ethernet_protocol->ether_type);
    switch (ethernet_type)
    {
    case 0x0800:
        tp = 1;
        ip_protocol_packet_handle(arg, pkt_header, pkt_content);
        break;
    case 0x0806:
        tp = 2;
        arp_protocol_packet_handle(arg, pkt_header, pkt_content);
        break;
    case 0x0835:
        tp = 3;
        printf("RARP\n");
        break;
    default:
        tp = 4;
        printf("Unknown Protocol\n");
        break;
    }
    return tp;
}

#endif /* packet_handle_h */
