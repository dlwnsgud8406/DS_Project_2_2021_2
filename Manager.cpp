#include "Manager.h"
#include <string>
#include <sstream>
Manager::Manager(int bpOrder) {
	avl=new AVLTree;
	bp=new BpTree;
	flog.open("log.txt", ios::trunc);//open log.txt to write log.txt
	flog.close();
}

Manager::~Manager() {
	fin.close();
	flog.close();
	delete avl;
	delete bp;
	exit(0);
}

void Manager::run(const char* command_txt) {
	fin.open("command.txt");//read command.txt
	flog.open("log.txt", ios::app);
	string cmd;//to receive command
	
	bool openstate=false;

    if (!fin)
    {//if no command.txt write at log.txt Error
        flog << "File Open Error" << endl;
        return;
    }
	while(!fin.eof())
	{
		getline(fin, cmd);//get line command
		if(cmd=="LOAD")//command is LOAD
		{
			if(openstate==false)
				openstate=LOAD();
				
			else
				printErrorCode(100);
		}
		else if(cmd.find("SEARCH_BP")==0)//command is SEARCH_BP
		{
			string meaningless_tempstring;//store command
			string tempstring1;//store factor
			string tempstring2;//store factor
			istringstream tempstring(cmd);//cmd line(command + factor)
			getline(tempstring, meaningless_tempstring, ' ');//command
			getline(tempstring, tempstring1, ' ');//factor1
			getline(tempstring, tempstring2, ' ');//factor2
			if(tempstring2.empty())//factor 2 is empty => username
				SEARCH_BP(tempstring1);
			else//have factor1 factor2 => user name range
				SEARCH_BP(tempstring1, tempstring2);//SEARCH_BP

		}
		else if(cmd=="PRINT_BP")
			PRINT_BP();//command is PRINT_BP
		else if(cmd.find("ADD")==0)//command is ADD
			{
			string meaningless_tempstring;//store command
			string tempstring1;//store factor1
			string tempstring2;//store factor2
			string tempstring3;//store factor3
			string tempstring4;//store factor4
			int add_age;//to stoi
			istringstream tempstring(cmd);//get cmd line
			getline(tempstring, meaningless_tempstring, ' ');//command
			getline(tempstring, tempstring1, ' ');//factor1
			getline(tempstring, tempstring2, ' ');//factor2
			getline(tempstring, tempstring3, ' ');//factor3
			getline(tempstring, tempstring4, ' ');//factor4
			if(tempstring1.empty()||tempstring2.empty()||tempstring3.empty()||tempstring4.empty())//there is no factor left
				printErrorCode(300);
			else
			{
				add_age=stoi(tempstring3);//stoi age
				ADD(tempstring1, tempstring2, add_age, tempstring4);//ADD
			}
			}
		else if(cmd.find("SEARCH_AVL")==0)//command is SEARCH_AVL
		{
			string meaningless_tempstring;//store command
			string tempstring1;//factor1
			istringstream tempstring(cmd);//get cmd line
			getline(tempstring, meaningless_tempstring, ' ');//command
			getline(tempstring, tempstring1, ' ');//factor1
			if(tempstring1.empty())//factor1 is empty
				printErrorCode(500);
			else//there is factor1
				SEARCH_AVL(tempstring1);
		}
		else if(cmd.find("VLOAD")==0)//command is VLOAD
			VLOAD();
		else if(cmd.find("VPRINT")==0)//command is VPRINT
			{
			string meaningless_tempstring;//store command
			string tempstring1;//factor1
			istringstream tempstring(cmd);//get cmd line
			getline(tempstring, meaningless_tempstring, ' ');//command
			getline(tempstring, tempstring1, ' ');//factor1
			if(tempstring1.empty())//factor 1 is empty
				printErrorCode(600);
			else//there is factor1
				VPRINT(tempstring1);
			}
		else if(cmd.find("EXIT")==0)
			EXIT();
			
		else
			printErrorCode(800);
		
	}
	flog.close();
}

