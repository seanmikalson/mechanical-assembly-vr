#include "MechanicalObject.h"
#define ALL_VISUAL_DATA_ENTRIES int i = 0; i < noVisData; i++

//-------------------------------------
// Constructors 
//-------------------------------------
MechanicalObject::MechanicalObject() : GameObject()
{
	mountingPoints = List<Vertex>();
	mountingNormals = List<Vertex>();
	correctMounts = List<Vertex*>();
	currentMounts = List<Vertex*>();
	for(int i = 0; i < 10; i++)
		currentMounts.addItem(nullptr);

	name = "";
}
MechanicalObject::MechanicalObject(Vertex nPosition,int visSize,int forceSize,int noPoints) 
	: GameObject(nPosition.getX(),nPosition.getY(),nPosition.getZ(),visSize,forceSize)
{
	mountingPoints = List<Vertex>(noPoints);
	mountingNormals = List<Vertex>(noPoints);
	correctMounts = List<Vertex*>(noPoints);
	currentMounts = List<Vertex*>(noPoints);
		for(int i = 0; i < noPoints; i++)
		currentMounts.addItem(nullptr);
	name = "";
}
MechanicalObject::MechanicalObject(const MechanicalObject& rhs)
{
	(*this).physicsData = rhs.physicsData;
	(*this).visualData = rhs.visualData;
	(*this).forces = rhs.forces;

	(*this).mountingPoints = rhs.mountingPoints;
	(*this).mountingNormals = rhs.mountingNormals;
	(*this).correctMounts = rhs.correctMounts;
	(*this).currentMounts = rhs.currentMounts;
	(*this).name = rhs.name;
}

//-------------------------------------
// Get Functions
//-------------------------------------
Vertex MechanicalObject::getMountingPointWorldPosition(int index)
{
	if(index < mountingPoints.getNoItems() && index >= 0)
		return physicsData.getPosition() + mountingPoints[index];

	return Vertex();
}
Vertex MechanicalObject::getMountingPoint(int index)
{
	if(index < mountingPoints.getNoItems() && index >= 0)
		return mountingPoints[index];

		return Vertex();
}
Vertex MechanicalObject::getMountingPointNormal(int index)
{
	if(index < mountingPoints.getNoItems() && index >= 0)
		return mountingNormals[index];

	return Vertex();
}
Vertex* MechanicalObject::getCorrectMount(int index)
{
	if(index < mountingPoints.getNoItems() && index >= 0)
		return correctMounts[index];

	return nullptr;
}
Vertex* MechanicalObject::getCurrentMount(int index)
{
	if(index < currentMounts.getNoItems() && index >= 0)
		return currentMounts[index];

	return nullptr;
}
Vertex* MechanicalObject::getMountingPointPtr(int index)
{
	if(index < mountingPoints.getNoItems() && index >= 0)
		return &mountingPoints[index];

		return nullptr;
}

//-------------------------------------
// Set Functions
//-------------------------------------
bool MechanicalObject::setCorrectMount(int index, Vertex* correct)
{
	if(index < correctMounts.getNoItems() && index >= 0)
	{
		correctMounts[index] = correct;
		return true;
	}
	return false;
}
bool MechanicalObject::setPoint(int index, Vertex point)
{
	if(index < mountingPoints.getNoItems() && index >= 0)
	{
		mountingPoints[index] = point;
		return true;
	}
	return false;
}
bool MechanicalObject::setNormal(int index, Vertex normal)
{
	if(index < mountingNormals.getNoItems() && index >= 0)
	{
		mountingNormals[index] = normal;
		return true;
	}
	return false;
}
bool MechanicalObject::setCurrentMount(int index, Vertex* current)
{
	if(index < currentMounts.getNoItems() && index >= 0)
	{
		currentMounts[index] = current;
		return true;
	}
	return false;
}

