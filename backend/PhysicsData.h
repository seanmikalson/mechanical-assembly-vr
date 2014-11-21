#include "TriangleMeshHull.h"

class PhysicsData
{
	protected:
		List<PhysicsHull*> physicsHulls;
		Vertex velocity,acceleration,position;
		GLfloat mass;
		GLfloat restitution;
		GLfloat staticFriction,dynamicFriction;
		
	public:
		PhysicsData();
		PhysicsData(int maxHulls, GLfloat posx, GLfloat posy, GLfloat posz);
		~PhysicsData();

		//-----------------------------------------------
		//   Operators
		//-----------------------------------------------
		PhysicsData& operator=( const PhysicsData&);

		//-----------------------------------------------
		//   Class Functions
		//-----------------------------------------------
		void accelerate(GLfloat x,GLfloat y,GLfloat z);
		void addVelocity(GLfloat x,GLfloat y,GLfloat z);
		void updateVelocity(GLfloat elapsedTime);
		void updatePosition(GLfloat elapsedTime);
		bool checkCollision(PhysicsData* otherObject,Vertex* collisionPt,Vertex* normal, GLfloat* movementLength,GLfloat elapsedTime);
		bool addPhysicsHull(HullType newHullType);
		void adjustPosition(GLfloat addx,GLfloat addy,GLfloat addz);
		void resetPhysHulls(int newMaxHulls);
		void collide(PhysicsData* target, GLfloat length,Vertex normal, GLfloat elapsedTime);
		void rotateX(GLfloat rad);
		void rotateY(GLfloat rad);
		void rotateZ(GLfloat rad);
		void rotate(GLfloat rad, Vertex axis);

		//-----------------------------------------------
		//   Get Functions
		//-----------------------------------------------
		PhysicsHull* getPhysicsHull(int index);
		TriangleMeshHull* getTriangleHull(int index);
		Vertex getVelocity(){return velocity;};
		Vertex getAcceleration(){return acceleration;};
		GLfloat getMass(){return mass;};
		GLfloat getRestitution(){return restitution;};
		Vertex getPosition(){return position;};
		int getNoHulls(){return physicsHulls.getNoItems();};
		int getMaxHulls(){return physicsHulls.getMaxItems();};
		GLfloat getStaticFriction(){return staticFriction;};
		GLfloat getDynamicFriction(){return dynamicFriction;};
		Vertex* getVelocityPointer(){return &velocity;};
		
		//-----------------------------------------------
		//   Set Functions
		//-----------------------------------------------
		void setMass(GLfloat newmass){mass = newmass;};
		void setPosition(GLfloat inX, GLfloat inY, GLfloat inZ);
		void setVelocity(GLfloat inX, GLfloat inY, GLfloat inZ);
		void setAcceleration(GLfloat inX, GLfloat inY, GLfloat inZ);
		void setRestitution(GLfloat nRestitution){restitution = nRestitution;};
		void setStaticFriction(GLfloat nStaticFriction){ staticFriction = nStaticFriction;};
		void setDynamicFriction(GLfloat nDynamicFriction){dynamicFriction = nDynamicFriction;};
};
