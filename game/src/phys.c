
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
					//check e org compared to p org to understand if it's really blocking p way
					/*if(p.spriteCharDir == SPRITE_CHAR_DIR_RIGHT){
						if(e.spriteOrg_x > p.spriteOrg_x){
							p.spriteOrg_x -= e.spriteDim_x/2+(m*2);
							return TRUE;
						}
					}
					else if(p.spriteCharDir == SPRITE_CHAR_DIR_LEFT){
						if(e.spriteOrg_x < p.spriteOrg_x){
							p.spriteOrg_x += e.spriteDim_x/2+(m*2);
							return TRUE;
						}
					}
					else if(p.spriteCharDir == SPRITE_CHAR_DIR_DOWN){
						if(e.spriteOrg_y > p.spriteOrg_y){
							p.spriteOrg_y -= e.spriteDim_y/2+(m*2);
							return TRUE;
						}
					}
					else if(p.spriteCharDir == SPRITE_CHAR_DIR_UP){
						if(e.spriteOrg_y < p.spriteOrg_y){
							p.spriteOrg_y += e.spriteDim_y/2+(m*2);
							return TRUE;
						}
					}*/
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
					/*
					//if(player.physCollidingTime == 0){
						player.spriteOrg += -direction * (input_timelength * 15.0);
						player.physMoving = TRUE;
					//}*/
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