#include "BpTree.h"
bool BpTree::Insert(VaccinationData* newData){
    string key = newData->GetUserName();// key
	VaccinationData* value = newData;// value
	map<string, VaccinationData*> Data;// map <string,VaccinationData*>
	BpTreeNode* pDataNode=NULL;
	Data.insert(make_pair(newData->GetUserName(), newData));// insert pair into Data

	if (root == NULL)	// don't exist root
	{
		pDataNode = new BpTreeDataNode;	// make new data node
		pDataNode->insertDataMap(key, value);	// insert data
		root = pDataNode;
		return true;
	}
	pDataNode = searchDataNode(key);// search data node from key

	map<string, VaccinationData*> *m = pDataNode->getDataMap();
	if (m->find(key) == m->end())	// dosen't have key
	{
		m->insert(map<string, VaccinationData*>::value_type(key, value)); // m get new element
		if (exceedDataNode(pDataNode) == 1) // if size of map is bigger than order - 1 check
			{splitDataNode(pDataNode);//and split

			}
	}
	return true;
}
BpTreeNode * BpTree::searchDataNode(string n) {
	BpTreeNode* pCur=NULL;
	pCur = root;
	if(root==NULL)
		return NULL;
	map<string, BpTreeNode*>::iterator itIndex;

	while (pCur->getMostLeftChild())
	{
		itIndex = pCur->getIndexMap()->begin();  //itIndex first node of getIndexMap

		if (n < itIndex->first)	//  if Username name is larger than n 
			pCur = pCur->getMostLeftChild();  // pCur get MostLeftChild

		else//  if Character's name is smaller than n 
		{	
			while (1)
			{
				itIndex++;  //  itIndex is next element
				if (itIndex == pCur->getIndexMap()->end() || n < itIndex->first)
				{  // if element ended or lower than n
					itIndex--; // itIndex is previous element
					pCur = itIndex->second; // pCur gets child of Node which pointed by element's second value
					break;
				}
			}
		}
	}
	return pCur;
}
void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	map<string, VaccinationData*>::iterator middle_data;    //middle_data will define dividing point element
	map<string, VaccinationData*>::iterator second_middle_data;   //  second_middle_data will define getting middle_data
	map<string, VaccinationData*>::iterator leftest_data; //leftest will define first element in Map(MostLeftChild data)
	BpTreeNode* NewDataNode = new BpTreeDataNode();  //  create NewDataNode to divide Map
	int count = 0;
	int del_count=0;
	int splitPosition = ceil((order - 1) / 2.0) + 1; //splitPosition_data defines divide point

	leftest_data = pDataNode->getDataMap()->begin();      // mostleftData gets Map from first node of pDataNode

	for (int i = 1; i < order; i++) // this Loop will find divide position and give data into middle_data
	{//order changed, number of element change.
		leftest_data++;//next leftestdata
		if (i == splitPosition - 1) // if i is a same divided point
			middle_data = leftest_data;   // middle_data get element
	}
	second_middle_data = middle_data;
	
	while (1)	// NewDataNode gets element that Username is bigger or same middle_Data
	{
		NewDataNode->insertDataMap(middle_data->first, middle_data->second); // NewDataNode's Map receive elements
		count++;
		if (count > order - splitPosition) // Username is bigger or same middle_Data
			break;
		middle_data++;//next element middle_Data
	}

	middle_data = second_middle_data; //repositioning

	while (1)  // delete divided part
	{
		pDataNode->deleteMap((leftest_data--)->first);//previous leftest delete pair
		del_count++;//increase d
		if (del_count > order - splitPosition)// Username is bigger or same with middle_data
			break;
	}

	// reposition
	NewDataNode->setNext(pDataNode->getNext());
	if (pDataNode->getNext() != NULL)
		pDataNode->getNext()->setPrev(NewDataNode);
	pDataNode->setNext(NewDataNode);
	NewDataNode->setPrev(pDataNode);

	if (pDataNode->getParent() == NULL) //no ParentNode
	{
		BpTreeNode * parentNode = new BpTreeIndexNode(); //allocate indexNode that is parentNode
		parentNode->insertIndexMap(NewDataNode->getDataMap()->begin()->first, NewDataNode);  //parentNode get element
		parentNode->setMostLeftChild(pDataNode); // pDataNode become mostLeftChild of parentNode
		pDataNode->setParent(parentNode); // pDataNode sets Parent
		NewDataNode->setParent(parentNode); // NewDataNode sets Parent
		root = parentNode; // parentNode is root
		//parentNode=NULL;
	}
	else  // ParentNode exists
	{
		NewDataNode->setParent(pDataNode->getParent());  // NewDataNode sets Parent
		pDataNode->getParent()->insertIndexMap(NewDataNode->getDataMap()->begin()->first, NewDataNode); // parentNode gets element						
		if (exceedIndexNode(pDataNode->getParent()) == 1)// if size of IndexNode Map is bigger than order - 1 (3-1)>1
			splitIndexNode(pDataNode->getParent());  // splitIndexNode
	
	}
	//delete NewDataNode;
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	

	BpTreeNode * NewIndexNode = new BpTreeIndexNode(); // allocate NewindexNode to receive element
	map <string, BpTreeNode*>::iterator leftestindex; // leftest defines first element in Map(MostLeftChild index)
	map <string, BpTreeNode*>::iterator middleindex;   //  middlendex defines divided element
	leftestindex = pIndexNode->getIndexMap()->begin(); // mostleftindex get Map's first element
	int splitPosition = ceil(order / 2.0); // splitPosition defines divided point(different splitposition splitindexdata)
	for (int i = 0; i < order; i++) // middleindex get divide point element and NewIndexNode get element after middleindex 
	{
		if (i + 1 >= splitPosition)
		{
			if (i + 1 == splitPosition)
				 middleindex = leftestindex;  //  middleindex get divide point element
			else 
				NewIndexNode->insertIndexMap(leftestindex->first, leftestindex->second);  //  NewIndexNode get element after middleindex
		}
		leftestindex++;//next leftestindex
	}

	NewIndexNode->setMostLeftChild(middleindex->second);//middleindex child becomes MostLeftChild of NewIndexNode
	middleindex->second->setParent(NewIndexNode);//sets parent

	for (int i = 0; i <= order - splitPosition; i++)  //  before divide, every childNode of IndexNode need to pick ParentNode After divide
	{
		if (i == 0) 
			(NewIndexNode->getIndexMap()->begin())++; // NewIndexNode's first element is middleindex
		else 
			(NewIndexNode->getIndexMap()->begin())++->second->setParent(NewIndexNode); //all children of NewIndexNode connect their parent
	}
	for (int i = 0; i < order - splitPosition; i++)
		pIndexNode->deleteMap((NewIndexNode->getIndexMap()->begin())++->first);//delete NewIndexNode's element from existing node
	


	if (pIndexNode->getParent() == NULL)  //  if pIndexNode doesn't have parent
	{
		BpTreeNode * rootNode = new BpTreeIndexNode();  // allocate ParentNode
		pIndexNode->setParent(rootNode); //rootNode becomes pIndexNode's parent
		NewIndexNode->setParent(rootNode);// rootnode become NewIndexNode's parent
		rootNode->insertIndexMap(middleindex->first, NewIndexNode);	// rootNode receives middleindex(divide point element)
		rootNode->setMostLeftChild(pIndexNode);	// pIndexNode becomes MostLeftChild of ParentNode
		pIndexNode->deleteMap(middleindex->first);	// delete middleNode from existing node at pIndexNode
		root = rootNode;// rootNode becomes root
	}
	else  // if pIndexNode has Parent
	{
		NewIndexNode->setParent(pIndexNode->getParent()); // existing node parent becomes NewIndexNode's parent
		pIndexNode->getParent()->insertIndexMap(middleindex->first, NewIndexNode); // Parentnode receives element that is middleindex
		pIndexNode->deleteMap(middleindex->first); //  pIndexNode deletes middleindex Map

		if (exceedIndexNode(pIndexNode->getParent()) == 1)  //  if Parent sizeofmap if bigger than order -1(3-1)
			splitIndexNode(pIndexNode->getParent());  // splitIndexNode
		
	}
}