bool Manager::LOAD() {//LOAD
	bool load_state=false;
	string tmp_string;//to getline
	string token[5];//to get factor
	string UserName;//username
	string VaccineName;//vaccinename
	string LocationName;//location name
	int gotvaccinecount;//vaccine count
	int age;//age
	data.open("input_data.txt",ios::app);// read input_data.txt
	if(!data)//input_data.txt is empty
		printErrorCode(100);
	else
	{
		while(!data.eof())//end of file
		{
		auto LoadData=new VaccinationData();//allocate VaccinationData
		getline(data, tmp_string); //Function to save a single line in temp by taking a string space as input
		if(tmp_string.empty())
			printErrorCode(100);
		istringstream stringStream(tmp_string);	// Copy temp and provide it as a stream from the buffer.
		getline(stringStream, token[0], ' ');// Read the first and the first from the string and store them in token[0]
        getline(stringStream, token[1], ' ');// Reads the next and front of the string and stores it in token[1].
        getline(stringStream, token[2], ' ');// Reads the next and front of the string and stores it in token[2].
		getline(stringStream, token[3], ' ');// Reads the next and front of the string and stores it in token[3].
		getline(stringStream, token[4], ' ');// Reads the next and front of the string and stores it in token[4]. It's okay because the sentence ends without it.
		
		gotvaccinecount=stoi(token[2]);//stoi to get gotvaccinecount

		age=stoi(token[3]);//stoi to get age
		
		LoadData->SetUserName(token[0]);//set to username at Vaccinationdatanode
		LoadData->SetVaccineName(token[1]);//set to vaccinename at Vaccinationdatanode
		LoadData->SetTimes(gotvaccinecount);//set to vaccinecount at Vaccinationdatanode
		LoadData->SetAge(age);//set to age at Vaccinationdatanode
		LoadData->SetLocationName(token[4]);//set to location name at Vaccinationdatanode
		load_state=bp->Insert(LoadData);//insert BP
		if((token[1]=="Janssen"&&gotvaccinecount>=1)||gotvaccinecount>=2)
			avl->Insert(LoadData);

		}
	}
	data.close();
	if(load_state==true){
		printSuccess("LOAD");
		return load_state;
	}
	else 
		return load_state;
}

bool Manager::VLOAD() {//VLOAD
	while(!Print_vector.empty())
		Print_vector.pop_back();
	avl->GetVector(Print_vector);//get VLOAD at AVL Tree
	if(Print_vector.empty())
		printErrorCode(200);
	else
		printSuccess("VLOAD");
}

bool Manager::ADD(string name, string vaccinename, int age, string area) {//ADD
	VaccinationData* searchavlnode=NULL;
	bool addstate=false;
	BpTreeNode* addnode= bp->searchDataNode(name);//search data node
	
	if((addnode->getDataMap()->begin()->first!=name)||addnode->getDataMap()->empty())
	{
		VaccinationData* newaddnode=new VaccinationData();
		newaddnode->SetUserName(name);
		newaddnode->SetVaccineName(vaccinename);
		newaddnode->SetTimes(1);
		newaddnode->SetAge(age);
		newaddnode->SetLocationName(area);
		addstate=bp->Insert(newaddnode);
		if(vaccinename=="Janssen")
			avl->Insert(newaddnode);
	}
	else
	{
		map<string, VaccinationData*>::iterator ite;
		ite=addnode->getDataMap()->begin();//iterator setting
		if((ite->second->GetVaccineName()=="Janssen"&&ite->second->GetTimes()<1)||ite->second->GetTimes()<2)
			{
				ite->second->SetTimesInc();//vaccinecount time ++
				if(ite->second->GetVaccineName()=="Janssen")
					avl->Insert(ite->second);
				if((ite->second->GetVaccineName()=="Janssen"&&ite->second->GetTimes()==1)||ite->second->GetTimes()==2)
					avl->Insert(ite->second);
			}
		else if((ite->second->GetVaccineName()=="Janssen"&&ite->second->GetTimes()>=1)||ite->second->GetTimes()>=2)
			{printErrorCode(300);
			return false;}

	}
	
	flog << "======== "<<"ADD"<<" ========" << endl;
	flog << name<<" "<<vaccinename<<" "<<age<<" "<<area << endl;
	flog << "=======================" << endl;
	
}

bool Manager::SEARCH_BP(string name) {//SEARCH_BP (username)
	BpTreeNode* searchnode= bp->searchDataNode(name);//search datanode username
	if(searchnode->getDataMap()->begin()->first!=name)
	{
		printErrorCode(400);
		return false;
	}
	map<string, VaccinationData*>::iterator ite;
	ite=searchnode->getDataMap()->begin();//iterator setting
	while(name!=ite->first)//if name==ite->first, break
	{if(name>ite->first)
		ite++;//if name is large, next iterator
	else if(name<ite->first)
		ite--;//if name is small, prev iterator
	}
	flog<<"\n"<<"======= SEARCH_BP ======="<<endl;
	flog<<ite->second->GetUserName()<<" "<<ite->second->GetVaccineName()<<" "<<ite->second->GetTimes()<<" "<<ite->second->GetAge()<<" "<<ite->second->GetLocationName()<<endl;
	flog<<"===================="<<endl;
}

