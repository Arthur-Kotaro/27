#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "main1.hpp"

class Track
{
    std::string name;
    std::tm creation_date;
    unsigned int length;
public:

    Track()
    {
	std::cout<< "Enter name of song: ";
	std::cin.ignore();
	std::getline(std::cin, name);
    	
	std::time_t auxilCrDateSec = std::time(nullptr);
	std::tm* creationDateTmp = std::localtime(&auxilCrDateSec);
	std::cout<< "Enter date of creation in format (yyyy/mm/dd): ";
	std::cin>> std::get_time(creationDateTmp, "%Y/%m/%d");
	creation_date = *creationDateTmp;


    std::cout<< "Enter length in sec: ";
	std::cin>> length;
	assert(length > 0);
    }
	std::string GetName() {return name;}

    void showInfo()
    {
	unsigned int len_min, len_sec;
	len_min = length / 60;
	len_sec = length - (len_min * 60);
	std::cout << "name:\t\t" << name << std::endl;
	std::cout << "Creation date:\t" << std::put_time(&creation_date, "%Y/%m/%d") << std::endl;
	std::cout << "Length:\t\t" << len_min << " min " << len_sec << " sec.\n";
    }
};

enum PlayerMode {play_mode, pause_mode, stop_mode, next_mode};

class Player
{
	int current_track_index = 0;
	PlayerMode current_mode = stop_mode;
	std::vector <Track*> track_list;
public:
	Player()
	{
		std::string answ;
		do
		{
			std::cout<< "\nAdd new track? ";
			std::cin >> answ;
			if(answ == "y" || answ == "yes" || answ == "YES")
			{
				Track* tmp = new Track;
				track_list.push_back(tmp);
			}
			else if(answ == "n" || answ == "no" || answ == "NO") break;
			else continue;
		} while(true);
	}


    void play()
    {
	if(current_mode != play_mode)
	{
		current_mode = play_mode;
		track_list[current_track_index]->showInfo();
	}
    }
    void pause()
    {
	if(current_mode == play_mode)
	{
		current_mode = pause_mode;
		std::cout<< "Track \"" <<  track_list[current_track_index]->GetName() << "\" paused.\n";
	}
    }
    void next()
    {
	current_track_index = std::rand() % (track_list.size());
	current_mode = next_mode;
	this->play();
    }
    void stop()
    {
	if(current_mode != stop_mode)
	{
		current_mode = stop_mode;
		std::cout << "Track playinng stoped.\n";
	}
    }
    ~Player()
    {
        for(int i = 0; i < track_list.size(); ++i) { delete track_list[i]; }
    }
};

int main()
{
    std::string input_str;
    Player * user_player = new Player;
    do
    {
        std::cout<< "\nEnter command (play/pause/next/stop/exit): ";
        std::cin>>input_str;
        if (input_str == "play")
        {
            user_player->play();
        }
        else if (input_str == "pause")
        {
            user_player->pause();
        }
        else if (input_str == "next")
        {
            user_player->next();
        }
        else if (input_str == "stop")
        {
            user_player->stop();
        }
        else if (input_str == "exit")
        {
            delete user_player;
            user_player = nullptr;
            break;
        }
        else
        {
            std::cout<< "Invalid input. Try again.\n";
            continue;
        }
    } while (true);
    return 0;
}
