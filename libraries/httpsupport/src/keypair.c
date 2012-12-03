//
//  keypair.c
//  httpsupport
//
//  Created by vhly on 12-11-28.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "keypair.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

KeyPair *FindLastPair(KeyPairs pairs)
{
    KeyPair *ret = NULL;
    if (pairs != NULL) {
        ret = pairs;
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

KeyPair *GetKeyPair(KeyPairs pairs, char *kName)
{
    KeyPair *ret = NULL;
    if (pairs != NULL && kName != NULL) {
        KeyPair *tmp = FindLastPair(pairs);
        if (tmp != NULL) {
            while (tmp != NULL) {
                if (tmp->name != NULL) {
                    int cmp = strcmp(kName, tmp->name);
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

char *GetKeyPairValue(KeyPairs headers, char *hName)
{
    char *ret = NULL;
    if (headers != NULL && hName != NULL) {
        KeyPair *header = GetKeyPair(headers, hName);
        if (header != NULL) {
            ret = header->value;
        }
    }
    return ret;
}

KeyPair *CreateKeyPair(char *hName, char *hValue)
{
    KeyPair *ret = NULL;
    if (hName != NULL && hValue != NULL) {
        ret = (KeyPair *)malloc(sizeof(KeyPair));
        ret->name = hName;
        ret->value = hValue;
        ret->prev = NULL;
        ret->next = NULL;
    }
    return ret;
}
