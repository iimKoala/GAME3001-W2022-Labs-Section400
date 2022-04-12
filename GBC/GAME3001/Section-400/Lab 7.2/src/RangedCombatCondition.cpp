#include "RangedCombatCondition.h"

RangedCombatCondition::RangedCombatCondition(const bool within_combat_range)
{
	m_name = "Ranged Combat Condition";
	setIsWithinCombatRange(within_combat_range);
}

RangedCombatCondition::~RangedCombatCondition()
= default;

void RangedCombatCondition::setIsWithinCombatRange(const bool state)
{
	m_isWithinCombatRange = state;
}

bool RangedCombatCondition::Condition()
{
	return m_isWithinCombatRange;
}
