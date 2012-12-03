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
            long maxTime = cookie->receivedTime + cookie->maxAge;
            if (t1 <= maxTime) {
                ret = COOKIE_EXPIRE_EXPIRED;
            }
        }else if (cookie->expireStr != NULL){
            time_t t2 = ParseGMTTime(cookie->expireStr);
            if (t2 > 0) {
                if (t1 <= t2) {
                    ret = COOKIE_EXPIRE_EXPIRED;
                }
            }
        }
    }
    return ret;
}