#pragma once
class CCreateEnt
{
public:
	CCreateEnt();
	~CCreateEnt();
	static AcDbObjectId CreatePoint(AcGePoint3d pt); //������

	static AcDbObjectId CreateLine(AcGePoint3d ptStart, AcGePoint3d ptEnd); //����ֱ��

	static AcDbObjectId CreateCircle(AcGePoint3d ptCenter, double radius);//����Բ
	static AcDbObjectId CreatePolyCircle(AcGePoint2d ptCenter, double radius, double width = 0);//���ߵķ�ʽ����Բ

	static AcDbObjectId CreateArc(AcGePoint2d ptCenter, double radius, double startAngle, double endAngle);//����Բ��
	static AcDbObjectId CreatePolyArc(AcGePoint2d ptCenter, double radius,
		double angleStart, double angleEnd, double width = 0);//�Զ��ߵķ�ʽ����Բ��

	static AcDbObjectId CreateEllipse(AcGePoint3d ptCenter,//������Բ
		AcGeVector3d vecNormal, AcGeVector3d majorAxis, double ratio);
	static AcDbObjectId CreateEllipse(AcGePoint2d pt1, AcGePoint2d pt2);//������Ӿ��δ�����Բ�����������أ�

	static AcDbObjectId CreateSpline(const AcGePoint3dArray& points,
		int order = 4, double fitTolerance = 0.0);//������������
	static AcDbObjectId CreateSpline(const AcGePoint3dArray& points,//���յ����ߵķ���������������
		const AcGeVector3d& startTangent, const AcGeVector3d&
		endTangent, int order = 4, double fitTolerance = 0.0);

	static AcDbObjectId CreatePolyline(AcGePoint2dArray points, double width = 0);//ͨ����ά���б�������

	static void CreatePoly();//ͨ���û��������ƶ���

	static AcDbObjectId CreateRect(AcGePoint2d pt1, AcGePoint2d pt2, double width = 0);//��������
	static AcDbObjectId CreateTriangle(AcGePoint3d pt1, AcGePoint3d pt2, AcGePoint3d pt3, double width = 0);//����������
	 
	static AcDbObjectId CreatePolygon(AcGePoint2d ptCenter, int number,
		double radius, double rotation, double width);//����������Σ��������Ϊ���ġ����������Բ�뾶����ת�Ƕȣ�����ֵ�����߿�

	static AcDbObjectId CreateText(const AcGePoint3d& ptInsert,//��������
		const ACHAR* text, AcDbObjectId style = AcDbObjectId::kNull,
		double height = 1, double rotation = 0);
	static AcDbObjectId CreateMText(const AcGePoint3d& ptInsert,//������������
		const ACHAR* text, AcDbObjectId style = AcDbObjectId::kNull,
		double height = 2.5, double width = 10);

	static AcDbObjectId CreateHatch(AcDbObjectIdArray objIds,//�������
		const ACHAR* patName, bool bAssociative);
	static AcDbObjectIdArray CreateRegion(const AcDbObjectIdArray& curveIds);//��������

	static CString NewLayer();//�½�һ��ͼ��
	static CString SetLayer();//����ͼ������
	static CString ChooseLayer();//ѡ��ͼ�㣨���û�ѡ��ʵ����ӵ�ָ����ͼ�㣩
	static CString DelLayer();//ɾ��ͼ��

	static AcDbObjectIdArray SSet();//����ѡ��

	static AcDbObjectId CreateBlk();//�����鶨��
	static void InsertBlk();//��������

	static AcDbObjectId CCreateEnt::PostToModelSpace(AcDbEntity* pEnt);//��ʵ����ӵ�ͼ�����ݿ�
};

