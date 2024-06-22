#pragma once
#include "CMyPoint.h"

class CCalculation
{
public:
	CCalculation();
	~CCalculation();

	static AcGePoint3d Pt2dTo3d(AcGePoint2d pt);//��ά��ת��ά��
	static AcGePoint2d Pt3dTo2d(AcGePoint3d pt);//��ά��ת��ά��

	static double PI();

	static double Min(double a, double b);
	static double Max(double a, double b);

	static AcGePoint2d MiddlePoint(AcGePoint2d pt1, AcGePoint2d pt2);
	static AcGePoint3d MiddlePoint(AcGePoint3d pt1, AcGePoint3d pt2);


	static double hudutodu(double angle);
	static double dutohudu(double angle);

	//����TIN�ĺ���
	//���������Բ��Բ��
	static double X0(double x1, double y1, double x2, double y2, double x3, double y3);
	static double Y0(double x1, double y1, double x2, double y2, double x3, double y3);
	//���������Բ�İ뾶
	static double R(double x0, double y0, double x1, double y1);
	//б����������
	static double SS(CMyTriangle san);
	static double H(CMyTriangle san, double gaocheng);
};
