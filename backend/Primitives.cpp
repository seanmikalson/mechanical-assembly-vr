#include "Primitives.h"
#include <math.h>

#define VIS_VERTEX visualData[0].getVertex
#define NORMAL (*visualData.getItem(0)).getNormal
#define SET_VIS_VERTEX *(*visualData.getItem(0)).getVertex
#define ADD_TRIANGLE (*visualData.getItem(0)).addVisualTriangle
#define ADD_VERTEX (*visualData.getItem(0)).addVertex
#define ADD_NORMAL (*visualData.getItem(0)).addNormal
#define HULL_ZERO (*physicsData.getTriangleHull(0))

#define SCALE_X (*Scale).getX()
#define SCALE_Y (*Scale).getY()
#define SCALE_Z (*Scale).getZ()

#define MAX_SIDES 64
#define MIN_SIDES 4

int checkSides(int sides)
{
	//if( sides > MAX_SIDES)
	//	 sides = MAX_SIDES;

	 if( sides < MIN_SIDES)
		sides = 4;

	sides += sides % 2;//force sides to even number

	return sides;
}
WorkShop::WorkShop(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, List<Material> material) : GameObject(dispx,dispy,dispz,2,10)
{
	addVisualData(0.0f,0.0f,0.0f,8,6,12,3);
	for(int i = 0; i < 3; i++)
		visualData[0].addMaterial(material[i]);

	 GLfloat PointFive = 0.5f * Scale;
	 GLfloat NegPointFive = -0.5f * Scale;

	 visualData[0].addVertex(-Scale,-Scale / 2.0f,Scale);
	 visualData[0].addVertex(Scale,-Scale /2.0f,Scale);
	 visualData[0].addVertex(Scale,-Scale /2.0f,-Scale);
	 visualData[0].addVertex(-Scale,-Scale/2.0f,-Scale);

	 for(int i = 0; i< 4; i++)
	 {
		Vertex temp =  *visualData[0].getVertex(i);
		temp.setY(temp.getY() * -1.0f);
		 visualData[0].addVertex(temp);
	 }

	 //floor
	 visualData[0].addNormal(0.0f,1.0f,0.0f);
	 visualData[0].addVisualTriangle(0,1,2,0,0,0);
	 visualData[0].setMaterialsForTriangle(0,0,0,0);
	 visualData[0].addVisualTriangle(0,2,3,0,0,0);
	 visualData[0].setMaterialsForTriangle(1,0,0,0);

	 //Roof
	 visualData[0].addNormal(0.0f,-1.0f,0.0f);
	 visualData[0].addVisualTriangle(4,6,5,1,1,1);
	 visualData[0].setMaterialsForTriangle(2,1,1,1);
	 visualData[0].addVisualTriangle(4,7,6,1,1,1);
	 visualData[0].setMaterialsForTriangle(3,1,1,1);

	 //walls
	 for(int i = 0; i < 3; i++)
	 {
		visualData[0].addNormal(0.0f,1.0f,0.0f);
		visualData[0].addVisualTriangle(i, i + 4, i+ 1,2 + i, 2+ i, 2 +i);
		(*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,2,2,2);
		visualData[0].addVisualTriangle(i + 4,i + 5,i + 1,2 + i,2 + i, 2+i);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1 ,2,2,2);
	 }
		visualData[0].addNormal(0.0f,1.0f,0.0f);
		visualData[0].addVisualTriangle(3, 7, 0,5, 5,5);
		(*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,2,2,2);
		visualData[0].addVisualTriangle(0,7,4,5,5,5);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1 ,2,2,2);
}
EngineHead::EngineHead(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material) : MechanicalObject(Vertex(dispx,dispy,dispz),10,10,1)
{
	Scale *= 2.0f;
	 addVisualData(0.0f,0.0f,0.0f,40,40,40,1);
	 (*visualData.getItem(0)).addMaterial(*material);

	 GLfloat PointFive = 0.5f * Scale;
	 GLfloat NegPointFive = -0.5f * Scale;

	 connections.addItem(Connections(10));

	 addMountingPoint(0,Vertex(NegPointFive * 0.35f,NegPointFive / 4.0f, Scale * 0.95f),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.35f,NegPointFive / 4.0f, Scale * 0.95f),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.35f,NegPointFive / 4.0f, Scale / 2.0f),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.35f,NegPointFive / 4.0f, Scale / 2.0f),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.35f,NegPointFive / 4.0f, 0.0f),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.35f,NegPointFive / 4.0f, 0.0f),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.35f,NegPointFive / 4.0f, -0.5f *Scale),Vertex(0.0f,-1.0f,0.0f));

	addMountingPoint(0,Vertex(PointFive * 0.35f,NegPointFive / 4.0f, -0.5f *Scale),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.35f,NegPointFive / 4.0f, -0.95 *Scale),Vertex(0.0f,-1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.35f,NegPointFive / 4.0f, -0.95 *Scale),Vertex(0.0f,-1.0f,0.0f));

	 visualData[0].addVertex(0.5f *NegPointFive, NegPointFive / 4.0f, 2 * PointFive);
	 visualData[0].addVertex(0.5f *PointFive, NegPointFive / 4.0f, 2 * PointFive);
	 visualData[0].addVertex(0.5f *PointFive, NegPointFive / 4.0f, 2 * NegPointFive);
	 visualData[0].addVertex(0.5f *NegPointFive, NegPointFive / 4.0f, 2 * NegPointFive);

	 visualData[0].addVertex(0.5f *NegPointFive * 0.8f, PointFive / 4.0f, 2 * PointFive * 0.9f);
	 visualData[0].addVertex(0.5f *PointFive * 0.8f, PointFive / 4.0f, 2 * PointFive * 0.9f);
	 visualData[0].addVertex(0.5f *PointFive * 0.8f, PointFive / 4.0f, 2 * NegPointFive * 0.9f);
	 visualData[0].addVertex(0.5f *NegPointFive * 0.8f, PointFive / 4.0f, 2 * NegPointFive * 0.9f);

	 //----------------------------------------------------
	 // Create Sides
	 //----------------------------------------------------
	 for(int i = 0; i < 3; i++)
	 {
		 visualData[0].addNormal(0.0f,0.0f,1.0f);
		 visualData[0].addVisualTriangle(i, i+1, i + 4,i,i,i);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
		 visualData[0].addVisualTriangle(i +1, i+5, i + 4,i,i,i);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
		 (*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();
	 }
		 visualData[0].addNormal(0.0f,0.0f,1.0f);
		 visualData[0].addVisualTriangle(3, 0, 7,3,3,3);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
		 visualData[0].addVisualTriangle(0, 4, 7,3,3,3);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
		 (*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();

	 //----------------------------------------------------
	 // Create Bottom
	 //----------------------------------------------------
		 visualData[0].addNormal(0.0f,0.0f,1.0f);
		 visualData[0].addVisualTriangle(2, 1, 0,4,4,4);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
		 visualData[0].addVisualTriangle(2, 0, 3,4,4,4);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
		 (*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();

	 //----------------------------------------------------
	 // Create Upper Edges
	 //----------------------------------------------------

		 visualData[0].addNormal(0.0f,1.0f,0.0f);
		 visualData[0].addVertex(*visualData[0].getVertex(4) + (Vertex(0.5f,0.0f,-0.5f) * Scale / 10.0f ));
		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 1, 4,5,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 visualData[0].addVertex(*visualData[0].getVertex(5) + (Vertex(-0.5f,0.0f,-0.5f) * Scale / 10.0f ));
		 visualData[0].addVisualTriangle(5,visualData[0].getNoVerticies() - 1,visualData[0].getNoVerticies() - 2 ,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 Vertex temp = *visualData[0].getVertex(visualData[0].getNoVerticies() - 1);
		 GLfloat tempZ = temp.getZ() * -1.0f;

		 visualData[0].addVertex(temp.getX(),temp.getY(),tempZ);
		 temp = *visualData[0].getVertex(visualData[0].getNoVerticies() - 3);
		 visualData[0].addVertex(temp.getX(),temp.getY(),tempZ);

		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 3, 5,6,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 2, visualData[0].getNoVerticies() - 3,6,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 2, 6,7,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		  visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 1, visualData[0].getNoVerticies() - 2,7,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 1, 7,4,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 1, 4,visualData[0].getNoVerticies() - 4,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 for(int i = 0; i < 4; i++)
		 {
			 Vertex temp = *visualData[0].getVertex(visualData[0].getNoVerticies() - 4);
			 temp.setY(temp.getY() - (Scale / 8.0f));
			 visualData[0].addVertex(temp);
		 }

		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 4, visualData[0].getNoVerticies() - 3,visualData[0].getNoVerticies() - 2,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 2, visualData[0].getNoVerticies() - 1,visualData[0].getNoVerticies() - 4,5,5,5);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 for(int i = 0 ; i< 3; i++)
		 {
			visualData[0].addNormal(0.0f,1.0f,0.0f);
			visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 1 - i, visualData[0].getNoVerticies() - 2 - i,visualData[0].getNoVerticies() - 5 - i,i+6,i+6,i+6);
			visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
			(*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();

			visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 2 - i, visualData[0].getNoVerticies() - 6 - i,visualData[0].getNoVerticies() - 5 - i,i+6,i+6,i+6);
			visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

		 }

			visualData[0].addNormal(0.0f,1.0f,0.0f);
			visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 1, visualData[0].getNoVerticies() - 5,visualData[0].getNoVerticies() - 4,9,9,9);
			visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
			(*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();

			visualData[0].addVisualTriangle(visualData[0].getNoVerticies() - 4, visualData[0].getNoVerticies() - 5,visualData[0].getNoVerticies() - 8,9,9,9);
			visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

			//------------------------------------------------------
			//  Create Valve Springs
			//------------------------------------------------------
			/*
			addVisualData(0.0f,0.0f,0.0f,132,512,256,1);
			visualData[1].addMaterial(*material);

			visualData[1].addVertex(Scale /20.0f, 0.0f,0.0f);
			visualData[1].addVertex(Scale / 40.0f, 0.0f,0.0f);
			visualData[1].addVertex(Scale / 40.0f, Scale / 80.0f,0.0f);
			visualData[1].addVertex(Scale / 20.0f, Scale / 80.0f,0.0f);

			GLfloat** rotMatrix = new GLfloat*[3];
			for(int i = 0; i < 3 ; i++)
				rotMatrix[i] = new GLfloat[3];

			generateRotateMatrix(60.0f * DEGREES_TO_RAD, Vertex(0.0f,1.0f,0.0f),rotMatrix);

			for(int i = 0; i < 32; i++)
			{
				for(int b = 0; b < 4; b++)
				{
					Vertex addition = *visualData[1].getVertex( (i * 4) + b);
					addition += Vertex(0.0f, Scale / 240.0f ,0.0f);
					visualData[1].addVertex(addition);
				}
				Vertex* temp = visualData[1].getVertex((i*4) + 4);

				runRotation(rotMatrix,4,temp);

				int normInd = 0;
			
				
				for(int b = 0; b < 3; b++)
				{
					visualData[1].addNormal(0.0f,0.0f,1.0f);
				    normInd = visualData[1].getNoNormals() -1;
					visualData[1].addNormal(0.0f,0.0f,1.0f);
					visualData[1].addNormal(0.0f,0.0f,1.0f);
					visualData[1].addNormal(0.0f,0.0f,1.0f);

					visualData[1].addVisualTriangle((i *4) +b, (i *4) + 5 +b, (i * 4) + 1 +b, normInd,normInd +3,normInd + 1);
					visualData[1].setMaterialsForTriangle(visualData[1].getNoTriangles() - 1, 0,0,0);

					visualData[1].addVisualTriangle((i*4) +b, (i*4) + 4 +b, (i*4) + 5+b, normInd,normInd +2,normInd +3);
					visualData[1].setMaterialsForTriangle(visualData[1].getNoTriangles() - 1, 0,0,0);

					(*visualData[1].getVisualTriangle(visualData[1].getNoTriangles() -1)).generateNormal();

					*visualData[1].getNormal(normInd) = *visualData[1].getNormal(normInd) * -1.0f;
					*visualData[1].getNormal(normInd +1) = *visualData[1].getNormal(normInd);
					*visualData[1].getNormal(normInd +2) = *visualData[1].getNormal(normInd);
					*visualData[1].getNormal(normInd +3) = *visualData[1].getNormal(normInd);
				}
				visualData[1].addNormal(0.0f,0.0f,1.0f);
				 normInd = visualData[1].getNoNormals() -1;
				 visualData[1].addNormal(0.0f,0.0f,1.0f);
				 visualData[1].addNormal(0.0f,0.0f,1.0f);
				 visualData[1].addNormal(0.0f,0.0f,1.0f);

				visualData[1].addVisualTriangle((i *4), (i *4) + 3, (i * 4) + 7, normInd,normInd,normInd);
				visualData[1].setMaterialsForTriangle(visualData[1].getNoTriangles() - 1, 0,0,0);

				visualData[1].addVisualTriangle((i*4), (i*4) + 7, (i*4) + 4, normInd,normInd,normInd);
				visualData[1].setMaterialsForTriangle(visualData[1].getNoTriangles() - 1, 0,0,0);

				(*visualData[1].getVisualTriangle(visualData[1].getNoTriangles() -1)).generateNormal();

				*visualData[1].getNormal(normInd) = *visualData[1].getNormal(normInd) * -1.0f;
				*visualData[1].getNormal(normInd +1) = *visualData[1].getNormal(normInd);
				*visualData[1].getNormal(normInd +2) = *visualData[1].getNormal(normInd);
				*visualData[1].getNormal(normInd +3) = *visualData[1].getNormal(normInd);
			}


			for(int i = 0; i < visualData[1].getNoTriangles(); i += 2)
			{

			}
			
			for(int i = 0; i < 3; i++)
				delete rotMatrix[i];
		
			delete []rotMatrix;
			*/
}
void EngineHead::setupCorrectMountingPoints(EngineBlock* engineBlock, int side)
{
	if(side ==0)
	{
		for(int i = 0; i < 10; i++)
		{
			(*engineBlock).setCorrectMount(i,side, (*connections.getItem(0)).getMountingPointPtr(i) );
			(*this).setCorrectMount(i,0,(*engineBlock).getMountingPointPtr(i,side));
		}	
	}
	else
	{
		for(int i = 0; i < 10; i+=2)
		{
			(*engineBlock).setCorrectMount(i+ 1,side, (*connections.getItem(0)).getMountingPointPtr(i) );
			(*this).setCorrectMount(i,0,(*engineBlock).getMountingPointPtr(i+1,side));
			(*engineBlock).setCorrectMount(i,side, (*connections.getItem(0)).getMountingPointPtr(i+1) );
			(*this).setCorrectMount(i+1,0,(*engineBlock).getMountingPointPtr(i,side));
		}


	}
}
EngineBlock::EngineBlock(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material) : MechanicalObject(Vertex(dispx,dispy,dispz),14,10,3)
{
	 int cylinderSize = 32;
	 for(int i = 0; i < 8; i++)
	 {
	 addVisualData(0.0f,0.0f,0.0f,(2*cylinderSize) + 4,1 + cylinderSize,(3*cylinderSize) + 4,1);
	 }
	 addVisualData(0.0f,0.0f,0.0f,7,1,5,1);
	 addVisualData(0.0f,0.0f,0.0f,7,1,5,1);
	 addVisualData(0.0f,0.0f,0.0f,4,1,2,1);
	 addVisualData(0.0f,0.0f,0.0f,4,1,2,1);
	 addVisualData(0.0f,0.0f,0.0f,4,1,2,1);
	  addVisualData(0.0f,0.0f,0.0f,4,1,2,1);
	 (*visualData.getItem(0)).addMaterial(*material);
	 (*visualData.getItem(8)).addMaterial(*material);
	 (*visualData.getItem(10)).addMaterial(*material);
	 (*visualData.getItem(11)).addMaterial(*material);
	  (*visualData.getItem(13)).addMaterial(*material);
	 
	

	 GLfloat PointFive = 0.5f * Scale;
	 GLfloat NegPointFive = -0.5f * Scale;

	//--------------------------------------------------------------------------
	// Create Mounting Points
	//--------------------------------------------------------------------------
	 connections.addItem(Connections(10));
	 addMountingPoint(0,Vertex(NegPointFive * 0.7f,0.0f, Scale * 0.9f),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.7f,0.0f, Scale * 0.9f),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.7f,0.0f, 0.0f),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.7f,0.0f, 0.0f),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.7f,0.0f, -Scale),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.7f,0.0f, -Scale),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.7f,0.0f, -2 *Scale),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.7f,0.0f, -2 *Scale),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(NegPointFive * 0.7f,0.0f, -2.9 *Scale),Vertex(0.0f,1.0f,0.0f));

	 addMountingPoint(0,Vertex(PointFive * 0.7f,0.0f, -2.9 *Scale),Vertex(0.0f,1.0f,0.0f));

	 GLfloat** rotMatrix = new GLfloat*[3];
		for(int i = 0; i < 3 ; i++)
			rotMatrix[i] = new GLfloat[3];

		generateRotateZMatrix(-45.0f * DEGREES_TO_RAD,rotMatrix);
		for(int i = 0; i< 10; i++)
		{
			runRotation(rotMatrix,1, (*connections.getItem(0)).getMountingPointPtr(i));
			runRotation(rotMatrix,1, (*connections.getItem(0)).getMountingNormalPtr(i));
			*(*connections.getItem(0)).getMountingPointPtr(i) += Vertex(1.25f * Scale,0.0f,Scale);
		}
		for(int i = 0; i < 3; i++)
			delete rotMatrix[i];

		delete []rotMatrix;

		connections.addItem(Connections(10));
		for(int i = 0; i < 10; i++)
		{
			Vertex tmoun = (*connections.getItem(0)).getMountingPoint(i);
			Vertex tnorm = (*connections.getItem(0)).getMountingNormal(i);
			tmoun *= Vertex(-1.0f,1.0f,1.0f);
			tnorm *= Vertex(-1.0f,1.0f,1.0f);

			addMountingPoint(1,tmoun,tnorm);
		}
	 
	//--------------------------------------------------------------------------
	// Create Cylinder Sleeves
	//--------------------------------------------------------------------------
	 ADD_VERTEX(NegPointFive, 0.0f, PointFive);
	 ADD_VERTEX(PointFive, 0.0f, PointFive);
	 ADD_VERTEX(PointFive, 0.0f, NegPointFive);
	 ADD_VERTEX(NegPointFive,0.0f, NegPointFive);
	 ADD_NORMAL(0.0f,1.0f,0.0f); //up
	 
	 GLfloat cylinderX = 0.75 * NegPointFive;
	 for(int i = 0; i < cylinderSize; i++)
	 {
		GLfloat x = cylinderX * cos((360.0f/ cylinderSize) * i * DEGREES_TO_RAD);
		GLfloat y = 0.0f;
		GLfloat z = cylinderX * sin((360.0f/ cylinderSize) * i *DEGREES_TO_RAD);
		ADD_VERTEX(x,0.0f,z);
		Vertex normal = Vertex(x,y,z);
		normal.normalize();
		normal *= -1.0f;
		ADD_NORMAL(normal.getX(),normal.getY(),normal.getZ());
	 }

	 int outsideIndex = 3;
	 for(int i = 0; i < (cylinderSize - 1); i++)
	 {
		 
		 if( i < cylinderSize / 4)
			 outsideIndex = 3;
		 else if(i < cylinderSize / 2)
			 outsideIndex = 2;
		 else if (i < (3 * cylinderSize / 4))
			 outsideIndex = 1;
		 else 
			 outsideIndex = 0;
			 

		 ADD_TRIANGLE(i + 4,i + 5,outsideIndex,0,0,0);
		 (*visualData.getItem(0)).setMaterialsForTriangle(i,0,0,0);
	 }
	  ADD_TRIANGLE(cylinderSize + 3,4,0,0,0,0);
	  (*visualData.getItem(0)).setMaterialsForTriangle(cylinderSize -1,0,0,0);

	  ADD_TRIANGLE(0,4,3,0,0,0);
	  (*visualData.getItem(0)).setMaterialsForTriangle(cylinderSize ,0,0,0);

	  ADD_TRIANGLE(3,4 + (cylinderSize /4),2,0,0,0);
	  (*visualData.getItem(0)).setMaterialsForTriangle(cylinderSize + 1,0,0,0);

	  ADD_TRIANGLE(2,4 + (cylinderSize /2),1,0,0,0);
	  (*visualData.getItem(0)).setMaterialsForTriangle(cylinderSize + 2,0,0,0);

	  ADD_TRIANGLE(1,4 + ( 3 *(cylinderSize /4)),0,0,0,0);
	  (*visualData.getItem(0)).setMaterialsForTriangle(cylinderSize + 3,0,0,0);

	  for(int i = 0; i < cylinderSize; i++)
	  {
		  ADD_VERTEX((*(*visualData.getItem(0)).getVertex(i + 4)).getX(),(*(*visualData.getItem(0)).getVertex(i + 4)).getY() - Scale,(*(*visualData.getItem(0)).getVertex(i + 4)).getZ());
	  }
	 for(int i = 0; i < cylinderSize - 1; i++)
	 {
		 ADD_TRIANGLE(4 + i, 4 + cylinderSize + i, 5+ i,i+1,i+1,i+2);
		 (*visualData.getItem(0)).setMaterialsForTriangle(cylinderSize + 4 + (2*i),0,0,0);

		 ADD_TRIANGLE(4 + cylinderSize + i,5 + cylinderSize + i , 5+ i,i+1,i+2,i+2);
		 (*visualData.getItem(0)).setMaterialsForTriangle(cylinderSize + 5 + (2*i),0,0,0);
	 }

		ADD_TRIANGLE(3 + cylinderSize,(2*cylinderSize) + 3, 4,cylinderSize,cylinderSize,1);
		 (*visualData.getItem(0)).setMaterialsForTriangle((3*cylinderSize) + 2,0,0,0);

		ADD_TRIANGLE((2*cylinderSize) + 3,cylinderSize + 4,4 ,cylinderSize,1,1);
		(*visualData.getItem(0)).setMaterialsForTriangle((3*cylinderSize) + 3,0,0,0);
		
	 
		for(int i = 1;i < 8; i++)
		*visualData.getItem(i) = *visualData.getItem(0);
		
		for(int i = 0; i < 4; i++)
		{
			(*(*this).getVisualData(i)).rotateZ(-45.0f * DEGREES_TO_RAD);
			(*(*this).getVisualData(i)).adjustPosition(1.25f * Scale,0.0f,Scale * -i);
			(*(*this).getVisualData(i + 4)).rotateZ(45.0f * DEGREES_TO_RAD);
			(*(*this).getVisualData(i + 4)).adjustPosition(1.25f * -Scale,0.0f,Scale * -i);	
		}
		

		//--------------------------------------------------------------------------
		// Create Front Of Engine
		//--------------------------------------------------------------------------
		for(int i = 0;i < 8; i++)
			(*(*this).getVisualData(i)).adjustPosition(0.0f,0.0f,1.5* Scale);
		
		Vertex temp = *(*visualData.getItem(0)).getVertex(0) + (*visualData.getItem(0)).getPosition();
		(*visualData.getItem(8)).addVertex(temp.getX(),temp.getY(),temp.getZ());

		temp = *(*visualData.getItem(4)).getVertex(1)+ (*visualData.getItem(4)).getPosition();
		(*visualData.getItem(8)).addVertex(temp.getX(),temp.getY(),temp.getZ());

		(*visualData.getItem(8)).addVertex(0.0f,-Scale,temp.getZ());
		
		temp = *(*visualData.getItem(0)).getVertex(1) + (*visualData.getItem(0)).getPosition();
		(*visualData.getItem(8)).addVertex(temp.getX(),temp.getY(),temp.getZ());

		temp = *(*visualData.getItem(4)).getVertex(0) + (*visualData.getItem(4)).getPosition();
		(*visualData.getItem(8)).addVertex(temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(8)).addNormal(0.0f,0.0f,1.0f);

		(*visualData.getItem(8)).addVisualTriangle(0,1,2,0,0,0);
		(*visualData.getItem(8)).setMaterialsForTriangle(0,0,0,0);

		(*visualData.getItem(8)).addVisualTriangle(2,3,0,0,0,0);
		(*visualData.getItem(8)).setMaterialsForTriangle(1,0,0,0);

	    (*visualData.getItem(8)).addVisualTriangle(2,1,4,0,0,0);
		(*visualData.getItem(8)).setMaterialsForTriangle(2,0,0,0);

		temp = Vertex(-cos(45 * DEGREES_TO_RAD),-sin(45 * DEGREES_TO_RAD),0.0f);
		temp *= Scale * 1.4;
		temp += *(*visualData.getItem(0)).getVertex(1) + (*visualData.getItem(0)).getPosition();
		(*visualData.getItem(8)).addVertex(temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(8)).addVertex(-temp.getX(),temp.getY(),temp.getZ());

		(*(*visualData.getItem(8)).getVertex(2)).setY(temp.getY());

		(*visualData.getItem(8)).addVisualTriangle(2,5,3,0,0,0);
		(*visualData.getItem(8)).setMaterialsForTriangle(3,0,0,0);

		(*visualData.getItem(8)).addVisualTriangle(2,4,6,0,0,0);
		(*visualData.getItem(8)).setMaterialsForTriangle(4,0,0,0);
		
		//--------------------------------------------------------------------------
		// Derive Back Of Engine From Front
		//--------------------------------------------------------------------------
		(*visualData.getItem(9)) = (*visualData.getItem(8));
		(*visualData.getItem(9)).rotateY(180.0f * DEGREES_TO_RAD);


		//--------------------------------------------------------------------------
		// Setup Top
		//--------------------------------------------------------------------------
		(*visualData.getItem(10)).addNormal(0.0f,1.0f,0.0f);
		temp = *(*visualData.getItem(8)).getVertex(0);
		(*visualData.getItem(10)).addVertex(temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(10)).addVertex(temp.getX(),temp.getY(),-temp.getZ());
		
		temp = *(*visualData.getItem(8)).getVertex(1);
		(*visualData.getItem(10)).addVertex(temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(10)).addVertex(temp.getX(),temp.getY(),-temp.getZ());

		(*visualData.getItem(10)).addVisualTriangle(0,1,2,0,0,0);
		(*visualData.getItem(10)).setMaterialsForTriangle(0,0,0,0);

		(*visualData.getItem(10)).addVisualTriangle(2,1,3,0,0,0);
		(*visualData.getItem(10)).setMaterialsForTriangle(1,0,0,0);

		connections.addItem(Connections(4));

		Vertex reference = *visualData[10].getVertex(0);

		reference *= Vertex(0.8f,1.0f,0.9f);
		addMountingPoint(2,reference,Vertex(0.0f,1.0f,0.0f));

		reference *= Vertex(-1.0f,1.0f,1.0f);
		addMountingPoint(2,reference,Vertex(0.0f,1.0f,0.0f));

		reference *= Vertex(1.0f,1.0f,-1.0f);
		addMountingPoint(2,reference,Vertex(0.0f,1.0f,0.0f));

		reference *= Vertex(-1.0f,1.0f,1.0f);
		addMountingPoint(2,reference,Vertex(0.0f,1.0f,0.0f));
		
		//--------------------------------------------------------------------------
		// Setup Lower Sides
		//--------------------------------------------------------------------------
		temp = *(*visualData.getItem(8)).getVertex(3);
		(*visualData.getItem(11)).addVertex(temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(11)).addVertex(temp.getX(),temp.getY(),-temp.getZ());
		(*visualData.getItem(11)).addNormal(0.0f,1.0f,0.0f);

		temp = *(*visualData.getItem(8)).getVertex(5);
		(*visualData.getItem(11)).addVertex(temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(11)).addVertex(temp.getX(),temp.getY(),-temp.getZ());

		(*visualData.getItem(11)).addVisualTriangle(0,2,1,0,0,0);
		(*visualData.getItem(11)).setMaterialsForTriangle(0,0,0,0);
		(*(*visualData.getItem(11)).getVisualTriangle(0)).generateNormal();

		(*visualData.getItem(11)).addVisualTriangle(2,3,1,0,0,0);
		(*visualData.getItem(11)).setMaterialsForTriangle(1,0,0,0);

		(*visualData.getItem(12)) = (*visualData.getItem(11));
		(*visualData.getItem(12)).rotateY(180.0f * DEGREES_TO_RAD);

		//--------------------------------------------------------------------------
		// Setup Bottom
		//--------------------------------------------------------------------------
		temp = *(*visualData.getItem(8)).getVertex(5);
		(*visualData.getItem(13)).addVertex(temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(13)).addVertex(temp.getX(),temp.getY(),-temp.getZ());

		(*visualData.getItem(13)).addVertex(-temp.getX(),temp.getY(),-temp.getZ());
		(*visualData.getItem(13)).addVertex(-temp.getX(),temp.getY(),temp.getZ());
		(*visualData.getItem(13)).addNormal(0.0f,-1.0f,0.0f);

		(*visualData.getItem(13)).addVisualTriangle(0,2,1,0,0,0);
		(*visualData.getItem(13)).setMaterialsForTriangle(0,0,0,0);

		(*visualData.getItem(13)).addVisualTriangle(0,3,2,0,0,0);
		(*visualData.getItem(13)).setMaterialsForTriangle(1,0,0,0);
}
Square::Square(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material) : GameObject(dispx,dispy,dispz,1,10)
 {

	 addVisualData(0.0f,0.0f,0.0f,4,1,2,1);
	 (*visualData.getItem(0)).addMaterial(*material);

	 GLfloat PointFive = 0.5f * Scale;
	 GLfloat NegPointFive = -0.5f * Scale;

	 //Setup Verticies
	 ADD_VERTEX(NegPointFive, 0.0f, PointFive);
	 ADD_VERTEX(PointFive, 0.0f, PointFive);
	 ADD_VERTEX(PointFive, 0.0f, NegPointFive);
	 ADD_VERTEX(NegPointFive,0.0f, NegPointFive);
	 ADD_NORMAL(0.0f,1.0f,0.0f); //up
	  
	 ADD_TRIANGLE(0,1,2,0,0,0);
	 (*visualData.getItem(0)).setMaterialsForTriangle(0,0,0,0);
	 ADD_TRIANGLE(0,2,3,0,0,0);
	 (*visualData.getItem(0)).setMaterialsForTriangle(1,0,0,0);
 }
