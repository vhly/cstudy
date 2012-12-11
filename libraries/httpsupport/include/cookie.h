//
//  cookie.h
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_cookie_h
#define httpsupport_cookie_h

#define COOKIE_EXPIRE_NO 0
#define COOKIE_EXPIRE_EXPIRED 1

typedef struct _Cookie {
    char *name;
    char *value;
    char *path;
    char *domain;

    char *expireStr;
    /**
     * Cookie max age since received from server<br/>
     * This field unit is second
     */
    int maxAge;

    /**
     * Must used by https protocol
     */
    char secure;

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

/**
 * Cookie to String, this function usally used by http client send to server.<br/>
 * Some time when this lib used by server dev, Server use this function for Cookie output with includeInfo parameter.
 * @param cookie Cookie* Cookie instance.
 * @param includeInfo char, 0 not include additional fields, like path, domain and others; 1 need output additional fields.
 * @return char* Cookie's string description.
 */
char *CookieToString(Cookie *cookie, char includeInfo);

/**
 * Stream all cookies to a string buffer
 * @param cookies CookieStore
 * @return char* all cookie key=value; stream
 */
char *CookieStreamToString(CookieStore cookies);

/**
 * Parse Cookie from string.
 * @param cookieStr char*, cookie str info.
 * @return Cookie* , Cookie instance.
 */
Cookie *ParseCookie(char *cookieStr);

/**
 * Remove all expired Cookies from CookieStore<br/>
 * You should use this function return value for next step process.
 * @param cookies CookieStore orig cookies
 * @return CookieStore new or orig
 */
CookieStore RemoveExpiredCookies(CookieStore cookies);

#endif