bool BpTree::exceedDataNode(BpTreeNode* pDataNode) {//check exceedDataNode
	map <string, VaccinationData* > *m = dynamic_cast<BpTreeDataNode*>(pDataNode)->getDataMap();//map m is converted temporarily BpTreeDataNode by "dynamic_cast" 
	if (m->size() > order - 1)
	 return true;//if exceed
	else
	 return false;//unless exceed
}

bool BpTree::exceedIndexNode(BpTreeNode* pIndexNode) {//check exceedIndexNode
	map <string, BpTreeNode*> *m = dynamic_cast<BpTreeIndexNode*>(pIndexNode)->getIndexMap();//map m is converted temporarily BpTreeIndexNode by "dynamic_cast" 
	if (m->size() > order - 1) 
	return true;//if exceed
	else
	 return false;//unless exceed
}

bool BpTree::SearchRange(string start, string end) {//search range both start and end
	ofstream flog;//to write log.txt
	flog.open("log.txt", ios::app);
	BpTreeNode* pCur = searchDataNode(start);// searchDataNode start
	if (pCur == NULL)		// if pCur doesn't exist
		return false;

	queue<VaccinationData*> q;	// use queue
	VaccinationData* print_pCur = NULL;

	map<string, VaccinationData* >::iterator it; //make a map iterator
	it = pCur->getDataMap()->begin();	//it points to first datanode
	while (it->first.at(0) <= end.at(0)) //range is smaller than last end
	{
		if (it->first.at(0) >= start.at(0))	// range is bigger than start alphabet
			q.push(it->second);	//push it into queue
		it++;
		if (it == pCur->getDataMap()->end()) //if end of node
		{
			pCur = pCur->getNext();	// pCur is next node
			if (!pCur)	// if pCur doesn't exist
				break;
			it = pCur->getDataMap()->begin();//it is first pCur data
		}
	}
	
	if (q.empty()) // if q is empty
		{
			flog << "========== ERROR ==========" <<endl;
			flog << 400 << endl;
			flog << "===========================" << endl << endl;
			return false;
		}
	flog << "======= SEARCH_BP =======" << endl;
	while (!q.empty()) // if q is not empty
	{
		print_pCur = q.front();	// print_pCur is front of q
		flog<<print_pCur->GetUserName()<<" "<<print_pCur->GetVaccineName()<< " "<<print_pCur->GetTimes()<< " "<<print_pCur->GetAge()<< " "<< print_pCur->GetLocationName()<<endl;
		q.pop();// pop from q
	}
	flog<<"========================"<<endl;
}

