#include "foo.h"

tDataBlob makeStruct()
{
	tDataBlob blob;
	blob.intValue = -1;
	blob.floatValue = 2.22;
	blob.intArray[0] = 0;
	blob.intArray[1] = 1;
	blob.intArray[2] = 2;
	return blob;
}