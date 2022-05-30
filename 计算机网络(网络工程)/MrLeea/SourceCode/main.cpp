//
//  main.cpp
//  jw
//
//  Created by 李毓琪 on 2021/7/12.
//  Copyright © 2021 李毓琪. All rights reserved.
//


#include "packet_handle.h"
#include "Apl_Packet.h"
#include <string.h>
void Get_packet();
void Apl_packet();
void choose_device();
void Flow_count();
void count_packet(int type);
void print_pro();
void change_con(double x);
void Write_TCP();
FILE *file = 0;
pcap_if_t *alldevs;    //适配器列表，它是一个链表的数据结构
pcap_if_t *d;        //保存某个适配器
pcap_t *fp;
int res;
struct pcap_pkthdr *header;
const u_char *pkt_data;
time_t local_tv_sec;
struct tm *ltime,start,end;
int start_usc,end_usc;
char timestr[16];
int count = 1;
int i = 0, inum;
int choice;
double tmp_usc;
char errbuf[PCAP_ERRBUF_SIZE];
int num;
u_int netmask;
int total;
int type;
struct bpf_program fcode;
const u_char *data[15000];
struct pcap_pkthdr *heads[15000];
char *name_pro[9]={"null","IP","ARP","RARP","Unknow","TCP","UDP","ICMP"};
int count_pro[9];//1->IP协议，2->ARP,3->RARP，4->Unknow,11->TCP,12->UDP,13->ICMP;
int main()
{
    choose_device();
    while(1){
        printf("1.抓包\n");
        printf("2.分析包\n");
        printf("3.发送包\n");
        printf("4.修改设备\n");
        printf("0.退出\n");
        printf("请选择功能：");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                Get_packet();
                break;
            case 2:
                Apl_packet();
                break;
            case 3:
                Write_TCP();
                break;
            case 4:
                choose_device();
                break;
            case 0:
                pcap_close(fp);//释放
                pcap_freealldevs(alldevs);
                fclose(stdin);
                if (file)
                    fclose(file);
                exit(0);
                break;
            default:
                printf("输入错误!");
                break;
        }
    }
}
void Get_packet(){
    printf("请输入需要抓包的数目:");
    scanf("%d",&num);
    *data = new u_char[num];
    *heads= new pcap_pkthdr[num];
    int type = 0;
    count = 0;
    while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0&& count <= num && count <= 14999)//获取一个报文
    {
        if (res == 0)//超时
            continue;
        local_tv_sec = header->ts.tv_sec;//将时间戳转化为可识别格式
        ltime = localtime(&local_tv_sec);
        if(count == 1){
            start = *ltime;
            start_usc = header->ts.tv_usec;
        }else{
            total += header -> len;
        }
        strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);
        data[count] = pkt_data;
        heads[count] = header;
        printf("No.%d\t%s.%.6d\t", count++, timestr,header->ts.tv_usec);//输出序号 时间戳 长度
        //深挖
        type = ethernet_protocol_packet_handle(NULL, header, pkt_data);
        count_packet(type);
    }
    end = *ltime;
    end_usc = header -> ts.tv_usec;
    double tmp = ((end . tm_hour - start . tm_hour) * 60 + end . tm_min - start . tm_min) * 60 + (end . tm_sec - start . tm_sec) + (end_usc - start_usc) * 0.000001;
    printf("抓包时间:%lfs\t",tmp);
    tmp_usc = total / tmp;
    change_con(tmp_usc);
    print_pro();
}

