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

//Sprite 

void Sprite_DrawEnt(entity e)
{
	local string s = strcat(e.spriteImgPath,".png");
	
	drawpic(e.spriteOrg+[screenX,screenY],s,e.spriteDim,e.spriteCol,e.spriteAlpha);
	if(debug){
		if(cvar("debug_collisions")){
			local vector v = e.spriteOrg;
			drawstring(e.spriteOrg+[screenX,screenY],strcat(ftos(v_x)," ",ftos(v_y)),[4,4],[1,0,0], 1, 0);
			local vector vpos = e.spriteOrg+[screenX,screenY];
			drawfill(vpos,[e.spriteDim_x,e.spriteDim_y],[0,1,0],0.2);
		}
	}
	if(gameState == GAME_STATE_ED){
		if(e.edSelected == TRUE){
			drawfill(e.spriteOrg+[screenX,screenY],[e.spriteDim_x,e.spriteDim_y],UI_COLOR_AZURE,0.9);
		}
	}
}

void Sprite_DrawEntSubParts(entity e,float part)
{
	local string s ="";
	local string path = strreplace(".png","",e.spriteImgPath);
	if(part == 0){
		if(e.spriteEntShdw != world){
			s = e.spriteEntShdw.spriteImgPath;
			drawpic(e.spriteOrg+[screenX,screenY],s,e.spriteDim,e.spriteCol,0.5);
		}
	}
	else{
		if(e.spriteEntTop != world){
			s = e.spriteEntTop.spriteImgPath;
			drawpic(e.spriteOrg+[screenX,screenY],s,e.spriteDim,e.spriteCol,e.spriteAlpha);
		}
	}
}

void Sprite_DrawArtwork(entity e)
{
	if(e != world){
		local int i;
		local float h=0,v=0,tot=31;
		for(i=0;i<SPRITE_ED_PIX_MAX;i++){
			local vector pos = e.spriteOrg+[screenX,screenY];
			drawfill([h+pos_x,v+pos_y],[1,1],e.spriteEdPix[i],1);
			e.spriteEdOrg[i] = [h+pos_x,v+pos_y];
			if(h < (tot)){
				h+=1;
			}
			else{
				h=0;
				v+=1;
			}
		}
	}
	//drawstring(e.spriteOrg+[screenX,screenY], vtos(spriteEdEntArtwork.spriteEdPix[14]),[1,1],[1,0,0],1,0);
}

void Sprite_DrawAction(entity e)
{
	if(e != world){
		local string s="";
		local string path = "";
		if(e.gameClass == GAME_CLASS_SPRITE){
			path = strreplace(".png","",e.spriteImgPath);
			path = strcat(path,"/");
			if(e.spriteClass == SPRITE_CLASS_PLAYER || e.spriteClass == SPRITE_CLASS_NPC){
				e.spriteFrame+=frametime * 10;
				if(e.spriteFrame >= e.spriteActionCurrentEnd){
					e.spriteFrame = 0;
				}
				if(gameState == GAME_STATE_ED){
					s = e.spriteImgPath;
				}
				else if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
					s = strcat(path,e.spriteActionCurrent,"/",e.charOrientation,"/",
					"f",ftos(rint(e.spriteFrame)),".png");
				}
				if(debug){
					if(cvar("debug_collisions")){
						local vector v = e.spriteOrg;
						drawstring(e.spriteOrg+[screenX,screenY],vtos([v_x,v_y]),[4,4],[1,0,0], 1, 0);
						local vector vpos = e.spriteOrg+[screenX,screenY];
						drawfill(vpos,[e.spriteDim_x,e.spriteDim_y],[0,1,0],0.2);
					}
				}
			}
			else if(e.spriteClass == SPRITE_CLASS_PART){
				if(gameState == GAME_STATE_ED){
					s = e.spriteImgPath;
				}
				else if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
					if(e.partLife != 0){
						e.spriteFrame+=frametime * 10;
						if(e.spriteFrame >= e.partLife-1){
							e.spriteFrame = 0;
							Util_Remove(e);
						}
					}
					else{
						e.spriteFrame+=frametime * 10;
						if(e.spriteFrame >= e.spriteActionAnimationEnd-1){
							e.spriteFrame = 0;
						}
					}
					s = strcat(SPRITE_FOLDER,SPRITE_FOLDER_PART,e.spriteImgName,"/","f",ftos(rint(e.spriteFrame)),".png");
				}
			}
			drawpic(e.spriteOrg+[screenX,screenY],s,e.spriteDim,e.spriteCol,e.spriteAlpha);
		}
	}
}

