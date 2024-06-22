#include "stdafx.h"
#include "CAuxiliary.h"
#include "CCreateEnt.h"
#include "CModifyEnt.h"
#include "CCalculation.h"

vector<CMyPoint> CAuxiliary::vec_pt;//��ʼ����̬�б�
vector<CMyTriangle> CAuxiliary::vec_tri;//��ʼ����̬�б�
CString CAuxiliary::result = "";

CAuxiliary::CAuxiliary()
{
} 


CAuxiliary::~CAuxiliary()
{
}

void CAuxiliary::GetWidth(ads_real *width_begin, ads_real *width_end)
{
	if (RTNORM == acedGetReal(_T("\n��������߿�:"), width_begin))
	{
		if (RTNORM == acedGetReal(_T("\n�����յ��߿�:"), width_end))
		{
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

int CAuxiliary::GetColorIndex()
{
	int nColorIndex = 0;
	if (RTNORM != acedGetInt(_T("\n������ɫ����ֵ(0��256):"), &nColorIndex))
	{
		return 0;
	}

	/// ������ɫ����ֵ��Ч�����
	while (nColorIndex < 0 || nColorIndex > 256)
	{
		acedPrompt(_T("\n��������Ч����ɫ����."));
		if (RTNORM != acedGetInt(_T("\n������ɫ����ֵ(0��256):"), &nColorIndex))
		{
			return 0;
		}
	}
	
	return nColorIndex;
}

void CAuxiliary::drawTriangle(vector<CMyPoint> pt, CString strLayerName)
{
#pragma region ��ʼ��
	CAuxiliary A;//�������ʵ���������ʹ�ó�Ա����,��Ϊ�����Ǿ�̬���������ⲿ���Ե���
	A.vec_tri.clear();
	//A.vec_v.clear();
	A.xmax = 0;
	A.ymax = 0;
	A.xmin = 100000000000;
	A.ymin = 100000000000;
#pragma endregion

#pragma region ���ɳ�ʼ������
	for (int i = 0; i < pt.size(); i++)
	{
		if (A.xmax < pt[i].pt.x)
			A.xmax = pt[i].pt.x;
		if (A.ymax < pt[i].pt.y)
			A.ymax = pt[i].pt.y;
		if (A.xmin > pt[i].pt.x)
			A.xmin = pt[i].pt.x;
		if (A.ymin > pt[i].pt.y)
			A.ymin = pt[i].pt.y;
	}

	AcGePoint3d pt1, pt2, pt3, pt4;
	pt1.x = A.xmin - 1;
	pt1.y = A.ymin - 1;
	pt2.x = A.xmin - 1;
	pt2.y = A.ymax + 1;
	pt3.x = A.xmax + 1;
	pt3.y = A.ymax + 1;
	pt4.x = A.xmax + 1;
	pt4.y = A.ymin - 1;

	CMyTriangle tri1;
	tri1.pt1 = pt1;
	tri1.pt2 = pt2;
	tri1.pt3 = pt3;

	A.vec_tri.push_back(tri1);

	CMyTriangle tri2;
	tri2.pt1 = pt1;
	tri2.pt2 = pt3;
	tri2.pt3 = pt4;

	A.vec_tri.push_back(tri2);
#pragma endregion

#pragma region ����ƽ��������
	double x0, y0, r;
	for (int i = 0; i < CAuxiliary::vec_pt.size(); i++)//��ÿ����ɢ����б���
	{
		vector<CMyTriangle> tri;//T2�������б�
		vector<int> b;//��¼T1��Ҫ���е�����������
		vector<CMyLine> vec_line;//�����洢ֱ��

		double x = CAuxiliary::vec_pt[i].pt.x;
		double y = CAuxiliary::vec_pt[i].pt.y;

		for (int j = 0; j < A.vec_tri.size(); j++)//��˳���T1��ȡ��һ��������ABC�����䶥��ΪA, B, C����������������Բ��Բ��O���뾶r
		{
			x0 = CCalculation::X0(A.vec_tri[j].pt1.x, A.vec_tri[j].pt1.y, A.vec_tri[j].pt2.x,
				A.vec_tri[j].pt2.y, A.vec_tri[j].pt3.x, A.vec_tri[j].pt3.y);
			y0 = CCalculation::Y0(A.vec_tri[j].pt1.x, A.vec_tri[j].pt1.y, A.vec_tri[j].pt2.x,
				A.vec_tri[j].pt2.y, A.vec_tri[j].pt3.x, A.vec_tri[j].pt3.y);
			r = CCalculation::R(x0, y0, A.vec_tri[j].pt1.x, A.vec_tri[j].pt1.y);

			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) < r * r)//���������ڲ�
			{
				CMyLine line1;
				CMyLine line2;
				CMyLine line3;
				line1.ptBegin = A.vec_tri[j].pt1;
				line1.ptEnd = A.vec_tri[j].pt2;
				line2.ptBegin = A.vec_tri[j].pt2;
				line2.ptEnd = A.vec_tri[j].pt3;
				line3.ptBegin = A.vec_tri[j].pt3;
				line3.ptEnd = A.vec_tri[j].pt1;
				vec_line.push_back(line1);
				vec_line.push_back(line2);
				vec_line.push_back(line3);//��tri�����������εı���Ϣ�洢�����б���

				tri.push_back(A.vec_tri[j]);//T2���������
				b.push_back(j);
			}
		}
		for (int j = (int)b.size() - 1; j >= 0; j--)//�б����ݵĽṹ�����˱���Ӻ���ǰ�Ƴ�����
		{
			A.vec_tri.erase(A.vec_tri.begin() + b[j]);//T1�Ƴ������Σ�ʵ��T1��T2����
		}

		/*CString str;
		str.Format(_T("%d"), A.vec_tri.size());
		acedAlert(str + _T("VEC"));
		str.Format(_T("%d"), tri.size());
		acedAlert(str);*/

		for (int j = 0; j < vec_line.size(); j++)//��T2����������Ѱ�����й����ߣ���ɾ����Щ�����ߣ��ٽ�ʣ�µı߼��뵽���б�S�У�Ȼ�����T2
		{
			for (int k = 0; k < vec_line.size(); k++)
			{
				if (j != k)//��ͬ���໥�Ƚ�
				{
					if (vec_line[j].ptBegin == vec_line[k].ptBegin && vec_line[j].ptEnd == vec_line[k].ptEnd
						|| vec_line[j].ptBegin == vec_line[k].ptEnd && vec_line[j].ptEnd == vec_line[k].ptBegin)//�ж��������Ƿ��غϣ��غϾ�ɾ��
					{
						vec_line.erase(vec_line.begin() + k);//j < k
						vec_line.erase(vec_line.begin() + j);
						if (j == 0)//Ϊ�˼���ѭ������
						{
							j = 0;
						}
						else
						{
							j--;
						}
					}
				}
			}
		}
		for (int j = 0; j < vec_line.size(); j++)//��S�е�ÿ���ߵĶ˵���P�����ӣ��õ�����µ������Σ�����������ӵ��������б�T1��
		{
			CMyTriangle triAngle;
			triAngle.pt1 = CAuxiliary::vec_pt[i].pt;
			triAngle.pt2 = vec_line[j].ptBegin;
			triAngle.pt3 = vec_line[j].ptEnd;
			A.vec_tri.push_back(triAngle);
		}
	}
#pragma endregion

#pragma region ���ɲ�����������
	vector<int> a;//�洢Ҫɾ���������ε�������Ϣ
	for (int i = 0; i < A.vec_tri.size(); i++)
	{
		if (A.vec_tri[i].pt1 == pt1 || A.vec_tri[i].pt1 == pt2 || A.vec_tri[i].pt1 == pt3 || A.vec_tri[i].pt1 == pt4
			|| A.vec_tri[i].pt2 == pt1 || A.vec_tri[i].pt2 == pt2 || A.vec_tri[i].pt2 == pt3 || A.vec_tri[i].pt2 == pt4
			|| A.vec_tri[i].pt3 == pt1 || A.vec_tri[i].pt3 == pt2 || A.vec_tri[i].pt3 == pt3 || A.vec_tri[i].pt3 == pt4)
		{
			a.push_back(i);
		}
	}
	for (int j = (int)a.size() - 1; j >= 0; j--)
	{
		A.vec_tri.erase(A.vec_tri.begin() + a[j]);
	}
#pragma endregion
	/*CString str;
	str.Format(_T("%d"), CAuxiliary::vec_tri.size());//���ھ�̬����������ʵ����ʱ���������ݣ�����ֱ���Ծ�̬�ķ�ʽ����
	acedAlert(_T("�����εĸ���Ϊ��") + str);*/

	AcDbObjectId triangleId;

	for (int i = 0; i < A.vec_tri.size(); i++)
	{
		triangleId = CCreateEnt::CreateTriangle(A.vec_tri[i].pt1, A.vec_tri[i].pt2, A.vec_tri[i].pt3);
		CModifyEnt::ChangeLayer(triangleId, strLayerName);//������������ͼ��
	}
}

CString CAuxiliary::calculateV(vector<CMyTriangle> vec_tri, int gaocheng)
{
	vector<double> vec_v;//�����洢�����������Ϣ

	for (int i = 0; i < vec_tri.size(); i++)
	{
		double SS, H;
		SS = CCalculation::SS(vec_tri[i]);
		H = CCalculation::H(vec_tri[i], gaocheng);
		vec_v.push_back(SS * H);
	}
	//�������
	for (int i = 0; i < vec_v.size(); i++)//ð�������㷨
	{
		for (int j = 0; j < vec_v.size() - 1 - i; j++)
		{
			if (vec_v[j] > vec_v[j + 1])
			{
				double temp = vec_v[j + 1];
				vec_v[j + 1] = vec_v[j];
				vec_v[j] = temp;
			}
		}
	}

	//���㱨��
	CString str;
	CString str_gaocheng;
	str_gaocheng.Format(_T("%d"),gaocheng);
	CString str_number;
	str_number.Format(_T("%d"), CAuxiliary::vec_tri.size());
	CString str_V;
	double V_sum = 0;
	for (int i = 0; i < vec_v.size(); i++)
	{
		V_sum += vec_v[i];
	}
	str_V.Format(_T("%.3f"),V_sum);

	str = "�������������������\n\n";
	str += "---------------������������Ϣ---------------\n";
	str += "��׼�̣߳�  " + str_gaocheng + "m\n";
	str += "�����θ�����  " + str_number + "\n";
	str += "�����  " + str_V + "\n\n";

	str += "---------------20��������˵��---------------\n";
	str += "���\t��������\n";
	CString str_i;
	for (int i = 0; i < 20; i++)
	{
		str_i.Format(_T("%d"),i + 1);
		str += str_i + "\t\n";
		//str += vec_tri[i].pt1.dianhao + vec_tri[i].pt2.dianhao + vec_tri[i].pt3.dianhao + "\n";
	}//����û�п��ǵ���Ӧ�����ó�CMyPoint���͵�
	str += "\n---------------�����С��5�����������---------------\n";
	CString str_vi;
	for (int i = 0; i < 5; i++)
	{
		str_i.Format(_T("%d"), i + 1);
		str += str_i + "\t";
		str_vi.Format(_T("%.3f"), vec_v[i]);
		str += str_vi + "\n";
	}
	str += "\n---------------�������5�����������---------------\n";
	for (int i = 0; i < 5; i++)
	{
		str_i.Format(_T("%d"), i + 1);
		str += str_i + "\t";
		str_vi.Format(_T("%.3f"), vec_v[vec_v.size() - 1 - i]);
		str += str_vi + "\n";
	}
	
	acedAlert(str);

	return str;
}