void Square::setupPhysData(GLfloat Scale)
{
	 physicsData.resetPhysHulls(1);
	 physicsData.addPhysicsHull(TriangleMesh);
	 HULL_ZERO.resetTriangles(2);
	 HULL_ZERO.resetVerticies(4);
	 GLfloat NegPointFive = Scale * -0.5f;
	 GLfloat PointFive = Scale * 0.5f;
	 HULL_ZERO.addVertex(NegPointFive, 0.0f, PointFive);
	 HULL_ZERO.addVertex(PointFive, 0.0f, PointFive);
	 HULL_ZERO.addVertex(PointFive, 0.0f, NegPointFive);
	 HULL_ZERO.addVertex(NegPointFive,0.0f, NegPointFive);

	 HULL_ZERO.addTriangle(0,1,2);
	 HULL_ZERO.addTriangle(0,2,3);
}
Cube::Cube(Vertex* Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material) : MechanicalObject(Vertex(dispx,dispy,dispz),1,10,1)
 {
	 addVisualData(0.0f,0.0f,0.0f,8,6,12,1);
	 (*visualData.getItem(0)).addMaterial(*material);

	 //----------------------------------------------
	 //    Setup Scaling For Each Axis
	 //----------------------------------------------
	 
	 GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat NegPointFiveX = -0.5f * SCALE_X;

	 GLfloat PointFiveY = 0.5f * SCALE_Y;
	 GLfloat NegPointFiveY = -0.5f * SCALE_Y;

	 GLfloat PointFiveZ = 0.5f * SCALE_Z;
	 GLfloat NegPointFiveZ = -0.5f * SCALE_Z;

	 connections.addItem(Connections(1));
	 addMountingPoint(0,Vertex(0.0f,PointFiveY,0.0f),Vertex(0.0f,1.0f,0.0f));

	 //----------------------------------------------
	 //    Setup Verticies
	 //----------------------------------------------
	 ADD_VERTEX(NegPointFiveX, NegPointFiveY, PointFiveZ);
	 ADD_VERTEX(PointFiveX, NegPointFiveY, PointFiveZ);
	 ADD_VERTEX(NegPointFiveX, PointFiveY, PointFiveZ);
	 ADD_VERTEX(PointFiveX,PointFiveY,PointFiveZ);

	 ADD_VERTEX(NegPointFiveX, NegPointFiveY, NegPointFiveZ);
	 ADD_VERTEX(PointFiveX, NegPointFiveY, NegPointFiveZ);
	 ADD_VERTEX(NegPointFiveX, PointFiveY, NegPointFiveZ);
	 ADD_VERTEX(PointFiveX,PointFiveY,NegPointFiveZ);

	 //----------------------------------------------
	 //    Setup Normals
	 //----------------------------------------------
	 ADD_NORMAL(0.0f,0.0f,1.0f);  //Front
	 ADD_NORMAL(0.0f,0.0f,-1.0f); //Back
	 ADD_NORMAL(1.0f,0.0f,0.0f);  //Right
	 ADD_NORMAL(-1.0f,0.0f,0.0f); //Left
	 ADD_NORMAL(0.0f,1.0f,0.0f);  //Top
	 ADD_NORMAL(0.0f,-1.0f,0.0f); //Bottom

	 //----------------------------------------------
	 //    Add Triangles To Object
	 //----------------------------------------------

	  //Front Side 
	  ADD_TRIANGLE(0,1,2,0,0,0);
	  (*visualData.getItem(0)).setMaterialsForTriangle(0,0,0,0);
	  ADD_TRIANGLE(1,3,2,0,0,0);
	  (*visualData.getItem(0)).setMaterialsForTriangle(1,0,0,0);

	  //Back Side 
	  ADD_TRIANGLE(6,5,4,1,1,1);
	  (*visualData.getItem(0)).setMaterialsForTriangle(2,0,0,0);
	  ADD_TRIANGLE(6,7,5,1,1,1);
	  (*visualData.getItem(0)).setMaterialsForTriangle(3,0,0,0);
	  
	  //Right Side
	  ADD_TRIANGLE(1,5,3,2,2,2);
	  (*visualData.getItem(0)).setMaterialsForTriangle(4,0,0,0);
	  ADD_TRIANGLE(5,7,3,2,2,2);
	  (*visualData.getItem(0)).setMaterialsForTriangle(5,0,0,0);
	  
	  //Left Side
	  ADD_TRIANGLE(4,0,2,3,3,3);
	  (*visualData.getItem(0)).setMaterialsForTriangle(6,0,0,0);
	  ADD_TRIANGLE(4,2,6,3,3,3);
	 (*visualData.getItem(0)).setMaterialsForTriangle(7,0,0,0);

	  // Top
	  ADD_TRIANGLE(2,3,7,4,4,4);
	  (*visualData.getItem(0)).setMaterialsForTriangle(8,0,0,0);
	  ADD_TRIANGLE(2,7,6,4,4,4);
	 (*visualData.getItem(0)).setMaterialsForTriangle(9,0,0,0);
	  
	  // Bottom
	  ADD_TRIANGLE(5,1,0,5,5,5);
	  (*visualData.getItem(0)).setMaterialsForTriangle(10,0,0,0);
	  ADD_TRIANGLE(4,5,0,5,5,5);
	  (*visualData.getItem(0)).setMaterialsForTriangle(11,0,0,0);
 }
