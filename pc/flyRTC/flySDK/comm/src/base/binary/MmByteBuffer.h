/***********************************************************************
 *
 * File:        ByteBuffer.h
 * Author:      iotazhang
 * Revision:    $Id: MmByteBuffer.h 292112 2012-04-21 17:32:10Z iotazhang $
 * Description: �ֽڻ���
 *
 ***********************************************************************/

#ifndef MM_PROXY_BYTE_BUFFER_H
#define MM_PROXY_BYTE_BUFFER_H

#include <vector>
#include <cstring>

namespace mm {

/**
 * �ֽڻ���
 */
class ByteBuffer {
public:
    /**
     * ���캯��
     */
    ByteBuffer() : _pos(0) {}

    /**
     * ��ȡ��С
     */
    size_t size() const {
        return _storage.size();
    }

    /**
     * ��ȡ�Ƿ�Ϊ�ջ���
     */
    bool empty() const {
        return _storage.empty();
    }

    /**
     * ��ȡʣ���ֽ���
     */
    size_t remaining() const {
        return _storage.size() - _pos;
    }

    /**
     * ���
     */
    void clear() {
        _storage.clear();
        _pos = 0;
    }

    /**
     * �������ݵ�����
     */
    void write(const void* buffer, size_t size) {
        _storage.insert(_storage.end(), (const char*)buffer, (const char*)buffer + size);
    }

    /**
     * �������ݵ�����
     */
    void write(ByteBuffer& buffer) {
        _storage.insert(_storage.end(), buffer.begin(), buffer.begin() + buffer.remaining());
        buffer.clear();
    }

    /**
     * �ӻ����ȡ����
     */
    size_t read(void* buffer, size_t size) {
        if (size > remaining()) {
            size = remaining();
        }

        memcpy(buffer, begin(), size);

        setPosition(_pos + size);
        return size;
    }

    /**
     * �ӻ����ȡ����, ���ƶ���λ��
     */
    size_t peek(char* buffer, size_t size) {
        if (size > remaining()) {
            size = remaining();
        }

        memcpy(buffer, begin(), size);
        return size;
    }

    /**
     * ��������
     */
    size_t skip(size_t size) {
        if (size > remaining()) {
            size = remaining();
        }

        setPosition(_pos + size);
        return size;
    }

    /**
     * ��������
     * @param pos ����λ��
     * @param buffer ����������
     * @param size ���������ݳ���
     */
    void insert(size_t pos, const char* buffer, size_t size) {
        if (pos > this->size()) {
            pos = this->size();
        }

        _storage.insert(_storage.begin() + pos, buffer, buffer + size);
    }

    /**
     * ��ȡ�����׵�ַ
     */
    const char* base() const {
        if (_storage.capacity() == 0) {
            return 0;
        }
        return &_storage[0];
    }

    /**
     * ��ȡ�����׵�ַ
     */
    char* base() {
        if (_storage.capacity() == 0) {
            return 0;
        }
        return &_storage[0];
    }

    /**
     * ��ȡ�����ַ
     */
    const char* begin() const {
        if (empty()) {
            return 0;
        }
        return &_storage[0] + _pos;
    }

    /**
     * ��ȡ�����ַ
     */
    char* begin() {
        if (empty()) {
            return 0;
        }
        return &_storage[0] + _pos;
    }

    /**
     * bool�Զ�ת��
     */
    operator bool() const {
        return remaining() > 0;
    }

    /**
     * ��ȡ��ǰλ��
     */
    int getPosition() const {
        return _pos;
    }

    /**
     * ���õ�ǰλ��
     */
    void setPosition(size_t pos) {
        if (pos >= size()) {
            clear();
        } else {
            _pos = pos;
        }
    }

    /**
     * Ԥ���仺��ռ�
     */
    void reserve(size_t size) {
        _storage.reserve(size);
    }

    /**
     * ����
     */
    size_t capacity() const {
        return _storage.capacity();
    }

private:
    std::vector<char> _storage;
    int _pos;
};

} //namespace mm

#endif
