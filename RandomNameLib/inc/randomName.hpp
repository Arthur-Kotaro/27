#pragma once
#include <iostream>
#include <fstream>
#include <string>
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
	RandomNameSurname();
    std::string getFIDO();
};