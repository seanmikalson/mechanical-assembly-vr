#include "TriangleMeshHull.h"

#define ALL_TRIANGLES_TO_COPY int i = 0; i < noTriangles; i++
#define VERT_ONE (*this).verticies.getItem(oneIndex)
#define VERT_TWO (*this).verticies.getItem(twoIndex)
#define VERT_THREE (*this).verticies.getItem(threeIndex)
#define NORMAL_I (*this).normals.getItem(i)
#define VERTEX_INDICIES_NOT_FOUND one || two || three

#define ALL_VERTICIES int i = 0; i < noVerticies; i++
#define ALL_NORMALS int i = 0; i < noTriangles; i++

#define TRIANGLES_FULL (noTriangles >= maxTriangles)
#define VERTICIES_FULL (noVerticies >= maxVerticies)
#define INDICIES_OUT_OF_RANGE (vertIndOne >= noVerticies || vertIndTwo >= noVerticies || vertIndThree >= noVerticies)

#define ALL_VERTICIES_IN_THIS_HULL int i = 0; i < noVerticies; i++
#define ALL_TRIANGLES_IN_OTHER_HULL int o = 0; o < (*(TriangleMeshHull*)(otherHull)).getNoTriangles(); o++
#define CURRENT_TRIANGLE (*(*(TriangleMeshHull*)(otherHull)).getTriangle(o))
#define CURRENT_VERTEX *(verticies.getItem(i)) + position
#define TRIANGLE_POSITION (*(TriangleMeshHull*)(otherHull)).getPosition()

#define NEW_INTERSECTION_CLOSER_OR_IS_FIRST_ONE_FOUND tempIntersect && (tempLength < *length || *length < 0.0f)

//----------------------------------------------
// Constructors and Destructors
//----------------------------------------------
TriangleMeshHull::TriangleMeshHull()
{
	verticies = List<Vertex>();
	normals = List<Vertex>();
	triangles = List<Triangle>();
	hullType = TriangleMesh;
	maxRadius = -1.0f;
	position = 0.0f;
}
TriangleMeshHull::TriangleMeshHull(int maxVerts,int maxTri,GLfloat x, GLfloat y, GLfloat z)
{
	position = Vertex(x,y,z);
	hullType = TriangleMesh;
	maxRadius = -1.0f;

	verticies = List<Vertex>(maxVerts);
	triangles = List<Triangle>(maxTri);
	normals = List<Vertex>(maxTri);
}
TriangleMeshHull::~TriangleMeshHull()
{

}
TriangleMeshHull::TriangleMeshHull(TriangleMeshHull& rhs)
{
	(*this).maxRadius = rhs.maxRadius;
	(*this).hullType = TriangleMesh;
	(*this).position = rhs.position;
	(*this).triangles = rhs.triangles;
	(*this).verticies = rhs.verticies;
	(*this).normals = rhs.normals;

	int noTriangles = rhs.triangles.getNoItems();
	for(ALL_TRIANGLES_TO_COPY)
	{
		int oneIndex = 0; int twoIndex = 0; int threeIndex = 0;
		bool one = true;
		bool two = true; 
		bool three = true;
		while(VERTEX_INDICIES_NOT_FOUND)
		{
			if(rhs.triangles[i].getVertexOne() == &rhs.verticies[oneIndex])
				one = false;
			else
				oneIndex++;

			if(rhs.triangles[i].getVertexTwo() == &rhs.verticies[twoIndex])
				two = false;
			else
				twoIndex++;

			if(rhs.triangles[i].getVertexThree() == &rhs.verticies[threeIndex])
				three = false;
			else
				threeIndex++;
		}

		(*this).triangles.addItem(Triangle(VERT_ONE,VERT_TWO,VERT_THREE,NORMAL_I));
	}
}

//----------------------------------------------
// Class Management Functions
//----------------------------------------------
void TriangleMeshHull::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
	verticies.addItem(Vertex(x,y,z));
	
	int index = verticies.getNoItems() - 1;
	GLfloat temp = (*verticies.getItem(index)).length();

	if( maxRadius < temp)
		maxRadius = temp;
}
bool TriangleMeshHull::addTriangle(int vertIndOne,int vertIndTwo, int vertIndThree)
{
	int noVerticies = verticies.getNoItems();
	if(INDICIES_OUT_OF_RANGE)
		return false;

	normals.addItem(Vertex());
	int normIndex = normals.getNoItems() - 1;
	triangles.addItem(Triangle(verticies.getItem(vertIndOne),
								verticies.getItem(vertIndTwo),
								verticies.getItem(vertIndThree),
								normals.getItem(normIndex)));

	(*triangles.getItem(normIndex)).generateNormal();
	return true;
}
void TriangleMeshHull::resetTriangles(int size)
{
	triangles.resetList(size);
	normals.resetList(size);
}
void TriangleMeshHull::resetVerticies(int size)
{
	verticies.resetList(size);
}
Triangle* TriangleMeshHull::getTriangle(int index)
{
	return triangles.getItem(index);
}
Vertex* TriangleMeshHull::getVertex(int index)
{
	return verticies.getItem(index);
}
Vertex* TriangleMeshHull::getNormal(int index)
{
	return normals.getItem(index);
}

