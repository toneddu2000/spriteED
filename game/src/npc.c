
void Npc_Think()
{
	self.nextthink = time + GAME_RETHINK;
	self.think = Npc_Think;
}

void Npc_Update()
{
	if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		if(player != world){
			local entity e = world;
			while ((e = nextent(e))){
				if(e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_NPC){
					if(e.charAggr != 0 && e.charHealth > 0){
						local float d = Util_Vec2Dist(player.spriteOrg,e.spriteOrg);
						if(d < CHAR_RADIUS_ATTACK){
							e.charAttacking = TRUE;
						}
						else if (d < CHAR_RADIUS_IDLE && d > CHAR_RADIUS_ATTACK){
							local vector midpos = player.spriteOrg-e.spriteOrg;
							e.spriteOrg_x += midpos_x * frametime * 1 * e.charSpeed;
							e.spriteOrg_y += midpos_y * frametime * 1 * e.charSpeed;
						}
					}
					if(e.charAttacking == TRUE){
						e.charAttackTime+=frametime*1;
						if(e.charAttackTime >= 0.5){
							e.charAttackTime = 0;
							e.charAttacking = FALSE;
						}
					}
				}
			}
		}
	}
}