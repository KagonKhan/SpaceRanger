#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(Configuration::Textures tex_id)
	: Entity(tex_id)
{
}

void Enemy::onDestroy()
{
	Entity::onDestroy();
}
