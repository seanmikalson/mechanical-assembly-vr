#include "VisualData.h"

#define VERTEX_INDICIES_IN_RANGE indOne < verticies.getNoItems() && indTwo < verticies.getNoItems() && indThree < verticies.getNoItems()
#define NORMAL_INDICIES_IN_RANGE indNorOne < normals.getNoItems() && indNorTwo < normals.getNoItems() && indNorThree < normals.getNoItems()

#define ALL_TRIANGLES_TO_COPY int i = 0; i < noVisTriangles; i++
#define VERTEX_INDICIES_NOT_FOUND oneVert || twoVert || threeVert || oneNorm || twoNorm || threeNorm || oneMat || twoMat || threeMat
#define VERT_ONE (*this).verticies.getItem(oneVertIndex)
#define VERT_TWO (*this).verticies.getItem(twoVertIndex)
#define VERT_THREE (*this).verticies.getItem(threeVertIndex)
#define NORM_ONE (*this).normals.getItem(oneNormIndex)
#define NORM_TWO (*this).normals.getItem(twoNormIndex)
#define NORM_THREE (*this).normals.getItem(threeNormIndex)
#define MAT_ONE (*this).materials.getItem(oneMatIndex)
#define MAT_TWO (*this).materials.getItem(twoMatIndex)
#define MAT_THREE (*this).materials.getItem(threeMatIndex)

//------------------------------------------------
// Constructors and Destructors
//------------------------------------------------
VisualData::VisualData()
{
	visMesh = List<GraphicsTriangle>();
	verticies = List<Vertex>();
	normals = List<Vertex>();
	materials = List<Material>();
	position = 0.0f;
}
VisualData::VisualData(GLfloat posX,GLfloat posY,GLfloat posZ, int maxVerts, int maxNorms, int maxTriangles, int maxMat)
{
	position = Vertex(posX,posY,posZ);
	visMesh = List<GraphicsTriangle>(maxTriangles);
	verticies = List<Vertex>(maxVerts);
	normals = List<Vertex>(maxNorms);
	materials = List<Material>(maxMat);
}
VisualData::~VisualData()
{

}
VisualData::VisualData(VisualData& rhs)
{
	(*this).position = rhs.position;
	(*this).visMesh = rhs.visMesh;
	(*this).verticies = rhs.verticies;
	(*this).normals = rhs.normals;
	(*this).materials = rhs.materials;
	int noVisTriangles = visMesh.getNoItems();

	for(ALL_TRIANGLES_TO_COPY)
	{
		int oneVertIndex = 0; int twoVertIndex = 0; int threeVertIndex = 0;
		int oneNormIndex = 0; int twoNormIndex = 0; int threeNormIndex = 0;
		int oneMatIndex = 0; int twoMatIndex = 0; int threeMatIndex = 0;

		bool oneVert = true;bool twoVert = true; bool threeVert = true;
		bool oneNorm = true;bool twoNorm = true; bool threeNorm = true;
		bool oneMat = true;bool twoMat = true; bool threeMat = true;
		
		
		while(VERTEX_INDICIES_NOT_FOUND)
		{
			if(rhs.visMesh[i].getVertexOne() == &rhs.verticies[oneVertIndex])
				oneVert = false;
			else
				oneVertIndex++;

			if(rhs.visMesh[i].getVertexTwo() == &rhs.verticies[twoVertIndex])
				twoVert = false;
			else
				twoVertIndex++;

			if(rhs.visMesh[i].getVertexThree() == &rhs.verticies[threeVertIndex])
				threeVert = false;
			else
				threeVertIndex++;

			if(rhs.visMesh[i].getNormalOne() == &rhs.normals[oneNormIndex])
				oneNorm = false;
			else
				oneNormIndex++;

			if(rhs.visMesh[i].getNormalTwo() == &rhs.normals[twoNormIndex])
				twoNorm = false;
			else
				twoNormIndex++;

			if(rhs.visMesh[i].getNormalThree() == &rhs.normals[threeNormIndex])
				threeNorm = false;
			else
				threeNormIndex++;

			if(rhs.visMesh[i].getMaterialOne() == &rhs.materials[oneMatIndex])
				oneMat = false;
			else
				oneMatIndex++;

			if(rhs.visMesh[i].getMaterialTwo() == &rhs.materials[twoMatIndex])
				twoMat = false;
			else
				twoMatIndex++;

			if(rhs.visMesh[i].getMaterialThree() == &rhs.materials[threeMatIndex])
				threeMat = false;
			else
				threeMatIndex++;
		}

		(*this).visMesh.setItem( GraphicsTriangle(VERT_ONE,VERT_TWO,VERT_THREE,NORM_ONE,NORM_TWO,NORM_THREE),i);
		(*(*this).visMesh.getItem(i)).setMaterialOne(MAT_ONE);
		(*(*this).visMesh.getItem(i)).setMaterialTwo(MAT_TWO);
		(*(*this).visMesh.getItem(i)).setMaterialThree(MAT_THREE);
	}
}

