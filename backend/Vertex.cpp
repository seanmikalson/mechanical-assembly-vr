#include "Vertex.h"
//---------------------------------------------
// Functions for Vertex Class
//---------------------------------------------
Vertex::Vertex(GLfloat inx, GLfloat iny, GLfloat inz)
{
	x = inx; y = iny; z = inz;
}
Vertex::Vertex()
{
	x = y = z = 0.0f;
}
Vertex& Vertex::operator=(const Vertex& rhs)
{
	if(this == &rhs)
		return *this;

	(*this).x = rhs.x;
	(*this).y = rhs.y;
	(*this).z = rhs.z;

	return *this;
}
Vertex& Vertex::operator=(const GLfloat& rhs)
{
	(*this).x = rhs;
	(*this).y = rhs;
	(*this).z = rhs;

	return *this;
}
Vertex Vertex::operator-(Vertex v)
{
	return Vertex(x-v.x,y-v.y,z-v.z); 
}
Vertex Vertex::operator-(GLfloat v)
{
	return Vertex(x-v,y-v,z-v); 
}
Vertex Vertex::operator+(Vertex v)
{
	return Vertex(x+v.x,y+v.y,z+v.z);
}
Vertex Vertex::operator+(GLfloat v)
{
	return Vertex(x+v,y+v,z+v);
}
Vertex Vertex::operator*(GLfloat rhs)
{
	return Vertex(x * rhs,y *rhs,z * rhs);
}
Vertex Vertex::operator*(Vertex rhs)
{
	return Vertex(x * rhs.x,y *rhs.y,z * rhs.z);
}
Vertex Vertex::operator/(Vertex rhs)
{
	return Vertex(x / rhs.x,y / rhs.y,z / rhs.z);
}
Vertex Vertex::operator/(GLfloat rhs)
{
	return Vertex(x / rhs,y / rhs,z / rhs);
}
bool Vertex::operator==(const Vertex& rhs) const
{
	if(this == &rhs)
		return true;

	bool same = true;
	same &= ((*this).x == rhs.x);
	same &= ((*this).y == rhs.y);
	same &= ((*this).z == rhs.z);
	return same;
}
bool Vertex::operator!=(const Vertex& rhs) const
{
	if(this == &rhs)
		return false;

	bool same = true;
	same &= ((*this).x == rhs.x);
	same &= ((*this).y == rhs.y);
	same &= ((*this).z == rhs.z);
	return !same;
}
Vertex& Vertex::operator+=(const Vertex& rhs)
{
	(*this).x += rhs.x;
	(*this).y += rhs.y;
	(*this).z += rhs.z;
	return *this;
}
Vertex& Vertex::operator+=(const GLfloat& rhs)
{
	(*this).x += rhs;
	(*this).y += rhs;
	(*this).z += rhs;
	return *this;
}
Vertex& Vertex::operator*=(const GLfloat& rhs)
{
	(*this).x *= rhs;
	(*this).y *= rhs;
	(*this).z *= rhs;
	return *this;
}
Vertex& Vertex::operator*=(const Vertex& rhs)
{
	(*this).x *= rhs.x;
	(*this).y *= rhs.y;
	(*this).z *= rhs.z;
	return *this;
}
Vertex& Vertex::operator/=(const GLfloat& rhs)
{
	(*this).x /= rhs;
	(*this).y /= rhs;
	(*this).z /= rhs;
	return *this;
}
Vertex& Vertex::operator/=(const Vertex& rhs)
{
	(*this).x /= rhs.x;
	(*this).y /= rhs.y;
	(*this).z /= rhs.z;
	return *this;
}
Vertex& Vertex::operator-=(const GLfloat& rhs)
{
	(*this).x -= rhs;
	(*this).y -= rhs;
	(*this).z -= rhs;
	return *this;
}
Vertex& Vertex::operator-=(const Vertex& rhs)
{
	(*this).x -= rhs.x;
	(*this).y -= rhs.y;
	(*this).z -= rhs.z;
	return *this;
}
Vertex Vertex::crossProduct(Vertex v)
{
	return Vertex(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);
}
void Vertex::normalize()
{
	GLfloat temp = x*x + y*y + z*z;
	temp = 1 / sqrt(temp);
	x *= temp;
	y *= temp;
	z *= temp;
}
GLfloat Vertex::length()
{
	GLfloat temp = x*x + y*y + z*z;
	return sqrt(temp);
}
GLfloat determinant(Vertex a, Vertex b, Vertex c)
{
	/*Matrix format
	* [ ax  bx  cx  ]
	* [ ay  by  cy  ]
	* [ az  bz  cz  ]
	*/
	GLfloat det = a.getX() * ((b.getY()*c.getZ()) - (b.getZ() * c.getY()));
	det -= b.getX() * ((a.getY() *c.getZ()) - (a.getZ()*c.getY()));
	det += c.getX() * ((a.getY()* b.getZ()) - (a.getZ() * b.getY()));

	return det;
}
void Vertex::reflect(Vertex normal)
{
	Vertex tempV = *this;
	GLfloat projectOnNorm = (normal.dotProduct(tempV * -1.0f));

	*this = tempV + (normal * 2.0f*  projectOnNorm);
}
GLfloat Vertex::dotProduct( Vertex rhs)
{
	return (x * rhs.getX()) + (y *rhs.getY()) + (z * rhs.getZ());
}