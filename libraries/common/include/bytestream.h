//
// bytestream.h
// common lib
// 
// Create by vhly on 12-12-16
// Copyright (c) 2012 vhly. All rights reserved.

#ifndef common_bytestream_h
#define common_bytestream_h

typedef struct _ByteStream {
    int dataLength;
    char *buf;
    
    struct _ByteStream *prev;
    struct _ByteStream *next;
} *ByteStream;

#endif