bool Manager::SEARCH_BP(string start, string end) {//SEARCH_BP (range)
	bp->SearchRange(start, end);
}

bool Manager::SEARCH_AVL(string name) {//SEARCH_AVL
	VaccinationData* receive_data=avl->Search(name);//get AVL Tree vaccinationData node
	if(receive_data==NULL)
		{
			printErrorCode(500);
			return false;
		}
		else{
		flog<<"\n"<<"======= SEARCH_AVL ======="<<endl;
		flog<<receive_data->GetUserName()<< " "<<receive_data->GetVaccineName()<<" "<<receive_data->GetTimes() << " "<<receive_data->GetAge()<< " "<<receive_data->GetLocationName()<<endl;
		flog<<"===================="<<endl;
		}
		
}

bool Compare(VaccinationData* vac1, VaccinationData* vac2) {//Compare input A
	if(vac1->GetVaccineName().at(0)==vac2->GetVaccineName().at(0))//if same vaccine
		{
			if(vac1->GetAge()==vac2->GetAge())//if same age
				{
					return vac1->GetUserName().at(0)<vac2->GetUserName().at(0);//return larger name node
				}
			else
				return vac1->GetAge()<vac2->GetAge();//else return larger age node
		}
	else
		return vac1->GetVaccineName().at(0)<vac2->GetVaccineName().at(0);//else return lareger vaccinename node
}
bool Compare1(VaccinationData* vac1, VaccinationData* vac2) {//Compare input B
	if(vac1->GetLocationName().at(0)==vac2->GetLocationName().at(0))//if same location name
		{
			if(vac1->GetAge()==vac2->GetAge())//if same age
				{
					return vac1->GetUserName().at(0)<vac2->GetUserName().at(0);//return larger name node
				}
			else
				return vac1->GetAge()>vac2->GetAge();//return larger age node
		}
	else
		return vac1->GetLocationName().at(0)<vac2->GetLocationName().at(0);//return larger location name node
}

bool Manager::VPRINT(string type_) {//VPRINT
	if(Print_vector.empty())
		printErrorCode(600);
	if(type_=="A")//if type_ is A
	{
		flog<<"\n"<<"======= VPRINT A ======="<<endl;
		sort(Print_vector.begin(), Print_vector.end(), Compare);//sort begin to end at function Compare
		for (int i=0; i<Print_vector.size();i++) //end of Print_vector
			flog<<Print_vector.at(i)->GetUserName()<< " "<<Print_vector.at(i)->GetVaccineName()<<" "<<Print_vector.at(i)->GetTimes() << " "<<Print_vector.at(i)->GetAge()<< " "<<Print_vector.at(i)->GetLocationName()<<endl;
		flog<<"===================="<<endl;
	}
	else if(type_=="B")//if type_ is B
	{
		flog<<"\n"<<"======= VPRINT B ======="<<endl;
		sort(Print_vector.begin(), Print_vector.end(), Compare1);//sort begin to end at function Compare1
		for (int i=0; i<Print_vector.size();i++) //end of Print_vector
			flog<<Print_vector.at(i)->GetUserName()<< " "<<Print_vector.at(i)->GetVaccineName()<<" "<<Print_vector.at(i)->GetTimes() << " "<<Print_vector.at(i)->GetAge()<< " "<<Print_vector.at(i)->GetLocationName()<<endl;
		flog<<"===================="<<endl;
	}
	
}

bool Manager::PRINT_BP() {//PRINT_BP
	bp->Print();
}

void Manager::EXIT()
{
	flog << "==========EXIT=========" << endl<<endl;
	flog << "=======================" << endl;
	fin.close();
	exit(0);
}

void Manager::printErrorCode(int n) {//print error
	flog << "========== ERROR ==========" <<endl;
	flog << n << endl;
	flog << "===========================" << endl << endl;
}

void Manager::printSuccess(char *n) { //print success
	flog << "======== "<<n<<" ========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl;
}