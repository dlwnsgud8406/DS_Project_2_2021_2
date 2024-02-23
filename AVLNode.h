#ifndef _AVLNODE_H_
#define _AVLNODE_H_

#include "VaccinationData.h"

class AVLNode//class of ALVNode
{
private:
	AVLNode*			pRight;//right node
	AVLNode*			pLeft;//left node
	VaccinationData*	pVaccinationData;//vaccinationdata node
	int					mBF;//balance factor

public:
	AVLNode(){//constructor(first setting)
		pRight = NULL;
		pLeft = NULL;
		pVaccinationData = NULL;
		mBF = 0;
	};
	~AVLNode(){};//destructor

	void setRight(AVLNode* SN){pRight = SN;}//setting rightnode
	void setLeft(AVLNode* SN){pLeft = SN;}//setting leftnode
	void setVacData(VaccinationData* pVac){ pVaccinationData = pVac;}//set vaccinationdata node
	void setBF(int a){mBF = a;}//set balance factor
	AVLNode*	getRight(){return pRight;}//return right node
	AVLNode*	getLeft(){return pLeft;}//return left node
	VaccinationData*	getVacData(){return pVaccinationData;}//return vaccinationdata node
	int				getBF(){return mBF;}//return balancefactor
};

#endif