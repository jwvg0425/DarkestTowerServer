#pragma once
#include "Types.h"
#include "pcPacket.h"
#include <vector>

class Hero;

class Skill
{
public:
	Skill(SkillType type_, int act_, int cool_)
		: type(type_), level(1), act(act_), cool(cool_)
	{ }
	virtual ~Skill() = default;

	int getLevel() const { return level; }
	int getAct() const { return act; }
	int getCool() const { return cool; }
	SkillType getType() const { return type; }

	//skill 해당 위치가 시전이 적절한 위치인지
	bool isValidActPos(Point pos) const;

	//해당 영웅이 스킬 효과 범위 내에 존재하는지
	bool isHeroInEffect(Point pos, const Hero* target, bool isAlly) const;

	//내 위치가 시전을 할 수 있는 위치인지
	virtual bool isActEnable(Point pos) const = 0;

	//skill 쓸 수 있는 범위 리턴
	virtual Range getRange(Point pos) const = 0;

	//skill의 효과가 들어가는 범위 리턴. 상대 좌표. pos는 시전하는 영웅의 위치.
	virtual std::vector<Point> getEffectRange(Point pos) const = 0;

	virtual bool doSkill(Point pos, Hero* target, bool isAlly) const = 0;

protected:

	SkillType type;
	int level;
	int act;
	int cool;
};