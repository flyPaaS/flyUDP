/*****************************************************************************
 *
 * File:        PackageHeader.h
 * Author:      iotazhang
 * Revision:    $Id$
 * Description: ���ݰ�ͷ
 *
 *****************************************************************************/

#if 0

#ifndef MM_PROXY_PACKAGE_HEADER_H
#define MM_PROXY_PACKAGE_HEADER_H

#include "ProxyProtocol.h"
#include "MmByteBuffer.h"

/**
 * ���ݰ�ͷ��
 */
struct PackageHeader {
    /**
     * ���캯��
     */
    PackageHeader();

    unsigned int packageLength;
    unsigned short headerLength;
    unsigned short version;
    unsigned int cmd;
    unsigned int seq;

    /**
     * ����
     */
    void reset();

    /**
     * ��ȡpayload����
     */
    unsigned int getPayloadLength() const;

    /**
     * �ӻ����ж�ȡ, ��ȡ��packageLength��headerLength����Ϊʣ��δ��ȡ����
     * @return ���ݰ�ͷ���Ƿ���ȷ
     */
    bool read(mm::ByteBuffer& buffer);

    /**
     * д�뻺��
     */
    void write(mm::ByteBuffer& buffer);
};

#endif

#endif