void Cube::setupPhysData(Vertex* Scale)
 {
	 physicsData.resetPhysHulls(1);
	 physicsData.addPhysicsHull(TriangleMesh);
	 HULL_ZERO.resetTriangles(12);
	 HULL_ZERO.resetVerticies(8);

	 //----------------------------------------------
	 //    Setup Scaling For Each Axis
	 //----------------------------------------------
	 GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat NegPointFiveX = -0.5f * SCALE_X;

	 GLfloat PointFiveY = 0.5f * SCALE_Y;
	 GLfloat NegPointFiveY = -0.5f * SCALE_Y;

	 GLfloat PointFiveZ = 0.5f * SCALE_Z;
	 GLfloat NegPointFiveZ = -0.5f * SCALE_Z;

	 //----------------------------------------------
	 //    Setup Verticies
	 //----------------------------------------------
	 HULL_ZERO.addVertex(NegPointFiveX, NegPointFiveY, PointFiveZ);
	 HULL_ZERO.addVertex(PointFiveX, NegPointFiveY, PointFiveZ);
	 HULL_ZERO.addVertex(NegPointFiveX, PointFiveY, PointFiveZ);
	 HULL_ZERO.addVertex(PointFiveX,PointFiveY,PointFiveZ);

	 HULL_ZERO.addVertex(NegPointFiveX, NegPointFiveY, NegPointFiveZ);
	 HULL_ZERO.addVertex(PointFiveX, NegPointFiveY, NegPointFiveZ);
	 HULL_ZERO.addVertex(NegPointFiveX, PointFiveY, NegPointFiveZ);
	 HULL_ZERO.addVertex(PointFiveX,PointFiveY,NegPointFiveZ);

	 //----------------------------------------------
	 //    Add Triangles To Object
	 //----------------------------------------------

	  //Front Side 
	  HULL_ZERO.addTriangle(0,1,2);
	  HULL_ZERO.addTriangle(1,3,2);

	  //Back Side 
	  HULL_ZERO.addTriangle(6,5,4);
	  HULL_ZERO.addTriangle(6,7,5);
	  
	  //Right Side
	  HULL_ZERO.addTriangle(1,5,3);
	  HULL_ZERO.addTriangle(5,7,3);
	  
	  //Left Side
	  HULL_ZERO.addTriangle(4,0,2);
	  HULL_ZERO.addTriangle(4,2,6);

	  // Top
	  HULL_ZERO.addTriangle(2,3,7);
	  HULL_ZERO.addTriangle(2,7,6);
	  
	  // Bottom
	  HULL_ZERO.addTriangle(5,1,0);
	  HULL_ZERO.addTriangle(4,5,0);
 }
