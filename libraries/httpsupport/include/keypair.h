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
	char *name;
	char *value;
	
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

/**
 * Get KeyPair's value by name
 * @param headers keypairs list
 * @param hName header name
 * @return char* header value or NULL
 */
char *GetKeyPairValue(KeyPairs headers, char *hName);

/**
 * Create a Key Pair
 * @param hName name
 * @param hValue value
 * @return KeyPair Created
 */
KeyPair *CreateKeyPair(char *hName, char *hValue);

#endif
