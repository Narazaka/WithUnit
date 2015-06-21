#include "WithUnit.h"
#include <stdio.h>
#include <iostream>

int main(){
	UnitBase eV,m,g,s,K,A;
	Unit unit(eV,m,g,s,K,A);
	eV.SetSI(eV.M);
	eV.power = 2;
	m.SetSI(eV.M);
	m.power = 2;
	g.SetSI(eV.M);
	g.power = 2;
	s.SetSI(eV.M);
	s.power = 2;
	K.SetSI(eV.M);
	K.power = 2;
	A.SetSI(eV.M);
	A.power = 2;
	eV.si = 1;
	WithUnit wu(2.0,unit);
	cout << A.GetSIString() << endl;
	printf("%d",eV.si);
	return 0;
}
