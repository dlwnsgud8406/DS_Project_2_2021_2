#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
class BpTreeIndexNode : public BpTreeNode{
private:
	map <string, BpTreeNode*> mapIndex;
	
public:
	BpTreeIndexNode(){}//constructor
	~BpTreeIndexNode() {}//destructor

	void insertIndexMap(string n, BpTreeNode* pN){//insert index map
		mapIndex.insert(map<string, BpTreeNode*>::value_type(n, pN));//inserting
	}

	void deleteMap(string n){//delete
		mapIndex.erase(n);//find node that has n and erase
	}

	map <string, BpTreeNode*>* getIndexMap(){return &mapIndex;}//return index map
};

#endif