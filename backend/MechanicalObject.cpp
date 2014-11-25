#include "MechanicalObject.h"
#define ALL_VISUAL_DATA_ENTRIES int i = 0; i < noVisData; i++

//-------------------------------------
// Constructors 
//-------------------------------------
MechanicalObject::MechanicalObject() : GameObject()
{
	mountingPoints = List<Vertex>();
	mountingNormals = List<Vertex>();
	mountingNormalPerps = List<Vertex>();
	correctMounts = List<Vertex*>();
	currentMounts = List<Vertex*>();
	currentMountsPerp = List<Vertex*>();
	currentMountsNormal = List<Vertex*>();
	for(int i = 0; i < 10; i++)
	{
		currentMounts.addItem(nullptr);
		currentMountsPerp.addItem(nullptr);
		currentMountsNormal.addItem(nullptr);
	}

	name = "";
	gameObjectType = Mechanical;
}
MechanicalObject::MechanicalObject(Vertex nPosition,int visSize,int forceSize,int noPoints) 
	: GameObject(nPosition.getX(),nPosition.getY(),nPosition.getZ(),visSize,forceSize)
{
	mountingPoints = List<Vertex>(noPoints);
	mountingNormals = List<Vertex>(noPoints);
	mountingNormalPerps = List<Vertex>(noPoints);
	correctMounts = List<Vertex*>(noPoints);
	currentMounts = List<Vertex*>(noPoints);
	currentMountsNormal = List<Vertex*>(noPoints);
	currentMountsPerp = List<Vertex*>(noPoints);
	for(int i = 0; i < noPoints; i++)
	{
		currentMounts.addItem(nullptr);
		currentMountsNormal.addItem(nullptr);
		currentMountsPerp.addItem(nullptr);
	}
	name = "";
	gameObjectType = Mechanical;
}
MechanicalObject::MechanicalObject(const MechanicalObject& rhs)
{
	(*this).physicsData = rhs.physicsData;
	(*this).visualData = rhs.visualData;
	(*this).forces = rhs.forces;

	(*this).mountingPoints = rhs.mountingPoints;
	(*this).mountingNormals = rhs.mountingNormals;
	(*this).mountingNormalPerps = rhs.mountingNormalPerps;
	(*this).correctMounts = rhs.correctMounts;
	(*this).currentMounts = rhs.currentMounts;
	(*this).currentMountsNormal = rhs.currentMountsNormal;
	(*this).currentMountsPerp = rhs.currentMountsPerp;
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
Vertex* MechanicalObject::getMountingPointNormalPtr(int index)
{
	if(index < mountingNormals.getNoItems() && index >= 0)
		return &mountingNormals[index];

	return nullptr;
}
Vertex* MechanicalObject::getMountingPointNormalPerpPtr(int index)
{
	if(index < mountingNormalPerps.getNoItems() && index >= 0)
		return &mountingNormalPerps[index];

	return nullptr;
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
		mountingNormalPerps[index] = normal.getPerpendicular();
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
	mountingNormalPerps.addItem(normal.getPerpendicular());
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
	#define ALL_MOUNTING_POINTS_IN_TARGET int b = 0; b < tgt.getNoMountingPoints(); b++
	#define CLOSE_ENOUGH_TO_VACANT_TARGET_POINT distances[minIndex] <= threshold && tgt.getCurrentMount(minIndex) == nullptr

	int noItems = mountingPoints.getNoItems();
	bool connected = false;
	
	for( int i = 0; i < noItems ; i++ )
	{
		List<GLfloat> distances = List<GLfloat>(noItems);

		//Find closest mounting point on target object
		for( int b = 0; b < (*target).getNoMountingPoints(); b++ )
		{
			
			GLfloat distance = ((mountingPoints[i] + getPosition())
				- ((*target).getMountingPoint(b) + (*target).getPosition() )).length();

			if(distance < 0)
				distance *= -1.0f;

			distances.addItem(distance);
		}

		for(int i = 0; i < distances.getNoItems(); i++)
		{
			printf("distance %d: %f\n", i, distances[i]);
		}

		int minIndex = distances.minIndex();
		if(minIndex < 0) break;

		if( distances[minIndex] <= threshold && (*target).getCurrentMount(minIndex) == nullptr )
		{
			//Setup Connection on this object and target Object
			currentMounts[i] = (*target).getMountingPointPtr(minIndex);
			currentMountsNormal[i] = (*target).getMountingPointNormalPtr(minIndex);
			currentMountsPerp[i] = (*target).getMountingPointNormalPerpPtr(minIndex);
			(*target).setCurrentMount(minIndex,&mountingPoints[i]);
			connected = true;
			printf("min distance: %f\n", distances[minIndex]);
		}

	}

	if(connected)
	{
		float angle;
		Vertex axis;

		Vertex* objectNormal = mountingNormals.getItem(0);
		Vertex* targetNormal = currentMountsNormal[0];
		Vertex targetNormalReversed = Vertex((*targetNormal).getX()*-1.0f, (*targetNormal).getY()*-1.0f, (*targetNormal).getZ()*-1.0f);
		printf("object: %f,%f,%f\n", (*objectNormal).getX(), (*objectNormal).getY(), (*objectNormal).getZ());
		
		float cosine = (*objectNormal).dotProduct(targetNormalReversed);
		printf("cosine: %f\n", cosine);
		angle = acosf(cosine);
		printf("angle: %f\n", angle);

		axis = (*objectNormal).crossProduct(targetNormalReversed);
		rotate(angle, axis);
		printf("axis: %f,%f,%f\n", axis.getX(), axis.getY(), axis.getZ());
		
		Vertex* objectNormalPerp = mountingNormalPerps.getItem(0);
		Vertex* targetNormalPerp = currentMountsPerp[0];
		Vertex targetPerpReversed = Vertex((*targetNormalPerp).getX(), (*targetNormalPerp).getY(), (*targetNormalPerp).getZ());
		printf("objectp: %f,%f,%f\n", (*objectNormalPerp).getX(), (*objectNormalPerp).getY(), (*objectNormalPerp).getZ());
		printf("targetp: %f,%f,%f\n", targetPerpReversed.getX(), targetPerpReversed.getY(), targetPerpReversed.getZ());

		float angle2;
		float cosine2 = (*objectNormalPerp).dotProduct(targetPerpReversed);
		if((cosine2 <= 0.9 || cosine2 >= 1.1) && (cosine2 <= -0.9 || cosine2 >= -1.1))
		{
			printf("cosine2: %f\n", cosine2);
			angle2 = acosf(cosine2);
			printf("angle2: %f\n", angle2);

			Vertex axis2 = (*objectNormalPerp).crossProduct((*targetNormalPerp));
			printf("axis2: %f,%f,%f\n", axis2.getX(), axis2.getY(), axis2.getZ());
			rotate(angle2, axis2);
		}

	}

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
	runRotation(rotMatrix,mountingNormalPerps.getNoItems(),mountingNormalPerps.getDataPtr());

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
	runRotation(rotMatrix,mountingNormalPerps.getNoItems(),mountingNormalPerps.getDataPtr());

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
	runRotation(rotMatrix,mountingNormalPerps.getNoItems(),mountingNormalPerps.getDataPtr());

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
	runRotation(rotMatrix,mountingNormalPerps.getNoItems(),mountingNormalPerps.getDataPtr());

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
	(*this).mountingNormalPerps = rhs.mountingNormalPerps;
	(*this).correctMounts = rhs.correctMounts;
	(*this).currentMounts = rhs.currentMounts;
	(*this).currentMountsNormal = rhs.currentMountsNormal;
	(*this).currentMountsPerp = rhs.currentMountsPerp;
	(*this).name = rhs.name;



	return *this;
}