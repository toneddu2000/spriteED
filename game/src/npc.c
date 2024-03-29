/*
MIT License

Copyright (c) 2019 Antonio "toneddu2000" Latronico

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//Non Player Characters (set aggr value in your npc .act file to determine if npc is player-friendly or not)

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
					if(e.charHealth > 0){
						//directions
						if(player.spriteOrg_x - e.spriteOrg_x < 0 && player.spriteOrg_y - e.spriteOrg_y < e.spriteDim_y){
							e.spriteCharDir = SPRITE_CHAR_DIR_LEFT;
						}
						else if(player.spriteOrg_x - e.spriteOrg_x > 0 && player.spriteOrg_y - e.spriteOrg_y < e.spriteDim_y){
							e.spriteCharDir = SPRITE_CHAR_DIR_RIGHT;
						}
						else if(player.spriteOrg_y - e.spriteOrg_y > e.spriteDim_y){
							e.spriteCharDir = SPRITE_CHAR_DIR_DOWN;
						}
						else if(player.spriteOrg_y - e.spriteOrg_y < -e.spriteDim_y){
							e.spriteCharDir = SPRITE_CHAR_DIR_UP;
						}
						e.charTarget = player;
						Phys_Move(e);
						//attacking
						if(e.charAggr != 0){
							local float d = fabs(Util_Vec2Dist(player.spriteOrg,e.spriteOrg));
							if(d < CHAR_RADIUS_ATTACK){
								e.physMoving = FALSE;
								e.charState = CHAR_STATE_ATTACK;
								
							}
							else if(d > CHAR_RADIUS_ATTACK && d < CHAR_RADIUS_IDLE){
								e.physMoving = TRUE;
								e.charState = CHAR_STATE_WALK;
								/*local vector midpos = player.spriteOrg-e.spriteOrg;
								e.spriteOrg_x += midpos_x * frametime * 1 * e.charSpeed;
								e.spriteOrg_y += midpos_y * frametime * 1 * e.charSpeed;
								*/
							}
							else if(d > CHAR_RADIUS_IDLE){
								e.physMoving = FALSE;
								e.charState = CHAR_STATE_IDLE;
							}
						}
						if(e.charState == CHAR_STATE_ATTACK){
							//TEMP
							if(e.charAttacking == TRUE){
								Char_AttackRadius(e);
								e.charAttacking = FALSE;
							}
							if(e.spriteFrame >= e.spriteActionCurrentEnd-1){
								e.charAttacking = TRUE;
							}
						}
					}
				}
			}
		}
	}
}