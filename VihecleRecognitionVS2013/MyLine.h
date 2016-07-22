#pragma once
#include <math.h>
template <class T> class C2DPoint
{
public:
	T x;
	T y;
public:
	void set_X(T data);
	void set_Y(T data);
	C2DPoint();
	C2DPoint(T m, T n);
	~C2DPoint();
	
};
template <class T> void C2DPoint <T>::set_X(T data)
{
	x = data;
}
template <class T> void C2DPoint <T>::set_Y(T data)
{
	y = data;
}
template <class T>  C2DPoint <T>::C2DPoint(T m, T n)
{
	x = m;
	y = n;
}
template <class T>  C2DPoint <T>::C2DPoint()
{

}
template <class T>  C2DPoint <T>::~C2DPoint()
{

}

class CLine
{
public:
	C2DPoint<int> startpnt;
	C2DPoint<int> endpnt;
	double k;
	double b;
	bool isY_x;
};
class CMyLine
{
public:
	static void CalculateLineEquation(CLine *line);
	static void CalculateLinesIntersectPoint(const CLine& line1, const CLine& line2, C2DPoint<float> *point);
	static bool GetXValueOnLine(const CLine& line, const int& y, int *x);
	static bool GetYValueOnLine(const CLine& line, const int& x, int *y);
};
inline void CMyLine::CalculateLineEquation(CLine *line)
{
	int yDiff = line->endpnt.y - line->startpnt.y;
	int xDiff = line->endpnt.x - line->startpnt.x;
	if (abs(xDiff)<abs(yDiff))
	{
		line->isY_x = false;
		line->k = 1.0*xDiff / yDiff;
		line->b = line->endpnt.x - line->k*line->endpnt.y;
	}
	else
	{
		line->isY_x = true;
		line->k = 1.0*yDiff / xDiff;
		line->b = line->endpnt.y - line->k*line->endpnt.x;
	}
}
inline void CMyLine::CalculateLinesIntersectPoint(const CLine& line1, const CLine& line2, C2DPoint<float> *point)
{
	if (line1.isY_x)
	{
		if (line2.isY_x)
		{
			point->x = (line2.b - line1.b) / (line1.k - line2.k);
			point->y = line1.k*point->x + line1.b;
		}
		else
		{
			point->y = (line1.k*line2.b + line1.b) / (1 - line1.k*line2.k);
			point->x = line2.k*point->y + line2.b;
		}
	}
	else
	{
		if (line2.isY_x)
		{
			point->x = (line1.k*line2.b + line1.b) / (1 - line1.k*line2.k);
			point->y = line2.k*point->x + line2.b;
		}
		else
		{
			point->y = (line2.b - line1.b) / (line1.k - line2.k);
			point->x = line1.k*point->y + line1.b;
		}
	}
}
inline bool CMyLine::GetXValueOnLine(const CLine& line, const int& y, int *x)
{
	if (!line.isY_x)
	{
		*x = line.k*y + line.b;
	}
	else
	{
		if (line.k == 0.00000)  return false;
		*x = (y - line.b) / line.k;
	}
	return true;
}
inline bool CMyLine::GetYValueOnLine(const CLine& line, const int& x, int *y)
{
	if (line.isY_x)
	{
		*y = line.k*x + line.b;
	}
	else
	{
		if (line.k == 0.00000) return false;
		*y = (x - line.b) / line.k;
	}
	return true;
}
