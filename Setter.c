#include "Setter.h"

/* class EasySetter : ISetable */
typedef struct {
	/* First, let's try the most simple one.
	 * This object is a joke; It doesn't actually
	 * do anything useful.
	 * You Set() it, IsSet() returns TRUE.
	 * You Unset() it, IsSet() returns FALSE. */

	/* First, must declare Interface functions: */
	ISetable_Member_Declarations;

	/* Then, declare any member variable/functions
	 * you needed to implement the Interface.
	 * For this object, we only need this: */
	BOOL isSet;
} EasySetter;

EasySetterToken EasySetter_Alloc() {
	EasySetter * self = (EasySetter *)malloc(sizeof(EasySetter));
	self->isSet = FALSE;
	self->fnIsSet = EasySetter_IsSet;
	self->fnSet = EasySetter_Set;
	self->fnUnset = EasySetter_Unset;
	return (EasySetterToken)self;
}
void EasySetter_Dealloc(EasySetterToken pSelf) {
	if (EasySetter_IsSet(pSelf)) {
		EasySetter_Unset(pSelf);
	}
	free(pSelf);
}

BOOL EasySetter_IsSet(
	EasySetterToken pSelf)
{
	EasySetter * self = (EasySetter *)pSelf;
	return self->isSet;
}

HRESULT EasySetter_Set(
	EasySetterToken pSelf,
	int nData,
	void const *pData)
{
	EasySetter * self = (EasySetter *)pSelf;
	self->isSet = TRUE;
	return S_OK;
}

HRESULT EasySetter_Unset(
	EasySetterToken pSelf)
{
	EasySetter * self = (EasySetter *)pSelf;
	self->isSet = FALSE;
	return S_OK;
}

/* class NameSetter : ISetable */
typedef struct {
	/* This object acts like a ReadOnlyCollection for c-string.
	  'names' is a c-string that contains many null-terminated c-string,
	    its data will be like: 'str1\0str2\0str3...'
	  'nameCount' records how many c-string does 'names' contain. */
	ISetable_Member_Declarations;
	int nameCount;
	char *names;
} NameSetter;

NameSetterToken NameSetter_Alloc() {
	NameSetter * self = (NameSetter *)malloc(sizeof(NameSetter));
	self->nameCount = 0;
	self->names = NULL;
	self->fnIsSet = NameSetter_IsSet;
	self->fnSet = NameSetter_Set;
	self->fnUnset = NameSetter_Unset;
	return (NameSetterToken)self;
}

void NameSetter_Dealloc(NameSetterToken pSelf) {
	if (NameSetter_IsSet(pSelf)) {
		NameSetter_Unset(pSelf);
	}
	free(pSelf);
}

BOOL NameSetter_IsSet(
	NameSetterToken pSelf)
{
	NameSetter * self = (NameSetter *)pSelf;
	return self->names != NULL;
}

HRESULT NameSetter_Set(
	NameSetterToken pSelf,
	int nData,
	void const *pData) /* array of c-string */
{
	NameSetter * self = (NameSetter *)pSelf;
	if (NameSetter_IsSet(pSelf)) { return S_FALSE; }
	int sizeNeeded = 0;
	char **names = (char**)pData;
	for (int a = 0; a < nData; ++a) {
		sizeNeeded += strlen(names[a]) + 1;
	}
	self->names = (char*)malloc(sizeNeeded);
	self->nameCount = nData;
	char *p = self->names;
	for (int i = 0; i < nData; ++i) {
		while (*p = *(names[i])++) { ++p; }
		*p++ = '\0';
	}
	return S_OK;
}

HRESULT NameSetter_Unset(
	NameSetterToken pSelf)
{
	NameSetter * self = (NameSetter *)pSelf;
	if (!NameSetter_IsSet(pSelf)) { return S_FALSE; }
	free(self->names);
	self->names = NULL;
	self->nameCount = 0;
	return S_OK;
}

HRESULT NameSetter_GetAt(
	NameSetterToken pSelf,
	int iName,
	char *buf,
	int maxCch)
{
	NameSetter * self = (NameSetter *)pSelf;
	if (!NameSetter_IsSet(pSelf)) { return E_FAIL; }
	if (self->nameCount <= iName) { return E_FAIL; }
	char *p = self->names;
	/* Skip 'null-termi' for 'iName' times */
	for (int i = 0; i < iName; ++i) {
		while (*p++);
	}
	strncpy(buf, p, maxCch);
	buf[maxCch-1] = '\0';
	return S_OK;
}

/* class PriceSetter : ISetAble */
typedef struct {
	/* This object acts like a ReadOnlyCollection for double.
	  'prices' is an array of double type.
	  'nameCount' records how many double does 'prices' contain. */
	ISetable_Member_Declarations;
	int priceCount;
	double *prices;
} PriceSetter;

PriceSetterToken PriceSetter_Alloc() {
	PriceSetter *self = (PriceSetter*)malloc(sizeof(PriceSetter));
	self->prices = NULL;
	self->priceCount = 0;
	self->fnIsSet = PriceSetter_IsSet;
	self->fnSet = PriceSetter_Set;
	self->fnUnset = PriceSetter_Unset;
	return (PriceSetterToken)self;
}

void PriceSetter_Dealloc(PriceSetterToken pSelf) {
	if (PriceSetter_IsSet(pSelf)) {
		PriceSetter_Unset(pSelf);
	}
	free(pSelf);
}

BOOL PriceSetter_IsSet(
	PriceSetterToken pSelf)
{
	PriceSetter * self = (PriceSetter *)pSelf;
	return self->prices != NULL;
}

HRESULT PriceSetter_Set(
	PriceSetterToken pSelf,
	int nData,
	void const *pData)
{
	if (PriceSetter_IsSet(pSelf)) { return S_FALSE; }
	PriceSetter * self = (PriceSetter *)pSelf;
	self->prices = (double*)malloc(sizeof(double) * nData);
	self->priceCount = nData;

	double *prices = (double *)pData;
	for (int i = 0; i < nData; ++i) {
		self->prices[i] = prices[i];
	}
	return S_OK;
}

HRESULT PriceSetter_Unset(
	PriceSetterToken pSelf)
{
	if (!PriceSetter_IsSet(pSelf)) { return S_FALSE; }
	PriceSetter * self = (PriceSetter *)pSelf;
	free(self->prices);
	self->prices = NULL;
	self->priceCount = 0;
	return S_OK;
}

HRESULT PriceSetter_GetTotal(
	PriceSetterToken pSelf,
	double *pRet)
{
	if (!PriceSetter_IsSet(pSelf)) { return E_FAIL; }
	PriceSetter * self = (PriceSetter *)pSelf;
	double ret = 0;
	for (int i = 0; i < self->priceCount; ++i) {
		ret += self->prices[i];
	}
	*pRet = ret;
	return S_OK;
}
