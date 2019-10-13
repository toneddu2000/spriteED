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

//User Interface 

void UI_Warning(float w,float h)
{
	static float pos;
	if(uiWarning != ""){
		uiWarningTime -= frametime * 0.25;
		if(pos < 0){
			pos += frametime * 400;
		}
		if(uiWarningTime < 0.2){
			pos -= frametime * 800;
		}
		if(uiWarningTime <= 0){
			uiWarningTime=1;
			uiWarning = "";
		}
		drawfill([0+pos,h-50],[stringwidth(uiWarning,0,[10,10]),50], [0.912,0.371,0.095],bound(0, uiWarningTime, 0.2));
		drawfill([0+pos,h-50],[stringwidth(uiWarning,0,[10,10]),4], [1,0,0],bound(0, uiWarningTime, 0.2));
		drawstring([2+pos,h-40], uiWarning,[8,8],[0,1,0.2], bound(0, uiWarningTime, 0.7), 0);
	}
	else{
		uiWarningTime = 1;
		pos = -150;
	}
}


void UI_Message(float w,float h)
{
	static float pos;
	if(uiMessage != ""){
		uiMessageTime -= frametime * 0.25;
		if(pos < 0){
			pos += frametime * 400;
		}
		if(uiMessageTime < 0.3){
			pos -= frametime * 800;
		}
		if(uiMessageTime <= 0){
			uiMessageTime=1;
			uiMessage = "";
		}
		drawfill([0+pos,h-50],[stringwidth(uiMessage,0,[10,10]),50], [1,1,1],bound(0, uiMessageTime, 0.2)); 
		drawstring([2+pos,h-40], uiMessage,[8,8],[0,1,0.2], bound(0, uiMessageTime, 0.5), 0);
	}
	else{
		uiMessageTime = 1;
		pos = -150;
	}
}

void UI_GameState(float w, float h)
{
	local string s = "";
	switch(gameState){
		case GAME_STATE_MENU:
			s="Menu";
		break;
		case GAME_STATE_RUNNING:
			s="Running";
		break;
		case GAME_STATE_ED:
			s="Editor";
		break;
		case GAME_STATE_TEST:
			s="Test";
		break;
		case GAME_STATE_PAUSED:
			s="Paused";
		break;
		case GAME_STATE_LEVELS:
			s="Levels";
		break;
		case GAME_STATE_SPRITEED:
			s="Sprite ED";
		break;
	}
	drawstring([2,h-20], strcat("GAME STATE: ",s),[6,6],[1,1,1], 0.3, 0);
	drawstring([2,h-10], strcat("PAGE: ",ftos(menuPage)),[6,6],[1,1,1], 0.3, 0);
}

void UI_EdSidebar(float w, float h)
{	
	//line below layers
	drawline(2,[w-130,160], [w-10,160],UI_COLOR_GREY_BRIGHT,1);
	//line above useful strings
	drawline(2,[w-130,h-60], [w-10,h-60],UI_COLOR_GREY_BRIGHT,1);
	//useful strings
	drawstring([w-130,h-10],strcat("GRID-SCR: "),[6,6],UI_COLOR_GREY_BRIGHT, 1, 0);
	drawstring([w-130,h-20],strcat(ftos(rint(edGrid_x-screenX)),":",ftos(rint(edGrid_y-screenY))),[6,6],UI_COLOR_GREY_BRIGHT, 1, 0);
	drawstring([w-130,h-30], strcat("EDGRID:",ftos(rint(edGrid_x)),"-",ftos(rint(edGrid_y))),[6,6],UI_COLOR_GREY_BRIGHT, 1, 0);
	drawstring([w-130,h-40],strcat("CURSOR:",ftos(rint(inputCursorOrigin_x)),"-",ftos(rint(inputCursorOrigin_y))),[6,6],UI_COLOR_GREY_BRIGHT, 1, 0);
	drawstring([w-130,h-50],"SCR:",[6,6],UI_COLOR_GREY_BRIGHT, 1, 0);
	drawstring([w-90,h-50],ftos(screenX),[6,6],UI_COLOR_RED, 1, 0);
	drawstring([w-40,h-50],ftos(screenY),[6,6],UI_COLOR_GREEN, 1, 0);
}

