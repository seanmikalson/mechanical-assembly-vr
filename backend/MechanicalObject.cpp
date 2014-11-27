#include "MechanicalObject.h"
#define ALL_VISUAL_DATA_ENTRIES int i = 0; i < noVisData; i++
#define CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE connectionIndex < 0 || connectionIndex >= connections.getNoItems() || pointIndex >= (*connections.getItem(connectionIndex)).getNoMountingPoints() || pointIndex < 0

//-------------------------------------
// Constructors 
//-------------------------------------
MechanicalObject::MechanicalObject() : GameObject()
{
	connections = List<Connections>();

	name = "";
	gameObjectType = Mechanical;
	connectedCorrect = false;
}
MechanicalObject::MechanicalObject(Vertex nPosition,int visSize,int forceSize,int noConnections) 
	: GameObject(nPosition.getX(),nPosition.getY(),nPosition.getZ(),visSize,forceSize)
{
	connections = List<Connections>(noConnections);
	name = "";
	gameObjectType = Mechanical;
	connectedCorrect = false;
}
MechanicalObject::MechanicalObject(const MechanicalObject& rhs)
{
	(*this).physicsData = rhs.physicsData;
	(*this).visualData = rhs.visualData;
	(*this).forces = rhs.forces;

	(*this).connections = rhs.connections;
	(*this).name = rhs.name;
	(*this).gameObjectType = rhs.gameObjectType;
	(*this).connectedCorrect = rhs.connectedCorrect;
}

//-------------------------------------
// Get Functions
//-------------------------------------
Vertex MechanicalObject::getMountingPointWorldPosition(int pointIndex, int connectionIndex)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return Vertex();

		return physicsData.getPosition() + (*connections.getItem(connectionIndex)).getMountingPoint(pointIndex);
}
Vertex MechanicalObject::getMountingPoint(int pointIndex, int connectionIndex)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return Vertex();

	return (*connections.getItem(connectionIndex)).getMountingPoint(pointIndex);
}
Vertex* MechanicalObject::getMountingPointNormalPtr(int pointIndex, int connectionIndex)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return nullptr;
	
	return (*connections.getItem(connectionIndex)).getMountingNormalPtr(pointIndex);
}
Vertex* MechanicalObject::getMountingPointNormalPerpPtr(int pointIndex, int connectionIndex)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return nullptr;
	
	return (*connections.getItem(connectionIndex)).getMountingNormalPerpPtr(pointIndex);
}
Vertex* MechanicalObject::getCorrectMount(int pointIndex, int connectionIndex)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return nullptr;
	
	return (*connections.getItem(connectionIndex)).getCorrectMount(pointIndex);
}
Vertex* MechanicalObject::getCurrentMount(int pointIndex, int connectionIndex)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return nullptr;
	
	return (*connections.getItem(connectionIndex)).getCurrentMount(pointIndex);
}
Vertex* MechanicalObject::getMountingPointPtr(int pointIndex, int connectionIndex)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return nullptr;
	
	return (*connections.getItem(connectionIndex)).getMountingPointPtr(pointIndex);
}

//-------------------------------------
// Set Functions
//-------------------------------------
bool MechanicalObject::setCorrectMount(int pointIndex, int connectionIndex, Vertex* correct)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return false;

	(*connections.getItem(connectionIndex)).setCorrectMount(correct,pointIndex);
	return true;
}
bool MechanicalObject::setPoint(int pointIndex, int connectionIndex, Vertex point)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return false;

	*(*connections.getItem(connectionIndex)).getMountingPointPtr(pointIndex) = point;
	return true;
}
bool MechanicalObject::setNormal(int pointIndex, int connectionIndex, Vertex normal)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return false;

	*(*connections.getItem(connectionIndex)).getMountingNormalPtr(pointIndex) = normal;
	return true;
}
bool MechanicalObject::setCurrentMount(int pointIndex, int connectionIndex, Vertex* current)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return false;

	(*connections.getItem(connectionIndex)).setCurrentMount(current,pointIndex);
	return true;
}

