#pragma once
#include "pcPacket.h"
#include "Types.h"
#include <vector>
#include <memory>
#include "Skill.h"

struct SkillInfo
{
	SkillInfo(std::unique_ptr<Skill> skill_)
		:skill(std::move(skill_)), cool(0)
	{
	}

	std::unique_ptr<Skill> skill;
	int cool;
};

class Hero
{
public:
	Hero(HeroClass type_, int maxHp_, int maxAct_);
	virtual ~Hero() = default;
	HeroClass getType() const { return type; }
	int getHp() const { return hp; }
	int getMaxHp() const { return maxHp; }
	int getAct() const { return act; }
	int getMaxAct() const { return maxAct; }
	int getLevel() const { return level; }
	Point getPos() const { return pos; }
	int getSkillNum() const { return skills.size(); }
	const Skill* getSkill(int idx) const { return skills[idx].skill.get(); }
	void setPos(Point pos_);
	bool move(Point pos_);
	bool consumeAct(int value);
	void damage(int value);
	void setSkillCool(int idx, int cool);
	int getSkillCool(int idx) const { return skills[idx].cool; }
	void turnUpdate();

protected:
	HeroClass type;
	int hp;
	int maxHp;
	int act;
	int maxAct;
	int level = 1;
	Point pos;
	std::vector<SkillInfo> skills;
};

std::unique_ptr<Hero> getRandomHero();