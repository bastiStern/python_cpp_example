#pragma once

#pragma pack(push, 1)
struct tDataBlob
{
	int intValue;
	float floatValue;
	int intArray[3];
};
#pragma pack(pop)

tDataBlob makeStruct();