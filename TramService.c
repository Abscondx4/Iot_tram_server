#include "TramService.h"

int aqi;
int temperature;
int humidity;
int CommandNum;
int testnum;
int retTest;

pid_t pidUTR;

#define OWNADDR "192.168.8.21"
#define OWNPORT 9999

#define DESTI_PORT 9999
#define DESTI_IP "192.168.8.111"

typedef struct homeMsg
{
    int homeAqi;
    int homeTemp;
    int homeHum;

} hMsg;
/**
 * 通过UDP协议发送数据。
 *
 * 该函数初始化一个UDP套接字，绑定本地地址，并向指定服务器地址发送数据。
 *
 * @param result 包含要发送的数据的字符串。
 */
void UdpTramSent(char *result)
{
    // 定义一个缓冲区来存储要发送的数据
    char resu[100];
    // 将要发送的数据复制到缓冲区
    strcpy(resu, result);

    // 创建一个UDP套接字
    int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd == -1)
    {
        // 处理套接字创建失败的情况
        perror("socket error");
        return;
    }

    // 设置发送方的地址信息
    struct sockaddr_in ownAddr;
    // 设置IP地址
    ownAddr.sin_addr.s_addr = inet_addr(OWNADDR);
    // 设置地址族为Internet地址族
    ownAddr.sin_family = AF_INET;
    // 设置端口
    ownAddr.sin_port = htons(OWNPORT);

    // 绑定套接字到发送方地址
    bind(socketfd, (struct sockaddr *)&ownAddr, sizeof(ownAddr));

    // 设置目标服务器的地址信息
    struct sockaddr_in destiAddr;
    // 设置服务器IP地址
    destiAddr.sin_addr.s_addr = inet_addr(DESTI_IP);
    // 设置地址族为Internet地址族
    destiAddr.sin_family = AF_INET;
    // 设置服务器端口
    destiAddr.sin_port = htons(DESTI_PORT);

    // 向服务器发送数据
    int ret = sendto(socketfd, resu, strlen(resu), 0, (struct sockaddr *)&destiAddr, sizeof(destiAddr));

    // 关闭套接字
    close(socketfd);
    return;
}

/**
 * UdpTramRecv函数用于通过UDP协议接收消息。
 * 该函数创建一个UDP套接字，并将其绑定到指定的本地地址和端口上，
 * 以便接收来自网络的消息，并打印消息中的环境质量、温度和湿度信息。
 */
void *UdpTramRecv()
{
    // 创建UDP套接字
    int socketfd1 = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketfd1 == -1)
    {
        // 如果创建套接字失败，输出错误信息并返回
        perror("socket error");
        return;
    }

    // 冗余代码，此处应避免重复创建套接字
    // int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    // if (socketfd == -1)
    // {
    //     perror("socket error");
    //     return;
    // }

    // 初始化本机地址结构
    struct sockaddr_in ownAddr;
    ownAddr.sin_addr.s_addr = inet_addr(OWNADDR); // 设置本机IP地址
    ownAddr.sin_family = AF_INET;                 // 设置地址族为Internet地址族
    ownAddr.sin_port = htons(OWNPORT);            // 设置本机端口并进行字节序转换

    // 将套接字绑定到本机地址和端口
    bind(socketfd1, (struct sockaddr *)&ownAddr, sizeof(ownAddr));

    // 无限循环等待接收消息
    while (1)
    {
        hMsg recv;                                                         // 定义用于接收消息的结构体变量
        int ret = recvfrom(socketfd1, &recv, sizeof(recv), 0, NULL, NULL); // 接收消息
        if (ret == -1)
        {
            // 如果接收消息失败，输出错误信息并返回
            perror("recvfrom error");
            return;
        }
        // 打印接收到的消息中的环境数据
        printf("recv: %d %d %d\n", recv.homeAqi, recv.homeTemp, recv.homeHum);
        aqi = recv.homeAqi;
        temperature = recv.homeTemp;
        humidity = recv.homeHum;
    }

    // 关闭套接字
    close(socketfd1);
    return;
}
