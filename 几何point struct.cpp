struct pt
{
	double x, y;
	pt(){}
	pt(double _x, double _y):x(_x), y(_y){}
	pt operator - (const pt p1){return pt(x - p1.x, y - p1.y);}
	pt operator + (const pt p1){return pt(x + p1.x, y + p1.y);}
	pt operator * (double s){return pt(x * s, y * s);}
	pt operator / (double s){return pt(x / s, y / s);}
	bool operator < (const pt p1)const{return y < p1.y-eps || y < p1.y+eps && x < p1.x;}
	bool operator == (const pt p1)const{return !SGN(y - p1.y) && !SGN(x - p1.x);}
	bool operator != (const pt p1)const{return SGN(y - p1.y) || SGN(x - p1.x);}
	void read(){scanf("%lf %lf", &x, &y);}
};
