#include "AVLTree.h"
bool AVLTree::Insert(VaccinationData* pVac){
    AVLNode* pNew=new AVLNode;
    pNew->setVacData(pVac);
    if(root==NULL)//special case:empty tree
    {
        root=pNew;
		//delete pNew;
		//pNew=NULL;
        return true;
    }
    //Phase 1: Locate insertion point for pVac
    AVLNode *a = root, //most recent node with bf =+-1
    *pa = NULL, //parent of a
    *p = root, //p moves through the tree
    *pp = NULL, //parent of p
    *rootSub = NULL;

    
	while (p != NULL)
	{
		if (p->getBF() != 0)
		{
			a = p;
			pa = pp;
		}
		if (p->getVacData()->GetUserName()>pNew->getVacData()->GetUserName())//take left branch
		{
			pp = p;
			p = p->getLeft();
		}
		else//take right branch
		{
			pp = p; p = p->getRight();
		}
	}
	//insert leftnode right node
	if (pNew->getVacData()->GetUserName()> pp->getVacData()->GetUserName())	//if new node name is bigger than name of pp pointer
		pp->setRight(pNew);	//insert as rightchild
	else
		pp->setLeft(pNew); //insert as leftchild

	//adjust balance factor of nodes on path from a to pp. By the definition
    //of a, all nodes on this path presently have a balacne facotr of 0. Their
    //balance factor will be +-1. d=+1 implies that k is inserted in the left
    //subtree of a. d=-1 implies that pVac is inserted in the right subtree of a
	int d;					//it is rotation
	AVLNode * b, *c;		//child of b,c

	if (pNew->getVacData()->GetUserName()> a->getVacData()->GetUserName())	//if new node go to right 
	{
		b = p = a->getRight();
		d = -1;		//it is bf
	}
	else			//if node is go to left
	{
		b = p = a->getLeft();
		d = 1;		//if if bf
	}

	while (p != pNew)
	{
		if (pNew->getVacData()->GetUserName()> p->getVacData()->GetUserName())
		{
			p->setBF(-1);
			p = p->getRight();//height of right increases by 1
		}
		else			
		{
			p->setBF(1);
			p = p->getLeft();//height of left increase by 1
		}
	}

	if (a->getBF() == 0 || a->getBF() + d == 0)//is AVLtree unbalanced?
	{//tree still balanced
		a->setBF(a->getBF() + d);
		return true;
	}

	if (d == 1)	//tree unbalanced, determine rotation type
	{	//left imbalance
		if (b->getBF() == 1)
		{	//rotation type LL
			a->setLeft(b->getRight());
			b->setRight(a); a->setBF(0); b->setBF(0);
			rootSub = b;	//b is the new root of the subtree
		}
		else
		{	//rotation type LR
			c = b->getRight();
			b->setRight(c->getLeft());
			a->setLeft(c->getRight());
			c->setLeft(b);
			c->setRight(a);
			switch (c->getBF())
			{
			case 0:
				b->setBF(0); a->setBF(0);
				break;
			case 1:
				b->setBF(0); a->setBF(-1);
				break;
			case -1:
				b->setBF(1); a->setBF(0);
				break;
			}
			c->setBF(0); rootSub = c;	//c is the new root of the subtree
		}	//end of LR
	}	//end of left imbalance

	else {	//right imbalance: this is symmetric to left imbalance
		if (b->getBF() == -1)
		{	//rototion type RR
			a->setRight(b->getLeft());
			b->setLeft(a); a->setBF(0); b->setBF(0);
			rootSub = b;	//b is the new root of the subtree
		}
		else
		{	//rotation type RL
			c = b->getLeft();
			b->setLeft(c->getRight());
			a->setRight(c->getLeft());
			c->setRight(b);
			c->setLeft(a);
			switch (c->getBF())
			{
			case 0:
				b->setBF(0); a->setBF(0);
				break;
			case 1:
				b->setBF(-1); a->setBF(0);
				break;
			case -1:
				b->setBF(0); a->setBF(1);
				break;
			}
			c->setBF(0); rootSub = c;	//c is the new root of the subtree
		}	//end of RL
	}	//end of right imbalance
	 //subtree with root b has been rebalanced
	if (pa == NULL)
		root = rootSub;
	else if (a == pa->getLeft())
		pa->setLeft(rootSub);
	else
		pa->setRight(rootSub);
	pNew->~AVLNode();
	return true; //good
}

void AVLTree::GetVector(vector<VaccinationData*>& v){
    queue<AVLNode*> q;
    AVLNode* currentNode = root; // visit root

    while (1)
	{
		while (currentNode)
		{
			q.push(currentNode);// push into queue
			currentNode = currentNode->getLeft();//	move to left
		}
        if (q.empty())//empty check
			break;
		currentNode = q.front();// front of queue
        v.push_back(currentNode->getVacData());
		q.pop();// pop from queue
		currentNode = currentNode->getRight();	// move to right
	}
}

VaccinationData* AVLTree::Search(string name){

    AVLNode* pCur = root;//pCur is AVL Tree root
    VaccinationData* pData=NULL;
	if (pCur == NULL)	// if pCur don't exist or don't exist name
		return pData;

	while (pCur->getVacData()->GetUserName()!= name)//search name	
	{
		if (pCur->getVacData()->GetUserName()> name&&(pCur->getLeft() && pCur->getRight()))	// if pCur Vacdata username is greater than name
			pCur = pCur->getLeft();	//	move to left
		else if (pCur->getVacData()->GetUserName()< name&&(pCur->getLeft() && pCur->getRight()))
			pCur = pCur->getRight();// move to right

		if (!pCur->getLeft() && !pCur->getRight()&& pCur->getVacData()->GetUserName()!=name)//don't exist
            {
				return pData;
			}
	}

	pData = pCur->getVacData();//get vaccine data of pCur to pData
	return pData;//return searched data 
}

