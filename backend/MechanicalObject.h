#include "GameObject.h"
#include <string>

class MechanicalObject EXTENDS GameObject
{
	protected:
		std::string name;
		List<Vertex> mountingPoints;
		List<Vertex> mountingNormals;
		List<Vertex*> correctMounts;

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
		Vertex getMountingPointNormal(int index);
		Vertex* getCorrectMount(int index);
		std::string getName(){return name;};

		//-------------------------------------
		// Set Functions
		//-------------------------------------
		bool setCorrectMount(int index, Vertex* correct);
		bool setPoint(int index, Vertex point);
		bool setNormal(int index, Vertex normal);
		void setName(std::string name){(*this).name = name;};
	
		//-------------------------------------
		// Class Specific Functions
		//-------------------------------------
		bool isCorrectMount(int index, Vertex* target);
		void addMountingPoint(Vertex point, Vertex normal, Vertex* correct);

		//-------------------------------------
		// Operators
		//-------------------------------------
		MechanicalObject& operator=(const MechanicalObject& rhs);
};