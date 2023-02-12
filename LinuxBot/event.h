#pragma once

#include <vector>
#include <string>
#include <dpp/dpp.h>

struct UserXP
{
	unsigned long long userID;
	unsigned long long xp = 0;
	short lvl = 1;
	bool sielent = 0;
};

struct RankData
{
	RankData(unsigned long long userID, unsigned long long xp, unsigned long long xptonextlvl, unsigned long long rank, unsigned long long maxrank, short lvl)
	{
		this->userID = userID;
		this->xp = xp;
		this->xptonextlvl = xptonextlvl;
		this->rank = rank;
		this->maxrank = maxrank;
		this->lvl = lvl;
	}

	unsigned long long userID;
	unsigned long long xp;
	unsigned long long xptonextlvl;
	unsigned long long rank;
	unsigned long long maxrank;
	short lvl;
};

std::vector<UserXP*> getDatabase();
bool addXP(dpp::user user);
unsigned long long getXP(dpp::user user);
void applyXP();
void setDatabase(std::vector<UserXP*> data);
std::vector<UserXP*> getTopDatabase(short howmany);
RankData getRank(unsigned long long ID);