#include "GameObject.h"
#define ALL_VISUAL_DATA_ENTRIES int i = 0; i < noVisData; i++

//------------------------------------------------
// Constructors
//------------------------------------------------
GameObject::GameObject()
{
	physicsData = PhysicsData();
	visualData = List<VisualData>();
	forces = List<Vertex>();
	grabbed=false;
	touched=false;
}
GameObject::GameObject(const GameObject& rhs)
{
	(*this).visualData = rhs.visualData;
	(*this).physicsData = rhs.physicsData;
	(*this).forces = rhs.forces;
	grabbed=false;
	touched=false;
}
GameObject::GameObject(GLfloat posX, GLfloat posY, GLfloat posZ,int visSize, int forceSize)
{
	visualData = List<VisualData>(visSize);
	forces = List<Vertex>(forceSize);
	physicsData = PhysicsData();
	physicsData.setPosition(posX,posY,posZ);
	grabbed=false;
	touched=false;
}

//------------------------------------------------
// Get Functions
//------------------------------------------------
VisualData* GameObject::getVisualData(int index)
{
	#define INDEX_OUT_OF_RANGE index >= visualData.getNoItems()

	if(INDEX_OUT_OF_RANGE)
		return nullptr;

	return visualData.getItem(index);
}

//------------------------------------------------
// Set / Add Functions
//------------------------------------------------
void GameObject::setPosition(GLfloat x, GLfloat y, GLfloat z)
{	
	int noVisData = visualData.getNoItems();
	for(ALL_VISUAL_DATA_ENTRIES)
	{
		Vertex temp = (*visualData.getItem(i)).getPosition() - physicsData.getPosition();
		(*visualData.getItem(i)).setPosition(x + temp.getX(),y + temp.getY(), z + temp.getZ());
	}
	physicsData.setPosition(x,y,z);
}
void GameObject::addVisualData(GLfloat posX,GLfloat posY,GLfloat posZ, int maxVerts, int maxNorms, int maxTriangles, int maxMat)
{
	visualData.addItem(VisualData(posX,posY,posZ,maxVerts,maxNorms,maxTriangles,maxMat));
}
void GameObject::resetVisualData(int size)
{
	visualData.resetList(size);
}
void GameObject::resetForces(int size)
{
	forces.resetList(size);
}

//------------------------------------------------
// Visual Functions
//------------------------------------------------
void GameObject::draw()
{
	#define OBJECT_POSITION physicsData.getPosition()
	for(int i = 0; i < visualData.getNoItems(); i++)
		(*visualData.getItem(i)).draw(OBJECT_POSITION.getX(),OBJECT_POSITION.getY(),OBJECT_POSITION.getZ());
}
void GameObject::drawPhysHull()
{

}
//------------------------------------------------
// Physics Management
//------------------------------------------------
void GameObject::updatePosition(GLfloat elapsedTime)
{
	physicsData.updatePosition(elapsedTime);
}
void GameObject::accelerate(GLfloat x,GLfloat y,GLfloat z)
{
	physicsData.accelerate(x,y,z);
}
void GameObject::addVelocity(GLfloat x,GLfloat y,GLfloat z)
{
	physicsData.addVelocity(x,y,z);
}
void GameObject::updateVelocity(GLfloat elapsedTime)
{
	physicsData.updateVelocity(elapsedTime);
}
void GameObject::rotateX(GLfloat rad)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	generateRotateXMatrix(rad,rotMatrix);
	physicsData.rotateX(rad);
	int noVisData = visualData.getNoItems();
	//all vis data should have same location at 0.0,0.0,0.0
	for(ALL_VISUAL_DATA_ENTRIES)
	{
		(*visualData.getItem(i)).rotateX(rad);
		Vertex temp = (*visualData.getItem(i)).getPosition();
		runRotation(rotMatrix,1,&temp);
		(*visualData.getItem(i)).setPosition(temp.getX(),temp.getY(),temp.getZ());
	}

	

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void GameObject::rotateY(GLfloat rad)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	generateRotateYMatrix(rad,rotMatrix);
	physicsData.rotateY(rad);
	int noVisData = visualData.getNoItems();
	//all vis data should have same location at 0.0,0.0,0.0
	for(ALL_VISUAL_DATA_ENTRIES)
	{
		(*visualData.getItem(i)).rotateY(rad);
		Vertex temp = (*visualData.getItem(i)).getPosition();
		runRotation(rotMatrix,1,&temp);
		(*visualData.getItem(i)).setPosition(temp.getX(),temp.getY(),temp.getZ());
	}

	

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void GameObject::rotateZ(GLfloat rad)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	generateRotateZMatrix(rad,rotMatrix);
	physicsData.rotateZ(rad);
	int noVisData = visualData.getNoItems();
	//all vis data should have same location at 0.0,0.0,0.0
	for(ALL_VISUAL_DATA_ENTRIES)
	{
		(*visualData.getItem(i)).rotateZ(rad);
		Vertex temp = (*visualData.getItem(i)).getPosition();
		runRotation(rotMatrix,1,&temp);
		(*visualData.getItem(i)).setPosition(temp.getX(),temp.getY(),temp.getZ());
	}

	

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;

}
void GameObject::rotate(GLfloat rad, Vertex axis)
{
	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	physicsData.rotate(rad,axis);
	generateRotateMatrix(rad,axis,rotMatrix);
	int noVisData = visualData.getNoItems();
	//all vis data should have same location at 0.0,0.0,0.0
	for(ALL_VISUAL_DATA_ENTRIES)
	{
		(*visualData.getItem(i)).rotate(rad,axis);
		Vertex temp = (*visualData.getItem(i)).getPosition();
		runRotation(rotMatrix,1,&temp);
		(*visualData.getItem(i)).setPosition(temp.getX(),temp.getY(),temp.getZ());
	}

	

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void GameObject::adjustPosition(GLfloat addX, GLfloat addY, GLfloat addZ)
{
	physicsData.adjustPosition(addX,addY,addZ);
}

//------------------------------------------------
// Operators
//------------------------------------------------
GameObject& GameObject::operator=(const GameObject& rhs)
{
	if(this == &rhs)
		return *this;

	(*this).physicsData = rhs.physicsData;
	(*this).visualData = rhs.visualData;
	(*this).forces = rhs.forces;

	return *this;
}
