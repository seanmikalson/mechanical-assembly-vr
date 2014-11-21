#include "GraphicsTriangle.h"

#define POS_PLUS_DISP_X (*position).getX()+ dispx
#define POS_PLUS_DISP_Y (*position).getY()+ dispy
#define POS_PLUS_DISP_Z (*position).getZ()+ dispz
#define NOR_X (*normal).getX()
#define NOR_Y (*normal).getY()
#define NOR_Z (*normal).getZ()
#define OPAQUE (*TriMat).isOpaque()

GraphicsTriangle::GraphicsTriangle(): Triangle()
{
	matOne = matTwo = matThree = nullptr;
	norTwo = norThree = nullptr;
}
GraphicsTriangle::GraphicsTriangle(Vertex* inOne,Vertex* inTwo, Vertex* inThree, Vertex* inNor): Triangle(inOne,inTwo,inThree,inNor)
{
		matOne = matTwo = matThree = nullptr;
		norThree = norTwo = norOne;
}
GraphicsTriangle::GraphicsTriangle(Vertex* inOne,Vertex* inTwo, Vertex* inThree, Vertex* inNorOne, Vertex* inNorTwo, Vertex* inNorThree)
{
	one = inOne;
	two = inTwo;
	three = inThree;
	matOne = matTwo = matThree = nullptr;
	norOne = inNorOne;
	norTwo = inNorTwo;
	norThree = inNorThree;
}
void GraphicsTriangle::drawVertex(Vertex* normal, Material* mat, Vertex* position, GLfloat dispx, GLfloat dispy, GLfloat dispz)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (*mat).getAmbient());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,(*mat).getDiffuse());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,(*mat).getShinniness());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,(*mat).getSpecular());

	glNormal3f(NOR_X, NOR_Y, NOR_Z);
    glVertex3f(POS_PLUS_DISP_X, POS_PLUS_DISP_Y, POS_PLUS_DISP_Z);
}
void GraphicsTriangle::draw(GLfloat dispx, GLfloat dispy, GLfloat dispz)
{
	drawVertex(norOne,matOne,one,dispx,dispy,dispz);
	drawVertex(norTwo,matTwo,two,dispx,dispy,dispz);
	drawVertex(norThree,matThree,three,dispx,dispy,dispz);		
}
