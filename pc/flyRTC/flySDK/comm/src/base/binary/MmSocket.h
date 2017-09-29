/***********************************************************************
 *
 * File:        Socket.h
 * Author:      iotazhang
 * Revision:    $Id: MmSocket.h 376038 2012-12-05 07:48:00Z iotazhang $
 * Description: socket����
 *
 ***********************************************************************/

#ifndef MM_PROXY_SOCKET_H
#define MM_PROXY_SOCKET_H

#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include "MmUtil.h"
#include "MmByteBuffer.h"

namespace mm {

using std::string;

//////////////////////////////////////////////////////////////////SocketAddress

/**
 * Socket��ַ��
 */
class SocketAddress {
public:
    /**
     * ��ַ����
     */
    enum Type {
        TYPE_LOOPBACK = 1, /**< ���ص�ַ */
        TYPE_INNER = 2, /**< ������ַ */
        TYPE_OUTER = 3 /**< ������ַ */
    };

    /**
     * ���캯��
     */
    SocketAddress();

    /**
     * ���캯��
     * @param port �˿�
     */
    SocketAddress(unsigned short port);

    /**
     * ���캯��
     * @param addr ��ַ
     */
    SocketAddress(const string& addr);

    /**
     * ���캯��
     * @param addr ��ַ
     * @param port �˿�
     */
    SocketAddress(const string& addr, unsigned short port);

    /**
     * ���õ�ַ
     * @param addr ��ַ
     */
    SocketAddress(const sockaddr_in& addr);

    /**
     * ���õ�ַ
     * @param port �˿�
     */
    void setAddress(unsigned short port);

    /**
     * ���õ�ַ
     * @param addr ��ַ
     */
    void setAddress(const string& addr);

    /**
     * ���õ�ַ
     * @param addr ��ַ
     * @param port �˿�
     */
    void setAddress(const string& addr, unsigned short port);

    /**
     * ��ȡip, �����ֽ���
     */
    unsigned long getIp() const;

    /**
     * ��ȡ�˿�, �����ֽ���
     */
    unsigned short getPort() const;

    /**
     * ��ȡ��ַ
     * @param addr ��ַ, �������
     */
    void getAddress(sockaddr_in& addr) const;

    /**
     * ���õ�ַ
     * @param addr ��ַ
     */
    void setAddress(const sockaddr_in& addr);

    /**
     * ��ȡ��������
     */
    string getHost() const;

    /**
     * תΪ�ַ���
     */
    string toString() const;

    /**
     * ��ȡ��ַ����
     */
    Type getAddressType() const;

    /**
     * ��ȱȽ�
     */
    bool operator ==(const SocketAddress& addr) const;

    /**
     * ��ȡ��ַ����
     */
    static Type getAddressType(const string& ip);

private:
    unsigned long   _ip;
    unsigned short  _port;
};

///////////////////////////////////////////////////////////////////////Socket

/**
 * Socket ����
 */
class SocketBase {
public:
    /**
     * ���캯��
     */
    SocketBase();

    /**
     * ���캯��
     */
    SocketBase(int handle);

    /**
     * ��������
     */
    virtual ~SocketBase();

    /**
     * ��ȡSocket���
     */
    virtual int getSocketHandle() const;

    /**
     * ����Socket���
     */
    virtual void setSocketHandle(int handle);

    /**
     * detach ���
     */
    virtual int detachSocketHandle();

    /**
     * ��ȡ�Ƿ������
     */
    virtual bool getNonBlocking() const;

    /**
     * ���÷�����ģʽ
     */
    virtual void setNonBlocking(bool on);

    /**
     * ���÷�����ģʽ
     */
    static void setNonBlocking(int fd, bool on);

    /**
     * ��ȡ�Ƿ������
     */
    static bool getNonBlocking(int fd);

    /**
     * �ر�Socket
     */
    virtual void close();

    /**
     * ����socket
     */
    virtual void reset();

protected:

    /**
     * ��ʼ�����
     */
    void initHandle();

    /**
     * ��ȡѡ��
     */
    socklen_t getOption(int level, int option, void* value, socklen_t optLen) const;

    /**
     * ����ѡ��
     */
    void setOption(int level, int option, void* value, socklen_t optLen) const;

    int _handle;
};

/**
 * Socket��
 */
class Socket : public SocketBase {
public:
    /**
     * ���캯��
     */
    Socket();