void Apl_packet(){
    int num;
    char temp[LINE_LEN + 1];
    printf("请输入您需要分析的包的序号:");
    scanf("%d",&num);
    printf("*****************Packet Content*****************\n");
    printf("****************👇Hexadecimal👇***************************👇ASCII👇***\n");
    for (i = 0; i < heads[num]->caplen; ++i)
      {
          printf("%.2x ", data[num][i]);
          if (isgraph(data[num][i]) || data[num][i] == ' ')//判断包内数据是否为空
              temp[i % LINE_LEN] = data[num][i];
          else
              temp[i % LINE_LEN] = '.';

          if (i % LINE_LEN == 15)
          {
              temp[16] = '\0';
              printf("        ");
              printf("%s", temp);
              printf("\n");
              memset(temp, 0, LINE_LEN);
          }
      }
    ethernet_protocol_packet_Apl(NULL, heads[num], data[num]);
}



void choose_device(){
    pcap_freealldevs(alldevs);
    if (pcap_findalldevs(&alldevs, errbuf) == -1)//获取所有驱动列表
    {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }
    for (d = alldevs; d != NULL; d = d->next)//输出设备名字
    {
        printf("%d. %s\n", ++i, d->name);
    }

    if (i == 0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return;
    }

    //获取选择编号
    while (1)
    {
        printf("输入设备的序号(1-%d): ", i);
        scanf("%d", &inum);
        fflush(stdin);
        if (inum > 0 && inum <= i)
            break;
    }

    for (d = alldevs, i = 0; i < inum - 1; ++i, d = d->next);//跳转到指定的网卡
    if ((fp = pcap_open_live(d->name, 65536, 1, 1, errbuf)) == NULL)//打开适配器
    {
        fprintf(stderr, "\nUnable to open the adapter: %s\n", errbuf);
        pcap_freealldevs(alldevs);
        return;
    }

    //检查链路层的类型
    if (pcap_datalink(fp) != DLT_EN10MB) //判断是否为以太网
    {
        fprintf(stderr, "该程序只能选择网卡\n");
        pcap_close(fp);//关闭pcap_open_live
        pcap_freealldevs(alldevs);//释放所有设备
        return;
        }
}

void count_packet(int type){
    switch(type){
        case 1:
            count_pro[1] ++;
            break;
        case 2:
            count_pro[2] ++;
            break;
        case 3:
            count_pro[3] ++;
            break;
        case 4:
            count_pro[4] ++;
            break;
        case 11:
            count_pro[5] ++;count_pro[1] ++;
            break;
        case 12:
            count_pro[6] ++;count_pro[1] ++;
            break;
        case 13:
            count_pro[7] ++;count_pro[1] ++;
            break;
        default:
            count_pro[8] ++;
            break;
    }
}

void print_pro()
{
    printf("\n统计结果：");
    for(int i=1 ; i<=8 ; i++){
        if(count_pro[i] != 0){
            printf("%s:%d\t",name_pro[i],count_pro[i]);
        }
    }
    printf("\n");
}

void change_con(double x){
    printf("当前网络的平均网速:");
    if(x > 1024){
        x /= 1024;
        if(x > 1024){
            x /= 1024;
            if(x > 1024){
                x /=1024;
                printf("%.3f GByte/s",x);
                return;
            }
            printf("%.3f MByte/s",x);
            return;
        }
        printf("%.3f KByte/s",x);
        return;
    }
    printf("%.3f Byte/s",x);
    return;
}

void Write_TCP(){
        u_char packet[100];
           //设置本机的MAC地址
           packet[0] = 255;
           packet[1] = 255;
           packet[2] = 255;
           packet[3] = 255;
           packet[4] = 255;
           packet[5] = 255;
           //设置目的主机的MAC地址
           packet[6] = 1;
           packet[7] = 1;
           packet[8] = 1;
           packet[9] = 1;
           packet[10] = 1;
           packet[11] = 1;
            packet[12] = 0x08;//IPv4协议
            packet[13] = 00;
    for(int i = 14 ; i < 100 ; i++){
        packet[i] = 1;
    }
     if (pcap_sendpacket(fp, packet, 100 /* size */) != 0){
        fprintf(stderr, "\nError sending the packet: \n", pcap_geterr(fp));
     }else{
         printf("Send Success!");
         fflush(stdin);
         getchar();getchar();
     }
}

