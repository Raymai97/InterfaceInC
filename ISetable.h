#ifndef ISETABLE_H
#define ISETABLE_H

#include <Windows.h>

typedef void *ISetableToken;

/* ISetable is an interface, so it is OK for the outsider
 * to peek at its internal structure. That said, outsider
 * will never know how do these functions work, because
 * interface has no implementation. */

/* As long as a struct declaration starts with this: */
#define ISetable_Member_Declarations \
	BOOL(*fnIsSet)(ISetableToken); \
	HRESULT(*fnSet)(ISetableToken, \
		int nData, void const *pData); \
	HRESULT(*fnUnset)(ISetableToken);
/* It's safe to cast their pointer as ISetableToken. */

typedef struct {
	ISetable_Member_Declarations;
} ISetable;

#endif/*ISETABLE_H*/
