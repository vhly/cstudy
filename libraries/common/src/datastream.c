//
//  datastream.c
//  commonsupport
//
//  Created by vhly on 12-12-16.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#include "datastream.h"

#include <stdio.h>

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

void WriteInt64ToStream(ByteStream stream, int iv)
{
    if (stream != NULL) {
        char chs[8];
        int i = 0;
        for (; i < 8; i++) {
            chs[i] = (iv >> (i * 8)) & 0x0ff;
        }
        AppendByteData(stream, chs, 0, 8);
    }
}

void WriteLong64ToStream(ByteStream stream, long lv)
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

void WriteBytesToStream(ByteStream stream, char *buf, int length)
{
    
}

void WriteBytesToStreamFrom(ByteStream stream, char *buf, int off, int length)
{
    
}

void WriteUTF8ToStream(ByteStream stream, char *str)
{
    
}