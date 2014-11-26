#include "GameObject.h"

class Connections
{
	private:
		List<Vertex> mountingPoints, mountingNormals, mountingNormalPerps;
		List<Vertex*> correctMounts, currentMounts, currentMountsPerp, currentMountsNormal;

	public:
		Connections(int noPoints);
		Connections();

		//---------------------------------------
		// Get Methods
		//---------------------------------------
		Vertex getMountingPoint(int index){ return *mountingPoints.getItem(index);};
		Vertex* getMountingPointPtr(int index){ return mountingPoints.getItem(index);};
		List<Vertex>* getMountingPoints(){return &mountingPoints;};

		Vertex* getCurrentMount(int index){return *currentMounts.getItem(index);};
		Vertex* getCorrectMount(int index){return *correctMounts.getItem(index);};

		Vertex getMountingNormal(int index){ return *mountingNormals.getItem(index);};
		Vertex* getMountingNormalPtr(int index){ return mountingNormals.getItem(index);};

		Vertex getMountingNormalPerp(int index){ return *mountingNormalPerps.getItem(index);};
		Vertex* getMountingNormalPerpPtr(int index){ return mountingNormalPerps.getItem(index);};

		Vertex* getCurrentMountsPerp(int index){return *currentMountsPerp.getItem(index);};
		Vertex* getCurrentMountsNormal(int index){return *currentMountsNormal.getItem(index);};

		int getNoMountingPoints(){return mountingPoints.getNoItems();};
		//---------------------------------------
		// Set Methods
		//---------------------------------------
		void addMountingPoint(Vertex addition){mountingPoints.addItem(addition);};
		void addMountingNormal(Vertex addition){mountingNormals.addItem(addition);};
		void addMountingNormalPerp(Vertex addition){mountingNormalPerps.addItem(addition);};
		bool setCorrectMount(Vertex *addition, int index);
		bool setCurrentMount(Vertex *addition, int index);
		bool setCurrentMountsPerp(Vertex *addition, int index);
		bool setCurrentMountsNormal(Vertex* addition, int index);

		//----------------------------------------
		// Operators
		//----------------------------------------
		Connections& operator=(const Connections& rhs);


};