/*****************************************************************************
 *
 * File:        Util.h
 * Author:      iotazhang
 * Revision:    $Id$
 * Description: ������
 *
 *****************************************************************************/

#ifndef MM_PROXY_UTIL_H
#define MM_PROXY_UTIL_H

#if 0
#include <mqueue.h>
#endif

#include <sstream>
#include <exception>
#include <cerrno>
#include <cstring>


#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>

namespace mm {

using std::string;
using std::ostringstream;
using std::exception;

/**
 * ת�ַ���
 */
template <class T>
string str(const T& t) {
    ostringstream os;
    os << t;
    return os.str();
}

/**
 * ת���ַ���
 */
string escape(const string& s);

/**
 * jsonת��
 */
string escapeJson(const string& s);

/**
 * �߳�������
 */
template <class T>
class ThreadAdapter {
public:
    /**
     * ���캯��
     */
    ThreadAdapter(T* t) : _t(t) {}

    /**
     * ����
     */
    void operator()() {
        _t->run();
    }

private:
    T* _t;
};

/**
 * ʮ�������ַ�����
 */
class Hex {
public:
    /**
     * ���ַ�תΪ��Ӧ�ֽ�, ��'1'תΪ1
     * @param c �ַ�
     * @return �ֽ�, �쳣�ַ����� 0xff
     */
    static unsigned char toByte(char c);

    /**
     * תΪ�ֽ�����
     * @param s Դ�ַ���
     * @param bytes �������, ��С����s��һ���С
     * @return �ֽ���, ����ʱ����-1
     */
    static int toBytes(const char* s, unsigned char* bytes);

    /**
     * תΪ�ַ���
     */
    static void toString(const unsigned char* bytes, int n, char* s);

private:
    static char _hexCharTable[16];
};

/**
 * ��ֹ����
 */
class Noncopyable {
protected:
    Noncopyable() {}
    ~Noncopyable() {}
private:
    Noncopyable(const Noncopyable&);
    const Noncopyable& operator=(const Noncopyable&);
};

/**
 * Posix ��Ϣ����
 */
class MessageQueue : public Noncopyable {
public:
    /**
     * ���캯��
     */
    MessageQueue();

    /**
     * ��������
     */
    virtual ~MessageQueue();

    /**
     * ����Ϣ����
     * @param path ��Ϣ����·��
     * @param oflag �򿪲���
     */
    void open(const string& path, int oflag = O_CREAT | O_RDWR);

    /**
     * ������Ϣ
     */
    bool send(const char* msg, size_t msgLen, unsigned int prio = 100);

    /**
     * ������Ϣ
     */
    bool receive(char* msg, size_t msgLen, unsigned int* prio = 0);

    /**
     * �ر���Ϣ����
     */
    void close();

private:

#if 0
    mqd_t   _mqd;
#endif
	
};

/**
 * ϵͳ�����쳣
 */
class SysCallException : public exception {
public:
    /**
     * ���캯��
     */
    SysCallException(int errCode, const string& errMsg, bool detail = true) : _errCode(errCode), _errMsg(errMsg) {
        if (detail) {
            _errMsg.append(", ").append(::strerror(errno));
        }
    }

    /**
     * ��������
     */
    virtual ~SysCallException() throw () {}

    /**
     * ��ȡ�������
     */
    int getErrorCode() const throw () {
        return _errCode;
    }

    /**
     * ��ȡ������Ϣ
     */
    const char* what() const throw () {
        return _errMsg.c_str();
    }

protected:
    int     _errCode;
    string  _errMsg;
};

/**
 * ��Ϣ�����쳣
 */
class MQException : public SysCallException {
public:
    /**
     * ���캯��
     */
    MQException(int errCode, const string& errMsg, bool detail = true)
        : SysCallException(errCode, errMsg, detail) {}

    /**
     * ��������
     */
    virtual ~MQException() throw () {}
};

} //namespace mm

#endif
