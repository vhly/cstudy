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
    char ret = 1;
    if (cookie != NULL) {
        ret = 0;
        if (cookie->maxAge != 0 && cookie->receivedTime != 0) {
            long maxTime = cookie->receivedTime + cookie->maxAge;
            time_t t1 = time(NULL);
            if (t1 <= maxTime) {
                ret = 1;
            }
        }else if (cookie->expireStr != NULL){
            
        }
    }
    return ret;
}