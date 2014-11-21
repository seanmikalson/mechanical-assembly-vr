#include "MechanicalObject.h"
#define EXTENDS : public 
#define DEGREES_TO_RAD 0.017453292f

//-----------------------------------------
//    Primitive Shapes
//-----------------------------------------

class WorkShop EXTENDS GameObject{
	public:
		WorkShop(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, List<Material> material);
};
class EngineHead EXTENDS MechanicalObject{
	public:
		EngineHead(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
};
class EngineBlock EXTENDS MechanicalObject{
	public:
		EngineBlock(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
};
class Square EXTENDS GameObject{

	public:
		Square(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
		void setupPhysData(GLfloat Scale);
};
class Cube : public GameObject{

	public:
		 Cube(Vertex* Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material);
		 void setupPhysData(Vertex* Scale);
};
/*
class SquarePyramid EXTENDS GameObject {
	public:
		 SquarePyramid(Vertex* Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* TriColor);
};

class Circle EXTENDS GameObject 
{
	public:
		Circle(int sides, GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* TriColor);
};

class Cylinder EXTENDS GameObject
{
	public:
		Cylinder(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor);
};

class Sphere EXTENDS GameObject
{
	public:
		Sphere(int insides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor);
};

class Cone EXTENDS GameObject
{
	public:
		Cone(int insides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor);
};
*/