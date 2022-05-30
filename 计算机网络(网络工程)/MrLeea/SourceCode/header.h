//
//  header.h
//  jw
//
//  Created by 李毓琪 on 2021/7/12.
//  Copyright © 2021 李毓琪. All rights reserved.
//

#ifndef header_h
#define header_h

#include "pcap.h"
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include "stdlib.h"
#include <time.h>
#pragma comment(lib, "wpcap.lib")
#pragma comment(lib, "Ws2_32.lib")

#define LINE_LEN 16
#define MAX_ADDR_LEN 16

typedef struct ether_header {
    u_char ether_dhost[6];        // 目标MAC地址
    u_char ether_shost[6];        // 源MAC地址
    u_short ether_type;            // 以太网类型
}ether_header;

// 用户保存4字节的IP地址
typedef struct ip_address {
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

// 用于保存IPV4的首部
typedef struct ip_header {
    u_char version_hlen;        // 首部长度 版本
    u_char tos;                    // 服务质量
    u_short tlen;                // 总长度
    u_short identification;        // 身份识别
    u_short flags_offset;        // 标识 分组偏移
    u_char ttl;                    // 生命周期
    u_char proto;                // 协议类型
    u_short checksum;            // 包头测验码
    u_int saddr;                // 源IP地址
    u_int daddr;                // 目的IP地址
}ip_header;

// 用于保存TCP首部
typedef struct tcp_header {
    u_short sport;
    u_short dport;
    u_int sequence;                // 序列码
    u_int ack;                    // 回复码
    u_char hdrLen;                // 首部长度保留字
    u_char flags;                // 标志
    u_short windows;            // 窗口大小
    u_short checksum;            // 校验和
    u_short urgent_pointer;        // 紧急指针
}tcp_header;

// 用于保存UDP的首部
typedef struct udp_header {
    u_short sport;                // 源端口
    u_short dport;                // 目标端口
    u_short datalen;            // UDP数据长度
    u_short checksum;            // 校验和
}udp_header;

// 用于保存ICMP的首部
typedef struct icmp_header {
    u_char type;                // ICMP类型
    u_char code;                // 代码
    u_short checksum;            // 校验和
    u_short identification;        // 标识
    u_short sequence;            // 序列号
    u_long timestamp;            // 时间戳
}icmp_header;

// 用于保存ARP的首部
typedef struct arp_header {
    u_short hardware_type;                    // 格式化的硬件地址
    u_short protocol_type;                    // 协议地址格式
    u_char hardware_length;                    // 硬件地址长度
    u_char protocol_length;                    // 协议地址长度
    u_short operation_code;                    // 操作码
    u_char source_ethernet_address[6];        // 发送者硬件地址
    u_char source_ip_address[4];            // 发送者协议地址
    u_char destination_ethernet_address[6];    // 目的方硬件地址
    u_char destination_ip_address[4];        // 目的方协议地址
}arp_header;

#endif /* header_h */
