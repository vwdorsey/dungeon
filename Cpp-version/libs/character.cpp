#include "character.hpp"

Character::Character(){
	Name = "Hero";
	Sprite = pc_sprite;
	Speed = pc_speed;
	HP = 100;
	alive = 1;
	priority = pc_speed;
	pos[0] = 0;
	pos[1] = 0;
	Damage = new Dice(0,1,4);
}

Character::Character(Char_template* mon){
		Name = mon -> Name;
		Sprite = mon -> Sprite;
		Color = mon -> Color;
		Description = std::vector<std::string>(mon->Description);
		Speed = mon -> Speed->roll();
		HP = mon -> HP->roll();
		Damage = new Dice(mon->Damage);
		priority = Speed + pc_speed;
		pos[0] = 0;
		pos[1] = 0;
}

Character::~Character(){
	delete Damage;
}

void Character::kill_character(){
	HP = 0;
}

int Character::is_alive(){
	return (HP > 0);
}

void PC::init_backpack(){
	equips.weapon = NULL;
	equips.offhand = NULL;
	equips.ranged = NULL;
	equips.armor = NULL;
	equips.helmet = NULL;
	equips.cloak = NULL;
	equips.gloves = NULL;
	equips.boots = NULL;
	equips.amulet = NULL;
	equips.light = NULL;
	equips.ring1 = NULL;
	equips.ring2 = NULL;
}
