#include <iostream>
#include <vector>
#include "main3.hpp"
#include "randomName.hpp"

#define FOREST_SIZE 5

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
    Branch* findElf(const std::string & NameToFind, const int depth)
    {
        Branch* result = nullptr;
        if(elfName == "None" || elfName == "none") std::cout<< "Incorrect name!\n";
        else if(elfName == NameToFind) return this;
        else if(depth != 1)
        {
            for (int i = 0; i < childBranches.size(); ++i)
            {
                result = childBranches[i]->findElf(NameToFind, depth-1);
                if(result) return result;
            }
        }
        return nullptr;
    }
    void ShowNeighbours(const Branch* elf, bool bigBranchFound = false)
    {
        if(elf == nullptr || parentBranch == nullptr) return;
        if(parentBranch->parentBranch != nullptr && !bigBranchFound)//big branch search
        {
            ShowNeighbours(parentBranch);
        }
        else if (parentBranch->parentBranch == nullptr && !bigBranchFound)//big branch found
        {
            ShowNeighbours(elf, true);
        }
        else if (bigBranchFound && elf->elfName != elfName)
        {
            std::cout << elfName;
            if(childBranches.size() == 0) return;
            for (int i = 0; i < childBranches.size(); ++i)
            {
                childBranches[i]->ShowNeighbours(elf, true);
            }
        }
    }
};



int main()
{
    RandomNameSurname initRandom;
    Branch* forest [FOREST_SIZE];
    for (int i = 0; i < FOREST_SIZE; ++i) {
        forest[i] = new Branch(initRandom, 3, nullptr);
    }

    return 0;
};
