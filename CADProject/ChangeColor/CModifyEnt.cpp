#include "stdafx.h"
#include "CModifyEnt.h"
#include "CCalculation.h"


CModifyEnt::CModifyEnt()
{
}


CModifyEnt::~CModifyEnt()
{
}
//Acad::ErrorStatus ��Ŀ�ľ��൱��һ��ʹ��BOOL ������Ϊ
//�����ķ���ֵ��������ʶ�����Ƿ�ִ�гɹ���

Acad::ErrorStatus CModifyEnt::ChangeColor(AcDbObjectId entId, Adesk::UInt16
	colorIndex)
{
	AcDbEntity *pEntity;
	// ��ͼ�����ݿ��еĶ���
	acdbOpenObject(pEntity, entId, AcDb::kForWrite);
	// �޸�ʵ�����ɫ
	pEntity->setColorIndex(colorIndex);
	// ����֮�󣬼�ʱ�ر�
	pEntity->close();

	return Acad::eOk;
}

Acad::ErrorStatus CModifyEnt::ChangeLayer(AcDbObjectId entId, CString strLayerName)
{
	AcDbEntity *pEntity;
	// ��ͼ�����ݿ��еĶ���
	acdbOpenObject(pEntity, entId, AcDb::kForWrite);
	// �޸�ʵ���ͼ��
	pEntity->setLayer(strLayerName);
	// ����֮�󣬼�ʱ�ر�
	pEntity->close();

	return Acad::eOk;
}

Acad::ErrorStatus CModifyEnt::ChangeLinetype(AcDbObjectId entId, CString strLinetype)
{
	AcDbEntity *pEntity;
	// ��ͼ�����ݿ��еĶ���
	acdbOpenObject(pEntity, entId, AcDb::kForWrite);
	// �޸�ʵ�������
	pEntity->setLayer(strLinetype);
	// ����֮�󣬼�ʱ�ر�
	pEntity->close();

	return Acad::eOk;
}

Acad::ErrorStatus CModifyEnt::Rotate(AcDbObjectId entId, AcGePoint2d ptBase, double rotation)
{
	AcGeMatrix3d xform;//����һ�����α任����
	AcGeVector3d vec(0, 0, 1);
	xform.setToRotation(rotation, vec, CCalculation::Pt2dTo3d(ptBase));//������ת
	AcDbEntity *pEnt;//����ʵ��
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite, false);
	pEnt->transformBy(xform);
	pEnt->close();
	return es;
}
Acad::ErrorStatus CModifyEnt::Move(AcDbObjectId entId, AcGePoint3d ptBase,AcGePoint3d ptDest)
{
	// ���ñ任����Ĳ���
	AcGeMatrix3d xform;
	AcGeVector3d vec(ptDest.x - ptBase.x, ptDest.y - ptBase.y, ptDest.z - ptBase.z);
	xform.setToTranslation(vec);
	AcDbEntity *pEnt;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite,false);
	pEnt->transformBy(xform);
	pEnt->close();
	return es;
}
Acad::ErrorStatus CModifyEnt::Scale(AcDbObjectId entId,AcGePoint3d ptBase, double scaleFactor)
{
	// ���ñ任����Ĳ���
	AcGeMatrix3d xform;
	xform.setToScaling(scaleFactor, ptBase);
	AcDbEntity *pEnt;
	Acad::ErrorStatus es = acdbOpenObject(pEnt, entId, AcDb::kForWrite,false);
	pEnt->transformBy(xform);
	pEnt->close();
	return es;
}