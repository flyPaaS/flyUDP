/**
@file
@brief unsigned int����תbyte����С��֧�֣���unsigned int����С��128����ֻռ��һ���ֽڡ�
*/

#pragma once

namespace Comm
{

/// Encodes the given uint value into the given buffer.
/** @return Returns the number of bytes needed to encode the value.
*/
int EncodeVByte32(unsigned int auValue, unsigned char *apcBuffer);

/// Decodes an uint value from the given buffer.
/** @return Puts the value into the given variable ("value") and 
			returns the number of bytes consumed from the buffer.
*/
int DecodeVByte32(unsigned int *apuValue, const unsigned char *apcBuffer);

}