//------------------------------------------------
// Get Functions
//------------------------------------------------
Vertex* VisualData::getVertex(int index)
{
	if(index >= verticies.getNoItems() || index < 0)
		return nullptr;

	return verticies.getItem(index);
}
Vertex* VisualData::getNormal(int index)
{
	if(index >= normals.getNoItems() || index < 0)
		return nullptr;

	return normals.getItem(index);
}
GraphicsTriangle* VisualData::getVisualTriangle(int index)
{
	return visMesh.getItem(index);
}
Material* VisualData::getMaterial(int index)
{
	if(index >= materials.getNoItems() || index < 0)
		return nullptr;

	return materials.getItem(index);
}

//------------------------------------------------
// Set Functions
//------------------------------------------------
void VisualData::setPosition(GLfloat inX, GLfloat inY, GLfloat inZ)
{
	position = Vertex(inX,inY,inZ);
}
bool VisualData::setMaterialsForTriangle(int triIndex, int matOneIndex, int matTwoIndex, int matThreeIndex)
{
	#define INDICIES_OUT_OF_RANGE triIndex >= visMesh.getNoItems() || matOneIndex >= materials.getNoItems() || matTwoIndex >= materials.getNoItems() || matThreeIndex >= materials.getNoItems()
	
	if(INDICIES_OUT_OF_RANGE)
		return false;

	(*visMesh.getItem(triIndex)).setMaterialOne(materials.getItem(matOneIndex));
	(*visMesh.getItem(triIndex)).setMaterialTwo(materials.getItem(matTwoIndex));
	(*visMesh.getItem(triIndex)).setMaterialThree(materials.getItem(matThreeIndex));
	return true;
}

//------------------------------------------------
// Other Class Functions
//------------------------------------------------
void VisualData::adjustPosition(GLfloat addx,GLfloat addy,GLfloat addz)
{
	position.setX(position.getX() + addx);
	position.setY(position.getY() + addy);
	position.setZ(position.getZ() + addz);
}
bool VisualData::addVisualTriangle(int indOne,int indTwo ,int indThree, int indNorOne, int indNorTwo, int indNorThree)
{
	if(VERTEX_INDICIES_IN_RANGE && NORMAL_INDICIES_IN_RANGE)
	{
		visMesh.addItem(GraphicsTriangle(verticies.getItem(indOne),verticies.getItem(indTwo),
										 verticies.getItem(indThree),normals.getItem(indNorOne),
										 normals.getItem(indNorTwo),normals.getItem(indNorThree)));
		return true;
	}
	return false;
}
void VisualData::addVertex(GLfloat x, GLfloat y, GLfloat z)
{
	verticies.addItem(Vertex(x,y,z));
}
void VisualData::addVertex(Vertex addition)
{
	verticies.addItem(Vertex(addition.getX(),addition.getY(),addition.getZ()));
}
void VisualData::addNormal(GLfloat x, GLfloat y, GLfloat z)
{
		Vertex temp = Vertex(x,y,z);
		temp.normalize();
		normals.addItem(temp);
}
void VisualData::addMaterial(Material addition)
{
	materials.addItem(addition);
}
void VisualData::resetVerticies(int size)
{
	verticies.resetList(size);
	visMesh.resetList(visMesh.getMaxItems());
}
void VisualData::resetVisualMesh(int size)
{
	visMesh.resetList(size);
}
void VisualData::resetNormals(int size)
{
	normals.resetList(size);
	resetVisualMesh(visMesh.getMaxItems());
}
void VisualData::resetMaterials(int size)
{
	materials.resetList(size);
	resetVisualMesh(visMesh.getMaxItems());
}
void VisualData::draw(GLfloat dispX,GLfloat dispY,GLfloat dispZ)
{
	int noVisTriangles = visMesh.getNoItems();
	for(int i = 0; i < noVisTriangles; i++)
		(*visMesh.getItem(i)).draw(position.getX() + dispX,position.getY() + dispY,position.getZ() + dispZ);
}
void VisualData::rotateX(GLfloat rad)
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
void VisualData::rotateY(GLfloat rad)
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
void VisualData::rotateZ(GLfloat rad)
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
void VisualData::rotate(GLfloat rad, Vertex axis)
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
void VisualData::extrude(List<Vertex> path, int materialIndex)
{
	if(path.getNoItems() < 2)
		return;

	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	
	int noPath = path.getNoItems();
	int noVerticies = verticies.getNoItems();

	Vertex toNextNode;
	Vertex toThisNode;
	Vertex pivot;
	GLfloat angle;

	for(int i = 1; i < noPath - 1; i++)
	{
		toThisNode = *path.getItem(i-1) - *path.getItem(i);
		toNextNode = *path.getItem(i+1) - *path.getItem(i);
		toThisNode.normalize();
		toNextNode.normalize();
		pivot = toThisNode.crossProduct(toNextNode);
		pivot.normalize();
		angle = toThisNode.dotProduct(toNextNode) + 0.5f;
		angle *= 3.141592654f / 2.0f;
		generateRotateMatrix(angle,pivot,rotMatrix);

		for(int b = (i * noVerticies); b < (i + 1) * noVerticies; b++)
		{
			Vertex temp = *verticies.getItem(b - noVerticies) - *path.getItem(i-1);
			runRotation(rotMatrix,1,&temp);
			temp += *path.getItem(i);
			addVertex(temp);
		}
	}
	for(int i = 0; i < noPath - 1; i++)
	{
		for(int b = (i * noVerticies); b < (i + 1) * noVerticies - 1; b++)
		{
			addNormal(0.0f,1.0f,0.0f);
			int noNormals = normals.getNoItems();
			addVisualTriangle(b, b+1, b + noVerticies,noNormals - 1, noNormals - 1, noNormals - 1);
			setMaterialsForTriangle(visMesh.getNoItems() - 1,materialIndex,materialIndex, materialIndex);
			addVisualTriangle(b + 1, b + 1 + noVerticies, b + noVerticies, noNormals -1, noNormals -1, noNormals -1);
			setMaterialsForTriangle(visMesh.getNoItems() - 1, materialIndex,materialIndex,materialIndex);
			(*visMesh.getItem(visMesh.getNoItems() -1)).generateNormal();
		}
	}

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}