//-------------------------------------
// Class Functions
//-------------------------------------
bool MechanicalObject::isCorrectMount(int index, Vertex* target)
{
	if(index < mountingPoints.getNoItems() && index >= 0)
	{
		if(target == correctMounts[index])
			return true;
	}
	return false;
}
void MechanicalObject::addMountingPoint(Vertex point, Vertex normal, Vertex* correct)
{
	mountingPoints.addItem(point);
	mountingNormals.addItem(normal);	
	correctMounts.addItem(correct);
}
bool MechanicalObject::isConnectedCorrectly()
{
	#define NUMBR_OF_CONNECTED_POINTS_INCORRECT currentMounts.getNoItems() != correctMounts.getNoItems()
	#define NO_CONNECTED_POINTS currentMounts.getNoItems() == 0

	if( NUMBR_OF_CONNECTED_POINTS_INCORRECT || NO_CONNECTED_POINTS )
		return false;
	
	for(int i = 0; i < currentMounts.getNoItems(); i++)
	{
		if(currentMounts[i] != nullptr && currentMounts[i] != correctMounts[i])
			return false;
	}
	
	return true;
}
bool MechanicalObject::connectTo(MechanicalObject* target, GLfloat threshold)
{	
	#define ALL_MOUNTING_POINTS_IN_THIS_OBJECT int i = 0; i < noItems ; i++
	#define ALL_MOUNTING_POINTS_IN_TARGET int b = 0; b < (*target).getNoMountingPoints(); b++
	#define CLOSE_ENOUGH_TO_VACANT_TARGET_POINT distances[minIndex] <= threshold && (*target).getCurrentMount(minIndex) == nullptr


	int noItems = mountingPoints.getNoItems();
	bool connected = false;
	
	for( ALL_MOUNTING_POINTS_IN_THIS_OBJECT )
	{
		List<GLfloat> distances = List<GLfloat>(noItems);

		//Find closest mounting point on target object
		for( ALL_MOUNTING_POINTS_IN_TARGET )
		{
			
			GLfloat distance = ((mountingPoints[i] + getPosition())
				- ((*target).getMountingPoint(b) + (*target).getPosition() )).length();

			if(distance < 0)
				distance *= -1.0f;

			distances.addItem(distance);
		}

		int minIndex = distances.minIndex();

		if( CLOSE_ENOUGH_TO_VACANT_TARGET_POINT )
		{
			//Setup Connection on this object and target Object
			currentMounts[i] = (*target).getMountingPointPtr(minIndex);
			(*target).setCurrentMount(minIndex,&mountingPoints[i]);
			connected = true;
		}

	}

	// TODO Orient Object
	
	// TODO Translate Object
	return connected;
}
bool MechanicalObject::isConnected()
{
	for(int i = 0; i < correctMounts.getNoItems(); i++)
	{
		if(correctMounts[i] != nullptr)
			return true;
	}

	return false;
}
void MechanicalObject::disconect()
{
	for(int i = 0; i < correctMounts.getNoItems(); i++)
		correctMounts[i] = nullptr;
}

void MechanicalObject::rotateX(GLfloat rad)
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

	runRotation(rotMatrix,mountingPoints.getNoItems(),mountingPoints.getDataPtr());
	runRotation(rotMatrix,mountingNormals.getNoItems(),mountingNormals.getDataPtr());

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void MechanicalObject::rotateY(GLfloat rad)
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

	runRotation(rotMatrix,mountingPoints.getNoItems(),mountingPoints.getDataPtr());
	runRotation(rotMatrix,mountingNormals.getNoItems(),mountingNormals.getDataPtr());

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
void MechanicalObject::rotateZ(GLfloat rad)
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

	runRotation(rotMatrix,mountingPoints.getNoItems(),mountingPoints.getDataPtr());
	runRotation(rotMatrix,mountingNormals.getNoItems(),mountingNormals.getDataPtr());

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;

}
void MechanicalObject::rotate(GLfloat rad, Vertex axis)
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

	runRotation(rotMatrix,mountingPoints.getNoItems(),mountingPoints.getDataPtr());
	runRotation(rotMatrix,mountingNormals.getNoItems(),mountingNormals.getDataPtr());

	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
//-------------------------------------
// Operators
//-------------------------------------
MechanicalObject& MechanicalObject::operator=(const MechanicalObject& rhs)
{
	if(this == &rhs)
		return *this;

	(*this).physicsData = rhs.physicsData;
	(*this).visualData = rhs.visualData;
	(*this).forces = rhs.forces;

	(*this).mountingPoints = rhs.mountingPoints;
	(*this).mountingNormals = rhs.mountingNormals;
	(*this).correctMounts = rhs.correctMounts;
	(*this).currentMounts = rhs.currentMounts;
	(*this).name = rhs.name;



	return *this;
}