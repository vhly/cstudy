//
//  datastream.c
//  commonsupport
//
//  Created by vhly on 12-12-16.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "datastream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ByteStream CreateDefaultDataStream(ByteStream stream)
{
    ByteStream ret = NULL;
    if (stream != NULL) {
        ByteArrayBlock *first = stream;
        while (1) {
            if (first->prev != NULL) {
                first = first->prev;
            }else{
                break;
            }
        }
        if (first != NULL) {
            ret = first;
            while (1) {
                first->currentPos = 0;
                first = first->next;
                if (first == NULL) {
                    break;
                }
            }
        }
    }
    return ret;
}

void WriteByteToStream(ByteStream stream, char bv)
{
    if (stream != NULL) {
        char chs[1];
        chs[0] = bv;
        AppendByteData(stream, chs, 0, 1);
    }
}

void WriteShortToStream(ByteStream stream, int sv)
{
    if (stream != NULL) {
        char chs[2];
        chs[0] = sv & 0x0ff;
        chs[1] = (sv >> 8) & 0x0ff;
        AppendByteData(stream, chs, 0, 2);
    }
}

void WriteInt32ToStream(ByteStream stream, int iv)
{
    if (stream != NULL) {
        char chs[4];
        chs[0] = iv & 0x0ff;
        chs[1] = (iv >> 8) & 0x0ff;
        chs[2] = (iv >> 16) & 0x0ff;
        chs[3] = (iv >> 24) & 0x0ff;
        AppendByteData(stream, chs, 0, 4);
    }
}


void WriteLongToStream(ByteStream stream, long lv)
{
    if (stream != NULL) {
        char chs[8];
        int i = 0;
        for (; i < 8; i++) {
            chs[i] = (lv >> (i * 8)) & 0x0ff;
        }
        AppendByteData(stream, chs, 0, 8);
    }
}

void WriteFloat32ToStream(ByteStream stream, float fv)
{
    
}

void WriteBytesToStream(ByteStream stream, char *buf, size_t length)
{
    AppendByteData(stream, buf, 0, length);
}

void WriteBytesToStreamFrom(ByteStream stream, char *buf, int off, size_t length)
{
    AppendByteData(stream, buf, off, length);
}

void WriteUTF8ToStream(ByteStream stream, char *str)
{
    size_t len = strlen(str);
    WriteShortToStream(stream, (short)len);
    AppendByteData(stream, str, 0, len);
}

char ReadByteFromStream(ByteStream stream)
{
    char ret = -1;
    if (stream != NULL) {
        char *buf = ReadBytesFromStream(stream, 1);
        if (buf != NULL) {
            ret = *buf;
        }
    }
    return ret;
}

int ReadShortFromStream(ByteStream stream)
{
    int ret = -1;
    if (stream != NULL) {
        char *buf = ReadBytesFromStream(stream, 2);
        if (buf != NULL) {
            char ch1 = *buf;
            char ch2 = *(buf + 1);
            ret = (ch1 & 0x0ff) | ((ch2 & 0x0ff) << 8);
        }
    }
    return ret;
}

int ReadInt32FromStream(ByteStream stream)
{
    int ret = -1;
    if (stream != NULL) {
        char *buf = ReadBytesFromStream(stream, 4);
        if (buf != NULL) {
            char ch1 = *buf;
            char ch2 = *(buf + 1);
            char ch3 = *(buf + 2);
            char ch4 = *(buf + 3);
            ret = (ch1 & 0x0ff) | ((ch2 & 0x0ff) << 8) | ((ch3 & 0x0ff) << 16) | ((ch4 & 0x0ff) << 24);
        }
    }
    return ret;
}

long ReadLongFromStream(ByteStream stream)
{
    long ret = -1;
    if (stream != NULL) {
        char *buf = ReadBytesFromStream(stream, 8);
        if (buf != NULL) {
            char ch;
            int i = 0;
            ret = 0;
            for (; i < 8; i++) {
                ch = *(buf + i);
                ret |= ((ch & 0x0ff) << (i * 8)); // ret = ch0 | (ch1 << 8) | (ch2 << 16) .......
            }
        }
    }
    return ret;
}

float ReadFloat32FromStream(ByteStream stream)
{
    return -1;
}

char *ReadBytesFromStream(ByteStream stream, size_t length)
{
    char *ret = NULL;
    if (stream != NULL) {
        if (stream->currentPos == stream->totalLength) {
            if (stream->next != NULL) {
                stream = stream->next;
                stream->currentPos = 0;
            }else{
                stream = NULL;
            }
        }
        size_t tt = length;
        int blen = 0;
        size_t dlen = sizeof(char) * length;
        ret = (char*)malloc(dlen);
        memset(ret, 0, dlen);
        while (1) {
            if (stream != NULL) {
                if (tt >= stream->dataLength) {
                    memcpy(ret + blen, stream->buf + stream->currentPos, stream->dataLength);
                    tt = tt - stream->dataLength;
                    blen += stream->dataLength;
                    stream->currentPos = stream->dataLength;
                    stream = stream->next;
                }else{
                    memcpy(ret + blen, stream->buf + stream->currentPos, tt);
                    stream->currentPos += tt;
                    break;
                }
            }else{
                break;
            }
        }
        
    }
    return ret;
}

char *ReadUTF8FromStream(ByteStream stream)
{
    char *ret = NULL;
    int slen = ReadShortFromStream(stream);
    if (slen > 0) {
        ret = ReadBytesFromStream(stream, slen);
    }
    return ret;
}