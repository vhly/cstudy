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

KeyPairs GetKeyPairs(KeyPairs pairs, char *hName)
{
    KeyPairs ret = NULL;
    if (pairs != NULL && hName != NULL) {
        KeyPair *pair = FindLastPair(pairs);
        if (pair != NULL) {
            while (pair != NULL) {
                if (pair->name != NULL) {
                    int cmp = strcmp(pair->name, hName);
                    if (cmp == 0) {
                        if (ret == NULL) {
                            ret = CreateKeyPair(pair->name, pair->value);
                        } else {
                            KeyPair *tmp = CreateKeyPair(pair->name, pair->value);
                            AppendToPairs(ret, tmp);
                        }
                    }
                }
                pair = pair->prev;
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

void AppendToPairs(KeyPairs pairs, KeyPair *pair)
{
    if (pairs != NULL && pair != NULL) {
        KeyPair *lastPair = FindLastPair(pairs);
        if (lastPair != NULL) {
            lastPair->next = pair;
            pair->prev = lastPair;
        } else {
            // TODO Normal is unreach
        }
    }
}

char *PairToString(KeyPair *pair, char splitChar)
{
    char *ret = NULL;
    if (pair != NULL) {
        if (splitChar == 0) {
            splitChar = '=';
        }
        size_t nlen, vlen;  // name length and value len
        char* name = pair->name;
        char* value = pair->value;

        if (name != NULL && value != NULL) {
            nlen = strlen(name);
            vlen = strlen(value);
            if (nlen > 0 && vlen > 0) {
                size_t totalLength = nlen + 2 + vlen;
                ret = (char *)malloc(sizeof(char) * totalLength);
                sprintf(ret, "%s%c%s", name,splitChar,value);
            }
        }
    }
    return ret;
}

