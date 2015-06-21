#ifndef WithUnit
#define WithUnit

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

class UnitMagnitudeTableItem{
public:
	UnitMagnitudeTableItem(const string& in_baseunit);
	~UnitMagnitudeTableItem();
private:
	string magnitudename;
	double magnitude;
};

vector<UnitMagnitudeTableItem> UnitMagnitudeTable; = {
public:
	UnitMagnitudeTable();
	~UnitMagnitudeTable();
};

class UnitMagnitude{
public:
	UnitMagnitude();
	~UnitMagnitude();
private:
	int magnitudeid;
}

class UnitBase{
public:
	UnitBase();
	~UnitBase();
	void SetMagnitude (SI esi);
	const string& GetSIString();
	const string& GetPowerString();
private:
	string unitname;
	UnitMagnitude magnitude;
}

class UnitTableItem{
public:
	UnitTableItem(const string& in_baseunit);
	~UnitTableItem();
private:
	string unitname;
	double ratio;
	map<string,int> construction;
};

UnitTable::UnitTable(){
	sistr.push_back("y");
	sistr.push_back("z");
	sistr.push_back("a");
	sistr.push_back("f");
	sistr.push_back("p");
	sistr.push_back("n");
	sistr.push_back("micro");
	sistr.push_back("m");
	sistr.push_back("c");
	sistr.push_back("d");
	sistr.push_back("");
	sistr.push_back("da");
	sistr.push_back("h");
	sistr.push_back("k");
	sistr.push_back("M");
	sistr.push_back("G");
	sistr.push_back("T");
	sistr.push_back("P");
	sistr.push_back("E");
	sistr.push_back("Z");
	sistr.push_back("Y");
}
UnitBase::~UnitBase(){}

void UnitBase::SetSI(SI esi){
	si = (int)esi;
}

const string& UnitBase::GetSIString(){
	return sistr[si];
}

const string& UnitBase::GetPowerString(){
	string *ret = new string();
	if(power != 0 && power != 1){
		stringstream tmp;
		tmp << "^" <<power;
		*ret = tmp.str();
	}else{*ret = "";}
	return *ret;
}

/*****************************************************************************
 *
 * Class
 * ::Unit
 *
 *****************************************************************************/
class Unit{
public:
	Unit();
//	Unit(const Unit& unit);
	Unit(const string& unitstr);
	Unit(const UnitBase& i_eV,const UnitBase& i_m,const UnitBase& i_g,const UnitBase& i_s,const UnitBase& i_K,const UnitBase& i_A);
	~Unit();
	UnitBase eV,m,g,s,K,A;
	void Set(const string& unitstr);
	void Set(const Unit& unit);
	void Set(const UnitBase& i_eV,const UnitBase& i_m,const UnitBase& i_g,const UnitBase& i_s,const UnitBase& i_K,const UnitBase& i_A);
	int GetOrder(const Unit& unit);
	double GetOrderd(const Unit& unit);
	Unit GetBaseUnit(const string& unitstr); //TODO
	//const string& GetDisplayUnit(const Unit& unit); // use ToString
	Unit operator*(const Unit& unit);
	Unit operator/(const Unit& unit);
	const string& ToString();//TODO
private:
	UnitBase UnitPlus(const UnitBase& unit1,const UnitBase& unit2);
	UnitBase UnitMinus(const UnitBase& unit1,const UnitBase& unit2);
	const string& UnitWithSI(UnitBase& ub,const string& unitstr);
};

/*****************************************************************************
 Constructor
 *****************************************************************************/
Unit::Unit(){
}

Unit::Unit(const string& unitstr){
//	*this = GetBaseUnit(unitstr);
}

Unit::Unit(const Unit& unit){
	*this = unit;
}

Unit::Unit(const UnitBase& i_eV,const UnitBase& i_m,const UnitBase& i_g,const UnitBase& i_s,const UnitBase& i_K,const UnitBase& i_A){
	eV = i_eV;m = i_m;g = i_g;s = i_s;K = i_K;A = i_A;
}

