#ifndef SETTER_H
#define SETTER_H

#include <Windows.h>
#include "ISetable.h"

/* Outsider should know that these Setter implement ISetable,
 * which provides functions like Set(), Unset() and IsSet().
 * Other than that, outsider is NOT obligated to know. */
typedef void *EasySetterToken;
typedef void *NameSetterToken;
typedef void *PriceSetterToken;

EasySetterToken		EasySetter_Alloc();
void				EasySetter_Dealloc(EasySetterToken);

NameSetterToken		NameSetter_Alloc();
void				NameSetter_Dealloc(NameSetterToken);

PriceSetterToken	PriceSetter_Alloc();
void				PriceSetter_Dealloc(PriceSetterToken);

BOOL EasySetter_IsSet(
	EasySetterToken);
HRESULT EasySetter_Set(
	EasySetterToken,
	int nData,
	void const *pData);
HRESULT EasySetter_Unset(
	EasySetterToken);

BOOL NameSetter_IsSet(
	NameSetterToken);
HRESULT NameSetter_Set(
	NameSetterToken,
	int nData,
	void const *pData);
HRESULT NameSetter_Unset(
	NameSetterToken);
HRESULT NameSetter_GetAt(
	NameSetterToken,
	int iName,
	char *buf,
	int maxCch);

BOOL PriceSetter_IsSet(
	PriceSetterToken);
HRESULT PriceSetter_Set(
	PriceSetterToken,
	int nData,
	void const *pData);
HRESULT PriceSetter_Unset(
	PriceSetterToken);
HRESULT PriceSetter_GetTotal(
	PriceSetterToken,
	double *);

#endif/*SETTER_H*/
