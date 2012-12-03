
#include "httpheader.h"

#include <stdio.h>

#include "stringutil.h"

#include "testdefine.h"

void TestHttpHeader()
{
    HttpHeader *header = CreateHttpHeader("Cookie", "JSESSIONID=902790172390790137490123");
    char *str = Header2String(header, 1);
    
    printf("ck -> %s", str);
    
    HttpHeaders headers = header;
    
    HttpHeader *h1 = CreateHttpHeader("Set-Cookie", "NAME=goddk");
    HttpHeader *h2 = CreateHttpHeader("Set-Cookie", "Email=goddk@gmail.com");

    AppendHeader(headers, h1);
    AppendHeader(headers, h2);
    
    HttpHeaders cks = GetHttpHeaders(headers, "Set-Cookie");
    
    testAssertNotNull(cks, "Cks must found\n");
    
}

void TestStringUtil()
{
    ParseGMTTime("Mon, 03 Dec 2012 09:01:42 GMT");
}

int main(int argc, char *argv[]){
	printf("HttpSupport Test:\n");
	
    TestHttpHeader();
    
    TestStringUtil();
    
    return 0;
}

