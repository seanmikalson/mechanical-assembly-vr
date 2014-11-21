#include "Vertex.h"

class Triangle{
	
	protected:
		Vertex *one, *two, *three,* norOne;

	public:
		Triangle();
		Triangle(Vertex* newOne, Vertex* newTwo, Vertex* newThree, Vertex* inNor);

		//-----------------------------------------
		// Set Functions
		//-----------------------------------------
		void setVertexOne(Vertex* newone){one = newone;};
		void setVertexTwo(Vertex* newtwo){two = newtwo;};
		void setVertexThree(Vertex* newthree){three = newthree;};
		void setNormalOne(Vertex* inNor){norOne = inNor;};

		//-----------------------------------------
		// Get Functions
		//-----------------------------------------
		Vertex* getThisVertex(int index);
		Vertex* getVertexOne(){return one;};
		Vertex* getVertexTwo(){return two;};
		Vertex* getVertexThree(){return three;};
		Vertex* getNormalOne(){return norOne;};

		//-----------------------------------------
		// Class Functions
		//-----------------------------------------
		bool getIntersection(Vertex* intersection,GLfloat* length, Vertex vector,Vertex origin,Vertex displacement);
		Triangle& operator=(const Triangle& rhs);
		void generateNormal();
};

void generateRotateXMatrix(GLfloat rad, GLfloat** rotMatrix);
void generateRotateYMatrix(GLfloat rad, GLfloat** rotMatrix);
void generateRotateZMatrix(GLfloat rad, GLfloat** rotMatrix);
void generateRotateMatrix(GLfloat rad, Vertex axis, GLfloat** rotMatrix);
void runRotation(GLfloat** rotMatrix, int noVerticies, Vertex* verticies);