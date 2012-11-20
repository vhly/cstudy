//
//  cookie.h
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_cookie_h
#define httpsupport_cookie_h

typedef struct _Cookie {
    char *name;
    char *value;
    char *path;
    char *domain;
    
    char *expireStr;
    
    int maxAge;
    
    char secret;
    char httpOnly;
    
    
    struct _Cookie *prevSub;
    struct _Cookie *nextSub;
} Cookie, *CookieStore;

Cookie *CreateCookie(char *name, char *value);

#endif
