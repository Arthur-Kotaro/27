#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "main2.hpp"
#include "randomName.hpp"


#define DEBUG

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
        std::cout << "Team N" << teamLeader->getID() << ':' << std::endl << "Leader of team is " << teamLeader->GetName() << ".\nTeam members: " << std::endl;
        for (int i = 0; i < workerVec.size(); i++)
        {
            std::cout << "\t\t" << workerVec[i]->GetName() << ",\tstatus: ";
            TaskType empl = workerVec[i]->GetEmployment();
            if(empl == work_free) std::cout<< "free of tasks";
            else if(empl == A) std::cout<< 'A';
            else if(empl == B) std::cout<< 'B';
            else if(empl == C) std::cout<< 'C';
            std::cout << std::endl;
        }
    }

    unsigned int SetTeamTask(int inSeed)
    {
        std::srand(inSeed + teamLeader->getID());
        unsigned int newTaskNum = std::rand() % workerVec.size() + 1;
        unsigned int tasksSettled = 0;
        for (int i = 0; i < workerVec.size(); i++)
        {
            if(workerVec[i]->GetEmployment() != work_free) tasksSettled++;
            else if (workerVec[i]->GetEmployment() == work_free && newTaskNum > 0)
            {
                workerVec[i]->setWorkerTask();
                tasksSettled++;
                newTaskNum--;

                std::cout << "Team N"<< teamLeader->getID() << ": " << workerVec[i]->GetName() << " received task ";
                TaskType empl = workerVec[i]->GetEmployment();
                if(empl == work_free) std::cout<< "free of tasks";
                else if(empl == A) std::cout<< 'A';
                else if(empl == B) std::cout<< 'B';
                else if(empl == C) std::cout<< 'C';
                std::cout << ".\n";
            } else break;
        }
        return workerVec.size() - tasksSettled; //return number free team workers
    }
};



class CEO: protected Person
{
	std::vector<Team *> teamsVec;
	unsigned int teamsQuontity;
public:
	CEO(RandomNameSurname & staffData): Person(staffData)
	{
        //std::cout << "Head of company: " << name << std::endl;
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
        unsigned int freeWorkersNum = 0;
        std::cout << "Enter any int (task): ";
        std::cin >> inputSeed;
        for (int i = 0; i < teamsVec.size(); i++)
            freeWorkersNum += teamsVec[i]->SetTeamTask(inputSeed);//var freeWorkersNum accumulates number free company workers
#ifdef DEBUG
        std::cout<< "DEBUG:  Number unbusy company workers " << freeWorkersNum << std::endl;
#endif
        return (freeWorkersNum == 0); //return true if all company employes are busy
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
    while(!workloadMax)
    {
        workloadMax = CEOptr->SetTask();
        //CEOptr->ShowInfo();
    }
    delete CEOptr;
	return 0;
}
