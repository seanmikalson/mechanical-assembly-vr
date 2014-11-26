#include"BoundingVolume.h"
#define ALL_OBJECTS int i = 0; i < gameObjects.getNoItems(); i++
#define ALL_OBJECTS_TO_COPY int i = 0; i < rhsObjects.getNoItems(); i++
GameObject* MechanicalObject::mountingMarker;
Vertex MechanicalObject::markerNormal;

//---------------------------------------------------------------
//  Constructors and Destructors
//---------------------------------------------------------------
BoundingVolume::BoundingVolume()
{
	GLfloat specular[4] = {1.0f,1.0f,1.0f,0.1f};
	GLfloat nothing[4] = {0.0f,0.0f,0.0f,0.0f};
	GLfloat diffPurp[4] = {0.9f,0.0f,0.9f,1.0f};
	GLfloat ambwht[4] = {1.0f,1.0f,1.0f,0.5f};
	GLfloat grnamb[4] = {0.0f,1.0f,0.0f,1.0f};
	GLfloat grndiff[4] = {0.0f,0.5f,0.0f,1.0f};
	GLfloat tanamb[4] = {1.0f,1.0f,0.8f,1.0f};
	GLfloat greyamb[4] = {0.5f,0.5f,0.5f,1.0f};
	GLfloat blueamb[4] = {0.0f,0.0f,0.5f,1.0f};
	GLfloat redamb[4] = {0.5f,0.0f,0.0f,1.0f};

    Material* Green = new  Material(grnamb,grndiff,nothing,30.0f);
    Material* Purple = new Material(diffPurp,diffPurp,specular,30.0f);
    Material* Tan = new Material(tanamb,tanamb,nothing,0.0f);
    Material* Grey = new Material(greyamb,greyamb,ambwht,130.0f);
	Material* floor = new Material(greyamb,greyamb,greyamb,10.0f);
	Material* Red = new Material(redamb,redamb,nothing,.0f);
	Material* Blue = new Material(blueamb,blueamb,nothing,0.0f);
	Material* roof = new Material(ambwht,ambwht,nothing,0.0f);


	gameObjects.addItem( new EngineBlock(2.0f,0.0f,0.0f,-10.0f,Grey));
	gameObjects.addItem(new EngineHead(2.0f,5.0f,0.0f,-10.0f,Grey));

	(*(EngineHead*)gameObjects[1]).setupCorrectMountingPoints((EngineBlock*)gameObjects[0],0);
	MechanicalObject tempm;
	tempm.mountingMarker = new Marker(16,new Vertex(0.3f,0.3f,0.3f),0.0f,0.0f,0.0f,Purple);
	tempm.markerNormal = Vertex(0.0f,1.0f,0.0f);
	
	
	//setup room
	List<Material> temp = List<Material>();
	temp.addItem(*floor);
	temp.addItem(*Tan);
	temp.addItem(*Tan);
	gameObjects.addItem(new WorkShop(30.0f,0.0f,0.0f,0.0f,temp));

	//setup table
	//Vertex cubeScale = Vertex(20.0f,4.0f,20.0f);
	//gameObjects.addItem(Cube(&cubeScale,0.0f,0.0f,10.0f,Purple));
	
}
BoundingVolume::~BoundingVolume()
{
	//for(ALL_OBJECTS)
	//	delete gameObjects[i];
}
BoundingVolume::BoundingVolume(const BoundingVolume& rhs)
{
	List<GameObject*> rhsObjects = rhs.gameObjects;
	(*this).gameObjects = List<GameObject*>(rhsObjects.getMaxItems());

	for(ALL_OBJECTS_TO_COPY)
	{
		if((*rhsObjects[i]).getType() == NoObjectType)
		{
			GameObject* temp = new GameObject();
			*temp = *rhsObjects[i];
			(*this).gameObjects.addItem(temp);
		}
		else if((*rhsObjects[i]).getType() == Mechanical)
		{
			MechanicalObject* temp = new MechanicalObject();
			*temp = *(MechanicalObject*) rhsObjects[i];
			(*this).gameObjects.addItem(temp);
		}

	}
}

//---------------------------------------------------------------
//  Class Specific Functions
//---------------------------------------------------------------
void BoundingVolume::draw()
{
	for(ALL_OBJECTS)
		(*gameObjects[i]).draw();

	for(ALL_OBJECTS)
	{
		if((*gameObjects[i]).getType() == Mechanical)
			(* (MechanicalObject*) gameObjects[i]).drawMountingMarkers();
	}
}
void BoundingVolume::adjustPositions(GLfloat x, GLfloat y, GLfloat z)
{
	for(ALL_OBJECTS)
		(**gameObjects.getItem(i)).adjustPosition(x,y,z);
}
GameObject* BoundingVolume::getGameObject(int index)
{
	return *gameObjects.getItem(index);
}
int BoundingVolume::getNoItems()
{
	return gameObjects.getNoItems();
}
GameObject* BoundingVolume::getGameObjectFromId(unsigned int id)
{
	for(int i = 0; i < gameObjects.getNoItems(); i++)
	{
		if((**gameObjects.getItem(i)).getShapeId() == id)
		{
			return *gameObjects.getItem(i);
		}
	}
	return NULL;
}

//---------------------------------------------------------------
//  Operators
//---------------------------------------------------------------
BoundingVolume& BoundingVolume::operator=(const BoundingVolume& rhs)
{
	if(this == &rhs)
		return *this;

	List<GameObject*> rhsObjects = rhs.gameObjects;
	(*this).gameObjects = List<GameObject*>(rhsObjects.getMaxItems());

	for(ALL_OBJECTS_TO_COPY)
	{
		if((*rhsObjects[i]).getType() == NoObjectType)
		{
			GameObject* temp = new GameObject();
			*temp = *rhsObjects[i];
			(*this).gameObjects.addItem(temp);
		}
		else if((*rhsObjects[i]).getType() == Mechanical)
		{
			MechanicalObject* temp = new MechanicalObject();
			*temp = *(MechanicalObject*) rhsObjects[i];
			(*this).gameObjects.addItem(temp);
		}
	}

	return *this;
}