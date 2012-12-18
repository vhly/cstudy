//
//  bytestream.c
//  commonsupport
//
//  Created by vhly on 12-12-16.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "bytestream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ByteArrayBlock *FindFirsBlock(ByteStream stream)
{
    ByteArrayBlock *ret = stream;
    if (stream != NULL) {
        while (ret != NULL) {
            if (ret->prev != NULL) {
                ret = ret->prev;
            }else{
                break;
            }
        }
    }
    return ret;
}

ByteArrayBlock *FindLastBlock(ByteStream stream)
{
    ByteArrayBlock *ret = stream;
    if (stream != NULL) {
        while (ret != NULL) {
            if (ret->next != NULL) {
                ret = ret->next;
            }else{
                break;
            }
        }
    }
    return ret;
}

ByteArrayBlock *CreateDefaultByteBlock()
{
    ByteArrayBlock *ret = NULL;
    ret = (ByteArrayBlock *)malloc(sizeof(ByteArrayBlock));
    ret->currentPos = 0;
    ret->dataLength = 0;
    ret->next = NULL;
    ret->prev = NULL;
    return ret;
}

void CloseByteStream(ByteStream stream)
{
    if (stream != NULL) {
        ByteArrayBlock *block = FindLastBlock(stream);
        while (block != NULL) {
            if (block->next != NULL) {
                free(block->next);
            }
            block = block->prev;
        }
    }
}

ByteStream AppendByteData(ByteStream stream, char *data, int off, int length)
{
    ByteStream ret = stream;
    if (stream != NULL) {
        if (data != NULL && off > -1 && length > 0) {
            ret = FindLastBlock(stream);
            int cdlen = ret->dataLength;
            if (cdlen + length <= BYTESTREAM_BUFFER_LENGTH) {
                // TODO direct copy to buf
                memcpy(ret->buf + cdlen, data + off, length);
                ret->dataLength += length;
            } else {
                // need create new
                int cc = BYTESTREAM_BUFFER_LENGTH - ret->dataLength;
                int num;
                int tmpLen = length - cc;
                
                int currentOff = off;
                
                if (cc > 0) {
                    memcpy(ret->buf + cdlen, data + off, cc);
                    currentOff += cc;
                    ret->dataLength += cc;
                }
                num = tmpLen / BYTESTREAM_BUFFER_LENGTH;
                
                cc = tmpLen % BYTESTREAM_BUFFER_LENGTH;
                if (cc > 0) {
                    num++;
                }
                int dd;
                ByteArrayBlock *block;
                int i;
                for (i = 0; i < num; i++) {
                    if (tmpLen <= 0) {
                        break;
                    }
                    block = CreateDefaultByteBlock();
                    dd = tmpLen - BYTESTREAM_BUFFER_LENGTH;
                    if (dd > 0) {
                        memcpy(block->buf, data + currentOff, BYTESTREAM_BUFFER_LENGTH);
                        tmpLen = dd;
                        currentOff += BYTESTREAM_BUFFER_LENGTH;
                        block->dataLength = BYTESTREAM_BUFFER_LENGTH;
                        block->prev = ret;
                        ret->next = block;
                        ret = block;
                    }else{
                        memcpy(block->buf, data + currentOff, tmpLen);
                        block->dataLength = tmpLen;
                        block->prev = ret;
                        ret->next = block;
                        ret = block;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}