    /**
     * ���캯��
     * @param addr ���ӵ�ַ
     */
    Socket(const SocketAddress& addr);

    /**
     * ���캯��
     */
    Socket(int handle);

    /**
     * ��������
     */
    virtual ~Socket();

    /**
     * ��ȡ���ͳ�ʱ/���ӳ�ʱ
     */
    int getSendTimeout() const;

    /**
     * ���÷��ͳ�ʱ/���ӳ�ʱ
     * @param timeout ��ʱ������
     */
    void setSendTimeout(int timeout);

    /**
     * ��ȡ���ճ�ʱ
     */
    int getReceiveTimeout() const;

    /**
     * ���ý��ճ�ʱ
     */
    void setReceiveTimeout(int timeout);

    /**
     * ���÷��ͻ�����
     */
    void setSendBufferSize(int size);

    /**
     * ���ý��ջ�����
     */
    void setReceiveBufferSize(int size);

    /**
     * ���� quick ack
     */
    void setQuickAck(bool on);

    /**
     * ��ȡ�Զ˵�ַ
     */
    SocketAddress getRemoteAddress() const;

    /**
     * ��ȡ�Զ˵�ַ
     */
    static SocketAddress getRemoteAddress(int fd);
    
    /**
     * ��ȡ���˵�ַ
     */
    SocketAddress getLocalAddress() const;

    /**
     * ��ȡ���˵�ַ
     */
    static SocketAddress getLocalAddress(int fd);

    /**
     * ���ӷ�����
     */
    virtual void connect(const SocketAddress& addr);

    /**
     * ��������
     * @param data ����������
     * @param dataSize ���ݴ�С
     * @param again �Ƿ��޻����д
     * @return ʵ�ʷ����ֽ���
     */
    virtual int send(const char* data, int dataSize, bool* again = 0);

    /**
     * ��������
     * @param data ����������
     * @param again �Ƿ��޻����
     * @return ʵ�ʷ����ֽ���
     */
    virtual int send(ByteBuffer& data, bool* again = 0);

    /**
     * ��������
     * @param buffer ���ջ���
     * @param bufferSize �����С
     * @param again �Ƿ������ݿɶ�
     * @return ʵ�ʽ����ֽ���
     */
    virtual int receive(char* buffer, int bufferSize, bool* again = 0);

    /**
     * ��������
     * @param buffer �������ݵ�����
     * @param again �Ƿ������ݿɶ�
     * @return ʵ�ʽ����ֽ���
     */
    virtual int receive(ByteBuffer& buffer, bool* again = 0);

    /**
     * ���ղ�����ָ���ֽ��������ݵ�����
     * @param buffer �������ݵ�����
     * @param maxBytes �������ֽ���
     * @param again �Ƿ������ݿɶ�
     * @return �����ֽ���
     */
    virtual int receive(ByteBuffer& buffer, int maxBytes, bool* again = 0);

    /**
     * �ر�����
     */
    virtual void shutdownInput();

    /**
     * �ر����
     */
    virtual void shutdownOutput();

    /**
     * ͬʱ�ر��������
     */
    virtual void shutdown();
};

///////////////////////////////////////////////////////////////////////ServerSocket

/**
 * �����Socket
 */
class ServerSocket : public SocketBase {
public:
    /**
     * ���캯��
     */
    ServerSocket();

    /**
     * ���캯��
     * @param addr �󶨵�ַ
     */
    ServerSocket(const SocketAddress& addr);

    /**
     * ��������
     */
    virtual ~ServerSocket();

    /**
     * ��ȡaccept��ʱ
     */
    int getAcceptTimeout() const;

    /**
     * ����accept��ʱ
     */
    void setAcceptTimeout(int timeout);

    /**
     * �����˿�
     * @param addr �����˿�
     */
    virtual void listen(const SocketAddress& addr);

    /**
     * accept �ͻ�������
     */
    virtual Socket* accept();

    /**
     * accept �ͻ�������
     */
    virtual int acceptfd(SocketAddress* addr);
};

///////////////////////////////////////////////////////////////////////SocketException

/**
 * socket�쳣
 */
class SocketException : public SysCallException {
public:
    /**
     * ���캯��
     */
    SocketException(const string& errMsg, bool detail = true)
        : SysCallException(errno, errMsg, detail) {}

    /**
     * ��������
     */
    virtual ~SocketException() throw () {}
};

} //namespace mm

#endif

