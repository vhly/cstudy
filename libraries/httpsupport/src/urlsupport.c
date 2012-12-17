//
//  urlsupport.c
//  httpsupport
//
//  Created by vhly on 12-12-17.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "urlsupport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringutil.h"

URL *ParseURL(char *url)
{
    URL *ret = NULL;
    if (url != NULL) {
        size_t slen = strlen(url);
        if (slen > 0) {
            char *nextPart = strstr(url, "://"); // find scheme
            if (nextPart == NULL) {
                nextPart = url;
            }
            
            ret = (URL *)malloc(sizeof(URL));
            memset(ret, 0, sizeof(URL));
            
            ret->protocol = "http";
            ret->port = 80;
            
            size_t clen = nextPart - url;
            if (clen > 0 && clen < 10) {  // Max schemd str len set to 10
                ret->protocol = Substring(url, 0, clen);
            }
            
            char ch1, ch2, ch3;
            
            ch1 = nextPart[0];
            ch2 = nextPart[1];
            ch3 = nextPart[2];
            
            if (ch1 == ':') {
                nextPart += 3; // move to domain
            }
            
            char *address = NULL;
            
            char *endDomain = strchr(nextPart, '/');
            if (endDomain == NULL) {
                ret->path = "/";
                address = nextPart;
                nextPart = "/"; // only has domain not path and file and others.
            }else{
                clen = endDomain - nextPart;
                address = Substring(nextPart, 0, clen);
                nextPart = endDomain;
            }
            
            if (address != NULL) {
                char *portIndex = strchr(address, ':');
                if (portIndex != NULL) {
                    int off = (int)(portIndex - address);
                    ret->domian = Substring(address, 0, off);
                    clen = strlen(portIndex);
                    char *stmp = Substring(address, off + 1, clen - 1);
                    ret->port = atoi(stmp);
                } else {
                    ret->domian = address;
                }
            }
            
            char *tmp = nextPart;
            
            char *fragment = strchr(nextPart, '#');
            char *query = strchr(nextPart, '?');
            char *endIndex = NULL;
            if (query != NULL) {
                if (fragment != NULL) {
                    if (query < fragment) {
                        endIndex = query;
                        clen = fragment - query;
                        int off = (int)(query - nextPart);
                        query = Substring(nextPart, off + 1, clen - 1);
                        
                        tmp = Substring(nextPart, 0, off);
                        
                        
                        off = (int)(fragment - nextPart);
                        clen = strlen(fragment);
                        fragment = Substring(nextPart, off + 1, clen - 1);
                    }else{
                        endIndex = fragment;
                        int off = (int)(fragment - nextPart);
                        clen = query - fragment;
                        fragment = Substring(nextPart, off + 1, clen - 1);
                        tmp = Substring(nextPart, 0, off);
                        query = NULL;
                    }
                }else{
                    int off = (int)(query - nextPart);
                    clen = strlen(query);
                    query = Substring(nextPart, off + 1, clen - 1);
                    tmp = Substring(nextPart, 0, off);
                }
            }else{
                if (fragment != NULL) {
                    endIndex = fragment;
                    int off = (int)(fragment - nextPart);
                    clen = strlen(fragment);
                    fragment = Substring(nextPart, off + 1, clen - 1);
                    tmp = Substring(nextPart, 0, off);
                }
            }
            
            ret->fragment = fragment;
            ret->query = query;
            
            endIndex = strrchr(tmp, '/');
            
            if (endIndex != NULL) {
                if (endIndex > tmp) {
                    // TODO Include sub path
                    clen = endIndex - tmp;
                    ret->path = Substring(tmp, 0, clen + 1);
                } else {
                    ret->path = "/";
                }
                clen = strlen(tmp);
                if (clen > endIndex - tmp + 1) {
                    int off = (int)(endIndex - tmp);
                    clen = strlen(endIndex);
                    ret->file = Substring(tmp, off + 1, clen - 1);
                }
            }
            
            
//            printf("URL next part is %s\n", nextPart);
            
        }
    }
    return ret;
}