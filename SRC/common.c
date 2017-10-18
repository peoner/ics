#include "common.h"


void SetVector(unsigned char __xdata * Addres, void * Vector) {
	unsigned char __xdata * TmpVector;
	TmpVector = Addres;
	*(TmpVector++) = 0x02;
	*(TmpVector++) = (unsigned char)((unsigned short)Vector >> 8);
	*(TmpVector) = (unsigned char)(Vector);
}
