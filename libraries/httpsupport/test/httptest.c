
#include "httpheader.h"

#include <stdio.h>

void TestHttpHeader()
{
    HttpHeader *header = CreateHttpHeader("Cookie", "JSESSIONID=902790172390790137490123");
    char *str = Header2String(header, 1);
    
    printf("ck -> %s", str);
}

int main(int argc, char *argv[]){
	printf("HttpSupport Test:\n");
	
    TestHttpHeader();
    
    return 0;
}

