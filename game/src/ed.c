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

//Editor 

//Ed_Cursor() from craFTEr - MIT licensed
void Ed_Cursor()
{
	local float sizex = getviewprop(VF_SIZE_X);
	if(gameState == GAME_STATE_ED){
		if(inputCursor == TRUE){
			//make sure cursor won't place at super top origins, when user touches header buttons
			if(
			(inputCursorOrigin_y > (UI_HEADER_HEIGHT * 2) && inputCursorOrigin_x < (sizex-UI_SIDEBAR_LEFT))
			){
				edGrid_x = floor(inputCursorOrigin_x / edGridSize) * edGridSize;
				edGrid_y = floor(inputCursorOrigin_y / edGridSize) * edGridSize;
			}
		}
	}
}

void Ed_Reset()
{
	local entity e = world;
	while((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE){
			e.spriteOrg = e.edOrg;
			e.charHealth = e.edHealth;
			//very important, otherwise view is not re-set correctly
			Screen_Reset();
		}
	}
}

void Ed_TileRemoveMiddleMouse()
{	
	if(gameState == GAME_STATE_ED){
		local entity e = world;
	
		while ((e = nextent(e))){
			if(e != world && e.gameClass == GAME_CLASS_SPRITE){
				if(e.spriteClass != SPRITE_CLASS_PLAYER){
					local float xaxis = e.spriteOrg_x + e.spriteDim_x;
					local float yaxis = e.spriteOrg_y + e.spriteDim_y;
					local vector pos = [inputCursorOrigin_x-screenX,inputCursorOrigin_y-screenY];
					
					if(inputCursor){
						if(pos_x < xaxis && pos_x > e.spriteOrg_x && 
						pos_y < yaxis && pos_y > e.spriteOrg_y){
							if(e.gameClass == GAME_CLASS_SPRITE){
								e.spriteImgPath = "";
								e.edSelected = FALSE;
								remove(e);
							}
						}
					}
				}
			}
		}
	}
	
}

float Ed_EmptySpotSearch(vector pos)
{	
	local entity e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE){
			if(e.spriteClass == edTileType){
				if(e.spriteOrg == pos){
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void Ed_SelAdd(entity e)
{
	local int i;
	for(i=0;i<ED_SEL_MAX;i++){
		if(edSel[i] == world && e.edSelected == FALSE){
			edSel[i] = e;
			e.edSelected = TRUE;
			edSelection = TRUE;
		}
		else{
			if(edSel[i] == e){
				return;
			}
		}
	}
}

void Ed_SelRemove()
{
	local int i,j;
	local entity e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE){
			if(e.spriteClass == edTileType && e.edSelected == TRUE){
				e.edSelected = FALSE;
				remove(e);
			}
		}
	}
	//then unflag all selected objects
	for(i = 0; i < ED_SEL_MAX ; i++){
		if(edSel[i] != world){
			edSel[i].edSelected = FALSE;
		}
	}
	for(j = 0; j < ED_SEL_MAX ; j++){
		if(edSel[j] != world){
			edSel[j] = world;
		}
	}
	edSelection = FALSE;
}

void Ed_SelClear()
{
	if(gameState == GAME_STATE_ED){
		local int i,j;

		//first, unflag all selected objects
		for(i = 0; i < ED_SEL_MAX ; i++){
			if(edSel[i] != world){
				edSel[i].edSelected = FALSE;
			}
		}
		//second, purge all slots
		for(j = 0; j < ED_SEL_MAX ; j++){
			edSel[j] = world;
		}
	}
	edSelection = FALSE;
}

void Ed_SelTileSwap()
{
	local entity e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE){
			if(e.edSelected == TRUE){
				if(spriteLibrary[spriteLibraryIdx] != ""){
					e.spriteImgPath = spriteLibrary[spriteLibraryIdx];
				}
			}
		}
	}
}

void Ed_TileSel()
{	
	if(gameState == GAME_STATE_ED){
		local entity e = world;
	
		while ((e = nextent(e))){
			if(e != world && e.gameClass == GAME_CLASS_SPRITE){
				if(e.spriteClass == edTileType){
					local float xaxis = e.spriteOrg_x + e.spriteDim_x;
					local float yaxis = e.spriteOrg_y + e.spriteDim_y;
					local vector pos = [inputCursorOrigin_x-screenX,inputCursorOrigin_y-screenY];
					
					if(inputCursor){
						if(pos_x < xaxis && pos_x > e.spriteOrg_x && 
						pos_y < yaxis && pos_y > e.spriteOrg_y){
							if(e.gameClass == GAME_CLASS_SPRITE){
								//e.edSelected = TRUE;
								Ed_SelAdd(e);
							}
						}
					}
				}
			}
		}
	}
}

