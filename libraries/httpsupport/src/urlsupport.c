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

// Private funcations

size_t URLAddressLength(URL *url)
{
    size_t ret = 0;
    if (url != NULL) {
        
        if (url->protocol == NULL) {
            ret += 7; // apppend "http://"
        } else {
            ret += strlen(url->protocol);
            ret += 3;
        }

        if (url->domian != NULL) {
            ret += strlen(url->domian);
        }

        if (url->port > 0) {
            char numBuf[32];
            size_t portLen = 0;
            sprintf(numBuf, "%d", url->port);
            portLen = strlen(numBuf);
            ret = ret + 1 + portLen;
        }
        
        if (url->path != NULL) {
            ret += strlen(url->path);
        }
        
        if (url->file != NULL) {
            ret += strlen(url->file);
        }
        
        if (url->query != NULL) {
            ret = ret + 1 + strlen(url->query);
        }
        
        if (url->fragment != NULL) {
            ret = ret + 1 + strlen(url->fragment);
        }
    }
    return ret;
}



// Public functions

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

char *URLtoString(URL *url)
{
    char *ret = NULL;
    if (url != NULL) {
        size_t slen = URLAddressLength(url);
        if (slen > 0) {
            size_t total = (slen + 1) * sizeof(char);
            ret = (char *)malloc(total);
            memset(ret, 0, total);
            size_t currentIndex = 0;
            if (url->protocol == NULL) {
                sprintf(ret, "http://");
                currentIndex = 7;
            } else {
                
                sprintf((ret + currentIndex), "%s://", url->protocol);
                currentIndex += strlen(url->protocol);
                currentIndex += 3;
            }
            
            if (url->domian != NULL) {
                sprintf((ret + currentIndex), "%s", url->domian);
                currentIndex += strlen(url->domian);
            }
            
            if (url->port > 0) {
                char numBuf[32];
                size_t portLen = 0;
                sprintf(numBuf, "%d", url->port);
                portLen = strlen(numBuf);
                sprintf((ret + currentIndex), ":%d", url->port);
                currentIndex = currentIndex + 1 + portLen;
            }
            
            if (url->path != NULL) {
                sprintf((ret + currentIndex), "%s", url->path);
                currentIndex += strlen(url->path);
            }
            
            if (url->file != NULL) {
                sprintf((ret + currentIndex), "%s", url->file);
                currentIndex += strlen(url->file);
            }
            
            if (url->query != NULL) {
                sprintf((ret + currentIndex), "?%s", url->query);
                currentIndex = currentIndex + 1 + strlen(url->query);
            }
            
            if (url->fragment != NULL) {
                sprintf((ret + currentIndex), "#%s", url->fragment);
            }
        }
    }
    return ret;
}