//----------------------------------------------
// Special Class Functions
//----------------------------------------------
bool TriangleMeshHull::getIntersection(PhysicsHull* otherHull, Vertex movementVector,Vertex* normal, GLfloat* length, Vertex* intersectionPt,Vertex originDisplacement, Vertex targetDisplacement)
{
	if((*otherHull).getHullType() == TriangleMesh)
		return getTriangleIntersection((TriangleMeshHull*) otherHull,movementVector,normal,length,intersectionPt,originDisplacement,targetDisplacement);

	return false;
}
bool TriangleMeshHull::getTriangleIntersection(PhysicsHull* otherHull, Vertex movementVector,Vertex* normal, GLfloat* length, Vertex* intersectionPt,Vertex originDisplacement, Vertex targetDisplacement)
{
	bool intersects = false;
	*intersectionPt = 0.0f;
	*length = -1.0f;

	int noVerticies = verticies.getNoItems();
	for(ALL_VERTICIES_IN_THIS_HULL)
	{
		bool tempIntersect = false;
		Vertex tempNormal = Vertex();
		Vertex tempIntersection = Vertex(0.0f,0.0f,0.0f);
		GLfloat tempLength = -1.0f;

		for(ALL_TRIANGLES_IN_OTHER_HULL)
		{
			tempIntersect = CURRENT_TRIANGLE.getIntersection(&tempIntersection,&tempLength,movementVector,CURRENT_VERTEX + originDisplacement,TRIANGLE_POSITION + targetDisplacement);
		
			if(NEW_INTERSECTION_CLOSER_OR_IS_FIRST_ONE_FOUND)
			{
				intersects = true;
				*normal = *CURRENT_TRIANGLE.getNormalOne();
				*length = tempLength;
				*intersectionPt = tempIntersection;
			}
		}
	}
	return intersects;
}
void TriangleMeshHull::rotateX(GLfloat rad)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	generateRotateXMatrix(rad,rotMatrix);
	
	runRotation(rotMatrix,verticies.getNoItems(),verticies.getDataPtr());
	runRotation(rotMatrix,normals.getNoItems(),normals.getDataPtr());


	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void TriangleMeshHull::rotateY(GLfloat rad)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	generateRotateYMatrix(rad,rotMatrix);
	
	runRotation(rotMatrix,verticies.getNoItems(),verticies.getDataPtr());
	runRotation(rotMatrix,normals.getNoItems(),normals.getDataPtr());

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void TriangleMeshHull::rotateZ(GLfloat rad)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	generateRotateZMatrix(rad,rotMatrix);
	
	runRotation(rotMatrix,verticies.getNoItems(),verticies.getDataPtr());
	runRotation(rotMatrix,normals.getNoItems(),normals.getDataPtr());


	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void TriangleMeshHull::rotate(GLfloat rad, Vertex axis)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	generateRotateMatrix(rad,axis,rotMatrix);
	
	runRotation(rotMatrix,verticies.getNoItems(),verticies.getDataPtr());
	runRotation(rotMatrix,normals.getNoItems(),normals.getDataPtr());


	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void TriangleMeshHull::drawPhysHull()
{
	#define ALL_TRIANGLES int i = 0; i < noTriangles; i++
	int noTriangles = triangles.getNoItems();

	for(ALL_TRIANGLES)
	{


	}
}
//----------------------------------------------
// Operators
//----------------------------------------------
TriangleMeshHull& TriangleMeshHull::operator=(TriangleMeshHull& rhs)
{
	if(this == &rhs)
		return (*this);

	(*this).maxRadius = rhs.maxRadius;
	(*this).hullType = TriangleMesh;
	(*this).position = rhs.position;
	(*this).triangles = rhs.triangles;
	(*this).verticies = rhs.verticies;
	(*this).normals = rhs.normals;

	int noTriangles = rhs.triangles.getNoItems();
	for(ALL_TRIANGLES_TO_COPY)
	{
		int oneIndex = 0; int twoIndex = 0; int threeIndex = 0;
		bool one = true;
		bool two = true; 
		bool three = true;
		while(VERTEX_INDICIES_NOT_FOUND)
		{
			if(rhs.triangles[i].getVertexOne() == &rhs.verticies[oneIndex])
				one = false;
			else
				oneIndex++;

			if(rhs.triangles[i].getVertexTwo() == &rhs.verticies[twoIndex])
				two = false;
			else
				twoIndex++;

			if(rhs.triangles[i].getVertexThree() == &rhs.verticies[threeIndex])
				three = false;
			else
				threeIndex++;
		}

		(*this).triangles.addItem(Triangle(VERT_ONE,VERT_TWO,VERT_THREE,NORMAL_I));
	}

	return *this;
}