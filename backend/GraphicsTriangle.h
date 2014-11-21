#include "Triangle.h"
#include "Material.h"

class GraphicsTriangle EXTENDS Triangle {

	private:
		Material *matOne, *matTwo, *matThree;
		Vertex *norTwo, *norThree;

	public:
		GraphicsTriangle();
		GraphicsTriangle(Vertex* inOne,Vertex* inTwo, Vertex* inThree, Vertex* inNor);
		GraphicsTriangle(Vertex* inOne,Vertex* inTwo, Vertex* inThree, Vertex* inNorOne, Vertex* inNorTwo, Vertex* inNorThree);

		//-----------------------------------------
		// Get Functions
		//-----------------------------------------
		Material* getMaterialOne(){return matOne;};
		Material* getMaterialTwo(){return matTwo;};
		Material* getMaterialThree(){return matThree;};
		Vertex* getNormalTwo(){return norTwo;};
		Vertex* getNormalThree(){return norThree;};

		//-----------------------------------------
		// Set Functions
		//-----------------------------------------
		void setMaterialOne(Material* inMat){matOne = inMat;};
		void setMaterialTwo(Material* inMat){matTwo = inMat;};
		void setMaterialThree(Material* inMat){matThree = inMat;};
		void setAllMaterials(Material* newMat){ matOne = matTwo = matThree = newMat;};
		void setNormalTwo(Vertex* inNor){norTwo = inNor;};
		void setNormalThree(Vertex* inNor){norThree = inNor;};

		//-----------------------------------------
		// Class Functions
		//-----------------------------------------
		void drawVertex(Vertex* normal, Material* mat, Vertex* position, GLfloat dispx, GLfloat dispy, GLfloat dispz);
		void draw(GLfloat dispx, GLfloat dispy, GLfloat dispz);
};