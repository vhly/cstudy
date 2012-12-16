#include <stdio.h>

#include "bytestream.h"
#include "datastream.h"

int main(int argc, char *argv[])
{
    ByteStream stream = CreateDefaultByteBlock();
    char data[10];
    for (int i = 1; i <= 10; i++) {
        data[i-1] = i;
    }
    
    WriteByteToStream(stream, 1);
    
	return 0;
}
