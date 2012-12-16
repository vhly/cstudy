#include <stdio.h>

#include "bytestream.h"

int main(int argc, char *argv[])
{
    ByteStream stream = CreateDefaultByteBlock();
    char data[10];
    for (int i = 1; i <= 10; i++) {
        data[i-1] = i;
    }
    AppendByteData(stream, data, 1, 8);
    AppendByteData(stream, data, 0, 5);
	return 0;
}
