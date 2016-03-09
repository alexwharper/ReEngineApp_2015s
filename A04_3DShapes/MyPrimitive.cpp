#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	vector3 topPoint(0.00f, a_fHeight / 2, 0.00f); //top vertex
	vector3 midPoint(0.00f, -(a_fHeight / 2), 0.00f); //mid-base vertex
	std::vector<vector3> basePoints; //base vertices
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		//calculate vertex positions
		float angle = ((2 * PI) / a_nSubdivisions) * x;
		float x_Value = a_fRadius * sin(angle);
		float z_Value = a_fRadius * cos(angle);

		basePoints.push_back(vector3(x_Value, -(a_fHeight / 2), z_Value));
	}
	//create cone
	for (int x = 0; x < basePoints.size(); x++)
	{
		AddVertexPosition(topPoint);
		AddVertexPosition(basePoints[x]);
		if (x == basePoints.size() - 1)
		{
			AddVertexPosition(basePoints[0]);
		}
		else
		{
			AddVertexPosition(basePoints[x + 1]);
		}
	}
	//create base
	for (int x = 0; x < basePoints.size(); x++)
	{
		AddVertexPosition(midPoint);
		if (x == basePoints.size() - 1)
		{
			AddVertexPosition(basePoints[0]);
		}
		else
		{
			AddVertexPosition(basePoints[x + 1]);
		}
		AddVertexPosition(basePoints[x]);
	}

	//float fValue = 0.5f;
	////3--2
	////|  |
	////0--1
	//vector3 point0(-fValue, -fValue, fValue); //0
	//vector3 point1(fValue, -fValue, fValue); //1
	//vector3 point2(fValue, fValue, fValue); //2
	//vector3 point3(-fValue, fValue, fValue); //3

	//AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	vector3 topMid(0.00f, a_fHeight / 2, 0.00f); //mid-top vertex
	vector3 baseMid(0.00f, -(a_fHeight / 2), 0.00f); //mid-base vertex
	std::vector<vector3> topPoints; //top vertices
	std::vector<vector3> basePoints; //base vertices
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		//calculate vertex positions
		float angle = ((2 * PI) / a_nSubdivisions) * x;
		float x_Value = a_fRadius * sin(angle);
		float z_Value = a_fRadius * cos(angle);

		basePoints.push_back(vector3(x_Value, -(a_fHeight / 2), z_Value));
	}
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		//calculate vertex positions
		float angle = ((2 * PI) / a_nSubdivisions) * x;
		float x_Value = a_fRadius * sin(angle);
		float z_Value = a_fRadius * cos(angle);

		topPoints.push_back(vector3(x_Value, a_fHeight / 2, z_Value));
	}
	//create base
	for (int x = 0; x < basePoints.size(); x++)
	{
		AddVertexPosition(baseMid);
		if (x == basePoints.size() - 1)
		{
			AddVertexPosition(basePoints[0]);
		}
		else
		{
			AddVertexPosition(basePoints[x + 1]);
		}
		AddVertexPosition(basePoints[x]);
	}
	//create top
	for (int x = 0; x <topPoints.size(); x++)
	{
		AddVertexPosition(topMid);
		AddVertexPosition(topPoints[x]);
		if (x == topPoints.size() - 1)
		{
			AddVertexPosition(topPoints[0]);
		}
		else
		{
			AddVertexPosition(topPoints[x + 1]);
		}
	}
	//create sides
	for (int x = 0; x < basePoints.size(); x++)
	{
		if (x != basePoints.size() - 1)
		{
			AddQuad(basePoints[x], basePoints[x + 1], topPoints[x], topPoints[x + 1]);
		}
		else
		{
			AddQuad(basePoints[x], basePoints[0], topPoints[x], topPoints[0]);
		}
	}

	//float fValue = 0.5f;
	////3--2
	////|  |
	////0--1
	//vector3 point0(-fValue, -fValue, fValue); //0
	//vector3 point1(fValue, -fValue, fValue); //1
	//vector3 point2(fValue, fValue, fValue); //2
	//vector3 point3(-fValue, fValue, fValue); //3

	//AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	std::vector<vector3> outerTopPoints; //outer-top vertices
	std::vector<vector3> outerBasePoints; //outer-base vertices
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		//calculate vertex positions
		float angle = ((2 * PI) / a_nSubdivisions) * x;
		float x_Value = a_fOuterRadius * sin(angle);
		float z_Value = a_fOuterRadius * cos(angle);

		outerBasePoints.push_back(vector3(x_Value, -(a_fHeight / 2), z_Value));
	}
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		//calculate vertex positions
		float angle = ((2 * PI) / a_nSubdivisions) * x;
		float x_Value = a_fOuterRadius * sin(angle);
		float z_Value = a_fOuterRadius * cos(angle);

		outerTopPoints.push_back(vector3(x_Value, a_fHeight / 2, z_Value));
	}
	std::vector<vector3> innerTopPoints; //inner-top vertices
	std::vector<vector3> innerBasePoints; //inner-base vertices
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		//calculate vertex positions
		float angle = ((2 * PI) / a_nSubdivisions) * x;
		float x_Value = a_fInnerRadius * sin(angle);
		float z_Value = a_fInnerRadius * cos(angle);

		innerBasePoints.push_back(vector3(x_Value, -(a_fHeight / 2), z_Value));
	}
	for (int x = 0; x < a_nSubdivisions; x++)
	{
		//calculate vertex positions
		float angle = ((2 * PI) / a_nSubdivisions) * x;
		float x_Value = a_fInnerRadius * sin(angle);
		float z_Value = a_fInnerRadius * cos(angle);

		innerTopPoints.push_back(vector3(x_Value, a_fHeight / 2, z_Value));
	}
	//create outer sides
	for (int x = 0; x < outerBasePoints.size(); x++)
	{
		if (x != outerBasePoints.size() - 1)
		{
			AddQuad(outerBasePoints[x], outerBasePoints[x + 1], outerTopPoints[x], outerTopPoints[x + 1]);
		}
		else
		{
			AddQuad(outerBasePoints[x], outerBasePoints[0], outerTopPoints[x], outerTopPoints[0]);
		}
	}
	//create inner sides
	for (int x = 0; x < innerBasePoints.size(); x++)
	{
		if (x != innerBasePoints.size() - 1)
		{
			AddQuad(innerTopPoints[x], innerTopPoints[x + 1], innerBasePoints[x], innerBasePoints[x + 1]);
		}
		else
		{
			AddQuad(innerTopPoints[x], innerTopPoints[0], innerBasePoints[x], innerBasePoints[0]);
		}
	}
	//create base ring
	for (int x = 0; x < outerBasePoints.size(); x++)
	{
		if (x != outerBasePoints.size() - 1)
		{
			AddQuad(innerBasePoints[x], innerBasePoints[x + 1], outerBasePoints[x], outerBasePoints[x + 1]);
		}
		else
		{
			AddQuad(innerBasePoints[x], innerBasePoints[0], outerBasePoints[x], outerBasePoints[0]);
		}
	}
	//create top ring
	for (int x = 0; x < outerTopPoints.size(); x++)
	{
		if (x != outerTopPoints.size() - 1)
		{
			AddQuad(outerTopPoints[x], outerTopPoints[x + 1], innerTopPoints[x], innerTopPoints[x + 1]);
		}
		else
		{
			AddQuad(outerTopPoints[x], outerTopPoints[0], innerTopPoints[x], innerTopPoints[0]);
		}
	}

	//float fValue = 0.5f;
	////3--2
	////|  |
	////0--1
	//vector3 point0(-fValue, -fValue, fValue); //0
	//vector3 point1(fValue, -fValue, fValue); //1
	//vector3 point2(fValue, fValue, fValue); //2
	//vector3 point3(-fValue, fValue, fValue); //3

	//AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	////Sets minimum and maximum of subdivisions
	//if (a_nSubdivisions < 1)
	//{
	//	GenerateCube(a_fRadius * 2, a_v3Color);
	//	return;
	//}
	//if (a_nSubdivisions > 6)
	//	a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	vector3 topPoint(0.00f, a_fRadius, 0.00f);
	vector3 bottomPoint(0.00f, -a_fRadius, 0.00f);
	std::vector<std::vector<vector3>> spherePoints; //holds all other vertices on the sphere

	//add the middle ring of vertices; if the number of subdivisions is even, there are two middle rings
	if (a_nSubdivisions % 2 == 0)
	{
		std::vector<vector3> topMiddleRing;
		for (int x = 0; x < a_nSubdivisions; x++)
		{
			//calculate vertex positions
			float angle = ((2 * PI) / a_nSubdivisions) * x;
			float x_Value = a_fRadius * sin(angle);
			float z_Value = a_fRadius * cos(angle);

			topMiddleRing.push_back(vector3(x_Value, a_fRadius / (2 * a_nSubdivisions), z_Value));
		}
		std::vector<vector3> bottomMiddleRing;
		for (int x = 0; x < a_nSubdivisions; x++)
		{
			//calculate vertex positions
			float angle = ((2 * PI) / a_nSubdivisions) * x;
			float x_Value = a_fRadius * sin(angle);
			float z_Value = a_fRadius * cos(angle);

			bottomMiddleRing.push_back(vector3(x_Value, -a_fRadius / (2 * a_nSubdivisions), z_Value));
		}
		spherePoints.push_back(topMiddleRing);
		spherePoints.push_back(bottomMiddleRing);
	}
	else
	{
		std::vector<vector3> middleRing;
		for (int x = 0; x < a_nSubdivisions; x++)
		{
			//calculate vertex positions
			float angle = ((2 * PI) / a_nSubdivisions) * x;
			float x_Value = a_fRadius * sin(angle);
			float z_Value = a_fRadius * cos(angle);

			middleRing.push_back(vector3(x_Value, 0.00f, z_Value));
		}
		spherePoints.push_back(middleRing);
	}

	//add more rings to the sphere equal to the number of subdivisions minus existing rings
	//rings can be added in pairs moving away from the middle ring/rings in both directions,
	//so the loop will run half the number of times
	int existingRings = spherePoints.size();
	for (int x = 0; x < (a_nSubdivisions -  existingRings)/ 2; x++)
	{
		std::vector<vector3> upperRing;
		std::vector<vector3> lowerRing;
		//get an adjusted radius for this pair of rings
		float adjustedRadius = (a_fRadius / ((a_nSubdivisions / 2) + 1)) * ((a_nSubdivisions / 2) - x);

		for (int y = 0; y < a_nSubdivisions; y++)
		{
			//calculate vertex positions
			float angle = ((2 * PI) / a_nSubdivisions) * y;
			float x_Value = adjustedRadius * sin(angle);
			float z_Value = adjustedRadius * cos(angle);

			upperRing.push_back(vector3(x_Value, a_fRadius - adjustedRadius, z_Value));
			lowerRing.push_back(vector3(x_Value, -a_fRadius + adjustedRadius, z_Value));
		}
		spherePoints.push_back(upperRing);
		spherePoints.push_back(lowerRing);
	}

	//draw quads around the sphere moving away from the middle ring/rings
	if (a_nSubdivisions % 2 == 0)
	{
		//draw middle ring of quads
		for (int x = 0; x < spherePoints[0].size(); x++)
		{
			if (x != spherePoints[0].size() - 1)
			{
				AddQuad(spherePoints[1][x], spherePoints[1][x + 1], spherePoints[0][x], spherePoints[0][x + 1]);
			}
			else
			{
				AddQuad(spherePoints[1][x], spherePoints[1][0], spherePoints[0][x], spherePoints[0][0]);
			}
		}
		//draw more rings of quads
		for (int x = 0; x < spherePoints.size() - 2; x++)
		{
			if (x % 2 == 0)
			{
				for (int y = 0; y < spherePoints[x].size(); y++)
				{
					if (y != spherePoints[x].size() - 1)
					{
						AddQuad(spherePoints[x][y], spherePoints[x][y + 1], spherePoints[x + 2][y], spherePoints[x + 2][y + 1]);
					}
					else
					{
						AddQuad(spherePoints[x][y], spherePoints[x][0], spherePoints[x + 2][y], spherePoints[x + 2][0]);
					}
				}
			}
			else
			{
				for (int y = 0; y < spherePoints[x].size(); y++)
				{
					if (y != spherePoints[x].size() - 1)
					{
						AddQuad(spherePoints[x + 2][y], spherePoints[x + 2][y + 1], spherePoints[x][y], spherePoints[x][y + 1]);
					}
					else
					{
						AddQuad(spherePoints[x + 2][y], spherePoints[x + 2][0], spherePoints[x][y], spherePoints[x][0]);
					}
				}
			}
		}
	}
	else
	{

	}

	//draw the tris for the top and bottom
	for (int x = 0; x < spherePoints[spherePoints.size() - 1].size(); x++)
	{
		AddVertexPosition(bottomPoint);
		if (x == spherePoints[spherePoints.size() - 1].size() - 1)
		{
			AddVertexPosition(spherePoints[spherePoints.size() - 1][0]);
		}
		else
		{
			AddVertexPosition(spherePoints[spherePoints.size() - 1][x + 1]);
		}
		AddVertexPosition(spherePoints[spherePoints.size() - 1][x]);
	}
	for (int x = 0; x < spherePoints[spherePoints.size() - 2].size(); x++)
	{
		AddVertexPosition(spherePoints[spherePoints.size() - 2][x]);
		if (x == spherePoints[spherePoints.size() - 2].size() - 1)
		{
			AddVertexPosition(spherePoints[spherePoints.size() - 2][0]);
		}
		else
		{
			AddVertexPosition(spherePoints[spherePoints.size() - 2][x + 1]);
		}
		AddVertexPosition(topPoint);
	}

	//float fValue = 0.5f;
	////3--2
	////|  |
	////0--1
	//vector3 point0(-fValue, -fValue, fValue); //0
	//vector3 point1(fValue, -fValue, fValue); //1
	//vector3 point2(fValue, fValue, fValue); //2
	//vector3 point3(-fValue, fValue, fValue); //3

	//AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}