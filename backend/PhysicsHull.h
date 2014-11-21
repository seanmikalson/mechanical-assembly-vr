#include "VisualData.h"

enum HullType{
	NoType,TriangleMesh,Sphereical
};

//------------------------------------------------------
//  Abstract Class for all Physics Hulls
//------------------------------------------------------
class PhysicsHull{

	protected:
		HullType hullType;
		Vertex position;
		GLfloat maxRadius;

	public:
		PhysicsHull();
		PhysicsHull(GLfloat x, GLfloat y, GLfloat z);

		//-----------------------------------------
		// Get Functions
		//-----------------------------------------
		HullType getHullType(){return hullType;};
		GLfloat getMaxRadius(){return maxRadius;};
		Vertex getPosition(){return position;};

		//-----------------------------------------
		// Set Functions
		//-----------------------------------------
		void setPosition(Vertex inPosition){position = inPosition;};

		//-----------------------------------------
		// Class Functions
		//-----------------------------------------
		virtual bool getIntersection(PhysicsHull* otherHull, Vertex movementVector, Vertex* normal, GLfloat* length, Vertex* intersectionPt,Vertex originDisplacement, Vertex targetDisplacement) = 0;
		virtual bool getTriangleIntersection(PhysicsHull* otherHull, Vertex movementVector, Vertex* normal, GLfloat* length, Vertex* intersectionPt,Vertex originDisplacemet, Vertex targetDisplacement) = 0;
		virtual void drawPhysHull() = 0;
		virtual void rotateX(GLfloat rad) = 0;
		virtual void rotateY(GLfloat rad) = 0;
		virtual void rotateZ(GLfloat rad) = 0;
		virtual void rotate(GLfloat rad, Vertex axis) = 0;
		void adjustPosition(GLfloat x, GLfloat y, GLfloat z);
};



//------------------------------------------------------
//  Class for Sphereical Hull
//------------------------------------------------------
class SphereicalHull EXTENDS PhysicsHull
{
	public:
		SphereicalHull();
		SphereicalHull( GLfloat x, GLfloat y, GLfloat z, GLfloat radius);
};
