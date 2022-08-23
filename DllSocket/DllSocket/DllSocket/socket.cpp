/************************************************************************************/
/*
C++ socket ��̬���ļ��ӿ�
Author: Hongliang Zhang_WHU                                                                   
Date:   2022-07-20
Type:	2D
*/
/************************************************************************************/

#include <winsock2.h> 
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

/*socket����ز�����������д������������ʧ�ܿ��ܻῨ��fluent*/
extern "C" __declspec(dllexport) char *FluentSocket(const std::string &sendMessage)
{
    WSADATA wsaData;
    /*����ͨѶ���׽���*/
    SOCKET s;
    /*python��ַ�����*/
    SOCKADDR_IN pythonAddress;
    /*����python��������Ϣ*/
    char recvInfo[1024];
    /*UDF���շ������ݵĴ�С*/
    int returenValue;
    /*ͨѶ�ӿ�*/
    int Port = 10003;
    /*���ڸ�ʽ�������Ϣ*/
    std::string msg;
 
    returenValue = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (returenValue != 0)
    {
        MessageBox(NULL, TEXT("Socket��ʼ��ʧ�ܣ�"), NULL, MB_OK);
        return NULL;
    }
 
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        MessageBox(NULL,TEXT("��ȡ�׽���ʧ�ܣ�"), NULL, MB_OK);
        ::WSACleanup();
        return NULL;
    }
 
    pythonAddress.sin_family = AF_INET;
    /*���ö˿�*/
    pythonAddress.sin_port = htons(Port);
    /*���õ�ַ*/
    pythonAddress.sin_addr.S_un.S_addr = ::inet_addr("127.0.0.1");
 
    if (::connect(s, (SOCKADDR *)&pythonAddress, sizeof(pythonAddress)) == SOCKET_ERROR)
    {
        msg = "Socket����ʧ�ܣ������룺";
        msg += std::to_string((long double)::WSAGetLastError());
        MessageBox(NULL,(TEXT(msg.c_str())), NULL, MB_OK);
        ::closesocket(s);
        ::WSACleanup();
        return NULL;
    }
 
    returenValue = ::send(s, sendMessage.c_str(), sendMessage.size(), 0);
    if (returenValue == SOCKET_ERROR)
    {
        msg = "Socket����ʧ�ܣ������룺";
        msg += std::to_string((long double)::WSAGetLastError());
        MessageBox(NULL,TEXT(msg.c_str()), NULL, MB_OK);
        ::closesocket(s);
        ::WSACleanup();
        return NULL;
    }
 
    returenValue = ::recv(s, recvInfo, sizeof(recvInfo), 0);
    if (returenValue == SOCKET_ERROR)
    {
        msg = "Socket����ʧ�ܣ������룺";
        msg += std::to_string((long double)::WSAGetLastError());
        MessageBox(NULL,TEXT(msg.c_str()), NULL, MB_OK);
        ::closesocket(s);
        ::WSACleanup();
        return NULL;
    }
 
    /*ע��˲���������fluent���������*/
    recvInfo[returenValue] = '\0';
	return (recvInfo);
    ::closesocket(s);
    ::WSACleanup();
}