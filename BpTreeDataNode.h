#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, VaccinationData*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;

public:
	BpTreeDataNode(){//constructor
	}
	~BpTreeDataNode(){//destructor
	}
	void setNext(BpTreeNode* pN){pNext = pN;}//setnextnode
	void setPrev(BpTreeNode* pN){pPrev = pN;}//setprevnode
	BpTreeNode* getNext(){return pNext;}//return nextnode
	BpTreeNode* getPrev(){return pPrev;}//return prevnode

	void insertDataMap(string n, VaccinationData* pN){//insert data map
		mapData.insert(map<string, VaccinationData*>::value_type(n,pN));//inserting
	}

	void deleteMap(string n){//delete
		mapData.erase(n);//find node that has n and erase
	}
	map<string, VaccinationData*> *getDataMap(){return &mapData;}//return data map
};

#endif