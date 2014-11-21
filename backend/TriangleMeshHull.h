#include "PhysicsHull.h"

class TriangleMeshHull EXTENDS PhysicsHull
{
	private:
		List<Vertex> verticies,normals;
		List<Triangle> triangles;

	public:
		TriangleMeshHull();
		TriangleMeshHull(int maxVerts,int maxTri,GLfloat x, GLfloat y, GLfloat z);
		~TriangleMeshHull();
		TriangleMeshHull(TriangleMeshHull& rhs);

		//--------------------------------------------------
		//   Operators
		//--------------------------------------------------
		TriangleMeshHull& operator=(TriangleMeshHull&);

		//--------------------------------------------------
		// Get Functions
		//--------------------------------------------------
		Triangle* getTriangle(int index);
		Vertex* getVertex(int index);
		Vertex* getNormal(int index);
		int getNoTriangles(){return triangles.getNoItems();};
		int getNoVerticies(){return verticies.getNoItems();};
		int getMaxTriangles(){return triangles.getMaxItems();};
		int getMaxVerticies(){return verticies.getMaxItems();};

		//-----------------------------------------
		// Class Functions
		//-----------------------------------------
		void addVertex(GLfloat x, GLfloat y, GLfloat z);
		bool addTriangle(int vertIndOne,int vertIndTwo, int vertIndThree);
		void resetVerticies(int size);
		void resetTriangles(int size);
		void rotateX(GLfloat rad);
		void rotateY(GLfloat rad);
		void rotateZ(GLfloat rad);
		void rotate(GLfloat rad, Vertex axis);

		bool getIntersection(PhysicsHull* otherHull, Vertex movementVector, Vertex* normal,GLfloat* length, Vertex* intersectionPt,Vertex originDisplacement, Vertex targetDisplacement);
		bool getTriangleIntersection(PhysicsHull* otherHull, Vertex movementVector,Vertex* normal, GLfloat* length, Vertex* intersectionPt,Vertex originDisplacement, Vertex targetDisplacement);
		void drawPhysHull();
};