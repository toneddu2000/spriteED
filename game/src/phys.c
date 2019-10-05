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

//Physics

float Phys_TileCollision(entity p,vector dir)
{
	local entity e = world;
	local float coll = FALSE;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_ENT){
			coll = Sprite_Collision(p,e,dir);
			return coll;
		}
	}
	return FALSE;
}

void Phys_TileCollision2(entity p,vector dir)
{
	local entity e = world;
	local float coll = FALSE,d=16;
	if(p.physMoving == TRUE){
		while ((e = nextent(e))){
			if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_ENT){
				if((e.spriteOrg_x+screenX)-(p.spriteOrg_x+screenX) < d
					&& (e.spriteOrg_y+screenY)-(p.spriteOrg_y+screenY)< d){
					coll = Sprite_Collision(p,e,dir);
					if(coll){
						p.physColliding = TRUE;
					}
					else{
						p.physColliding = FALSE;
					}
				}
				
			}
		}
	}
}

void Phys_TileCollision3(entity p,vector dir)
{
	local entity e = world;
	local float coll = FALSE,d=16;
	if(p.physMoving == TRUE){
		while ((e = nextent(e))){
			if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_ENT){
				p.physCollisionDist = Util_Vec2Dist(p.spriteOrg+[screenX,screenY],e.spriteOrg+[screenX,screenY]);
				//try collision only if ents are under some range
				if(p.physCollisionDist < (e.spriteDim_x)){
					//coll = Sprite_Collision(p,e,dir);
					coll = Sprite_CollisionMoz(p,e);
					if(coll){
						p.physColliding = TRUE;
					}
					else{
						p.physColliding = FALSE;
					}
				}
			}
		}
	}
}

float Phys_RadiusCollision(entity p, float d)
{
	local entity e = world;
	
	while((e=nextent(e))){
		if(e!=world && e.gameClass == GAME_CLASS_SPRITE){
			if(e.spriteClass == SPRITE_CLASS_ENT || e.spriteClass == SPRITE_CLASS_NPC || e.spriteClass == SPRITE_CLASS_PLAYER){
				local float dist = Util_Vec2Dist(p.spriteOrg,e.spriteOrg);
				local float m = 2;
				if(dist < e.spriteDim_x+m){
					local vector opposdir = normalize(e.spriteOrg-p.spriteOrg);
					p.spriteOrg += -opposdir;
				}
			}
		}
	}
	return FALSE;
}

void Phys_PlayerMoveOld()
{
	if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		local vector direction = normalize([input_movevalues_y,-input_movevalues_x]);
		if(player!=world){
			//movements
			local vector pos = [edGrid_x-screenX,edGrid_y-screenY];
			local float collrad = Phys_RadiusCollision(player,32);
			if(input_movevalues_x != 0 || input_movevalues_y != 0){
				if(player.physColliding == FALSE && collrad == FALSE){
					player.spriteOrg += direction/*+[screenX,screenY]*/;
					//player.spriteOrg += direction+pos * 0.0001;
					player.physMoving = TRUE;
					player.spriteOrgUnstuck = player.spriteOrg;
				}
				
				//we hit the collider, now we go back in the opposite direction,
				//instead of increasing collisions
				else{
					player.spriteOrg = player.spriteOrgUnstuck-direction*2;
				}
			}
			else{
				player.physMoving = FALSE;
			}
			//collision
			if(player.physMoving == TRUE){
				Phys_TileCollision3(player,direction);
			}
			
			//collision stuck avoid (reset collision every X msec, otherwise char will get stuck)
			if(player.physColliding == TRUE){
				player.physCollidingTime += frametime * 1;
				if(player.physCollidingTime > PHYS_UNSTUCKTIME){
					player.physCollidingTime = 0;
					player.physColliding = FALSE;
				}
			}
			//sprite orientation
			if(input_movevalues_x > 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_UP;
			}
			else if(input_movevalues_x < 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_DOWN;
			}
			else if(input_movevalues_y > 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_RIGHT;
			}
			else if(input_movevalues_y < 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_LEFT;
			}
			player.physDirection = normalize(input_movevalues);
		}
	}
}

void Phys_Move(entity e)
{
	if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		if(e!=world && e.gameClass == GAME_CLASS_SPRITE){
			local vector direction;
			if(e.spriteClass == SPRITE_CLASS_PLAYER){
				direction = normalize([input_movevalues_y,-input_movevalues_x]);
			}
			else{
				direction = normalize(e.spriteOrg-e.charTarget.spriteOrg);
			}
			//movements
			local vector pos = [edGrid_x-screenX,edGrid_y-screenY];
			local float collrad = Phys_RadiusCollision(e,32);
			local vector movevel;
			if(e.spriteClass == SPRITE_CLASS_PLAYER){
				movevel = input_movevalues;
			}
			else{
				movevel = e.charVelocity;
			}
			if(movevel_x != 0 || movevel_y != 0){
				if(e.physColliding == FALSE && collrad == FALSE){
					e.spriteOrg += direction;
					e.physMoving = TRUE;
					e.spriteOrgUnstuck = e.spriteOrg;
				}
				//we hit the collider, now we go back in the opposite direction,
				//instead of increasing collisions
				else{
					e.spriteOrg = e.spriteOrgUnstuck-direction*2;
				}
			}
			else{
				e.physMoving = FALSE;
			}
			//collision
			if(e.physMoving == TRUE){
				Phys_TileCollision3(e,direction);
			}
			
			//collision stuck avoid (reset collision every X msec, otherwise char will get stuck)
			if(e.physColliding == TRUE){
				e.physCollidingTime += frametime * 1;
				if(e.physCollidingTime > PHYS_UNSTUCKTIME){
					e.physCollidingTime = 0;
					e.physColliding = FALSE;
				}
			}
			//sprite orientation
			if(movevel_x > 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_UP;
			}
			else if(movevel_x < 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_DOWN;
			}
			else if(movevel_y > 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_RIGHT;
			}
			else if(movevel_y < 0){
				player.spriteCharDir = SPRITE_CHAR_DIR_LEFT;
			}
			e.physDirection = normalize(movevel);
		}
	}
}