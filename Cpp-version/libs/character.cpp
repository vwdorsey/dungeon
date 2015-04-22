#include "character.hpp"

Character::Character(Char_template* mon){
		Name = mon -> Name;
		Sprite = mon -> Sprite;
		Color = mon -> Color;
		Description = mon->Description;
		Attribs = mon -> Attribs;
		Speed = mon -> Speed->roll();
		HP = mon -> HP->roll();
		Damage = mon->Damage;
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