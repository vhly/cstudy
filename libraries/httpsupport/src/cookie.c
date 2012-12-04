//
//  cookie.c
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "cookie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "stringutil.h"

Cookie *CreateCookie(char *name, char *value)
{
    Cookie *ret = NULL;
    if (name != NULL) {
        ret = (Cookie *)malloc(sizeof(Cookie));
        ret->name = name;
        ret->value = value;
        ret->path = NULL;
        ret->domain = NULL;
        ret->expireStr = NULL;
        ret->httpOnly = 0;
        ret->secure = 0;
        ret->maxAge = 0;
        ret->nextSub = NULL;
        ret->prevSub = NULL;
        ret->receivedTime = 0;
    }
    return ret;
}

char CookieIsExpired(Cookie *cookie)
{
    char ret = COOKIE_EXPIRE_EXPIRED;
    if (cookie != NULL) {
        ret = COOKIE_EXPIRE_NO;
        time_t t1 = time(NULL);

        if (cookie->maxAge != 0 && cookie->receivedTime != 0) {
            // maxAge unit is second, so * 1000
            long maxTime = cookie->receivedTime + (cookie->maxAge * 1000);
            if (t1 > maxTime) {
                ret = COOKIE_EXPIRE_EXPIRED;
            }
        }else if (cookie->expireStr != NULL){
            time_t t2 = ParseGMTTime(cookie->expireStr);
            if (t2 > 0) {
                if (t1 > t2) {
                    ret = COOKIE_EXPIRE_EXPIRED;
                }
            }
        }
    }
    return ret;
}

char *CookieToString(Cookie *cookie, char includeInfo)
{
    char *ret = NULL;
    if (cookie != NULL) {
        char *name = cookie->name;
        char *value = cookie->value;
        if (name != NULL) {
            int totalLen = 0;
            int nlen = strlen(name);
            int vlen = 0;

            if (value != NULL) {
                vlen = strlen(value);
            }

            totalLen = nlen + 1 + vlen + 1; // "name=value;"

            if (includeInfo) {
                char *str = cookie->path;
                int slen = 0;
                if (str != NULL){
                    slen = strlen(str);
                    if (slen > 0){
                        totalLen = totalLen + 6 + slen + 1; // "name=value; path=<path>;"
                    }
                }

                str = cookie->expireStr;
                if (str != NULL){
                    slen = strlen(cookie->expireStr);
                    if(slen > 0){
                        totalLen = totalLen + 9 + slen + 1; // "name=value; expires=<exprieStr>;"
                    }
                } else if (cookie->maxAge > 0) {
                    char tmp[20];
                    sprintf(tmp, "%d", cookie->maxAge);
                    slen = strlen(tmp);
                    if(slen > 0){
                        totalLen = totalLen + 8 + slen + 1; // "name=value; maxAge=<maxAge>;"
                    }
                }

                str = cookie->domain;
                if (str != NULL){
                    slen = strlen(cookie->domain);
                    if(slen > 0){
                        totalLen = totalLen + 8 + slen + 1; // "name=value; domain=<domain>;"
                    }
                }

                if (cookie->secure) {
                    totalLen = totalLen + 7 + 1; // "name=value; secure;"
                }
            }

            if (totalLen > 0) {
                ret = (char *)malloc((sizeof(char))*totalLen + 1);
                if (includeInfo) {
                    // TODO process
                    if (value != NULL){
                        sprintf(ret, "%s=%s;", name, value);
                    }else {
                        sprintf(ret, "%s=;", name);
                    }
                    int ddindex = strlen(ret);

                    char *buf;

                    char *str = cookie->path;
                    if (str != NULL){
                        buf = ret+ddindex;
                        sprintf(buf, " path=%s;", cookie->path);
                    }

                    ddindex = strlen(ret);

                    buf = ret + ddindex;

                    str = cookie->expireStr;
                    if (str != NULL){
                        sprintf(buf, " expires=%s;", cookie->expireStr);
                    } else if (cookie->maxAge > 0) {
                        sprintf(buf, " maxAge=%d;", cookie->maxAge);
                    }

                    ddindex = strlen(ret);

                    buf = ret + ddindex;

                    str = cookie->domain;
                    if (str != NULL){
                        sprintf(buf, " domain=%s;", cookie->domain);
                    }

                    ddindex = strlen(ret);

                    buf = ret + ddindex;

                    if (cookie->secure) {
                        sprintf(buf, " secure;");
                    }
                } else {
                    if (value != NULL){
                        sprintf(ret, "%s=%s;", name, value);
                    }else {
                        sprintf(ret, "%s=;", name);
                    }
                }
            }
        }
    }
    return ret;
}


Cookie *ParseCookie(char *cookieStr)
{
    // TODO Parse cookie string
    Cookie *ret = NULL;
    if (cookieStr != NULL) {
        int sindex = 0;
        int eindex = -1;

        int slen = strlen(cookieStr);

        int i;

        char ch;

        char *str;

        ret = (Cookie *)malloc(sizeof(Cookie));

        char *key = NULL;
        char *value = NULL;

        for(i = 0;i<slen;i++){
            ch = *(cookieStr + i);
            if (ch == ';') {
                eindex = i;
                int dlen = eindex - sindex;

                str = (char *)malloc((sizeof(char)) * dlen + 1);

                memset(str, 0, (sizeof(char)) * dlen + 1);

                strncpy(str, (cookieStr + sindex), dlen);

                // TODO Process key and value.

                value = strchr(str, '=');

                if(value != NULL){
                    int blen = value - str;
                    key = (char *)(malloc(sizeof(char) * blen + 1));
                    memset(key, 0, sizeof(char) * blen + 1);
                    strncpy(key, str, blen);
                    value++; // skip '=' character.
                    blen = value - str;
                    if(blen == slen){
                        value = NULL;
                    }
                } else {
                    key = str;
                }

                printf("CKParser: key %s\n", key);

                if(value != NULL){
                    printf("CKParser: value %s\n", value);
                }

                sindex = eindex;

                if (sindex < slen) {
                    sindex++;
                }
            }
        }

        if (eindex == -1){
            // TODO process only key=value style.
        }
    }
    return ret;
}

