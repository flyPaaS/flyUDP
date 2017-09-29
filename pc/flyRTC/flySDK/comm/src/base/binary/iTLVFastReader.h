#ifndef __ITLVFASTREADER_H__
#define __ITLVFASTREADER_H__

#include "iTLVPack.h"

namespace Comm
{

/// TLVPack�����������ȡ��
/** �������ֶηǳ����TLVPack�����ȡ���ڳ�ʼ���Լ�TLVPackÿһ��д��������״ζ�ȡ��������֯������
	����һ�㣬֮�����һֱ���Ƕ������ͻ�ܿ��ˡ�
*/
class TLVFastReader
{
public:
	/// ���캯��
	TLVFastReader();
	~TLVFastReader();

	/// ����tlv pack
	int SetTLVPack(CTLVPack *apTLV);

	/// get char
	int GetChar(const int aiType, char *apcVal);

	/// get byte
	int GetByte(const int aiType, unsigned char *apcVal);	

	/// get short
	int GetShort(const int aiType, short *aphVal, bool abNetOrder = true);

	/// get word
	int GetWord(const int aiType, unsigned short *apwVal, bool abNetOrder = true);

	/// get int
	int GetInt(const int aiType, int *apiVal, bool abNetOrder = true);

	/// get unsigned int
	int GetUInt(const int aiType, unsigned int *apuVal, bool abNetOrder = true);

	/// get long
	int GetLong(const int aiType, long *aplVal, bool abNetOrder = true);

	/// get unsigned long
	int GetDWord(const int aiType, unsigned long *apdwVal, bool abNetOrder = true);

	/// get long long
	int GetLongLong(const int aiType, long long *apllVal, bool abNetOrder = true);

	/// get unsigned long long
	int GetULongLong(const int aiType, unsigned long long *apullVal, bool abNetOrder = true);

	/// get bool
	int GetBool(const int aiType, bool *apbVal);

	/// get buffer
	int GetBuf(const int aiType, char *apcVal, int *apiLen);

	/// get nested tlv buffer
	int GetNestedTLVBuf(const int aiType, CTLVPack **appoVal);

protected:
	void *m_pInternal;
	
protected:
	int CreateIndex();
	template <typename T> int GetNumber(const int aiType, T *apoVal);
};

}
#endif /* __ITLVFASTREADER_H__ */