/*****************************************************************************
 Destructor
 *****************************************************************************/
Unit::~Unit(){}

/*****************************************************************************
 Methods
 *****************************************************************************/
void Unit::SetUnit(const string& unitstr){
//	*this = GetBaseUnit(unitstr);
}

void Unit::SetUnit(const Unit& unit){
	*this = unit;
}

void Unit::SetUnit(const UnitBase& i_eV,const UnitBase& i_m,const UnitBase& i_g,const UnitBase& i_s,const UnitBase& i_K,const UnitBase& i_A){
	eV = i_eV;m = i_m;g = i_g;s = i_s;K = i_K;A = i_A;
}

int Unit::GetOrder(const Unit& unit){
	if(eV.power == unit.eV.power &&
	   m.power == unit.m.power &&
	   g.power == unit.g.power &&
	   s.power == unit.s.power &&
	   K.power == unit.K.power &&
	   A.power == unit.A.power){
		return (int)(
		  (eV.si + m.si + g.si + s.si + K.si + A.si)
		   - (unit.eV.si + unit.m.si + unit.g.si + unit.s.si + unit.K.si + unit.A.si)
		);
	}else{return 0xffffffff;}
}

double Unit::GetOrderd(const Unit& unit){
	return pow(1000,(double)(GetOrder(unit)));
}

Unit Unit::operator*(const Unit& unit){
	Unit ret;
	ret.eV = UnitPlus(eV,unit.eV);
	ret.m = UnitPlus(m,unit.m);
	ret.g = UnitPlus(g,unit.g);
	ret.s = UnitPlus(s,unit.s);
	ret.K = UnitPlus(K,unit.K);
	ret.A = UnitPlus(A,unit.A);
	return ret;
}

Unit Unit::operator/(const Unit& unit){
	Unit ret;
	ret.eV = UnitMinus(eV,unit.eV);
	ret.m = UnitMinus(m,unit.m);
	ret.g = UnitMinus(g,unit.g);
	ret.s = UnitMinus(s,unit.s);
	ret.K = UnitMinus(K,unit.K);
	ret.A = UnitMinus(A,unit.A);
	return ret;
}

UnitBase Unit::UnitPlus(const UnitBase& ub1,const UnitBase& ub2){
	UnitBase ret;
	ret.power = ub1.power + ub2.power;
	ret.si = ub1.si + ub2.si;
	return ret;
}

UnitBase Unit::UnitMinus(const UnitBase& ub1,const UnitBase& ub2){
	UnitBase ret;
	ret.power = ub1.power - ub2.power;
	ret.si = ub1.si - ub2.si;
	return ret;
}

const string& Unit::ToString(){
	string *ret = new string();
	*ret += UnitWithSI(eV,"eV");
	*ret += UnitWithSI(m,"m");
	*ret += UnitWithSI(g,"g");
	*ret += UnitWithSI(s,"s");
	*ret += UnitWithSI(K,"K");
	*ret += UnitWithSI(A,"A");
	return *ret;
}

const string& Unit::UnitWithSI(UnitBase& ub,const string& unitstr){
	string *ret = new string();
	if(ub.power){
		*ret += ub.GetSIString() + unitstr + ub.GetPowerString();
	}else{*ret = "";}
	return *ret;
}

/*****************************************************************************
 *
 * Class
 * ::WithUnit
 *
 *****************************************************************************/