//-------------------------------------
// Class Functions
//-------------------------------------
bool MechanicalObject::isCorrectMount(int pointIndex, int connectionIndex, Vertex* target)
{
	if(CONNECTION_OR_POINT_INDICIES_OUT_OF_RANGE)
		return false;

	Vertex * current = (*connections.getItem(connectionIndex)).getCurrentMount(pointIndex);
	Vertex * correct = (*connections.getItem(connectionIndex)).getCorrectMount(pointIndex);
	
	return (current == correct);
}
void MechanicalObject::addMountingPoint(int connectionIndex, Vertex point, Vertex normal)
{
	(*connections.getItem(connectionIndex)).addMountingPoint(point);
	(*connections.getItem(connectionIndex)).addMountingNormal(normal);
	(*connections.getItem(connectionIndex)).addMountingNormalPerp(normal.getPerpendicular());
}
bool MechanicalObject::isConnectedCorrectly()
{
	return connectedCorrect;
}
bool MechanicalObject::canConnectToConnection(MechanicalObject* target, int tgtConnection, int thisConnection)
{
	#define TGT_INDEX_OUT_OF_RANGE tgtConnection >= (*target).getNoConnections() || tgtConnection < 0 
	#define THIS_INDEX_OUT_OF_RANGE thisConnection <0 || thisConnection >= getNoConnections()
	

	if(TGT_INDEX_OUT_OF_RANGE || THIS_INDEX_OUT_OF_RANGE )
		return false;

	for(int b = 0; b < getNoMountingPoints(thisConnection); b++)// FOR all correct mounts
	{
		for(int i = 0; i < (*target).getNoMountingPoints(tgtConnection); i++) // all mounting points int target connection
		{
			if(*getCorrectMount(b,thisConnection) + (*target).getPosition() == (*target).getMountingPointWorldPosition(i,tgtConnection))
				return true;
		}
	}
	return false;
}
bool MechanicalObject::canConnectTo(MechanicalObject* target, int* tgtIndex, int* thisIndex)
{
	for(int b = 0; b < getNoConnections(); b++)
	{
		for(int i = 0; i < (*target).getNoConnections(); i++)
		{
			if(canConnectToConnection(target,i,b))
			{
				*thisIndex = b;
				*tgtIndex = i;
				return true;
			}
		}
	}
	return false;
}
bool MechanicalObject::connectTo(MechanicalObject* target, GLfloat threshold)
{	
	#define ALL_MOUNTING_POINTS_I int i = 0; i < getNoMountingPoints(connectionIndex); i++

	int connectionIndex;
	int tgtConnectionIndex;
	bool canConnectToTarget = canConnectTo(target,&tgtConnectionIndex,&connectionIndex);

	connectedCorrect = false;
	if(!canConnectToTarget)
	{
		return false;
	}
	//Check if all points close enough to their target
	for(ALL_MOUNTING_POINTS_I)
	{
		Vertex currentPoint = getMountingPointWorldPosition(i,connectionIndex);
		Vertex correctPoint = (*getCorrectMount(i,connectionIndex) + (*target).getPosition());

		if((currentPoint - correctPoint).length() > threshold)
			return false;
	}
	
	Connections* currentConnection = connections.getItem(connectionIndex);

	//Set current mounts
	for(ALL_MOUNTING_POINTS_I)
	{
		(*currentConnection).setCurrentMount(getCorrectMount(i,connectionIndex),i);
		(*currentConnection).setCurrentMountsNormal((*target).getMountingPointNormalPtr(i,tgtConnectionIndex),i);
		(*currentConnection).setCurrentMountsPerp((*target).getMountingPointNormalPerpPtr(i,tgtConnectionIndex),i);
		(*target).setCurrentMount(i,tgtConnectionIndex,(*currentConnection).getMountingPointPtr(i));
	}

	connectedCorrect = true;
	(*target).setConnectedCorrectly(true);

	float angle;
	Vertex axis;

	// Rotate the object to attach it
	Vertex objectNormal = (*currentConnection).getMountingNormal(0);
	Vertex* targetNormal =  (*currentConnection).getCurrentMountsNormal(0);
	Vertex targetNormalReversed = Vertex((*targetNormal).getX()*-1.0f, (*targetNormal).getY()*-1.0f, (*targetNormal).getZ()*-1.0f);
		
	float cosine = objectNormal.dotProduct(targetNormalReversed);
	printf("cosine: %f\n", cosine);
	angle = acosf(cosine);
	axis = objectNormal.crossProduct(targetNormalReversed);
	printf("axis: %f,%f,%f\n", axis.getX(),axis.getY(),axis.getZ());
	if(axis.length() > 0.0005 && (angle > 0.01)) rotate(angle, axis);
		
	Vertex objectNormalPerp = (*currentConnection).getMountingNormalPerp(0);
	Vertex* targetNormalPerp = (*currentConnection).getCurrentMountsPerp(0); 
	Vertex targetPerpReversed = Vertex((*targetNormalPerp).getX()*-1.0f, (*targetNormalPerp).getY()*-1.0f, (*targetNormalPerp).getZ()*-1.0f);

	float angle2;
	float cosine2 = objectNormalPerp.dotProduct(targetPerpReversed);
	printf("cosine2: %f\n", cosine2);
	angle2 = acosf(cosine2);
	Vertex axis2 = objectNormalPerp.crossProduct(targetPerpReversed);
	printf("axis2: %f,%f,%f    %d\n", axis2.getX(),axis2.getY(),axis2.getZ(), axis2.length() > 0.0005);
	if(axis2.length() > 0.0005 && (angle2 > 0.01) ) rotate(angle2, axis2);

	//translate the object into position
	Vertex objectPosition = (*currentConnection).getMountingPoint(0) + getPosition();
	Vertex targetPosition = *(*currentConnection).getCorrectMount(0) + (*target).getPosition();
	adjustPosition(targetPosition.getX() - objectPosition.getX(), targetPosition.getY() - objectPosition.getY(), targetPosition.getZ() - objectPosition.getZ());

	return true;
}
void MechanicalObject::drawMountingMarkers()
{
	if(mountingMarker == nullptr || markerNormal == Vertex(0.0f,0.0f,0.0f))
		return;

	GLfloat** rotMatrix = new GLfloat*[3];
	for(int i = 0; i < 3 ; i++)
		rotMatrix[i] = new GLfloat[3];

	for(int b = 0; b < connections.getNoItems(); b++)
	{
		for(int i = 0; i < (*connections.getItem(b)).getNoMountingPoints() && !isConnected(b); i++)
		{
			Connections * currentConnection = connections.getItem(b);
			Vertex currentNormal = (*currentConnection).getMountingNormal(i);
			Vertex currentPoint =  (*currentConnection).getMountingPoint(i);

			GLfloat angle = acos(markerNormal.dotProduct(currentNormal));
			Vertex axis = markerNormal.crossProduct(currentNormal);
			Vertex translate = (*this).getPosition() + currentPoint;

			printf("angle: %f\n",angle);
			if(angle < 3.15 && angle > 3.14)
					axis = Vertex(1.0, 0, 0);

			if(axis.length() > 0.0005f && abs(angle) > 0.01)
			{
				generateRotateMatrix(angle ,axis,rotMatrix);

				runRotation(rotMatrix,1,&markerNormal);
				(*mountingMarker).rotate(angle ,axis);
			}
		
			(*mountingMarker).adjustPosition(translate.getX(),
										 translate.getY(),
										 translate.getZ());

			(*mountingMarker).draw();

			(*mountingMarker).adjustPosition(-translate.getX(),
										 -translate.getY(),
										 -translate.getZ());

			if(axis.length() > 0.0005f && abs(angle) > 0.01)
			{
				(*mountingMarker).rotate(-angle ,axis);

				generateRotateMatrix(-angle ,axis,rotMatrix);
				runRotation(rotMatrix,1,&markerNormal);
			}
		}
	}
	for(int i = 0; i < 3; i++)
		delete rotMatrix[i];

	delete []rotMatrix;
}
bool MechanicalObject::isConnected()
{
	#define ALL_CONNECTIONS_I int i = 0; i < getNoConnections(); i++

	for(ALL_CONNECTIONS_I)
	{
		if(isConnected(i))
			return true;
	}

	return false;
}
bool MechanicalObject::isCompletelyConnected()
{
	#define ALL_CONNECTIONS_I int i = 0; i < getNoConnections(); i++

	for(ALL_CONNECTIONS_I)
	{
		if(!isConnected(i))
			return false;
	}

	return true;
}
bool MechanicalObject::isConnected(int connectionIndex)
{
	#define ALL_CORRECT_MOUNTS_I int i = 0; i < (*connections.getItem(connectionIndex)).getNoMountingPoints(); i++

	if(connectionIndex >= connections.getNoItems() || connectionIndex < 0)
		return false;

	Connections* currentConnection = connections.getItem(connectionIndex);
	for(ALL_CORRECT_MOUNTS_I)
	{
		if((*currentConnection).getCurrentMount(i) == nullptr)
			return false;
	}
	return true;
}
void MechanicalObject::disconect()
{
	#define ALL_CONNECTIONS_I int i = 0; i < getNoConnections(); i++
	#define ALL_CORRECT_MOUNTS_B int b = 0; b < (*connections.getItem(i)).getNoMountingPoints(); b++
	
	connectedCorrect = false;
	for(ALL_CONNECTIONS_I)
	{
		Connections* currentConnection = connections.getItem(i);

		for(ALL_CORRECT_MOUNTS_B)
			(*currentConnection).setCurrentMount(nullptr,b);
	}
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

	for(int i = 0; i < connections.getNoItems(); i++)
	{
		Connections* currentConnection = connections.getItem(i);
		int noPoints = (*currentConnection).getNoMountingPoints();

		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingPointPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPerpPtr(0));
	}

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

	for(int i = 0; i < connections.getNoItems(); i++)
	{
		Connections* currentConnection = connections.getItem(i);
		int noPoints = (*currentConnection).getNoMountingPoints();

		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingPointPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPerpPtr(0));
	}

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

	for(int i = 0; i < connections.getNoItems(); i++)
	{
		Connections* currentConnection = connections.getItem(i);
		int noPoints = (*currentConnection).getNoMountingPoints();

		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingPointPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPerpPtr(0));
	}

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

	for(int i = 0; i < connections.getNoItems(); i++)
	{
		Connections* currentConnection = connections.getItem(i);
		int noPoints = (*currentConnection).getNoMountingPoints();

		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingPointPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPtr(0));
		runRotation(rotMatrix,noPoints,(*currentConnection).getMountingNormalPerpPtr(0));
	}

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

	(*this).connections = rhs.connections;
	(*this).name = rhs.name;
	(*this).gameObjectType = rhs.gameObjectType;
	(*this).connectedCorrect = rhs.connectedCorrect;

	return *this;
}