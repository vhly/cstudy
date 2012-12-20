//
//  urlsupport.h
//  httpsupport
//
//  Created by vhly on 12-12-17.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_urlsupport_h
#define httpsupport_urlsupport_h

typedef struct _URL{
    char *protocol;
    char *domian;
    int  port;
    char *path;
    char *file;
    char *query;
    char *fragment;
} URL;

/**
 * Parse url string to URL struct
 * @param url string
 * @return URL URL instance
 */
URL *ParseURL(char *url);

/**
 * Convert URL object to string
 * @param url URL*
 * @return char* string or NULL
 */
char *URLtoString(URL *url);

#endif
