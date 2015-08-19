#pragma once
#include <memory>
#include <vector>
#include "Hero.h"
#include "Map.h"
#ifndef OUT
#define OUT
#endif
#define MAX_NUM 2

class Player;

class Match
{
public:
	Match();
	void registerPlayer(std::shared_ptr<Player>& player);
	void ready(std::shared_ptr<Player>& player);

	void placeHero(std::shared_ptr<Player>& player, int num, Point* points);
	void moveHero(std::shared_ptr<Player>& player, int idx, Point pos);

	void randomHero(std::shared_ptr<Player>& player);
	void getHeroData(std::shared_ptr<Player>& player, OUT std::vector<const Hero*>& data);

	void selectHero(std::shared_ptr<Player>& player, int idx);
	void getSkillRange(std::shared_ptr<Player>& player, int heroIdx, int skillIdx);

	void turnChange(std::shared_ptr<Player>& player);
	void actHero(std::shared_ptr<Player>& player, int heroIdx, int skillIdx, Point pos);

private:
	void sendHeroState(int t, int heroIdx);

	template<typename Packet>
	void sendPacket(int idx, Packet& p)
	{
		auto context = new PacketContext<Packet>();
		
		context->packet = p;
		context->session = players[idx]->getSession();

		HmmoApplication::getInstance()->getIoPort()->take(context, 0);
	}

	template<typename Packet>
	void broadcastPacket(Packet& p)
	{
		for (int i = 0; i < playerNum; i++)
		{
			sendPacket(i, p);
		}
	}

	bool isAllReady();

	int getPlayerIndex(std::shared_ptr<Player>& player);
	std::shared_ptr<Player> players[MAX_NUM];
	bool isReady[MAX_NUM];
	int board[MAX_NUM][3][3];
	std::unique_ptr<Hero> heroData[MAX_NUM][4];
	int playerNum = 0;
	int nowTurn = 0;
	bool isStart = false;
	Map map;
};