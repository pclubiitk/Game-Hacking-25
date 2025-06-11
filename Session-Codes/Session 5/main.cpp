#include <string>
#include <cstdint>
#include <set>
#include <map>
#include <vector>
#include <functional>
#include "gamelogic.h"
#include <dlfcn.h>

void Player::SetJumpState(bool b){
	printf("SetJumpState is (%d)\n",b);
}
void World::Tick(float f){
    ClientWorld* w = *((ClientWorld**)dlsym(RTLD_NEXT, "GameWorld"));
    Player* player = (Player*)w->m_players.begin()->Get();
    
    player->m_walkingSpeed = 99999.0f;
    player->m_health = 99999;
    player->m_mana = 99999;
    player->m_jumpSpeed = 9999;
    player->m_jumpHoldTime = 99999;
}

int main(){
	
}