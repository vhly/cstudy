//
//  keypair.h
//  httpsupport
//
//  Created by vhly on 12-11-28.
//  Copyright (c) 2012 vhly. All rights reserved.
//

#ifndef httpsupport_keypair_h
#define httpsupport_keypair_h

typedef struct _KeyPair {
	char *headerName;
	char *headerValue;
	
	struct _KeyPair *prev;
	struct _KeyPair *next;
} KeyPair, *KeyPairs;

KeyPair *FindLastPair(KeyPairs pairs);

/**
 * Get KeyPair by name<br/>
 * Get first key pair from pairs
 * @param kName char* header name
 * @return KeyPair pair or NULL
 */
KeyPair *GetKeyPair(KeyPairs pairs, char *kName);

#endif
