#include "Connections.h"
#include <string>

class MechanicalObject EXTENDS GameObject
{
	protected:
		List<Connections> connections;
		std::string name;
		bool connectedCorrect;

	public:
		static GameObject* mountingMarker;
		static Vertex markerNormal;
		//-------------------------------------
		// Constructors 
		//-------------------------------------
		MechanicalObject();
		MechanicalObject(Vertex nPosition,int visSize,int forceSize,int noConnections);
		MechanicalObject(const MechanicalObject& rhs);

		//-------------------------------------
		// Get Functions 
		//-------------------------------------
		Vertex getMountingPointWorldPosition(int pointindex, int connectionIndex);
		Vertex getMountingPoint(int pointIndex, int connectionIndex);
		Vertex* getMountingPointPtr(int pointIndex, int connectionIndex);
		Vertex* getMountingPointNormalPtr(int pointIndex, int connectionIndex);
		Vertex* getMountingPointNormalPerpPtr(int pointIndex, int connectionIndex);
		Vertex* getCorrectMount(int pointIndex, int connectionIndex);
		Vertex* getCurrentMount(int pointIndex, int connectionIndex);
		std::string getName(){return name;};
		int getNoMountingPoints(int index){return (*(*connections.getItem(index)).getMountingPoints()).getNoItems();};
		int getNoConnections(){return connections.getNoItems();};

		//-------------------------------------
		// Set Functions
		//-------------------------------------
		bool setCorrectMount(int pointIndex, int connectionIndex, Vertex* correct);
		bool setCurrentMount(int pointIndex, int connectionIndex, Vertex* current);
		bool setPoint(int pointIndex, int connectionIndex, Vertex point);
		bool setNormal(int pointIndex, int connectionIndex, Vertex normal);
		void setName(std::string name){(*this).name = name;};
		void setConnectedCorrectly(bool connected){connectedCorrect =  true;};
	
		//-------------------------------------
		// Class Specific Functions
		//-------------------------------------
		bool isCorrectMount(int pointIndex, int connectionIndex, Vertex* target);
		void addMountingPoint(int connectionIndex, Vertex point, Vertex normal);
		bool isConnectedCorrectly();
		bool connectTo(MechanicalObject* target, GLfloat threshold);
		bool isConnected();
		bool isConnected(int connectionIndex);
		bool isCompletelyConnected();
		void disconect();
		void drawMountingMarkers();
		bool canConnectToConnection(MechanicalObject* target, int tgtConnection, int thisConnection);
		bool canConnectTo(MechanicalObject* target, int* tgtIndex, int* thisIndex);

		void rotateX(GLfloat rad);
		void rotateY(GLfloat rad);
		void rotateZ(GLfloat rad);
		void rotate(GLfloat rad, Vertex axis);

		//-------------------------------------
		// Operators
		//-------------------------------------
		MechanicalObject& operator=(const MechanicalObject& rhs);
};