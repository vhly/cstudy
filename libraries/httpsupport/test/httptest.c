
#include "httpheader.h"

#include <stdio.h>

#include "stringutil.h"

#include "cookie.h"

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
    time_t tt1 = ParseGMTTime("Mon, 03 Dec 2012 09:01:42 GMT");

    time_t tt2 = ParseGMTTime("Mon, 03 Dec   2012 09:01:42 GMT");

    long lt1 = tt1 / 10000;

    long lt2 = tt2 / 10000;

    testAssertEquals(lt2, lt1, "Time must equals\n");
}

void TestCookieSupport()
{
    Cookie *ck1 = CreateCookie("UName", "vhly");
    ck1->expireStr = "Mon, 03 Dec 2012 09:01:42 GMT";
    char st = CookieIsExpired(ck1);

    testAssertEquals(COOKIE_EXPIRE_EXPIRED, st, "Cookie Must expired\n");

}

int main(int argc, char *argv[]){
	printf("HttpSupport Test:\n");

    TestHttpHeader();

    TestStringUtil();

    TestCookieSupport();

    return 0;
}