void UI_SpriteLibraryIcon(float w,float h)
{
	local string img = "",type="";
	
	/*
	if(edTileType != SPRITE_CLASS_ARTWORK){
		img = spriteLibrary[spriteLibraryIdx];
		drawfill([w/2-32-2,h-70-2],[68,68], [1,1,1],1);
		if(img != ""){
			drawpic([w/2-32,h-70],img,[64,64],[1,1,1],1);
		}
		else{
			drawpic([w/2-32,h-70],"assets/gfx/no_image.png",[64,64],[1,1,1],1);
		}
	}
	else{
		File_ArtworkReadSingleEnt(uiArtworkIcon,"");
		local int i;
		local float hs=0,v=0,tot=62;
		local vector pos = [w/2-32,h-70];
		drawfill([w/2-32-2,h-70-2],[68,68], [1,1,1],1);
		for(i=0;i<SPRITE_ED_PIX_MAX;i++){
			drawfill([hs+pos_x,v+pos_y],[2,2],uiArtworkIcon.spriteEdPix[i],1);
			uiArtworkIcon.spriteEdOrg[i] = [hs+pos_x,v+pos_y];
			if(hs < (tot)){
				hs+=2;
			}
			else{
				hs=0;
				v+=2;
			}
		}
	}
	*/
	
	img = spriteLibrary[spriteLibraryIdx];
	drawfill([w/2-32-2,h-70-2],[68,68], [1,1,1],1);
	if(img != ""){
		drawpic([w/2-32,h-70],img,[64,64],[1,1,1],1);
	}
	else{
		drawpic([w/2-32,h-70],"assets/gfx/no_image.png",[64,64],[1,1,1],1);
	}
	//type display
	switch(edTileType){
		case SPRITE_CLASS_GROUND:
			type = "ground";
		break;
		case SPRITE_CLASS_NPC:
			type = "NPCs";
		break;
		case SPRITE_CLASS_ENT:
			type = "entities";
		break;
		case SPRITE_CLASS_PLAYER:
			type = "player";
		break;
		case SPRITE_CLASS_PART:
			type = "particles";
		break;
		case SPRITE_CLASS_ARTWORK:
			type = "artworks(experimental)";
		break;
	}
	drawstring([w/2-(stringwidth(type,0,[8,8])/2),h-85],type,[8,8],[1,1,1], 0.6, 0);
}

void UI_DebugPlayer()
{
	if(player){
		drawfill([20,40],[80,80],[0.1,0.1,0.1],0.4);
		drawstring([50,50],ftos(player.physMoving),[8,8],[0,1,0], 0.6, 0);
		drawstring([70,50],ftos(player.physColliding),[8,8],[1,0,0], 0.6, 0);
		drawstring([90,50],ftos(player.physCollisionDist),[8,8],[1,0,1], 0.6, 0);
	}
}

void UI_PostUpdate(float w,float h)
{
	
	switch(gameState){
		case GAME_STATE_ED:
			UI_EdSidebar(w,h);
			UI_SpriteLibraryIcon(w,h);
			debug = cvar("debug_enabled");
			if(debug){
				drawstring([inputCursorOrigin_x,inputCursorOrigin_y],
				strcat(ftos(inputCursorOrigin_x-screenX),"-",ftos(inputCursorOrigin_y-screenY)),[4,4],[0,1,0], 0.6, 0);
				UI_DebugPlayer();
			}
		break;
		case GAME_STATE_LEVELS:
			drawstring([inputCursorOrigin_x,inputCursorOrigin_y],
				strcat(ftos(inputCursorOrigin_x),"-",ftos(inputCursorOrigin_y)),[4,4],[0,1,0], 0.6, 0);
		break;
		case GAME_STATE_TEST:
			UI_DebugPlayer();
		break;
		default:
		break;
	}
	UI_GameState(w,h);
	UI_Message(w,h);
	UI_Warning(w,h);
}

void UI_Init()
{
	uiArtworkIcon = spawn();
}