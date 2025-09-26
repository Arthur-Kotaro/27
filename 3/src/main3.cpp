#include <iostream>
#include <vector>
#include "main3.hpp"
#include "randomName.hpp"

#define FOREST_SIZE 5
#define DEBUG

class Branch
{
    Branch* parentBranch;
    std::vector<Branch*> childBranches;
    std::string elfName;
public:
    Branch(RandomNameSurname & namesDATA, const int depth = 3, Branch* inParent = nullptr): parentBranch(inParent)
    {
        unsigned int childBranchNum;
        if(depth == 1 && inParent != nullptr)
        {
            elfName = namesDATA.getFIDO();
            return;
        } else if(inParent == nullptr)
        {
            elfName = "None";
            childBranchNum = ((std::rand() % 3) + 3);
        }
        else
        {
            elfName = namesDATA.getFIDO();
            childBranchNum = ((std::rand() % 2) + 2);
        }
        for (int i = 0; i < childBranchNum; ++i) childBranches.push_back(new Branch(namesDATA, depth-1, this));
    }

    Branch* findElf(const std::string & NameToFind)
    {
        Branch* result = nullptr;
        if(NameToFind == "None" || NameToFind == "none") std::cout<< "Incorrect name!\n";
        else if(elfName == NameToFind) return this;
        else if(!childBranches.empty())
        {
            for (int i = 0; i < childBranches.size(); ++i)
            {
                result = childBranches[i]->findElf(NameToFind);
                if(result) return result;
            }
        }
        return nullptr;
    }

    Branch* FindBigBranch()
    {
        if(parentBranch == nullptr) return nullptr;
        if(parentBranch->parentBranch != nullptr) return parentBranch->FindBigBranch();
        else return this;
    }

    int ShowChild(Branch* excludeElf = nullptr)
    {
        int count = 0;
        if (elfName != "None" && (!excludeElf  ||  (excludeElf && elfName != excludeElf->elfName)))
        {
            std::cout << elfName << std::endl;
            count++;
        }
        if(!childBranches.empty())
        for (int i = 0; i < childBranches.size(); ++i) count += childBranches[i]->ShowChild(excludeElf);
        return count;
    }

    void ShowNeighbours( const std::string & NameToFind)
    {
        Branch* SearchElfResult = findElf(NameToFind);
        if (SearchElfResult)
        {
            std::cout << "Neighbours of " << NameToFind << ":\n";
            int neibNum = SearchElfResult->FindBigBranch()->ShowChild(SearchElfResult);
            std::cout << "Neighbours number = " << neibNum << std::endl;
        }
    }

    ~Branch()
    {
        if (!childBranches.empty())
        {
            for (int i = childBranches.size()-1; i+1 > 0; --i)
            {
                if (childBranches[i]->childBranches.empty()) delete childBranches[i];
                else childBranches[i]->~Branch();
                childBranches[i] = nullptr;
                childBranches.pop_back();
            }
        }
    }
};


int main()
{
    RandomNameSurname initRandom;
    Branch* forest [FOREST_SIZE];
    for (auto & i : forest) i = new Branch(initRandom, 3, nullptr);

    for (int i = 0; i < FOREST_SIZE; ++i)
    {
        std::cout << "Tree N" << i+1 << " contents:\n\n";
        forest[i]->ShowChild();
        std::cout << std::endl;
    }

    std::string inputName;
    std::cout << "Enter elf\'s name to show his neighbours: ";
    std::getline(std::cin, inputName);
    for (auto & i : forest) i->ShowNeighbours( inputName);
    for (auto & i : forest) delete i;
    return 0;
};
