#include "BulletBase.h"
#include "Hero.h"
BulletBase::BulletBase(){
	m_iAtkValue = 1;
	m_speed = 1;
}

BulletBase::~BulletBase(){
}

void BulletBase::setUsed(bool isUsed){
	this->m_isUsed = isUsed;
	setVisible(isUsed);
}

bool BulletBase::isUsed(){
	return m_isUsed;
}

bool BulletBase::isArrive(){
	return m_isArrive;
}

Hero* BulletBase::getTarget(){
	return m_targetHero;
}

void BulletBase::lockTarget(Hero* hero){
	if (hero!=NULL)
	{
		m_targetHero = hero;
		onLockAim(m_targetHero);
	}
}