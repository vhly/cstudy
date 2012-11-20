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