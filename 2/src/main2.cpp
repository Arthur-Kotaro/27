#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <map>

#define NAME_NUMBER 31


class RandomNameSurname
{
	std::string NamesFileName = "male_names_31_ru_latin.txt";
	std::string SurnamesFileName = "male_surnames_31_ru_latin.txt";
	std::map<unsigned int, std::string> name;
	std::map<unsigned int, std::string> surname;
    int additionalSeedComponent;
	public:
	RandomNameSurname()
	{
		std::ifstream NameStream(NamesFileName);
		std::ifstream SurnameStream(SurnamesFileName);
		if(!NameStream.is_open() || !SurnameStream.is_open())
		{
			std::cout << "Can\'t be opened file with names/surnames.\n";
		}
		else
		{
			std::string fileBuffer;
			for(unsigned int i = 0; i < NAME_NUMBER; i++)
			{
				NameStream >> fileBuffer;
				name.insert({i+1, fileBuffer});
				SurnameStream >> fileBuffer;
				surname.insert({i+1, fileBuffer});
	    	}
		}
		NameStream.close();
		SurnameStream.close();
	}

	std::string getFIDO()
	{
		std::string FIDO;
		std::srand(std::time(NULL) + additionalSeedComponent);
		FIDO = surname[(std::rand() % NAME_NUMBER) + 1];
		FIDO.append(" " + name[(std::rand() % NAME_NUMBER ) + 1]);
        for (int i = 0; i <FIDO.length(); i++) additionalSeedComponent +=FIDO[i];
		return FIDO;
	}
};

class Person
{
    protected:
    std::string name;
    public:
    Person(RandomNameSurname & staffDATA) { name = staffDATA.getFIDO(); }
    const std::string & GetName() { return name; }
};


enum TaskType {A, B, C, work_free};

class Worker: public Person
{
	TaskType employment;
	public:
    Worker(RandomNameSurname & staffData): Person(staffData)
	{
        employment = work_free;
    }
    
    TaskType GetEmployment() { return employment;}
    
    void setWorkerTask()
    {
        int randInt = (std::rand() % 3) + 1;
        if(randInt == 1) employment = A;
        else if(randInt == 2) employment = B;
        else if(randInt == 3) employment = C;
    }
};

class Manager: public Person
{
	unsigned int ID;
    public:
    Manager(RandomNameSurname & staffData, const unsigned int TeamNumber): Person(staffData), ID(TeamNumber) { }
    int getID() { return ID;}
};


class Team
{
		std::vector<Worker*> workerVec;
		unsigned int workersQuontity;
        Manager* teamLeader;
	public:
	Team(RandomNameSurname & staffData, unsigned int TeamNumber)
	{
        teamLeader = new Manager(staffData, TeamNumber);
		std::cout << "Enter number of workers: ";
		std::cin >>  workersQuontity;
		Worker *tmp;
		for(int i = 0; i < workersQuontity; i++)
		{
			tmp = new Worker(staffData);
			workerVec.push_back(tmp);
		}
	}
	~Team()
	{
		for(int i = 0; i < workersQuontity; i++)
			delete workerVec[i];
	}
    void showTeam()
    {
        std::cout << "Team N°" << teamLeader->getID() << ':' << std::endl << "Leader of team is " << teamLeader->GetName() << ".\nTeam members: " << std::endl;
        for (int i = 0; i < workerVec.size(); i++)
        {
            std::cout << '\t' << workerVec[i]->GetName() << ", status: ";
            TaskType empl = workerVec[i]->GetEmployment();  
            if(empl == work_free) std::cout<< "free of tasks";
            else if(empl == A) std::cout<< 'A';
            else if(empl == B) std::cout<< 'B';
            else if(empl == C) std::cout<< 'C';
            std::cout << std::endl;
        }
    }

    int SetTeamTask(int inSeed)
    {
        std::srand(inSeed + teamLeader->getID());
        int newTaskNum = std::rand() % workerVec.size() + 1;
        int tasksSettled = 0;
        for (int i = 0; i < workerVec.size() || newTaskNum == tasksSettled; i++)
        {
            if(workerVec[i]->GetEmployment() == work_free)
            {
                workerVec[i]->setWorkerTask();
                tasksSettled++;
            }
        }
        //if (condition) {
        
        //}
    }
};



class CEO: protected Person
{;
	std::vector<Team *> teamsVec;
	unsigned int teamsQuontity;
public:
	CEO(RandomNameSurname & staffData): Person(staffData)
	{
        std::cout << "Head of company: " << name << std::endl;
		std::cout << "Enter number of teams: ";
		std::cin >> teamsQuontity;
		Team *tmp = nullptr;
		for(int i = 0; i < teamsQuontity; i++)
		{
			tmp = new Team(staffData, i+1);
			teamsVec.push_back(tmp);
		}	
	}
	~CEO()
	{
		for(int i = 0; i < teamsQuontity; i++)
			delete teamsVec[i];
	}
    bool SetTask()
    {
        int inputSeed;
        std::cout << "Enter any int (task): ";
        std::cin >> inputSeed;
        for (int i = 0; i < teamsVec.size(); i++) {
            teamsVec[i]->SetTeamTask(inputSeed);
        }




        return 0;
    }

    void ShowInfo()
    {
        std::cout << "CEO of company: " << name << std::endl;
        for(int i = 0; i < teamsVec.size(); i++)
		    teamsVec[i]->showTeam();
    }
};


int main()
{
	RandomNameSurname initRandom;
	CEO *CEOptr = new CEO(initRandom);
    CEOptr->ShowInfo();
    bool workloadMax = false;
    //while(!workloadMax)
    //{
        //workloadMax = CEOptr->SetTask();
        //CEOptr->ShowInfo();
    //}
    delete CEOptr;
        
	return 0;
}