Cylinder::Cylinder(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor) : GameObject(dispx,dispy,dispz,1,10)
{	  
	//    Check that sides in range and an even number
	sides = checkSides(sides);

	addVisualData(0.0f,0.0f,0.0f,2 + (2 * sides),2 + sides,4 * sides,1);
	visualData[0].addMaterial(*TriColor);
	 //----------------------------------------------
	 //    Setup For Scaling
	 //----------------------------------------------
     GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat PointFiveY = 0.5f * SCALE_Y;
	 GLfloat NegPointFiveY = -0.5f * SCALE_Y;
	 GLfloat PointFiveZ = 0.5f * SCALE_Z;
	 
	 //----------------------------------------------
	 //    Setup Verticies
	 //----------------------------------------------
	 GLfloat angle = 0.0f;
	 int next = sides + 1;
	 GLfloat increment = 360.0f / (float) sides;
	 

	 //setup centres and normals for top and bottom 
	 ADD_VERTEX(0.0f,PointFiveY,0.0f);
	 ADD_NORMAL(0.0f,1.0f,0.0f);
	 visualData[0].setNoVerticies(2 + 2 * sides);
	 SET_VIS_VERTEX(next) = Vertex(0.0f,NegPointFiveY,0.0f);
	 ADD_NORMAL(0.0f,-1.0f,0.0f);
	 next++;
	 
	 GLfloat x = 0.0f;
	 GLfloat z = 0.0f;
	 //setup outer verticies and normals;
	 for(int i = 1; i <= sides; i++)
	 {  
		 x =  PointFiveX * cos(angle * DEGREES_TO_RAD);
		 z =  PointFiveZ * sin(angle * DEGREES_TO_RAD);
		  SET_VIS_VERTEX(i) = Vertex(x, PointFiveY, z);
		 ADD_NORMAL(x, 0.0f,z);
		 SET_VIS_VERTEX(next) = Vertex(x, NegPointFiveY, z);
		 angle += increment;
		 next++;
	 }
	 next = 2;

	 //----------------------------------------------
	 //    Create Triangles For Top and Bottom
	 //----------------------------------------------
	 for(int i = 1; i <= sides; i++)
	 {
		 if(next == sides + 1)
			 next = 1;
		 
		 ADD_TRIANGLE(0,next,i,0,0,0);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,0,0);
	     next++;
	 }
	 next = (2*sides);

	 for(int i = (2*sides) + 1; i > (sides + 1); i--)
	 {
		  if(next == sides + 1)
			 next = (2* sides + 1);
		 
		ADD_TRIANGLE(sides + 1,next,i,1,1,1);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,0,0);
	     next--;
	 }
	 
	 //----------------------------------------------
	 //    Create Normals For Sides And Add Triangles
	 //----------------------------------------------
	 next = sides + 2;
	 int count = 2;
	 for( int i = 1; i < sides; i++)
	 {
		 ADD_TRIANGLE(i,i+1,next,count,count + 1,count);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,0,0);
		 ADD_TRIANGLE(next,i+1,next+1,count,count + 1,count + 1);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,0,0);
		 next++;
		 count ++;
	 } 
	    ADD_TRIANGLE(sides,1,(2*sides) + 1,count,2,count);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,0,0);
	  	ADD_TRIANGLE((2*sides)+1,1,sides+ 2,count,2,2);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,0,0);

 }
