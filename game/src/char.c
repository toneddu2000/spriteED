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

//character common functions

void Char_Update(entity e)
{
	if(e != world){
		if(gameState == GAME_STATE_RUNNING || gameState == GAME_STATE_TEST)
		{
			//orientation
			switch(e.spriteCharDir){
				case SPRITE_CHAR_DIR_UP:
					e.charOrientation = "up";
				break;
				case SPRITE_CHAR_DIR_DOWN:
					e.charOrientation = "down";
				break;
				case SPRITE_CHAR_DIR_LEFT:
					e.charOrientation = "left";
				break;
				case SPRITE_CHAR_DIR_RIGHT:
					e.charOrientation = "right";
				break;
			}
			//states
			if(e.physMoving == FALSE && e.charAttacking == FALSE){
				e.charState = CHAR_STATE_IDLE;
			}
			else if(e.physMoving == TRUE && e.charAttackFinished == FALSE){
				e.charState = CHAR_STATE_WALK;
			}
			else if(e.physMoving == FALSE && e.charAttacking == TRUE){
				e.charState = CHAR_STATE_ATTACK;
			}
			//action frames
			if(e.charState == CHAR_STATE_ATTACK){
				e.spriteActionCurrent = "attack";
				e.spriteActionCurrentEnd = e.spriteActionAttackEnd;
			}
			else{
				if(e.charState == CHAR_STATE_WALK){
					e.spriteActionCurrent = "walk";
					e.spriteActionCurrentEnd = e.spriteActionWalkEnd;
				}
				else if(e.charState == CHAR_STATE_IDLE){
					e.spriteActionCurrent = "idle";
					e.spriteActionCurrentEnd = e.spriteActionIdleEnd;
				}
			}
			//damage
			if(e.charDamaged == TRUE){
				e.charDamageTime += frametime *1;
				if(e.charDamageTime > 0.1){
					e.charDamageTime = 0;
					e.charDamaged = FALSE;
				}
			}
		}
	}
}

void Char_Damage(entity e, float f)
{
	if(e != world){
		e.charHealth -= f + random(2);
		e.charDamaged = TRUE;
	}
}

void Char_Death(entity e)
{
	if(e != world){
		Part_Spawn(e.spriteOrg,"explosion");
		Util_Remove(e);
	}
}

void Char_AttackRadius(entity p)
{
	local float dist=0;
	
	if(p == player){
		local entity e = world;
		while ((e = nextent(e))){
			if(e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_NPC){
				if(e.charHealth > 0){
					dist = Util_Vec2Dist(p.spriteOrg,e.spriteOrg);
					if(dist < CHAR_RADIUS_ATTACK){
						Char_Damage(e,p.charDamage);
						//Part_Spawn(p.spriteOrg,"campfire");
						if(e.charDamage <= 0){
							Char_Death(e);
						}
					}
				}
			}
		}
	}
	else{
		if(player != world && player.charHealth > 0){
			dist = Util_Vec2Dist(player.spriteOrg,p.spriteOrg);
			if(dist < CHAR_RADIUS_ATTACK){
				Char_Damage(player,p.charDamage);
				Part_Spawn(player.spriteOrg,"explosion");
				if(player.charDamage <= 0){
					Char_Death(player);
				}
			}
		}
	}
}