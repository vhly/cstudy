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

void WriteByteToStream(ByteStream stream, char bv);

void WriteShortToStream(ByteStream stream, int sv);

void WriteInt32ToStream(ByteStream stream, int iv);

void WriteInt64ToStream(ByteStream stream, int iv);

void WriteLong64ToStream(ByteStream stream, long lv);

void WriteFloat32ToStream(ByteStream stream, float fv);

void WriteBytesToStream(ByteStream stream, char *buf, int length);

void WriteBytesToStreamFrom(ByteStream stream, char *buf, int off, int length);

void WriteUTF8ToStream(ByteStream stream, char *str);

#endif
