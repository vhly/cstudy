//
// bytestream.h
// commonsupport
// 
// Create by vhly on 12-12-16
// Copyright (c) 2012 vhly. All rights reserved.

#ifndef common_bytestream_h
#define common_bytestream_h

#define BYTESTREAM_BUFFER_LENGTH 128

typedef struct _ByteStream {
    
    char buf[BYTESTREAM_BUFFER_LENGTH];
    /**
     * current data total length, it should be less than BYTESTREAM_BUFFER_LENGTH
     */
    int dataLength;
    /**
     * current operation index.
     */
    int currentPos;
    
    struct _ByteStream *prev;
    struct _ByteStream *next;
} ByteArrayBlock, *ByteStream;

/**
 * Create empty default block for operation
 * @return ByteArrayBlock *
 */
ByteArrayBlock *CreateDefaultByteBlock();

/**
 * Append data from off to length bytes to stream
 * @param stream ByteStream
 * @param data   char* the data which will be append to stream
 * @param off    int data start index
 * @param length int data length
 * @return ByteStream current stream of new stream
 */
ByteStream AppendByteData(ByteStream stream, char *data, int off, int length);

/**
 * Release all stream block
 */
void CloseByteStream(ByteStream stream);

#endif

