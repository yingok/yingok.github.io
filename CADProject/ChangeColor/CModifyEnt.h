#pragma once
class CModifyEnt
{
public:
	CModifyEnt();
	~CModifyEnt();
	static Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex);//�ı�ʵ����ɫ
	static Acad::ErrorStatus ChangeLayer(AcDbObjectId entId, CString strLayerName);//�ı�ʵ��ͼ��
	static Acad::ErrorStatus ChangeLinetype(AcDbObjectId entId, CString strLinetype);
	//�ı�ʵ�����ͣ�ͨ���ı�ͼ��ķ�ʽ��

	static Acad::ErrorStatus Rotate(AcDbObjectId entId, AcGePoint2d ptBase, double rotation);
	//����ָ���ĽǶȣ��û���ֵ��ʾ����תָ����ʵ��
	static Acad::ErrorStatus Move(AcDbObjectId entId, AcGePoint3d ptBase, AcGePoint3d ptDest);
	//����ָ���������ƶ�ָ����ʵ��
	static Acad::ErrorStatus Scale(AcDbObjectId entId, AcGePoint3d ptBase, double scaleFactor);
	//����ʵ��
};

