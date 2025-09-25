#include "randomName.hpp"

RandomNameSurname::RandomNameSurname()
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

std::string RandomNameSurname::getFIDO()
{
    std::string FIDO;
    std::srand(std::time(NULL) + additionalSeedComponent);
    FIDO = surname[(std::rand() % NAME_NUMBER) + 1];
    FIDO.append(" " + name[(std::rand() % NAME_NUMBER ) + 1]);
    for (int i = 0; i <FIDO.length(); i++) additionalSeedComponent +=FIDO[i];
    return FIDO;
}