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
    
    /**
     * Must used by https protocol
     */
    char secret;
    
    /**
     * Only support http protocol not support https
     */
    char httpOnly;
    
    /**
     * Received from http server's time
     */
    long receivedTime;
    
    
    struct _Cookie *prevSub;
    struct _Cookie *nextSub;
} Cookie, *CookieStore;

/**
 * Create default cookie by name and value
 * @param name char* name must not be NULL
 * @param value char* value can be NULL or other content.
 * @return Cookie* Set name and value, other field is NULL or default 0
 */
Cookie *CreateCookie(char *name, char *value);

/**
 * Check Cookie is expired?
 * @param cookie Cookie
 * @return char 0 is no; 1 is expired
 */
char CookieIsExpired(Cookie *cookie);

#endif
