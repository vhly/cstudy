//
//  datastream.h
//  commonsupport
//
//  Created by vhly on 12-12-16.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef commonsupport_datastream_h
#define commonsupport_datastream_h

#include "bytestream.h"

#include <stdio.h>

void WriteByteToStream(ByteStream stream, char bv);

void WriteShortToStream(ByteStream stream, int sv);

void WriteInt32ToStream(ByteStream stream, int iv);

void WriteLongToStream(ByteStream stream, long lv);

void WriteFloat32ToStream(ByteStream stream, float fv);

void WriteBytesToStream(ByteStream stream, char *buf, size_t length);

void WriteBytesToStreamFrom(ByteStream stream, char *buf, int off, size_t length);

void WriteUTF8ToStream(ByteStream stream, char *str);



char ReadByteFromStream(ByteStream stream);

int ReadShortFromStream(ByteStream stream);

int ReadInt32FromStream(ByteStream stream);

long ReadLongFromStream(ByteStream stream);

float ReadFloat32FromStream(ByteStream stream);

char *ReadBytesFromStream(ByteStream stream, size_t length);

char *ReadUTF8FromStream(ByteStream stream);

#endif
