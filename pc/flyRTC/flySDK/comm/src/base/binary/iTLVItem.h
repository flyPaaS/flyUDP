#pragma once

namespace Comm
{

/// tlv��
class tTLVItem
{
public:
	int iType;			///< ����
	int iLength;		///< ����
	char *pcValPtr;		///< ֵ
	int iNextOffset;	///< �¸�λ��

	/// ���캯��
	tTLVItem();

	/// ��������
	virtual ~tTLVItem() {};

	/// ӳ������
	virtual bool MapTo(const char *apcSrc, const int aiSrcSize, const int aiOffset) = 0;
};

/// Util struct for traversing Fixed-Size TLV buffer
class tFixedSizeTLVItem : public tTLVItem
{
public:	
	/// Map this struct to the given buffer
	bool MapTo(const char *apcSrc, const int aiSrcSize, const int aiOffset);
};

/// Util struct for traversing Variable-Size TLV buffer
class tVariableSizeTLVItem : public tTLVItem
{
public:
	/// Map this struct to the given buffer
	bool MapTo(const char *apcSrc, const int aiSrcSize, const int aiOffset);
};

}