Marker::Marker(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor) : GameObject(dispx,dispy,dispz,1,10)
{	  
	//    Check that sides in range and an even number
	sides = checkSides(sides);
	GLfloat not[4] = {0.0f,0.0f,0.0f,0.0f};
	GLfloat diff[4] = {1.0f,1.0f,1.0f,0.1f};
	diff[0] = (*TriColor).getDiffuse()[0];
	diff[1] = (*TriColor).getDiffuse()[1];
	diff[2] = (*TriColor).getDiffuse()[2];
	diff[3] = 0.0f;
	Material nothing = Material(diff,diff,not,0.0f);
	diff[3] = 1.0f;
	Material material = Material(diff,diff,not,0.0f);

	addVisualData(0.0f,0.0f,0.0f,2 + (2 * sides),2 + sides,2 * sides,2);
	visualData[0].addMaterial(material);
	visualData[0].addMaterial(nothing);
	 //----------------------------------------------
	 //    Setup For Scaling
	 //----------------------------------------------
     GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat PointFiveY = SCALE_Y;
	 GLfloat NegPointFiveY = 0.0f;
	 GLfloat PointFiveZ = 0.5f * SCALE_Z;
	 
	 //----------------------------------------------
	 //    Setup Verticies
	 //----------------------------------------------
	 GLfloat angle = 0.0f;
	 int next = sides + 1;
	 GLfloat increment = 360.0f / (float) sides;
	 

	 //setup centres and normals for top and bottom 
	 ADD_VERTEX(0.0f,PointFiveY,0.0f);
	 ADD_NORMAL(0.0f,1.0f,0.0f);
	 visualData[0].setNoVerticies(2 + 2 * sides);
	 SET_VIS_VERTEX(next) = Vertex(0.0f,NegPointFiveY,0.0f);
	 ADD_NORMAL(0.0f,-1.0f,0.0f);
	 next++;
	 
	 GLfloat x = 0.0f;
	 GLfloat z = 0.0f;
	 //setup outer verticies and normals;
	 for(int i = 1; i <= sides; i++)
	 {  
		 x =  PointFiveX * cos(angle * DEGREES_TO_RAD);
		 z =  PointFiveZ * sin(angle * DEGREES_TO_RAD);
		  SET_VIS_VERTEX(i) = Vertex(x, PointFiveY, z);
		 ADD_NORMAL(x, 0.0f,z);
		 SET_VIS_VERTEX(next) = Vertex(x, NegPointFiveY, z);
		 angle += increment;
		 next++;
	 }
	 next = 2;

	 
	 //----------------------------------------------
	 //    Create Normals For Sides And Add Triangles
	 //----------------------------------------------
	 next = sides + 2;
	 int count = 2;
	 for( int i = 1; i < sides; i++)
	 {
		 ADD_TRIANGLE(i,i+1,next,count,count + 1,count);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 1,1,0);
		 ADD_TRIANGLE(next,i+1,next+1,count,count + 1,count + 1);
		 visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,1,0);
		 next++;
		 count ++;
	 } 
	    ADD_TRIANGLE(sides,1,(2*sides) + 1,count,2,count);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 1,1,0);
	  	ADD_TRIANGLE((2*sides)+1,1,sides+ 2,count,2,2);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1, 0,1,0);

 }
