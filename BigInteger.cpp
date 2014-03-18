#ifndef big_integer
#define big_integer

#include<iostream>
#include<string.h>
using namespace std;

class Error{
public:
	Error(char* r):reason(r) {}
	char* what() {return reason;}
private:
	char* reason;
};

const int IntegerLen=1000;

class Integer{
public:
	Integer(int num=0);
	Integer(const Integer& obj);
	Integer operator = (const Integer& another);
	Integer operator + (const Integer& another) const;
	Integer operator - (const Integer& another) const;
	Integer operator - () const;
	Integer operator * (const Integer& another) const;
	Integer operator / (const Integer& another) const;
	Integer operator % (const Integer& another) const;
	bool operator > (const Integer& another) const;
	bool operator < (const Integer& another) const;
	bool operator == (const Integer& another) const;
	bool operator != (const Integer& another) const;
	bool operator >= (const Integer& another) const;
	bool operator <= (const Integer& another) const;
	friend ostream& operator << (ostream& stream,const Integer& obj);
	friend istream& operator >> (istream& stream,Integer& obj);
private:
	Integer absolute() const;
	int IntegerLength() const;
	void augment(int n);
	int& operator [] (int index);
	const int& operator [] (int index) const;
	int NumArray[IntegerLen];
	int sign;
};

Integer::Integer(int num)
{
	if(num<0){
		sign=-1;
		num=-num;
	}
	else sign=1;
	for(int i=0;i<IntegerLen;i++){
		(*this)[i]=num%10;
		num/=10;
	}		
	return;
}

Integer::Integer(const Integer& obj)
{
	sign=obj.sign;
	for(int i=0;i<IntegerLen;i++) (*this)[i]=obj[i];
	return;
}

Integer Integer::operator = (const Integer& another)
{
	int i;
	(*this).sign=another.sign;
	for(i=0;i<IntegerLen;i++)
		(*this)[i]=another[i];
	return *this;
}

Integer Integer::operator + (const Integer& another) const
{
    int i;
	Integer result;
	if(sign==another.sign){
		for(i=0;i<IntegerLen;i++){
			result[i]=(*this)[i]+another[i]+result[i];
			while(result[i]>=10){
				result[i]-=10;
				result[i+1]++;
			}
		}
		result.sign=(*this).sign;
	}
	else result=(*this)-(-another);
	return result;
}

Integer Integer::operator - (const Integer& another) const
{
	int i;
	Integer result;
	const Integer *max,*min;
	if((*this)==another) return Integer(0);
	if(sign==another.sign){
		if((*this).absolute()>another.absolute()){
			max=this;
			min=&another;
		}else{
			max=&another;
			min=this;
		}
		for(i=0;i<IntegerLen;i++){
			result[i]=(*max)[i]-(*min)[i]+result[i];
			while(result[i]<0){
				result[i]+=10;
				result[i+1]--;
			}
		}
		if(max==this) result.sign=(*this).sign;
		else result.sign=-(*this).sign;
	}else{
		result=(*this)+(-another);
	}
	return result;
}

Integer Integer::operator - () const
{
	Integer result;
	result=*this;
	if(result!=Integer(0))
		result.sign=-sign;
	return result;
}

Integer Integer::operator * (const Integer& another) const
{
	Integer result,temp;
	int i,j;
	if((*this)==0||another==0) return result;
	for(i=0;i<IntegerLen;i++){
		temp=Integer(0);
		for(j=0;j<IntegerLen-i;j++){
			temp[i+j]=(*this)[i]*another[j]+temp[i+j];
			while(temp[i]>=10){
				temp[i]-=10;
				temp[i+1]++;
			}
		}
		result=result+temp;
	}
	if(sign==another.sign) result.sign=1;
	else result.sign=-1;
	return result;
}