void Ed_TileSpawn()
{
	if(gameState == GAME_STATE_ED && edLoaded == TRUE){
		//this makes the magic happen. Place the entity with the screen offset
		local vector pos = [edGrid_x-screenX,edGrid_y-screenY];
		local float sizex = getviewprop(VF_SIZE_X);
		if(inputCursorOrigin_y > (UI_HEADER_HEIGHT * 2) && inputCursorOrigin_x < (sizex-UI_SIDEBAR_LEFT))
		{
			local float tileempty = Ed_EmptySpotSearch(pos);
			if(tileempty == FALSE){
				if(edSelection == FALSE){
					switch(edTileType){
						case SPRITE_CLASS_GROUND:
							spriteEntity = Sprite_Spawn(edTileType,spriteLibrary[spriteLibraryIdx],pos, [edGridSize,edGridSize],[1,1,1],1);
						break;
						case SPRITE_CLASS_NPC:
							spriteEntity = Sprite_Spawn(edTileType,spriteLibrary[spriteLibraryIdx],pos, [edGridSize,edGridSize],[1,1,1],1);
						break;
						case SPRITE_CLASS_ENT:
							spriteEntity = Sprite_Spawn(edTileType,spriteLibrary[spriteLibraryIdx],pos, [edGridSize,edGridSize],[1,1,1],1);
						break;
						case SPRITE_CLASS_PLAYER:
							//player must be spawned only once!
							if(playerSpawned == FALSE){
								player = Sprite_Spawn(edTileType,spriteLibrary[spriteLibraryIdx],pos, [edGridSize,edGridSize],[1,1,1],1);
							}
							else{
								uiMessage = "You already added a player. Delete it first";
							}
						break;
						case SPRITE_CLASS_PART:
							spriteEntity = Sprite_Spawn(edTileType,spriteLibrary[spriteLibraryIdx],pos, [edGridSize,edGridSize],[1,1,1],1);
						break;
						case SPRITE_CLASS_ARTWORK:
							spriteEntity = Sprite_Spawn(edTileType,spriteLibrary[spriteLibraryIdx],pos, [edGridSize,edGridSize],[1,1,1],1);
						break;
					}
					edEntOnScreen++;
				}
				else{
					Ed_SelClear();
				}
			}
			else{
				uiMessage = "Tile not empty";
			}
		}
	}
}

void Ed_LayerGroundToggle(){edLayerGround=!edLayerGround;}
void Ed_LayerEntToggle(){edLayerEnt=!edLayerEnt;}
void Ed_LayerCharToggle(){edLayerNpc=!edLayerNpc;}
void Ed_LayerPlayerToggle(){edLayerPlayer=!edLayerPlayer;}
void Ed_LayerPartToggle(){edLayerPart=!edLayerPart;}
void Ed_LayerArtworkToggle(){edLayerArtwork=!edLayerArtwork;}

void Ed_Grid(float w,float h)
{
	if(gameState == GAME_STATE_ED){
		local float x,y;
		for(x=0;x<h;x+=edGridSize){
			drawline(1,[0,x],[w,x],UI_COLOR_GREY_BRIGHT,1);
			for(y=0;y<w;y+=edGridSize){
				drawline(1,[y,0],[y,h],UI_COLOR_GREY_BRIGHT,1);
			}
		}
	}
}

void Ed_LibraryUp()
{
	if(gameState == GAME_STATE_ED){
		if(spriteLibraryIdx < spriteGroundLibrarySize-1 && spriteLibrary[spriteLibraryIdx] != ""){
			spriteLibraryIdx++;
		}
		Ed_SelTileSwap();
	}
}

void Ed_LibraryDown()
{
	if(gameState == GAME_STATE_ED){
		if(spriteLibraryIdx > 0){
			spriteLibraryIdx--;
		}
		else{
			spriteLibraryIdx = 0;
		}
		Ed_SelTileSwap();
	}
}

void Ed_TileTypeSwitch()
{
	if(gameState == GAME_STATE_ED){
		Ed_SelClear();
		if(edTileType < SPRITE_CLASS_ARTWORK){
			edTileType ++;
		}
		else{
			edTileType = 0;
		}
		File_LibraryRead();
	}
}

void Ed_LevelClear()
{
	local entity e=world;
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE){
			if(e.spriteClass!=SPRITE_CLASS_PLAYER){
				Util_Remove(e);
			}
		}
	}
	Screen_Reset();
}

void Ed_LoadedEnable()
{
	if(gameState == GAME_STATE_ED){
		//this avoids spriteEntity spawning when ed still not fully loaded
		if(edLoaded == FALSE){
			edLoaded = TRUE;
		}
	}
}

void Ed_Init()
{
	edLayerGround = TRUE;
	edLayerEnt = TRUE;
	edLayerNpc = TRUE;
	edLayerPlayer = TRUE;
	edLayerPart = TRUE;
	edLayerArtwork = TRUE;
	edGridSize = 32;
}

.float counted;
void Ed_EntOnScreen()
{
	local entity e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITE){
			if(e.counted == FALSE){
				e.counted = TRUE;
			}
		}
	}
}

void Ed_Quit()
{
	if(gameState == GAME_STATE_ED){
		localcmd("quit");
	}
}

void Ed_Update()
{
	if(gameState == GAME_STATE_ED){
		Ed_Cursor();
		Ed_EntOnScreen();
	}
}

void Ed_PostUpdate(float w,float h)
{
	if(gameState == GAME_STATE_ED){
		Ed_Grid(w,h);
	}
}