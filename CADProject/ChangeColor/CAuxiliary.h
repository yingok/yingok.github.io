#pragma once
#include <vector> 
#include "CMyPoint.h"
using namespace std;

class CAuxiliary
{
public:
	CAuxiliary();
	~CAuxiliary();

	//��ȡ�û�������߿�
	static void GetWidth(ads_real *width_begin, ads_real *width_end);

	//��ʾ�û�������ɫ����ֵ
	static int GetColorIndex();

	static vector<CMyPoint> vec_pt;//�����洢ɢ��
	static vector<CMyTriangle> vec_tri;//�����洢������

	double xmax, xmin, ymax, ymin;//�洢��ʼ������Ϣ

	static CString result;//������㱨��

	//�����ŷָ��ַ���
	/*BOOL GetFieldText(CString strLineText, CStringArray &fields)
	{
		if (strLineText.Find(",", 0) == -1) // ����Ҳ���Ӣ�Ķ��ţ������˳�
		{
		return FALSE;
		}
		int nLeftPos = 0, nRightPos = 0; // ���ҷָ�������ʼλ��
		while ((nRightPos = strLineText.Find(",", nRightPos)) != -1)
		{
			fields.Add(strLineText.Mid(nLeftPos, nRightPos - nLeftPos));
			nLeftPos = nRightPos + 1;
			nRightPos++;
		}
		// ���һ���е�����
		fields.Add(strLineText.Mid(nLeftPos));
		return TRUE;
	}*/

	//����������
	static void drawTriangle(vector<CMyPoint> vec_pt, CString strLayerName);

	//����TIN���
	static CString calculateV(vector<CMyTriangle> vec_tri, int gaocheng);

};