void BpTree::Print() {
	ofstream flog;//to write log.txt
	flog.open("log.txt", ios::app);
	VaccinationData* print_data=NULL;
	BpTreeNode* pCur = root; // pCur is root

	if (root == NULL)	// if root doesn't exist
		{
			ofstream flog;//to write log.txt
			flog.open("log.txt", ios::app);
			flog << "========== ERROR ==========" <<endl;
			flog << 700 << endl;
			flog << "===========================" << endl << endl;
			flog.close();
			return;
		}

	map<string, VaccinationData*>::iterator it, it1;//setting iterator map

	while (pCur->getMostLeftChild() != NULL)	
		pCur = pCur->getMostLeftChild();// pCur is MostLeftChild


	flog << "======= PRINT_BP =======" << endl;
	while (1)//when meet break
	{
		for (it = pCur->getDataMap()->begin(); it != pCur->getDataMap()->end(); it++)
		{
			it1 = it;
			if (pCur->getDataMap()->size() == 1) // if sizeof data map is 1
			{
				it1 = pCur->getDataMap()->begin();//it1 is first node pCur
				print_data = it1->second; // print_data is it1's VaccinationDatanode
				flog<<print_data->GetUserName()<<" "<<print_data->GetVaccineName()<< " "<<print_data->GetTimes()<< " "<<print_data->GetAge()<< " "<< print_data->GetLocationName()<<endl;
			}
			else
			{//unless sizeof data map is 1
				for (int i = pCur->getDataMap()->size(); i > 1; i--)
				{
					print_data = it1->second; // print_data is it1's VaccinationDatanode
					flog<<print_data->GetUserName()<<" "<<print_data->GetVaccineName()<< " "<<print_data->GetTimes()<< " "<<print_data->GetAge()<< " "<< print_data->GetLocationName()<<endl;
				}
			}
		}
		pCur = pCur->getNext();	// pCur is next node
		if(!pCur)
			break;
		/*if (!pCur)// if pCur doesn't exist
		{
			flog << "========================" << endl;
			flog.close();
			break;
		}*/
	}
}
