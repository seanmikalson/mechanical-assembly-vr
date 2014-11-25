#include "GameObject.h"
#include <string>

class MechanicalObject EXTENDS GameObject
{
	protected:
		std::string name;
		List<Vertex> mountingPoints, mountingNormals, mountingNormalPerps;
		List<Vertex*> correctMounts, currentMounts, currentMountsPerp, currentMountsNormal;

	public:
		static GameObject* mountingMarker;
		static Vertex markerNormal;
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
		Vertex* getMountingPointNormalPtr(int index);
		Vertex* getMountingPointNormalPerpPtr(int index);
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
		void drawMountingMarkers();

		void rotateX(GLfloat rad);
		void rotateY(GLfloat rad);
		void rotateZ(GLfloat rad);
		void rotate(GLfloat rad, Vertex axis);

		//-------------------------------------
		// Operators
		//-------------------------------------
		MechanicalObject& operator=(const MechanicalObject& rhs);
};