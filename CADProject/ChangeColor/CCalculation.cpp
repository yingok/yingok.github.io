#include "stdafx.h"
#include "CCalculation.h"
#include <math.h>

CCalculation::CCalculation()
{
}


CCalculation::~CCalculation()
{
}

AcGePoint3d CCalculation::Pt2dTo3d(AcGePoint2d pt)
{
	AcGePoint3d ptTemp(pt.x, pt.y, 0);//����ά��ת����XOYƽ�����ά��
	return ptTemp;
}

AcGePoint2d CCalculation::Pt3dTo2d(AcGePoint3d pt)
{
	AcGePoint2d ptTemp(pt.x, pt.y);
	return ptTemp;
}

double CCalculation::PI()
{
	return 4 * atan(1.0);
}

double CCalculation::Min(double a, double b)
{
	if (a > b)
		return b;
	else
		return a;
}

double CCalculation::Max(double a, double b)
{
	if (a > b)
		return a;
	else
		return b;
}

AcGePoint2d CCalculation::MiddlePoint(AcGePoint2d pt1, AcGePoint2d pt2)
{
	AcGePoint2d pt;
	pt[X] = (pt1[X] + pt2[X]) / 2;
	pt[Y] = (pt1[Y] + pt2[Y]) / 2;
	return pt;
}
AcGePoint3d CCalculation::MiddlePoint(AcGePoint3d pt1, AcGePoint3d pt2)
{
	AcGePoint3d pt;
	pt[X] = (pt1[X] + pt2[X]) / 2;
	pt[Y] = (pt1[Y] + pt2[Y]) / 2;
	pt[Z] = (pt1[Z] + pt2[Z]) / 2;
	return pt;
}

//���Ȼ��Ƕ�
double CCalculation::hudutodu(double angle)
{
	return angle * 180 / CCalculation::PI();
}
// �Ƕ�ת��Ϊ����
double CCalculation::dutohudu(double angle)
{
	return angle * CCalculation::PI() / 180;
}

double CCalculation::X0(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double x0;
	x0 = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) - (y3 - y1) 
		* (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) / (2 * (x3 - x1) * (y2 - y1) - 2 * (x2 - x1) * (y3 - y1));
	return x0;
}
double CCalculation::Y0(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double y0;
	y0 = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) - (x3 - x1) 
		* (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) / (2 * (y3 - y1) * (x2 - x1) - 2 * (y2 - y1) * (x3 - x1));
	return y0;
}

double CCalculation::R(double x0, double y0, double x1, double y1)
{
	double r;
	r = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
	return r;
}

double CCalculation::SS(CMyTriangle san)
{
	double s;
	s = abs((san.pt2.x - san.pt1.x) * (san.pt3.y - san.pt1.y) - (san.pt3.x - san.pt1.x) * (san.pt2.y - san.pt1.y)) / 2;
	return s;
}
double CCalculation::H(CMyTriangle san, double gaocheng)
{
	double h;
	h = (san.pt1.z + san.pt2.z + san.pt3.z) / 3 - gaocheng;
	return h;
}