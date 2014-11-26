#include "Connections.h"

//------------------------------------------------------------
// Constructors
//------------------------------------------------------------
Connections::Connections(int noPoints)
{
	if(noPoints <= 0)
		noPoints = 10;

	mountingPoints = List<Vertex>(noPoints);
	mountingNormals = List<Vertex>(noPoints);
	mountingNormalPerps = List<Vertex>(noPoints);
	correctMounts = List<Vertex*>(noPoints);
	currentMounts = List<Vertex*>(noPoints);
	currentMountsPerp = List<Vertex*>(noPoints);
	currentMountsNormal = List<Vertex*>(noPoints);

	for(int i = 0; i < noPoints; i++)
	{
		currentMounts.addItem(nullptr);
		correctMounts.addItem(nullptr);
		currentMountsPerp.addItem(nullptr);
		currentMountsNormal.addItem(nullptr);
	}
}
Connections::Connections()
{
	int noPoints = 10;
	mountingPoints = List<Vertex>(noPoints);
	mountingNormals = List<Vertex>(noPoints);
	mountingNormalPerps = List<Vertex>(noPoints);
	correctMounts = List<Vertex*>(noPoints);
	currentMounts = List<Vertex*>(noPoints);
	currentMountsPerp = List<Vertex*>(noPoints);
	currentMountsNormal = List<Vertex*>(noPoints);

	for(int i = 0; i < 10; i++)
	{
		currentMounts.addItem(nullptr);
		correctMounts.addItem(nullptr);
		currentMountsPerp.addItem(nullptr);
		currentMountsNormal.addItem(nullptr);
	}
}

//------------------------------------------------------------
// Set Functions
//------------------------------------------------------------
bool Connections::setCorrectMount(Vertex *addition, int index)
{
	if(index >= correctMounts.getNoItems())
		return false;

	correctMounts[index] = addition;
	return true;
}
bool Connections::setCurrentMount(Vertex *addition, int index)
{
	if(index >= currentMounts.getNoItems())
		return false;

	currentMounts[index] = addition;
	return true;
}
bool Connections::setCurrentMountsPerp(Vertex *addition, int index)
{
	if(index >= currentMountsPerp.getNoItems())
		return false;

	currentMountsPerp[index] = addition;
	return true;
}
bool Connections::setCurrentMountsNormal(Vertex* addition, int index)
{
	if(index >= currentMountsNormal.getNoItems())
		return false;

	currentMountsNormal[index] = addition;
	return true;
}

//------------------------------------------------------------
// Operators
//------------------------------------------------------------
Connections& Connections::operator=(const Connections& rhs)
{
	if(this == &rhs)
		return *this;

	(*this).mountingPoints = rhs.mountingPoints;
	(*this).mountingNormals = rhs.mountingNormals;
	(*this).mountingNormalPerps = rhs.mountingNormalPerps;
	(*this).correctMounts = rhs.correctMounts;
	(*this).currentMounts = rhs.currentMounts;
	(*this).currentMountsPerp = rhs.currentMountsPerp;
	(*this).currentMountsNormal = rhs.currentMountsNormal;

	return *this;
}