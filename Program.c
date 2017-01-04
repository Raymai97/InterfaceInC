#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Setter.h"

#define ARRAY_LEN(arr)		(sizeof(arr) / sizeof(*arr))
#define MAX_CHAR	(99)

/* These functions don't bother if the object is
 * NameSetter or FunnySetter. As long as it is
 * ISetable, it will be fine. */
void PrintState(ISetableToken);
void SetIt(ISetableToken, int nData, void const *pData);
void UnsetIt(ISetableToken);

void TestEasySetter();
void TestPriceSetter();
void TestNameSetter();

int main() {
	printf("OO Design ~ Interface ~ in C ~ by raymai97 \n\n");
	TestEasySetter();
	_getch();
	TestPriceSetter();
	_getch();
	TestNameSetter();
	_getch();
	printf("End of demo.\n");
	return 0;
}

void PrintState(ISetableToken pSelf) {
	ISetable *self = (ISetable *)pSelf;
	printf("The SetableToken is %s. \n",
		self->fnIsSet(self) ? "set" : "not set");
}

void SetIt(ISetableToken pSelf, int nData, void const *pData) {
	ISetable *self = (ISetable *)pSelf;
	HRESULT hr = self->fnSet(pSelf, nData, pData);
	if (FAILED(hr)) {
		printf("Failed to set the SetableToken. \n");
		printf("HRESULT: 0x%.8X \n", hr);
	}
	else {
		printf("Succeeded setting the SetableToken. \n");
	}
}

void UnsetIt(ISetableToken pSelf) {
	ISetable *self = (ISetable *)pSelf;
	HRESULT hr = self->fnUnset(pSelf);
	if (FAILED(hr)) {
		printf("Failed to unset the SetableToken. \n");
		printf("HRESULT: 0x%.8X \n", hr);
	}
	else {
		printf("Succeeded unsetting the SetableToken. \n");
	}
}

void TestEasySetter() {
	printf("Test subject: EasySetter \n");
	EasySetterToken est = EasySetter_Alloc();
	PrintState(est);
	SetIt(est, 0, NULL);
	PrintState(est);
	UnsetIt(est);
	PrintState(est);
	EasySetter_Dealloc(est);
	printf("...\n\n");
}

void TestPriceSetter() {
	int count = 0;
	double total = 0.0;
	double prices[] = {
		2.00, 3.00, 5.80, 0.90
	};
	printf("Test subject: PriceSetter \n");
	PriceSetterToken pst = PriceSetter_Alloc();
	PrintState(pst);
	SetIt(pst, ARRAY_LEN(prices), prices);
	PrintState(pst);
	PriceSetter_GetTotal(pst, &total);
	printf(".GetTotal() = %.2f \n", total);
	UnsetIt(pst);
	PrintState(pst);
	PriceSetter_Dealloc(pst);
	printf("...\n\n");
}

void TestNameSetter() {
	int count = 0;
	char name[MAX_CHAR] = {0};
	char const * const names[] = {
		"Chris Tomson",
		"John Stanford",
		"Tina Angelia"};
	printf("Test subject: NameSetter \n");
	NameSetterToken nst = NameSetter_Alloc();
	PrintState(nst);
	SetIt(nst, ARRAY_LEN(names), names);
	PrintState(nst);
	/* Error-proof test (handling out of range) */
	for (int i = 0; i < 9; ++i) {
		HRESULT hr = NameSetter_GetAt(nst, i, name, MAX_CHAR);
		if (FAILED(hr)) {
			printf(".GetAt(%i) error! \n", i);
			printf("If you see this message, it means "
				"the error-proof test is OK. \n\n");
			break;
		}
		else {
			printf(".GetAt(%i) = %s \n", i, name);
		}
	}
	UnsetIt(nst);
	PrintState(nst);
	NameSetter_Dealloc(nst);
	printf("...\n\n");
}
