#include "GraphicsTriangle.h"
#include "List.h"

class VisualData
{
	protected:
		List<GraphicsTriangle> visMesh;
		List<Vertex> normals, verticies;
		List<Material> materials;
		Vertex position;

	public:
		//------------------------------------------------
		// Constructors and Destructors
		//------------------------------------------------
		VisualData();
		VisualData(VisualData& rhs);
		VisualData(GLfloat posX,GLfloat posY,GLfloat posZ, int maxVerts, int maxNorms, int maxTriangles, int maxMat);
		~VisualData();

		//------------------------------------------------
		// Misc Class Functions
		//------------------------------------------------
		bool addVisualTriangle(int indOne,int indTwo ,int indThree, int indNorOne, int indNorTwo, int indNorThree);
		void addVertex(GLfloat x, GLfloat y, GLfloat z);
		void addVertex(Vertex addition);
		void addNormal(GLfloat x, GLfloat y, GLfloat z);
		void addMaterial(Material addition);
		void resetVisualMesh(int size);
		void resetVerticies(int size);
		void resetNormals(int size);
		void resetMaterials(int size);
		void draw(GLfloat dispX,GLfloat dispY,GLfloat dispZ);
		void adjustPosition(GLfloat addx,GLfloat addy,GLfloat addz);
		void rotateX(GLfloat rad);
		void rotateY(GLfloat rad);
		void rotateZ(GLfloat rad);
		void rotate(GLfloat rad, Vertex axis);
		void extrude(List<Vertex> path,int materialIndex);
		
		//-----------------------------------------------
		//   Get Functions
		//-----------------------------------------------
		int getNoVerticies(){return verticies.getNoItems();};
		int getNoTriangles(){return visMesh.getNoItems();};
		int getNoNormals(){return normals.getNoItems();};
		int getNoMaterials(){return materials.getNoItems();};
		int getMaxVerticies(){return verticies.getMaxItems();};
		int getMaxTriangles(){return visMesh.getMaxItems();};
		int getMaxNormals(){return normals.getMaxItems();};
		int getMaxMaterials(){return materials.getMaxItems();};
		GraphicsTriangle* getVisualTriangle(int index);
		Vertex* getVertex(int index);
		Vertex* getNormal(int index);
		Material* getMaterial(int index);
		Vertex getPosition(){return position;};
		
		//-----------------------------------------------
		//   Set Functions
		//-----------------------------------------------
		void setPosition(GLfloat inX, GLfloat inY, GLfloat inZ);
		void setNoVerticies(int noVerticies){verticies.setNoItems(noVerticies);};
		void setNoNormals(int noNormals){normals.setNoItems(noNormals);};
		bool setMaterialsForTriangle(int triIndex, int matOneIndex, int matTwoIndex, int matThreeIndex);

		//-----------------------------------------------
		//   Operators
		//-----------------------------------------------
		VisualData& operator=(VisualData&);
};
