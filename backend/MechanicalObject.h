#include "GameObject.h"
#include <string>

class MechanicalObject EXTENDS GameObject
{
	protected:
		std::string name;
		List<Vertex> mountingPoints, mountingNormals;
		List<Vertex*> correctMounts, currentMounts;

	public:
		//-------------------------------------
		// Constructors 
		//-------------------------------------
		MechanicalObject();
		MechanicalObject(Vertex nPosition,int visSize,int forceSize,int noPoints);
		MechanicalObject(const MechanicalObject& rhs);

		//-------------------------------------
		// Get Functions 
		//-------------------------------------
		Vertex getMountingPointWorldPosition(int index);
		Vertex getMountingPoint(int index);
		Vertex* getMountingPointPtr(int index);
		Vertex getMountingPointNormal(int index);
		Vertex* getCorrectMount(int index);
		Vertex* getCurrentMount(int index);
		std::string getName(){return name;};
		int getNoMountingPoints(){return mountingPoints.getNoItems();};

		//-------------------------------------
		// Set Functions
		//-------------------------------------
		bool setCorrectMount(int index, Vertex* correct);
		bool setCurrentMount(int index, Vertex* current);
		bool setPoint(int index, Vertex point);
		bool setNormal(int index, Vertex normal);
		void setName(std::string name){(*this).name = name;};
	
		//-------------------------------------
		// Class Specific Functions
		//-------------------------------------
		bool isCorrectMount(int index, Vertex* target);
		void addMountingPoint(Vertex point, Vertex normal, Vertex* correct);
		bool isConnectedCorrectly();
		bool connectTo(MechanicalObject* target, GLfloat threshold);
		bool isConnected();
		void disconect();

		//-------------------------------------
		// Operators
		//-------------------------------------
		MechanicalObject& operator=(const MechanicalObject& rhs);
};