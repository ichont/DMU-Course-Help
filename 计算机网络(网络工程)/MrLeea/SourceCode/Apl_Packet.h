//
//  Apl_Packet.h
//  jw
//
//  Created by 李毓琪 on 2021/7/12.
//  Copyright © 2021 李毓琪. All rights reserved.
//

#ifndef Apl_Packet_h
#define Apl_Packet_h

#include "header.h"

void tcp_protocol_packet_Apl(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    tcp_header *tcp_protocol;
    tcp_protocol = (tcp_header*)(pkt_content + 14 + 20);
    printf("*****************TCP Protocol******************\n");
    printf("Source Port:%i\n", ntohs(tcp_protocol->sport));//源端口号 端口号范围0-65535
    printf("Destination Port:%i\n", ntohs(tcp_protocol->dport));//目的端口号
    printf("Header Length: %d\n", (tcp_protocol->hdrLen >> 4) * 4);//头部长度
    printf("Flags: 0x%.3x\n ", tcp_protocol->flags);//标示符号
    printf("seq: %u\n", ntohl(tcp_protocol->sequence));//序号
    printf("ack: %u\n", ntohl(tcp_protocol->ack));//确认号
    if (tcp_protocol->flags & 0x08) printf("[PSH]");//六个表示符表示
    if (tcp_protocol->flags & 0x10) printf("[ACK]");
    if (tcp_protocol->flags & 0x02) printf("[SYN]");
    if (tcp_protocol->flags & 0x20) printf("[URG]");
    if (tcp_protocol->flags & 0x01) printf("[FIN]");
    if (tcp_protocol->flags & 0x04) printf("[RST]");
    printf("\n");
    printf("Windows Size: %i\n", ntohs(tcp_protocol->windows));//窗口大小
    printf("Checksum: 0x%.4x\n", ntohs(tcp_protocol->checksum));//校验和
    printf("Urgent Pointer: %i\n", ntohs(tcp_protocol->urgent_pointer));//紧急指针
}

void udp_protocol_packet_Apl(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    udp_header *udp_protocol;
    udp_protocol = (udp_header*)(pkt_content + 14 + 20);

   printf("*****************UDP Protocol*****************\n");
    printf("Source Port:%i\n", ntohs(udp_protocol->sport));//源端口
    printf("Destination Port:%i\n", ntohs(udp_protocol->dport));//目的端口
    printf("Datalen: %i\n", ntohs(udp_protocol->datalen));//数据长度
    printf("Checksum: 0x%.4x\n", ntohs(udp_protocol->checksum));//校验和
}


void icmp_protocol_packet_Apl(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    icmp_header *icmp_protocol;
    icmp_protocol = (icmp_header*)(pkt_content + 14 + 20);

    printf("*****************ICMP Protocol*****************\n");
    printf("Type: %d\t", icmp_protocol->type);//类型
    switch (icmp_protocol->type)//具体类型
    {
    case 11:
        printf("[Time out]\n");
        break;
    case 8:
        printf("[request]\n");
        break;
    case 0:
        printf("[reply]\n");
        break;
    default:
        printf("[unknown type]\n");
        break;
    }
    printf("Code: %d\n", icmp_protocol->code);//代码
    printf("CheckSum: 0x%.4x\n", ntohs(icmp_protocol->checksum));//校验和
    printf("Identification: 0x%.4x\n", ntohs(icmp_protocol->identification));//标示符
    printf("Sequence: 0x%.4x\n", ntohs(icmp_protocol->sequence)); //序号
}

void arp_protocol_packet_Apl(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    arp_header *arp_protocol;
    arp_protocol = (arp_header*)(pkt_content + 14);

    printf("*****************ARP Protocol*****************\n");
    printf("Hardware Type: ");
    switch (ntohs(arp_protocol->hardware_type))
    {
    case 1:
        printf("Ethernet");
        break;
    default:
        break;
    }
    printf(" (%d)\n", ntohs(arp_protocol->hardware_type));
    printf("Protocol Type: \n");
    switch (ntohs(arp_protocol->protocol_type))
    {
    case 0x0800:
        printf("%s", "IP");
        break;
    case 0x0806:
        printf("%s", "ARP");
        break;
    case 0x0835:
        printf("%s", "RARP");
        break;
    default:
        printf("%s", "Unknown Protocol");
        break;
    }
    printf(" (0x%04x)\n", ntohs(arp_protocol->protocol_type));
    printf("Hardware Length: %d\n", arp_protocol->hardware_length);
    printf("Protocol Length: %d\n", arp_protocol->protocol_length);
    printf("Operation Code: ");
    switch (ntohs(arp_protocol->operation_code))
    {
    case 1:
        printf("Ask");
        break;
    case 2:
        printf("Recall");
        break;
    default:
        printf("Unknow");
        break;
    }
    printf(" (%i)\n", ntohs(arp_protocol->operation_code));
}