float Sprite_CollisionMoz(entity e, entity collider)
{
	//https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
	local vector epos = [e.spriteOrg_x-screenX,e.spriteOrg_y-screenY];
	local vector colliderpos = [collider.spriteOrg_x-screenX,collider.spriteOrg_y-screenY];
	//TONEDDUFIXME: why collisions work only if every entity has same size?(32x32 in this case)
	if(
		epos_x < (colliderpos_x + e.spriteDim_x)&& 
		(epos_x + e.spriteDim_x) > colliderpos_x &&
		epos_y < (colliderpos_y + collider.spriteDim_y)&&
		(epos_y + e.spriteDim_y) > colliderpos_y
	){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

float Sprite_Collision(entity p,entity e,vector dir)
{
	local float xaxis = e.spriteOrg_x + (e.spriteDim_x)+screenX;
	local float yaxis = e.spriteOrg_y + (e.spriteDim_y)+screenY;
	local vector pos = p.spriteOrg+[screenX,screenY];
	
	if(pos_x < xaxis && pos_x > e.spriteOrg_x && pos_y < yaxis && pos_y > e.spriteOrg_y){
		if(e.gameClass == GAME_CLASS_SPRITE){
			return TRUE;
		}
	}
	return FALSE;
}

entity Sprite_Spawn(float cl,string imgname,vector org, vector dim,vector col,float a)
{
	local float readsuccess=0;
	local entity e = spawn();
	
	e.gameClass = GAME_CLASS_SPRITE;
	e.spriteClass = cl;
	e.spriteImgName = imgname;
	e.spriteOrg = [org_x,org_y,0];
	e.edOrg = e.spriteOrg;
	e.spriteActive = TRUE;
	e.spriteDim = dim;
	e.spriteCol = col;
	e.spriteAlpha = a;
	e.spriteActionCurrent = "idle";
	e.levelSaveThis = TRUE;
	switch(cl){
		case SPRITE_CLASS_ENT:
			e.spriteImgFolder = SPRITE_FOLDER_ENT;
		break;
		case SPRITE_CLASS_NPC:
			e.spriteImgFolder = SPRITE_FOLDER_CHAR;
			e.charOrientation = "up";
		break;
		case SPRITE_CLASS_PLAYER:
			playerSpawned = TRUE;
			e.spriteFrame = 0;
			e.charOrientation = "up";
			e.spriteImgFolder = SPRITE_FOLDER_PLAYER;
		break;
		case SPRITE_CLASS_PART:
			e.spriteImgFolder = SPRITE_FOLDER_PART;
			e.spriteFrame = 0;
		break;
	}
	e.spriteImgName =  strreplace(SPRITE_FOLDER,"",imgname);
	e.spriteImgName =  strreplace(e.spriteImgFolder,"",e.spriteImgName);
	e.spriteImgName =  strreplace(".png","",e.spriteImgName);
	e.spriteImgPath = strcat(imgname);
	e.spriteImgSubfolder = strcat(SPRITE_FOLDER,e.spriteImgFolder,e.spriteImgName,"/",e.spriteImgName);
	switch(cl){
		case SPRITE_CLASS_ENT:
			File_EntSubPartsRead(e);
		break;
		case SPRITE_CLASS_NPC:
			File_ActionRead(e);
		break;
		case SPRITE_CLASS_PLAYER:
			File_ActionRead(e);
		break;
		case SPRITE_CLASS_PART:
			File_PartRead(e);
		break;
		case SPRITE_CLASS_ARTWORK:
			e.spriteArtworkName = imgname;
			File_ArtworkReadSingleEnt(e,spriteArtworkSelected);
		break;
	}
	return e;
}

void Sprite_DrawLoopGround()
{
	local entity e;
	
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_GROUND){
			if(edLayerGround == TRUE){
				Sprite_DrawEnt(e);
			}
		}
	}
}

void Sprite_DrawLoopEnt()
{
	local entity e;
	
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_ENT){
			if(edLayerEnt == TRUE){
				Sprite_DrawEnt(e);
			}
		}
	}
}
void Sprite_DrawLoopEntShdw()
{
	local entity e;
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_ENT){
			if(edLayerEnt == TRUE){
				if(e.spriteEntShdw != world){
					Sprite_DrawEntSubParts(e,0);
				}
			}
		}
	}
}

void Sprite_DrawLoopEntTop()
{
	local entity e;
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_ENT){
			if(edLayerEnt == TRUE){
				if(e.spriteEntTop != world){
					Sprite_DrawEntSubParts(e,1);
				}
			}
		}
	}
}

void Sprite_DrawLoopNpc()
{
	local entity e;
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_NPC){
			if(edLayerNpc == TRUE){
				Sprite_DrawAction(e);
				Char_Update(e);
			}
		}
	}
}

void Sprite_DrawLoopArtwork()
{
	local entity e;
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_ARTWORK){
			if(edLayerArtwork == TRUE){
				Sprite_DrawArtwork(e);
			}
		}
	}
}

void Sprite_DrawLoopPart()
{
	local entity e;
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE && e.spriteClass == SPRITE_CLASS_PART){
			if(edLayerPart == TRUE){
				Sprite_DrawAction(e);
			}
		}
	}
}

void Sprite_DrawPlayer()
{
	if(player != world){
		if(edLayerPlayer == TRUE){
			Sprite_DrawAction(player);
			Char_Update(player);
		}
	}
}

void Sprite_PostUpdate()
{	
	if(gameState == GAME_STATE_ED || gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		Sprite_DrawLoopGround();
		Sprite_DrawLoopArtwork();
		Sprite_DrawLoopEntShdw();
		Sprite_DrawLoopEnt();
		Sprite_DrawPlayer();
		Sprite_DrawLoopNpc();
		Sprite_DrawLoopEntTop();
		Sprite_DrawLoopPart();
	}
}

void Sprite_Init()
{
	File_LibraryRead();
}