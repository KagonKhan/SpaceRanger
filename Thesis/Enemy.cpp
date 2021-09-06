#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const sf::Texture& texture)
	: Entity(texture)
{
}

void Enemy::onDestroy()
{
	Entity::onDestroy();
}
