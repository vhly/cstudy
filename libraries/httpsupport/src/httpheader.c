//
//  httpheader.c
//  httpsupport
//
//  Created by vhly on 12-11-20.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "httpheader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Private functions

HttpHeader *FindLastHeader(HttpHeaders headers)
{
    HttpHeader *ret = NULL;
    if (headers != NULL) {
        ret = headers;
        while (ret != NULL) {
            if (ret->next != NULL) {
                ret = ret->next;
            } else {
                break;
            }
        }
    }
    return ret;
}

// Public functions

HttpHeader *GetHttpHeader(HttpHeaders headers, char *hName)
{
    HttpHeader *ret = NULL;
    if (headers != NULL && hName != NULL) {
        HttpHeader *tmp = FindLastHeader(headers);
        if (tmp != NULL) {
            while (tmp != NULL) {
                if (tmp->headerName != NULL) {
                    int cmp = strcmp(hName, tmp->headerName);
                    if (cmp == 0) {
                        ret = tmp;
                        break;
                    }
                }
                if (tmp->prev != NULL) {
                    tmp = tmp->prev;
                }
            }
        }
    }
    return ret;
}

HttpHeader *CreateHttpHeader(char *hName, char *hValue)
{
    HttpHeader *ret = NULL;
    if (hName != NULL && hValue != NULL) {
        ret = (HttpHeader *)malloc(sizeof(HttpHeader));
        ret->headerName = hName;
        ret->headerValue = hValue;
        ret->prev = NULL;
        ret->next = NULL;
    }
    return ret;
}

void AppendHeader(HttpHeaders headers, HttpHeader *header)
{
    if (headers != NULL && header != NULL) {
        HttpHeader *lastHeader = FindLastHeader(headers);
        if (lastHeader != NULL) {
            lastHeader->next = header;
            header->prev = lastHeader;
        } else {
            // TODO Normal is unreach
        }
    }
}

char *Header2String(HttpHeader *header, char needCRLF)
{
    char *ret = NULL;
    if (header != NULL) {
        size_t nlen, vlen;  // name length and value len
        char* name = header->headerName;
        char* value = header->headerValue;
        
        if (name != NULL && value != NULL) {
            nlen = strlen(name);
            vlen = strlen(value);
            if (nlen > 0 && vlen > 0) {
                size_t totalLength = nlen + 2 + vlen;
                ret = (char *)malloc(sizeof(char) * totalLength);
                if (needCRLF == 1) {
                    sprintf(ret, "%s: %s\n", name, value);
                }else{
                    sprintf(ret, "%s: %s", name, value);
                }
            }
        }
    }
    return ret;
}
