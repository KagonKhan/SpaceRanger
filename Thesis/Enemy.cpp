#include "Enemy.h"

Enemy::Enemy(Configuration::Textures tex_id, World& world)
	: Entity(tex_id,world)
{
}

void Enemy::onDestroy()
{
	Entity::onDestroy();
}
