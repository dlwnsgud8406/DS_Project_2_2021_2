#pragma once
#include "VaccinationData.h"
class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;

public:
	BpTreeNode() {//constructor
	}
	~BpTreeNode() {//destructor
	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }//set most left child
	void setParent(BpTreeNode* pN) { pParent = pN; }//set parent

	BpTreeNode* getParent() { return pParent; }//return parent
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }//return mostleftchild

//---------------------------Virtual----------------------------------
	virtual void insertDataMap(string n, VaccinationData* pN) {} //insert data map
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}//insert index map
	virtual void deleteMap(string n) {}//delete map

	virtual map<string, BpTreeNode*>* getIndexMap() { map<string, BpTreeNode*> m; return &m; }//return indexmap
	virtual map<string, VaccinationData*> *getDataMap() { map<string, VaccinationData*> m; return &m; }//return datamap

	virtual void setNext(BpTreeNode* pN) {}//set next node
	virtual void setPrev(BpTreeNode* pN) {}//set prev node
	virtual BpTreeNode* getNext() { return NULL; }//return next node
	virtual BpTreeNode* getPrev() { return NULL; }//return prev node
};