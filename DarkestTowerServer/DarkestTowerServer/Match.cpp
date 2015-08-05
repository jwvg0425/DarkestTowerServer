#include "Match.h"
#include "pcPacket.h"
#include "Player.h"
#include "ClientSession.h"
#include "LogicContext.h"
#include "HmmoApplication.h"

Match::Match(std::shared_ptr<Player>& player1, std::shared_ptr<Player>& player2)
{
	players[0] = player1;
	players[1] = player2;
}

void Match::ready(std::shared_ptr<Player>& player)
{
	int t = getPlayerIndex(player);

	isReady[t] = true;

	//�� �� ready(���� ��ġ ����)�� ��¥ ���� ����(���� ���� ��Ŷ ����)
	if (isReady[0] && isReady[1])
	{
		GameData data;
		data.classNum = 4;
		data.type = Type::GAME_DATA;

		for (int t = 0; t < 2; t++)
		{
			data.turn = t;
			
			for (int i = 0; i < 4; i++)
			{
				data.classes[i] = heroData[t][i].type;
				data.hp[i] = heroData[t][i].maxHp;
				data.act[i] = heroData[t][i].maxAct;
				data.skillNum[i] = heroData[t][i].skills.size();

				for (int s = 0; s < heroData[t][i].skills.size(); s++)
				{
					data.skillIdx[i] = heroData[t][i].skills[s].idx;
					data.skillLevel[i] = heroData[t][i].skills[s].level;
				}

				data.x[i] = heroData[t][i].pos.x;
				data.y[i] = heroData[t][i].pos.y;
			}

			auto context = new PacketContext<GameData>();
			context->packet = data;
			context->session = players[t]->getSession();

			skylark::postContext(HmmoApplication::getInstance()->getIoPort(), context, 0);
		}
		
		isStart = true;
	}
}

void Match::placeHero(std::shared_ptr<Player>& player, int num, Point * points)
{
	int t = getPlayerIndex(player);

	for (int i = 0; i < num; i++)
	{
		heroData[t][i].pos.x = points[i].x;
		heroData[t][i].pos.y = points[i].y;
	}

	ready(player);
}

void Match::randomHero(std::shared_ptr<Player>& player)
{
	int t = getPlayerIndex(player);

	for (int i = 0; i < 4; i++)
	{
		//hero ���� ����. ���� ���� ���� �����ͼ� �ʱ�ȭ �������� �ϴ��� Ŭ������ ��������.
		heroData[t][i].type = static_cast<HeroClass>(rand() % 6);
		heroData[t][i].maxHp = 5;
		heroData[t][i].maxAct = 5;
	}
}

void Match::getHeroData(std::shared_ptr<Player>& player, OUT std::vector<Hero>& data)
{
	int t = getPlayerIndex(player);

	for (int i = 0; i < 4; i++)
	{
		data.push_back(heroData[t][i]);
	}
}

int Match::getPlayerIndex(std::shared_ptr<Player>& player)
{
	int t = -1;

	for (int i = 0; i < 2; i++)
	{
		if (players[i] == player)
			t = i;
	}

	return t;
}