template <class NUM_CLASS>
class WithUnit{
public:
	WithUnit();
//	WithUnit(const WithUnit& in_wu);
	WithUnit(string& in_num_unit);
	WithUnit(NUM_CLASS in_num,Unit& in_unit);
	WithUnit(NUM_CLASS in_num,string& in_unitstr);
	~WithUnit();
	void Set(string& in_num_unit);
	void Set(NUM_CLASS in_num,Unit& in_unit);
	void Set(NUM_CLASS in_num,string& in_unitstr);
	WithUnit& operator=(const WithUnit& wu);
	const WithUnit operator+(const WithUnit& wu) const;
	WithUnit& operator+=(const WithUnit& wu);
	const WithUnit operator-(const WithUnit& wu) const;
	WithUnit& operator-=(const WithUnit& wu);
	const WithUnit operator*(const WithUnit& wu) const;
	WithUnit& operator*=(const WithUnit& wu);
	const WithUnit operator/(const WithUnit& wu) const;
	WithUnit& operator/=(const WithUnit& wu);
	bool operator==(const WithUnit& wu) const;
	bool operator!=(const WithUnit& wu) const;
	bool operator>(const WithUnit& wu) const;
	bool operator<(const WithUnit& wu) const;
	bool operator>=(const WithUnit& wu) const;
	bool operator<=(const WithUnit& wu) const;
	const NUM_CLASS ToNum(const Unit& to_unit);
	const NUM_CLASS ToNum(const string& to_unitstr);
	const NUM_CLASS ToNumWithUnit(const Unit& to_unit);
	const NUM_CLASS ToNumWithUnit(const string& to_unitstr);
	const Unit& GetUnit();
	const string& GetUnitString(const Unit& to_unit);
	const string& GetUnitString(const string& to_unitstr);
private:
	NUM_CLASS num;
	Unit *unit;
};

/*****************************************************************************
 Constructor
 *****************************************************************************/
template <class NUM_CLASS>
WithUnit<NUM_CLASS>::WithUnit(){}

template <class NUM_CLASS>
WithUnit<NUM_CLASS>::WithUnit(string& in_num_unit){
	Set(in_num_unit);
}

template <class NUM_CLASS>
WithUnit<NUM_CLASS>::WithUnit(NUM_CLASS in_num,Unit& in_unit){
	Set(in_num,in_unit);
}

template <class NUM_CLASS>
WithUnit<NUM_CLASS>::WithUnit(NUM_CLASS in_num,string& in_unitstr){
	Set(in_num,in_unitstr);
}

/*****************************************************************************
 Destructor
 *****************************************************************************/
template <class NUM_CLASS>
WithUnit<NUM_CLASS>::~WithUnit(){}

/*****************************************************************************
 Methods
 *****************************************************************************/
template <class NUM_CLASS>
void WithUnit<NUM_CLASS>::Set(string& in_num_unit){
	cout << "Sorry, this section is under construction..." << endl;
}

template <class NUM_CLASS>
void WithUnit<NUM_CLASS>::Set(NUM_CLASS in_num,Unit& in_unit){
	num = in_num;
	unit = in_unit;
}

template <class NUM_CLASS>
void WithUnit<NUM_CLASS>::Set(NUM_CLASS in_num,string& in_unitstr){
	num = in_num;
	unit.SetUnit(in_unitstr);
}

template <class NUM_CLASS>
WithUnit WithUnit<NUM_CLASS>::operator+(const WithUnit& wu){
	WithUnit ret;
	ret.num = num + wu.num * unit.GetOrderd(wu.unit);
	ret.unit = unit;
	return ret;
}

template <class NUM_CLASS>
WithUnit WithUnit<NUM_CLASS>::operator-(const WithUnit& wu){
	WithUnit ret;
	ret.x = x - wu.x * unit.GetOrderd(wu.unit);
	ret.unit = unit;
	return ret;
}

template <class NUM_CLASS>
WithUnit WithUnit<NUM_CLASS>::operator*(const WithUnit& wu){
	WithUnit ret;
	ret.x = x * wu.x;
	ret.unit = unit * wu.unit;
	return ret;
}

template <class NUM_CLASS>
WithUnit WithUnit<NUM_CLASS>::operator/(const WithUnit& wu){
	WithUnit ret;
	ret.x = x / wu.x;
	ret.unit = unit / wu.unit;
	return ret;
}

template <class NUM_CLASS>
Unit WithUnit<NUM_CLASS>::GetUnit(){
	return unit;
}

template <class NUM_CLASS>
const string& WithUnit<NUM_CLASS>::GetUnitString(){
	return unit.ToString();
}

#endif
