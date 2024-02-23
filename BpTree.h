#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeNode.h"
#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "VaccinationData.h"
// BpTree

class BpTree{
private:
	BpTreeNode*	root;
	int			order;		// m children

public:
	BpTree(int order = 3){//constructor(first setting)
		root = NULL;
		this->order = order;
	}
	~BpTree(){
		
	}
	bool		Insert(VaccinationData* newData); //insert node
	bool		exceedDataNode(BpTreeNode* pDataNode); // check exceeddatanode
	bool		exceedIndexNode(BpTreeNode* pIndexNode); //check exceedindexnode
	void		splitDataNode(BpTreeNode* pDataNode); //split datanode
	void		splitIndexNode(BpTreeNode* pIndexNode);//split indexnode
	BpTreeNode*	searchDataNode(string n); //search VaccinationData node
	bool	SearchRange(string start, string end);// search range and write log.txt
	void	Print(); // print all
	int count=0;
};

#endif
