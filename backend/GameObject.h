#include <glew.h>
#include "PhysicsData.h"

class GameObject
{
	protected:
		List<VisualData> visualData;
		List<Vertex> forces;
		PhysicsData physicsData;
		bool touched;
		bool grabbed;
		unsigned int shapeId;

	public: 
		GameObject();
		GameObject(GLfloat posx,GLfloat posy,GLfloat posz,int visSize,int forceSize);
		GameObject(const GameObject& rhs);

		//-----------------------------------------
		// Set Functions
		//-----------------------------------------
		void setPosition(GLfloat x, GLfloat y, GLfloat z);
		void setTouched(bool touch) {touched = touch;};
		void setGrabbed(bool grabbedv){grabbed = grabbedv;};
		void setShapeId(unsigned int id){shapeId = id;};
		

		//-----------------------------------------
		// Get Functions
		//-----------------------------------------
		VisualData* getVisualData(int index);
		PhysicsData* getPhysicsData(){return &physicsData;};
		Vertex getPosition(){return physicsData.getPosition();};
		int getMaxVisData(){return visualData.getMaxItems();};
		int getNoVisData(){return visualData.getNoItems();};
		bool isTouched(){return touched;};
		bool isGrabbed(){return grabbed;};
		unsigned int getShapeId(){return shapeId;};

		
		//-----------------------------------------
		// Class Functions
		//-----------------------------------------
		virtual void draw();
		virtual void drawPhysHull();
		void adjustPosition(GLfloat addX, GLfloat addY, GLfloat addZ);
		void addVisualData(GLfloat posX,GLfloat posY,GLfloat posZ, int maxVerts, int maxNorms, int maxTriangles, int maxMat);
		void resetVisualData(int size);
		void resetForces(int size);
		void accelerate(GLfloat x,GLfloat y,GLfloat z);
		void addVelocity(GLfloat x,GLfloat y,GLfloat z);
		void updateVelocity(GLfloat elapsedTime);
		void updatePosition(GLfloat elapsedTime);
		virtual void rotateX(GLfloat rad);
		virtual void rotateY(GLfloat rad);
		virtual void rotateZ(GLfloat rad);
		virtual void rotate(GLfloat rad, Vertex axis);

		//-----------------------------------------
		// Operators
		//-----------------------------------------
		GameObject& operator=(const GameObject& rhs);
};
