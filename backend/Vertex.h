#include <glew.h>
#include <math.h>
#define EXTENDS : public 
#define ALL_VERTICIES int i = 0; i < noVerticies; i++

//--------------------------------------
// Class For a Vertex
//--------------------------------------
class Vertex{

	private:
		GLfloat x,y,z;

	public:
		Vertex();
		Vertex(GLfloat inx,GLfloat iny,GLfloat inz);
	
		//-----------------------------------------
		// Get Functions
		//-----------------------------------------
		GLfloat getX(){return x;};
		GLfloat getY(){return y;};
		GLfloat getZ(){return z;};

		//-----------------------------------------
		// Set Functions
		//-----------------------------------------
		void setX(GLfloat inx){x = inx;};
		void setY(GLfloat iny){y = iny;};
		void setZ(GLfloat inz){z = inz;};
		void set(GLfloat inX, GLfloat inY, GLfloat inZ){ x = inX; y = inY; z = inZ;};

		//-----------------------------------------
		// Class Functions
		//-----------------------------------------
		void normalize();
		GLfloat length();
		Vertex crossProduct(Vertex);
		Vertex getPerpendicular();
		GLfloat dotProduct(Vertex rhs);
		void reflect(Vertex normal);
	
		//-----------------------------------------
		// Operators
		//-----------------------------------------
		Vertex& operator=(const Vertex&);
		Vertex& operator=(const GLfloat&);

		bool operator==(const Vertex& rhs) const;
		bool operator!=(const Vertex& rhs) const;

		Vertex operator-(Vertex);
		Vertex operator-(GLfloat);

		Vertex operator+(Vertex);
		Vertex operator+(GLfloat);

		Vertex operator*(GLfloat);
		Vertex operator*(Vertex);

		Vertex operator/(Vertex);
		Vertex operator/(GLfloat);

		Vertex& operator+=(const Vertex& rhs);
		Vertex& operator+=(const GLfloat& rhs);

		Vertex& operator*=(const GLfloat& rhs);
		Vertex& operator*=(const Vertex& rhs);

		Vertex& operator/=(const Vertex& rhs);
		Vertex& operator/=(const GLfloat& rhs);

		Vertex& operator-=(const GLfloat& rhs);
		Vertex& operator-=(const Vertex& rhs);
};
GLfloat determinant(Vertex a,Vertex b,Vertex c);