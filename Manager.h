#pragma once
#include "VaccinationData.h"
#include "AVLTree.h"
#include "BpTree.h"
#include <algorithm>

using namespace std;
class Manager{
private:
	AVLTree		*avl;	// AVL tree
	BpTree		*bp;		// B+ tree
	vector<VaccinationData*> Print_vector;
	ifstream fin;//command.txt
    ifstream data;//input_data.txt
	ofstream flog;//log.txt
public:
	Manager(int bpOrder); //b+ node map size == bpOrder
	~Manager(); //memory free only on newly allocated avl and bp
	
	void	run(const char * command_txt);
	bool	LOAD();//LOAD input_data.txt
	bool	VLOAD();//LOAD vector in AVL
	bool	ADD(string name, string vaccinename, int age, string area);//ADD(get a shot)
	bool	SEARCH_BP(string name);//search username in BP
	bool	SEARCH_BP(string start, string end);//search range in BP
	bool	SEARCH_AVL(string name);//search username in AVL
	bool	VPRINT(string type_);//print vector in AVL to VLOAD
	bool	PRINT_BP();//print BP
	void	printErrorCode(int n);//print error code
	void 	printSuccess(char * n);//print success
	void	EXIT();
};

