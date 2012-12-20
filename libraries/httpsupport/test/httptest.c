
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <netinet/in.h>

#include <sys/socket.h>

#include <netdb.h>

#include <arpa/inet.h>

#include "httpheader.h"

#include "stringutil.h"

#include "cookie.h"

#include "socketclient.h"

#include "urlsupport.h"

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
    
    HttpHeader *h3 = ParseHttpHeader("Expires: Wed, 10 Dec 2012 09:01:32 GMT");
    
    testAssertNotNull(h3, "h3 must not be null\n");

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
    
    char *ss = "This is a Good Library for Every developers";
    
    s1 = Substring(ss, 0, 4);
    
    testAssertNotNull(s1, "Substring: s1 must not be null\n");
    
    testAssertStringEquals("This", s1, "Substring: s1 must is This\n");
    
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

void TestSocket()
{
    struct hostent *host = gethostbyname("www.baidu.com");
    printf("Host Name: %s\n", host->h_name);
    char str[64];
    inet_ntop(host->h_addrtype, host->h_addr, str, 64);
    printf("Host IP: %s\n", str);
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in *target = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    memset(target, 0, sizeof(struct sockaddr_in));
    target->sin_family = AF_INET;
    target->sin_port = htons(80);
    target->sin_addr.s_addr = inet_addr(str);
    
    int ok = connect(sock, (struct sockaddr *)target, sizeof(struct sockaddr));
    printf("Connect ret: %d\n", ok);
    if (ok == -1) {
        printf("Connect error!\n");
    }else{
        
    }
    shutdown(sock, 2);
    
    
    SocketRequest *request = (SocketRequest *)malloc(sizeof(SocketRequest));
    memset(request, 0, sizeof(SocketRequest));
    request->hostName = "www.sina.com.cn";
    request->port = 80;
    
    sock = ConnectSocket(request);
    printf("Request Socket: %d\n", sock);
    
    if (sock != -1) {
        shutdown(sock, 2);
    }
}

void TestURLSupport()
{
    ParseURL("http://www.google.com.hk/");
    ParseURL("http://www.google.com.hk");
    ParseURL("http://www.google.com.hk/?t=1");
    ParseURL("http://www.google.com.hk/?t=1#asd");
    ParseURL("http://www.google.com.hk/image/search?q=Java");
    ParseURL("http://www.google.com.hk/image/search.cgi?q=Java");
    ParseURL("http://www.google.com.hk/image/search.cgi#hello");
    ParseURL("http://www.google.com.hk/image/search.cgi#hello?q=java");
    ParseURL("https://www.google.com.hk/image/search.cgi#hello?q=java");
    ParseURL("www.google.com.hk/image/search.cgi#hello?q=java");
    
    URL *url = ParseURL("http://www.google.com.hk/image/search.cgi?q=Java#fkk");
    char *surl = URLtoString(url);
    printf("URL: %s\n", surl);
}

int main(int argc, char *argv[]){
	printf("HttpSupport Test:\n");

    TestHttpHeader();

    TestStringUtil();

    TestCookieSupport();
    
    TestSocket();
    
    TestURLSupport();

    return 0;
}