Integer Integer::operator / (const Integer& another) const
{
	if(another==Integer(0)) throw Error("Divisor can't be zero!");
	int i,j,margin;
	Integer result,dividend=(*this).absolute(),divisor=another.absolute();
	if(divisor>dividend) return Integer(0);
	i=IntegerLength();
	j=another.IntegerLength();
	margin=i-j;
	divisor.augment(margin);
	while(margin>=0){
		if(dividend>=divisor){
			dividend=dividend-divisor;
			result.NumArray[IntegerLen-margin-1]++;
		}else{
			margin--;
			divisor.augment(-1);
		}
	}
	if(sign==another.sign) result.sign=1;
	else result.sign=-1;
	return result;
}

Integer Integer::operator % (const Integer& another) const
{
	Integer result;
	result=(*this)-((*this)/another)*another;
	return result;
}

bool Integer::operator > (const Integer& another) const
{
	int i;
	if(sign>another.sign) return true;
	else if(sign<another.sign) return false;
	else if(sign==1){
		for(i=IntegerLen-1;i>=0;i--)
			if((*this)[i]>another[i]) return true;
			else if((*this)[i]<another[i]) return false;
	}else{
		for(i=IntegerLen-1;i>=0;i--)
			if((*this)[i]>another[i]) return false;
			else if((*this)[i]<another[i]) return true;
	}
	return false;
}

bool Integer::operator < (const Integer& another) const
{
	int i;
	if(sign>another.sign) return false;
	else if(sign<another.sign) return true;
	else if(sign==1){
		for(i=IntegerLen-1;i>=0;i--)
			if((*this)[i]>another[i]) return false;
			else if((*this)[i]<another[i]) return true;
	}else{
		for(i=IntegerLen-1;i>=0;i--)
			if((*this)[i]>another[i]) return true;
			else if((*this)[i]<another[i]) return false;
	}
	return false;
}

bool Integer::operator == (const Integer& another) const
{
	if(!(*this>another)&&!(*this<another)) return true;
	else return false;
}

bool Integer::operator != (const Integer& another) const
{
	if(*this==another) return false;
	else return true;
}

bool Integer::operator >= (const Integer& another) const
{
	if(*this<another) return false;
	else return true;
}

bool Integer::operator <= (const Integer& another) const
{
	if(*this>another) return false;
	else return true;
}

ostream& operator << (ostream& stream,const Integer& obj)
{
	int i;
	if(obj.sign==-1) stream<<'-';
	for(i=0;i<IntegerLen&&obj.NumArray[i]==0;i++);
	if(i==IntegerLen) stream<<0;
	else for(;i<IntegerLen;i++) stream<<obj.NumArray[i];
	return stream;
}

istream& operator >> (istream& stream,Integer& obj)
{
	int n,i;
	char input[IntegerLen];
	stream>>input;
	n=strlen(input);
	for(i=0;n-i-1>0;i++){
		if(input[n-i-1]>'9'||input[n-i-1]<'0') throw Error("Input Error!");
		obj[i]=input[n-i-1]-'0';
	}
	if(input[n-i-1]=='-') obj.sign=-1;
	else if(input[n-i-1]>'9'||input[n-i-1]<'0') throw Error("Input Error!");
	else obj[i]=input[n-1-i++]-'0'; 
	for(;i<IntegerLen;i++) obj[i]=0;
	return stream;
}

Integer Integer::absolute() const
{
	Integer result;
	result=*this;
	result.sign=1;
	return result;
}

int Integer::IntegerLength() const
{
	int i,result=0;
	for(i=0;i<IntegerLen&&NumArray[i]==0;i++);
	result=IntegerLen-i;
	return result;
}

void Integer::augment(int n)
{
	int i;
	if(n>=0){
		for(i=0;i<IntegerLen;i++)
			if(i<IntegerLen-n) NumArray[i]=NumArray[i+n];
			else NumArray[i]=0;
	}else{
		for(i=IntegerLen-1;i>=0;i--)
			if(i>=-n) NumArray[i]=NumArray[i+n];
			else NumArray[i]=0;
	}
}

int& Integer::operator [] (int index)
{
	if(index<0||index>=IntegerLen) throw Error("Out of Bounds!");
	return NumArray[IntegerLen-index-1];
}

const int& Integer::operator [] (int index) const
{
	if(index<0||index>=IntegerLen) throw Error("Out of Bounds!");
	return NumArray[IntegerLen-index-1];
}

#endif

