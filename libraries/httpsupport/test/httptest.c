
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

    char *s1 = "    ";

    char *ds = TrimString(s1);

    printf("Trim: %s\n", ds);

    s1 = "    a";

    ds = TrimString(s1);

    printf("Trim: %s\n", ds);

    s1 = "    a ";

    ds = TrimString(s1);

    printf("Trim: %s\n", ds);

    s1 = "    a b c se a";

    ds = TrimString(s1);

    printf("Trim: %s\n", ds);

    s1 = "b b c se a";

    ds = TrimString(s1);

    printf("Trim: %s\n", ds);
    
    
}

void TestCookieSupport()
{
    Cookie *ck1 = CreateCookie("UName", "vhly");
    ck1->expireStr = "Mon, 03 Dec 2012 09:01:42 GMT";
    char st = CookieIsExpired(ck1);

    testAssertEquals(COOKIE_EXPIRE_EXPIRED, st, "Cookie Must expired\n");

    ck1->expireStr = "Wen, 05 Dec 2012 09:01:42 GMT";

    st = CookieIsExpired(ck1);

    testAssertEquals(COOKIE_EXPIRE_NO, st, "Cookie Must Not expired\n");

    ck1->expireStr = NULL;

    ck1->receivedTime = time(NULL);

    ck1->maxAge = 300;

    st = CookieIsExpired(ck1);

    testAssertEquals(COOKIE_EXPIRE_NO, st, "Cookie Must Not expired\n");

    ck1->receivedTime = time(NULL) - (2 * 24 * 60 * 60 * 1000);

    ck1->maxAge = 300;

    st = CookieIsExpired(ck1);

    testAssertEquals(COOKIE_EXPIRE_EXPIRED, st, "Cookie Must expired\n");

    ck1->path = "/";

    ck1->expireStr = "Wen, 01 Dec 2012 09:01:42 GMT";

    ck1->domain = ".baidu.com";

    ck1->secure = 1;

    char *cs = CookieToString(ck1, 1);

    printf("Cookie: %s\n", cs);

    Cookie *ck2 = ParseCookie(cs);

    printf("TestParse: %s\n", ck2->name);

    printf("TestParse: %s\n", ck2->value);

    printf("TestParse: %s\n", ck2->path);

    printf("TestParse: %s\n", ck2->domain);

    printf("TestParse: %s\n", ck2->expireStr);

    printf("TestParse: %d", ck2->secure);
    
    Cookie *ck3 = CreateCookie("ERROR", "Not Login");
    
    ck2->nextSub = ck3;
    
    ck3->prevSub = ck2;
    
   
    char *acc = CookieStreamToString(ck2);
    
    printf("Stream Cookie: %s\n", acc);
    
    CookieStore ncs = RemoveExpiredCookies(ck2);
    
    testAssertNotNull(ncs, "NCS must not be null \n");
    
    
    ck2->nextSub = ck3;
    
    ck3->prevSub = ck2;
    
    ck3->receivedTime = time(NULL) - 3000000;
    
    ck3->maxAge = 10;
    
    ncs = RemoveExpiredCookies(ck2);
    
    testAssertNull(ncs, "NCS must be null \n");
    
    Cookie *ck4 = ParseCookie("Key=value");
    
    testAssertNotNull(ck4, "CK4 must not be null\n");
}

int main(int argc, char *argv[]){
	printf("HttpSupport Test:\n");

    TestHttpHeader();

    TestStringUtil();

    TestCookieSupport();

    return 0;
}

