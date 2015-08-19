#pragma once
#include "Skill.h"

class FighterAttack : public Skill
{
public:
	FighterAttack();
	~FighterAttack() override = default;

	bool isActEnable(Point pos, const Map& map, int t) const override;

	Range getRange(Point pos, const Map& map, int t) const override;

	std::vector<Point> getEffectRange(Point pos) const override;

	bool doSkill(Point pos, Hero* user, Hero* target, bool isAlly) const override;

private:
};