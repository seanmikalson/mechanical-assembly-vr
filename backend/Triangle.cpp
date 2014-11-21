#include "Triangle.h"

#define TOLERANCE 0.0f
#define DOES_NOT_INTERSECT  a1 <= (0 - TOLERANCE) || a2 <= (0 - TOLERANCE) || (a1 + a2) >= (1 + TOLERANCE) || t <= (0 - TOLERANCE)


Triangle::Triangle()
{
	one = two = three = nullptr;
	norOne = nullptr;
}
Triangle::Triangle(Vertex* newOne,Vertex* newTwo,Vertex* newThree, Vertex* inNor)
{
	one = newOne;
	two = newTwo;
	three = newThree;
	norOne = inNor;
	generateNormal();
}
Vertex* Triangle::getThisVertex(int index)
{
		if(index == 0)
			return one;
		if(index == 1)
			return two;
		if(index == 2)
			return three;
		
		return nullptr;
}
Triangle& Triangle::operator=(const Triangle& rhs)
{
	if( this == &rhs)
		return *this;

	(*this).one = rhs.one;
	(*this).two = rhs.two;
	(*this).three = rhs.three;
	(*this).norOne = rhs.norOne;

	return *this;
}
bool Triangle::getIntersection(Vertex* intersection,GLfloat* length, Vertex vector,Vertex origin,Vertex displacement)
{
	GLfloat a1 = 0;
	GLfloat a2 = 0; 
	GLfloat t = 0;

	//MagM = det(p2 - p1,p3-p1,-v)
	GLfloat MagM = determinant( (*two  - *one),( *three - *one),(vector * -1.0));

	//prevent divide by zero
	if (MagM == 0.0f)
		return false;

	MagM = 1 / MagM;
	//------------------------------------
	// Calculate A1
	//------------------------------------
	a1 = determinant(origin - ((*one) + displacement), *three - *one, (vector * -1.0));
	a1 *= MagM;
	//------------------------------------
	// Calculate A2
	//------------------------------------
	a2 = determinant(*two - *one,origin - ((*one) + displacement), (vector * -1.0));
	a2 *= MagM;
	//------------------------------------
	// Calculate t
	//------------------------------------
	t = determinant(*two-*one,*three-*one,origin - ((*one) + displacement));
	t *= MagM;
 
	//check if it intersects, if not return the ray
	if(DOES_NOT_INTERSECT)
		return false;

	//if it intersects calculate point
	GLfloat Solx = origin.getX() + (vector.getX() * t);
	GLfloat Soly = origin.getY()+ (vector.getY() * t);
	GLfloat Solz = origin.getZ() + (vector.getZ() * t);

	//make sure triangle isnt past vector end point
	Vertex temp = Vertex(Solx - origin.getX(),Soly - origin.getY(),Solz - origin.getZ());

	GLfloat tlength = temp.length();

	if(tlength > (vector.length() + TOLERANCE))
		return false;

	*length = tlength;
	(*intersection).set(Solx,Soly,Solz);

    return true;
}
void Triangle::generateNormal()
{
	Vertex temp1 = (*one) - (*two);
	Vertex temp2 = (*three) - (*two);
	temp2 = temp2.crossProduct(temp1);
	temp2.normalize();
	*norOne = temp2;
}
void generateRotateXMatrix(GLfloat rad, GLfloat** rotMatrix)
{
	GLfloat cosRot = cos(rad);
	GLfloat sinRot = sin(rad);

	rotMatrix[0][0] = 1.0f; rotMatrix[0][1] = 0.0f; rotMatrix[0][2] = 0.0f;
	rotMatrix[1][0] = 0.0f; rotMatrix[1][1] = cosRot; rotMatrix[1][2] = -sinRot;
	rotMatrix[2][0] = 0.0f; rotMatrix[2][1] = sinRot; rotMatrix[2][2] = cosRot;
}
void generateRotateYMatrix(GLfloat rad, GLfloat** rotMatrix)
{
	GLfloat cosRot = cos(rad);
	GLfloat sinRot = sin(rad);

	rotMatrix[0][0] = cosRot; rotMatrix[0][1] = 0.0f; rotMatrix[0][2] = sinRot;
	rotMatrix[1][0] = 0.0f; rotMatrix[1][1] = 1.0f; rotMatrix[1][2] = 0.0f;
	rotMatrix[2][0] = -sinRot; rotMatrix[2][1] = 0.0f; rotMatrix[2][2] = cosRot;
}
void generateRotateZMatrix(GLfloat rad, GLfloat** rotMatrix)
{
	GLfloat cosRot = cos(rad);
	GLfloat sinRot = sin(rad);

	rotMatrix[0][0] = cosRot; rotMatrix[0][1] = -sinRot; rotMatrix[0][2] = 0.0f;
	rotMatrix[1][0] = sinRot; rotMatrix[1][1] = cosRot; rotMatrix[1][2] = 0.0f;
	rotMatrix[2][0] = 0.0f; rotMatrix[2][1] = 0.0f; rotMatrix[2][2] = 1.0f;
}
void generateRotateMatrix(GLfloat rad, Vertex axis, GLfloat** rotMatrix)
{
	GLfloat cosRot = cos(rad);
	GLfloat sinRot = sin(rad);
	GLfloat oneMinusCos = 1.0f - cosRot;
	axis.normalize();
	GLfloat x = axis.getX(); GLfloat y = axis.getY(); GLfloat z = axis.getZ();

	rotMatrix[0][0] = cosRot + (x * x * oneMinusCos);
	rotMatrix[0][1] = (x * y * oneMinusCos) - (z * sinRot); 
	rotMatrix[0][2] = (x * z * oneMinusCos) + (y * sinRot);
	rotMatrix[1][0] = (y * x * oneMinusCos) + (z * sinRot);
	rotMatrix[1][1] = cosRot + ((y * y) * oneMinusCos);
	rotMatrix[1][2] = (y * z * oneMinusCos) - (x * sinRot);
	rotMatrix[2][0] = (z * x * oneMinusCos) - (y * sinRot); 
	rotMatrix[2][1] = (z * y * oneMinusCos) + (x * sinRot); 
	rotMatrix[2][2] = cosRot + ((z * z) * oneMinusCos);
}
void runRotation(GLfloat** rotMatrix, int noVerticies, Vertex* verticies)
{
	GLfloat x,y,z;

	for(ALL_VERTICIES)
	{
		x = verticies[i].getX(); y = verticies[i].getY(); z = verticies[i].getZ();

		verticies[i].setX( (x * rotMatrix[0][0]) + ( y * rotMatrix[0][1]) + (z * rotMatrix[0][2]));
		verticies[i].setY( (x * rotMatrix[1][0]) + ( y * rotMatrix[1][1]) + (z * rotMatrix[1][2]));
		verticies[i].setZ( (x * rotMatrix[2][0]) + ( y * rotMatrix[2][1]) + (z * rotMatrix[2][2]));	
	}
}