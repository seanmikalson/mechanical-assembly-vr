#include "MechanicalObject.h"

//-------------------------------------
// Constructors 
//-------------------------------------
MechanicalObject::MechanicalObject() : GameObject()
{
	mountingPoints = List<Vertex>();
	mountingNormals = List<Vertex>();
	correctMounts = List<Vertex*>();
	name = "";
}
MechanicalObject::MechanicalObject(Vertex nPosition,int visSize,int forceSize,int noPoints) 
	: GameObject(nPosition.getX(),nPosition.getY(),nPosition.getZ(),visSize,forceSize)
{
	mountingPoints = List<Vertex>(noPoints);
	mountingNormals = List<Vertex>(noPoints);
	correctMounts = List<Vertex*>(noPoints);
	name = "";
}
MechanicalObject::MechanicalObject(const MechanicalObject& rhs) : GameObject(rhs)
{
	(*this).mountingPoints = rhs.mountingPoints;
	(*this).mountingNormals = rhs.mountingNormals;
	(*this).correctMounts = rhs.correctMounts;
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
	(*this).name = rhs.name;

	return *this;
}