void ip_protocol_packet_Apl(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    ip_header *ip_protocol;
    sockaddr_in source, dest;
    char sourceIP[MAX_ADDR_LEN], destIP[MAX_ADDR_LEN];
    ip_protocol = (ip_header*)(pkt_content + 14);
    source.sin_addr.s_addr = ip_protocol->saddr;
    dest.sin_addr.s_addr = ip_protocol->daddr;
    strncpy(sourceIP, inet_ntoa(source.sin_addr), MAX_ADDR_LEN);
    strncpy(destIP, inet_ntoa(dest.sin_addr), MAX_ADDR_LEN);
    printf("*****************IP Protocol*********************\n");
    printf("Version: %d\n", ip_protocol->version_hlen >> 4);
    printf("Header Length: %d bytes\n", (ip_protocol->version_hlen & 0x0f) * 4);
    printf("Tos: %d\n", ip_protocol->tos);
    printf("Total Length: %d\n", ntohs(ip_protocol->tlen));
    printf("Identification: 0x%.4x (%i)\n", ntohs(ip_protocol->identification), ntohs(ip_protocol->identification));
    printf("Flags: %d\n", ntohs(ip_protocol->flags_offset) >> 13);
    printf("/-Reserved bit: %d\n", (ntohs(ip_protocol->flags_offset) & 0x8000) >> 15);
    printf("/-Don't fragment: %d\n", (ntohs(ip_protocol->flags_offset) & 0x4000) >> 14);
    printf("/-More fragment: %d\n", (ntohs(ip_protocol->flags_offset) & 0x2000) >> 13);
    printf("Fragment offset: %d\n", ntohs(ip_protocol->flags_offset) & 0x1fff);
    printf("Time to live: %d\n", ip_protocol->ttl);
    printf("Protocol Type: ");
    switch (ip_protocol->proto)
    {
    case 1:
        printf("ICMP");
        break;
    case 6:
        printf("TCP");
        break;
    case 17:
        printf("UDP");
        break;
    default:
        break;
    }
    printf(" (%d)\n", ip_protocol->proto);
    printf("Header checkSum: 0x%.4x\n", ntohs(ip_protocol->checksum));
    printf("Source IP:%s\n", sourceIP);
    printf("Destination IP:%s\n", destIP);

    if (ip_protocol->proto == htons(0x0600))
        tcp_protocol_packet_Apl(arg, pkt_header, pkt_content);
    else if (ip_protocol->proto == htons(0x1100))
        udp_protocol_packet_Apl(arg, pkt_header, pkt_content);
    else if (ip_protocol->proto == htons(0x0100))
        icmp_protocol_packet_Apl(arg, pkt_header, pkt_content);
}

void ethernet_protocol_packet_Apl(u_char *arg, const struct pcap_pkthdr *pkt_header, const u_char *pkt_content)
{
    ether_header *ethernet_protocol;//以太网协议
    u_short ethernet_type;            //以太网类型
    u_char *mac_string;                //以太网地址
    ethernet_protocol = (ether_header*)pkt_content;
    ethernet_type = ntohs(ethernet_protocol->ether_type);
    //以太网目标地址
    mac_string = ethernet_protocol->ether_dhost;
    printf("\n*************Ethernet Protocol*******************\n");
    printf("Destination Mac Address: %02x:%02x:%02x:%02x:%02x:%02x\n", // 输出目的MAC地址
        *mac_string,
        *(mac_string + 1),
        *(mac_string + 2),
        *(mac_string + 3),
        *(mac_string + 4),
        *(mac_string + 5));
    //以太网源地址
    mac_string = ethernet_protocol->ether_shost;
    printf("Source Mac Address: %02x:%02x:%02x:%02x:%02x:%02x\n", //输出源MAC地址
        *mac_string,
        *(mac_string + 1),
        *(mac_string + 2),
        *(mac_string + 3),
        *(mac_string + 4),
        *(mac_string + 5));
    printf("Ethernet type: ");//输出网络层协议
    switch (ethernet_type)
    {
    case 0x0800:
        printf("%s", "IP");
        break;
    case 0x0806:
        printf("%s", "ARP");
        break;
    case 0x0835:
        printf("%s", "RARP");
        break;
    default:
        printf("%s", "Unknown Protocol");
        break;
    }
    printf(" (0x%04x)\n", ethernet_type);
    switch (ethernet_type)
    {
    case 0x0800:
        ip_protocol_packet_Apl(arg, pkt_header, pkt_content);
        break;
    case 0x0806:
        arp_protocol_packet_Apl(arg, pkt_header, pkt_content);
        break;
    case 0x0835:
        printf("***************RARP Protocol*****************\n");
        printf("RARP\n");
        break;
    default:
        printf("*****************Unknown Protocol*****************\n");
        printf("Unknown Protocol\n");
        break;
    }
    printf("*******************Over*************************\n");
}
#endif /* Apl_Packet_h */