IntakeManifold::IntakeManifold(GLfloat Scale,GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material) : MechanicalObject(Vertex(dispx,dispy,dispz),10,10,2)
{
	Scale /= 2.0f;
	addVisualData(0.0f,0.0f,0.0f,8,6,12,1);
	visualData[0].addMaterial(*material);

	Vertex temp = Vertex(1.79289317,0.707106769,4.0000) * Scale;
	visualData[0].addVertex(temp);
	
	temp *= Vertex(-1.0f,1.0f,1.0f);
	visualData[0].addVertex(temp);

	temp *= Vertex(1.0f,1.0f,-1.0f);
	visualData[0].addVertex(temp);

	temp*= Vertex(-1.0f,1.0f,1.0f);
	visualData[0].addVertex(temp);

	//bottom
	visualData[0].addNormal(0.0f,-1.0f,0.0f);
	visualData[0].addVisualTriangle(1,2,0,0,0,0);
	visualData[0].setMaterialsForTriangle(0,0,0,0);
	visualData[0].addVisualTriangle(0,2,3,0,0,0);
	visualData[0].setMaterialsForTriangle(1,0,0,0);

	
	temp = Vertex(2.64142132,1.27279222,3.59999990) * Scale;
	visualData[0].addVertex(temp);

	temp *= Vertex(-1.0f,1.0f,1.0f);
	visualData[0].addVertex(temp);
	
	temp *= Vertex(1.0f,1.0f,-1.0f);
	visualData[0].addVertex(temp);

	temp *= Vertex(-1.0f,1.0f,1.0f);
	visualData[0].addVertex(temp);

	for(int i = 0; i < 3; i++)
	{
		visualData[0].addNormal(0.0f,-1.0f,0.0f);
		visualData[0].addVisualTriangle(1 + i,0 + i,4 + i,1 + i,1 + i,1 + i);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
		(*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();

		visualData[0].addVisualTriangle(1 + i,4 + i,5 + i,1 + i,1 +i ,1 + i);
		visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
	}

	visualData[0].addNormal(0.0f,-1.0f,0.0f);
	visualData[0].addVisualTriangle(0,3,7,4,4,4);
	visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
	(*visualData[0].getVisualTriangle(visualData[0].getNoTriangles() - 1)).generateNormal();

	visualData[0].addVisualTriangle(0,7,4,4,4 ,4);
	visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

	visualData[0].addNormal(0.0f,1.0f,0.0f);
	visualData[0].addVisualTriangle(4,6,5,5,5,5);
	visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);

	visualData[0].addVisualTriangle(4,7,6,5,5,5);
	visualData[0].setMaterialsForTriangle(visualData[0].getNoTriangles() - 1,0,0,0);
	//-----------------------------------------------------------
	// Add bottom mounting points
	//-----------------------------------------------------------
	connections.addItem(Connections(4));
	Vertex mountTemp = Vertex(1.79289317,0.707106769,4.0000) * Scale;

	mountTemp *= Vertex(0.8f,1.0f,0.9f);
	addMountingPoint(0,mountTemp,(Vertex(0.0f,-1.0f,0.0f)));

	mountTemp *= Vertex(-1.0f,1.0f,1.0f);
	addMountingPoint(0,mountTemp,(Vertex(0.0f,-1.0f,0.0f)));

	mountTemp *= Vertex(1.0f,1.0f,-1.0f);
	addMountingPoint(0,mountTemp,(Vertex(0.0f,-1.0f,0.0f)));

	mountTemp *= Vertex(-1.0f,1.0f,1.0f);
	addMountingPoint(0,mountTemp,(Vertex(0.0f,-1.0f,0.0f)));

	//-----------------------------------------------------------
	// Add Top mounting points
	//-----------------------------------------------------------
	connections.addItem(Connections(4));
	mountTemp = Vertex(2.64142132,1.27279222,3.59999990) * Scale;;
	mountTemp *= Vertex(1.0f /2.64142132f,1.0f,1.0f / 3.59999990f);
	mountTemp *= Vertex(Scale,1.0f,Scale);

	addMountingPoint(1,mountTemp,Vertex(0.0f,1.0f,0.0f));

	mountTemp *= Vertex(-1.0f,1.0f,1.0f);
	addMountingPoint(1,mountTemp,(Vertex(0.0f,1.0f,0.0f)));

	mountTemp *= Vertex(1.0f,1.0f,-1.0f);
	addMountingPoint(1,mountTemp,(Vertex(0.0f,1.0f,0.0f)));

	mountTemp *= Vertex(-1.0f,1.0f,1.0f);
	addMountingPoint(1,mountTemp,(Vertex(0.0f,1.0f,0.0f)));


}
void IntakeManifold::setupCorrectMountingPoints(EngineBlock* engineBlock)
{
	for(int i = 0; i < 4; i++)
	{
		(*engineBlock).setCorrectMount(i,2,getMountingPointPtr(i,0));
		setCorrectMount(i,0,(*engineBlock).getMountingPointPtr(i,2));
	}                                   
}
ThrottleBody::ThrottleBody(GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* material) : MechanicalObject(Vertex(dispx,dispy,dispz),10,10,1)
{
	addVisualData(0.0f,0.0f,0.0f,8,6,12,1);
	addVisualData(0.0f,0.0f,0.0f,8,6,12,1);
	visualData[0].addMaterial(*material);

	Scale /= 2.0f;
	//-----------------------------------------------------------
	// Add mounting points
	//-----------------------------------------------------------
	connections.addItem(Connections(4));
	Vertex mountTemp = Vertex(2.64142132,-0.125f,3.59999990) * Scale;;
	mountTemp *= Vertex(1.0f /2.64142132f,1.0f,1.0f / 3.59999990f);
	mountTemp *= Vertex(Scale,1.0f,Scale);

	addMountingPoint(0,mountTemp,Vertex(0.0f,-1.0f,0.0f));

	mountTemp *= Vertex(-1.0f,1.0f,1.0f);
	addMountingPoint(0,mountTemp,(Vertex(0.0f,-1.0f,0.0f)));

	mountTemp *= Vertex(1.0f,1.0f,-1.0f);
	addMountingPoint(0,mountTemp,(Vertex(0.0f,-1.0f,0.0f)));

	mountTemp *= Vertex(-1.0f,1.0f,1.0f);
	addMountingPoint(0,mountTemp,(Vertex(0.0f,-1.0f,0.0f)));

	Scale *= 2.5f;
	Vertex temp = Vertex(Scale,Scale /8.0f,Scale);
	Cube tSquare = Cube(&temp,0.0f,0.0f,0.0f,material);

	visualData[0] = *tSquare.getVisualData(0);
	temp = Vertex(Scale / 2.0f, Scale, Scale / 2.0f);
	Cylinder tCyl = Cylinder(32,&temp,0.0f,0.0f,0.0f,material);
	tCyl.rotateZ(-90.0f * DEGREES_TO_RAD);

	visualData[1] = *tCyl.getVisualData(0);
	visualData[1].adjustPosition(0.0f,Scale/4.0f,0.0f);

}
void ThrottleBody::setupCorrectMountingPoints(IntakeManifold* intakeManifold)
{
	for(int i = 0; i < 4; i++)
	{
		(*intakeManifold).setCorrectMount(i,1,getMountingPointPtr(i,0));
		setCorrectMount(i,0,(*intakeManifold).getMountingPointPtr(i,1));
	}   
}
/*
 SquarePyramid::SquarePyramid(Vertex* Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* TriColor) : GameObject(dispx,dispy,dispz)
 {
	 (*visualData).resetVisualMeshSize(6);
	(*visualData).resetVisualVerticies(5);
	 (*visualData).resetNormals(5);
	 //----------------------------------------------
	 //    Setup For Scaling
	 //----------------------------------------------
	 GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat NegPointFiveX = -0.5f * SCALE_X ;
	 GLfloat PointFiveY = 0.5f * SCALE_Y;
	 GLfloat NegPointFiveY = -0.5f * SCALE_Y;
	 GLfloat PointFiveZ = 0.5f * SCALE_Z;
	 GLfloat NegPointFiveZ = -0.5f * SCALE_Z;

	 //----------------------------------------------
	 //    Setup Verticies
	 //----------------------------------------------
	 ADD_VERTEX(NegPointFiveX, NegPointFiveY, PointFiveZ);
	 ADD_VERTEX(PointFiveX, NegPointFiveY, PointFiveZ);
	 ADD_VERTEX(PointFiveX, NegPointFiveY, NegPointFiveZ);
	 ADD_VERTEX(NegPointFiveX,NegPointFiveY,NegPointFiveZ);
	 ADD_VERTEX(0.0f, PointFiveY, 0.0f);// tip
	  
	 //---------------------------------------------
	 //    Add Triangles To Object
	 //---------------------------------------------
	 ADD_TRIANGLE(VIS_VERTEX(0),VIS_VERTEX(1),VIS_VERTEX(4),NORMAL(0),TriColor);//front
	 ADD_TRIANGLE(VIS_VERTEX(1),VIS_VERTEX(2),VIS_VERTEX(4),NORMAL(1),TriColor);//right
	 ADD_TRIANGLE(VIS_VERTEX(2),VIS_VERTEX(3),VIS_VERTEX(4),NORMAL(2),TriColor);//back
	 ADD_TRIANGLE(VIS_VERTEX(3),VIS_VERTEX(0),VIS_VERTEX(4),NORMAL(3),TriColor);//left
	 (*visualData).setNoNormals(4);

	 ADD_NORMAL(0.0f,-1.0f,0.0f);
	 //Bottom
	 ADD_TRIANGLE(VIS_VERTEX(0),VIS_VERTEX(2),VIS_VERTEX(1),NORMAL(4),TriColor);
	 ADD_TRIANGLE(VIS_VERTEX(0),VIS_VERTEX(3),VIS_VERTEX(2),NORMAL(4),TriColor);
 } 
 Circle::Circle(int sides, GLfloat Scale, GLfloat dispx, GLfloat dispy, GLfloat dispz, Material* TriColor) : GameObject(dispx,dispy,dispz)
 {
	//Check that sides in range and an even number
	sides = checkSides(sides);

	(*visualData).resetVisualMeshSize(sides);
	(*visualData).resetVisualVerticies(sides + 1);
	(*visualData).resetNormals(1);

	 //----------------------------------------------
	 //    Setup Verticies for Circle
	 //----------------------------------------------
	 GLfloat radius = 0.5f * Scale;
	 GLfloat angle = 0.0f;
	 GLfloat increment = 360.0f / (float) sides;
	 ADD_VERTEX(0.0f,0.0f,0.0f);
	 ADD_NORMAL(0.0f,1.0f,0.0f);

	 for(int i = 0; i < sides; i++)
	 {
		 ADD_VERTEX( radius * cos(angle * DEGREES_TO_RAD), 0.0f, radius * sin(angle * DEGREES_TO_RAD));
		 angle += increment;
	 }

	 //----------------------------------------------
	 //    Setup Triangles for Circle
	 //----------------------------------------------
	 int next = 2;
	 for(int i = 1; i <= sides; i++)
	 {
		 if(next == sides + 1)
			 next = 1;
		 
		 ADD_TRIANGLE(VIS_VERTEX(0),VIS_VERTEX(next),VIS_VERTEX(i),NORMAL(0),NORMAL(0),NORMAL(0),TriColor);
	     next++;
	 }
 }
 Cylinder::Cylinder(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor) : GameObject(dispx,dispy,dispz)
{	  
	//    Check that sides in range and an even number
	sides = checkSides(sides);

	(*visualData).resetVisualMeshSize(4 * sides);
	(*visualData).resetVisualVerticies(2 + (2 * sides));
	(*visualData).resetNormals(2 + sides);
	 //----------------------------------------------
	 //    Setup For Scaling
	 //----------------------------------------------
     GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat PointFiveY = 0.5f * SCALE_Y;
	 GLfloat NegPointFiveY = -0.5f * SCALE_Y;
	 GLfloat PointFiveZ = 0.5f * SCALE_Z;
	 
	 //----------------------------------------------
	 //    Setup Verticies
	 //----------------------------------------------
	 GLfloat angle = 0.0f;
	 int next = sides + 1;
	 GLfloat increment = 360.0f / (float) sides;
	 

	 //setup centres and normals for top and bottom 
	 ADD_VERTEX(0.0f,PointFiveY,0.0f);
	 ADD_NORMAL(0.0f,1.0f,0.0f);
	 SET_VIS_VERTEX(next) = Vertex(0.0f,NegPointFiveY,0.0f);
	 ADD_NORMAL(0.0f,-1.0f,0.0f);
	 next++;
	 
	 GLfloat x = 0.0f;
	 GLfloat z = 0.0f;
	 //setup outer verticies and normals;
	 for(int i = 1; i <= sides; i++)
	 {  
		 x =  PointFiveX * cos(angle * DEGREES_TO_RAD);
		 z =  PointFiveZ * sin(angle * DEGREES_TO_RAD);
		 ADD_VERTEX(x, PointFiveY, z);
		 ADD_NORMAL(x, 0.0f,z);
		 SET_VIS_VERTEX(next) = Vertex(x, NegPointFiveY, z);
		 angle += increment;
		 next++;
	 }
	 next = 2;

	 (*visualData).setNoVerticies(2 + 2 * sides);

	 //----------------------------------------------
	 //    Create Triangles For Top and Bottom
	 //----------------------------------------------
	 for(int i = 1; i <= sides; i++)
	 {
		 if(next == sides + 1)
			 next = 1;
		 
		 ADD_TRIANGLE(VIS_VERTEX(0),VIS_VERTEX(next),VIS_VERTEX(i),NORMAL(0),NORMAL(0),NORMAL(0),TriColor);
	     next++;
	 }
	 next = (2*sides);

	 for(int i = (2*sides) + 1; i > (sides + 1); i--)
	 {
		  if(next == sides + 1)
			 next = (2* sides + 1);
		 
		ADD_TRIANGLE(VIS_VERTEX(sides + 1),VIS_VERTEX(next),VIS_VERTEX(i),NORMAL(1),NORMAL(1),NORMAL(1),TriColor);
	     next--;
	 }
	 
	 //----------------------------------------------
	 //    Create Normals For Sides And Add Triangles
	 //----------------------------------------------
	 next = sides + 2;
	 int count = 2;
	 for( int i = 1; i < sides; i++)
	 {
		 ADD_TRIANGLE(VIS_VERTEX(i),VIS_VERTEX(i+1),VIS_VERTEX(next),NORMAL(count),NORMAL(count + 1),NORMAL(count),TriColor);
		ADD_TRIANGLE(VIS_VERTEX(next),VIS_VERTEX(i+1),VIS_VERTEX(next+1),NORMAL(count),NORMAL(count + 1),NORMAL(count + 1),TriColor);
		 next++;
		 count ++;
	 } 
	    ADD_TRIANGLE(VIS_VERTEX(sides),VIS_VERTEX(1),VIS_VERTEX((2*sides) + 1),NORMAL(count),NORMAL(2),NORMAL(count),TriColor);
	  	ADD_TRIANGLE(VIS_VERTEX((2*sides)+1),VIS_VERTEX(1),VIS_VERTEX(sides+ 2),NORMAL(count),NORMAL(2),NORMAL(2),TriColor);

 }
 Sphere::Sphere(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor) : GameObject(dispx,dispy,dispz)
 {
	// Make Sure Sides In range and an Even Number
	sides = checkSides(sides);

	(*visualData).resetVisualMeshSize(2 * sides * sides);

	 //----------------------------------------------
	 //    Setup For Scaling
	 //----------------------------------------------
     GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat PointFiveY = 0.5f * SCALE_Y;
	 GLfloat PointFiveZ = 0.5f * SCALE_Z;

	  //----------------------------------------------
	 //    Setup Verticies
	 //----------------------------------------------
	 int size = (sides / 2) -1;
	 int totalsize = 2 + ((2*(size +1)) * size);

	 (*visualData).resetVisualVerticies(totalsize);
	 (*visualData).resetNormals(totalsize);
	 GLfloat increment = 360.0f / (float) sides;
	 GLfloat angle = increment;
	 GLfloat angley = 0.0f;

	 ADD_VERTEX(0.0f,PointFiveY,0.0f);
	 ADD_VERTEX(0.0f,-PointFiveY,0.0f);
	 ADD_NORMAL(0.0f,1.0f,0.0f);
	 ADD_NORMAL(0.0f,-1.0f,0.0f);
	 GLfloat x = 0.0f;
	 GLfloat y = 0.0f;
	 GLfloat z = 0.0f;
	 int position = 2;
	
	 
	 for(int i = 0; i < (2*(size+1)); i++)
	 {
		 angle = increment;
		 for(int b = 0; b < size; b++)
		 {
			 x = PointFiveX * sin(angle * DEGREES_TO_RAD) ;
			 x *= cos(angley * DEGREES_TO_RAD);
			 y = PointFiveY * cos(angle* DEGREES_TO_RAD);
			 z = PointFiveZ * sin(angle * DEGREES_TO_RAD);
			 z *= sin(angley *DEGREES_TO_RAD); 
			 SET_VIS_VERTEX(position) = Vertex(x,y,z);
			 *NORMAL(position) = Vertex(x,y,z);
			 angle += increment;
			 position++;
		 }
		 angley+=increment;
	 }

	 (*visualData).setNoNormals(totalsize);
	(*visualData).setNoVerticies(totalsize);

	 //----------------------------------------------
	 //    Add Triangles
	 //----------------------------------------------
	 position = 2;
      #define LEFT position + size
      #define ABOVE position - 1
      #define ABOVE_RIGHT position - size - 1
	  int aboveRight = totalsize - size;
	     
	 ADD_TRIANGLE(VIS_VERTEX(LEFT), VIS_VERTEX(position), VIS_VERTEX(0),NORMAL(LEFT), NORMAL(position), NORMAL(0),TriColor);
	 position++;
     for(int b = 0; b <= (size - 2) ; b++)
	 {
			 ADD_TRIANGLE(VIS_VERTEX(LEFT),VIS_VERTEX(position), VIS_VERTEX(ABOVE),NORMAL(LEFT), NORMAL(position), NORMAL(ABOVE),TriColor);
			 ADD_TRIANGLE(VIS_VERTEX(position), VIS_VERTEX(aboveRight), VIS_VERTEX(ABOVE),NORMAL(position), NORMAL(aboveRight), NORMAL(ABOVE),TriColor);
			 position++;
			 aboveRight++;
     }
	 position--;
	 ADD_TRIANGLE(VIS_VERTEX(LEFT), VIS_VERTEX(1), VIS_VERTEX(position),NORMAL(LEFT), NORMAL(1), NORMAL(position),TriColor);
	 position++;
    
	int count = (2 * size);
	 for(int i = 0; i < count; i++)
	 {
		 ADD_TRIANGLE(VIS_VERTEX(LEFT), VIS_VERTEX(position), VIS_VERTEX(0),NORMAL(LEFT), NORMAL(position), NORMAL(0),TriColor);
		 position++;
		 for(int b = 0; b <= (size - 2) ; b++)
		 {
			 ADD_TRIANGLE(VIS_VERTEX(LEFT), VIS_VERTEX(position), VIS_VERTEX(ABOVE),NORMAL(LEFT), NORMAL(position), NORMAL(ABOVE),TriColor);
			 ADD_TRIANGLE(VIS_VERTEX(position), VIS_VERTEX(ABOVE_RIGHT), VIS_VERTEX(ABOVE),NORMAL(position), NORMAL(ABOVE_RIGHT), NORMAL(ABOVE),TriColor);
			 position++;
		 }
		 position--;
		 ADD_TRIANGLE(VIS_VERTEX(LEFT),VIS_VERTEX(1), VIS_VERTEX(position),NORMAL(LEFT), NORMAL(1), NORMAL(position),TriColor);
		 position++;
	 }
	 
	 int left = 2;
	 ADD_TRIANGLE(VIS_VERTEX(left), VIS_VERTEX(position), VIS_VERTEX(0),NORMAL(left), NORMAL(position), NORMAL(0),TriColor);
	 position++;
	 left++;
	 
     for(int b = 0; b <= (size - 2) ; b++)
	 {
			 ADD_TRIANGLE(VIS_VERTEX(left), VIS_VERTEX(position), VIS_VERTEX(ABOVE),NORMAL(left), NORMAL(position), NORMAL(ABOVE),TriColor);
			 ADD_TRIANGLE(VIS_VERTEX(position), VIS_VERTEX(ABOVE_RIGHT), VIS_VERTEX(ABOVE),NORMAL(position), NORMAL(ABOVE_RIGHT), NORMAL(ABOVE),TriColor);
			 position++;
			 left++;
     }
	 position--;
	 left--;
	 ADD_TRIANGLE(VIS_VERTEX(left), VIS_VERTEX(1), VIS_VERTEX(position),NORMAL(left), NORMAL(1), NORMAL(position),TriColor);
}
 Cone::Cone(int sides,Vertex* Scale,GLfloat dispx,GLfloat dispy ,GLfloat dispz,Material* TriColor): GameObject(dispx,dispy,dispz)
 {
	 // Make Sure Sides In range and an Even Number
	 sides = checkSides(sides);

	 (*visualData).resetVisualMeshSize(2 * sides);
	 //----------------------------------------------
	 //    Setup For Scaling
	 //----------------------------------------------
     GLfloat PointFiveX = 0.5f * SCALE_X;
	 GLfloat PointFiveY = 0.5f * SCALE_Y;
	 GLfloat NegPointFiveY = -0.5f * SCALE_Y;
	 GLfloat PointFiveZ = 0.5f * SCALE_Z;
	 
	  //----------------------------------------------
	 //    Setup Vertecies for Circle
	 //----------------------------------------------
     int numverts = 2 + sides;
	 (*visualData).resetVisualVerticies(numverts);
	 (*visualData).resetNormals((3 * sides) + 1);

	 ADD_VERTEX(0.0f,PointFiveY,0.0f);
	 ADD_VERTEX(0.0f,NegPointFiveY,0.0f);
	 ADD_NORMAL(0.0f,-1.0f,0.0f);

	 //-----------------------------------------------------
	 // Setup Verticies for Base
	 //-----------------------------------------------------
	 GLfloat angle = 0.0f;
	 GLfloat increment = 360.0f / (float) sides;
	 for(int i = 0; i < sides; i++)
	 {
		 ADD_VERTEX( PointFiveX * cos(angle * DEGREES_TO_RAD), NegPointFiveY, PointFiveZ * sin(angle * DEGREES_TO_RAD));
		 angle += increment;
	 }

	 //-----------------------------------------------------
	 // Setup Triangles for Base
	 //-----------------------------------------------------
	 int next = 3;
	 for(int i = 2; i <= (sides+1); i++)
	 {
		 if(next == sides + 2)
			 next = 2;
		 
		 ADD_TRIANGLE(VIS_VERTEX(1),VIS_VERTEX(i),VIS_VERTEX(next),NORMAL(0),TriColor);
	     next++;
	 }
	 
	 next = 3;
	 //----------------------------------------------------
	 // Setup Triangles and normals for sides
	 //----------------------------------------------------
	 int count = 1;
	 Vertex *one,*two,*three;
	 for(int i = 2; i <= (sides + 1); i++)
	 {
		
		if(next == sides + 2)
			 next = 2;

		one = VIS_VERTEX(i);
		two = VIS_VERTEX(0);
		three = VIS_VERTEX(next);

		 // Setup Normals for cone sides
		 Vertex temp1 = (*two) - (*one);
	     Vertex temp2 = (*two) - (*three);
	     temp2 = temp2.crossProduct(temp1);
		 temp2.normalize();
		 temp1 = temp2;
		 temp1.setX(0.0f);
		 temp1.setZ(0.0f);
		 *NORMAL(count) = temp1;
		 temp1 = temp2;
	   	 temp2.setX( (*one).getX());
		 temp2.setZ((*one).getZ());
		 temp1.setX( (*three).getX());
		 temp1.setZ((*three).getZ());
	     temp2.normalize();
	     temp1.normalize();

		 *NORMAL(count + 1) = temp2;
		 *NORMAL(count + 2) = temp1;
		 ADD_TRIANGLE(one,two,three,NORMAL(count+1),NORMAL(count),NORMAL(count+ 2),TriColor);
	     next++;
		 count +=3;
	 }
	 (*visualData).setNoNormals((3 * sides) + 1);
 }
 
  */