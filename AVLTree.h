#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "VaccinationData.h"
#include "AVLNode.h"
/* class AVL */

class AVLTree{//class of AVL Tree
private:
	AVLNode*	root;//root

public:
	
	AVLTree(){//constructor(first setting)
		root=NULL;
	}
	~AVLTree(){
	};//destructor
	bool		Insert(VaccinationData* pVac);//insert to AVL Tree from pVac(Vaccination node)
	VaccinationData*	Search(string name);//fucntion to search name from AVL Tree
	void GetVector(vector<VaccinationData*>& v);//make vector
};

#endif