//------------------------------------------------
// Operators
//------------------------------------------------
VisualData& VisualData::operator=(VisualData& rhs)
{
	if(this == &rhs)
		return *this;

	(*this).position = rhs.position;
	(*this).visMesh = rhs.visMesh;
	(*this).verticies = rhs.verticies;
	(*this).normals = rhs.normals;
	(*this).materials = rhs.materials;
	int noVisTriangles = visMesh.getNoItems();

	for(ALL_TRIANGLES_TO_COPY)
	{
		int oneVertIndex = 0; int twoVertIndex = 0; int threeVertIndex = 0;
		int oneNormIndex = 0; int twoNormIndex = 0; int threeNormIndex = 0;
		int oneMatIndex = 0; int twoMatIndex = 0; int threeMatIndex = 0;

		bool oneVert = true;bool twoVert = true; bool threeVert = true;
		bool oneNorm = true;bool twoNorm = true; bool threeNorm = true;
		bool oneMat = true;bool twoMat = true; bool threeMat = true;
		
		
		while(VERTEX_INDICIES_NOT_FOUND)
		{
			if(rhs.visMesh[i].getVertexOne() == &rhs.verticies[oneVertIndex] )
				oneVert = false;
			else
				oneVertIndex++;

			if(rhs.visMesh[i].getVertexTwo() == &rhs.verticies[twoVertIndex])
				twoVert = false;
			else
				twoVertIndex++;

			if(rhs.visMesh[i].getVertexThree() == &rhs.verticies[threeVertIndex])
				threeVert = false;
			else
				threeVertIndex++;

			if(rhs.visMesh[i].getNormalOne() == &rhs.normals[oneNormIndex])
				oneNorm = false;
			else
				oneNormIndex++;

			if(rhs.visMesh[i].getNormalTwo() == &rhs.normals[twoNormIndex])
				twoNorm = false;
			else
				twoNormIndex++;

			if(rhs.visMesh[i].getNormalThree() == &rhs.normals[threeNormIndex])
				threeNorm = false;
			else
				threeNormIndex++;

			if(rhs.visMesh[i].getMaterialOne() == &rhs.materials[oneMatIndex])
				oneMat = false;
			else
				oneMatIndex++;

			if(rhs.visMesh[i].getMaterialTwo() == &rhs.materials[twoMatIndex])
				twoMat = false;
			else
				twoMatIndex++;

			if(rhs.visMesh[i].getMaterialThree() == &rhs.materials[threeMatIndex])
				threeMat = false;
			else
				threeMatIndex++;
		}

		(*this).visMesh.setItem( GraphicsTriangle(VERT_ONE,VERT_TWO,VERT_THREE,NORM_ONE,NORM_TWO,NORM_THREE),i);
		(*(*this).visMesh.getItem(i)).setMaterialOne(MAT_ONE);
		(*(*this).visMesh.getItem(i)).setMaterialTwo(MAT_TWO);
		(*(*this).visMesh.getItem(i)).setMaterialThree(MAT_THREE);
	}
	return *this;
}