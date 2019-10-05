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

//menu functions . In Menu_Init() add your menu entitites that will be visible in game

void Menu_Levels()
{
	menuLevelsTitle = CUI_Title("Level load",GAME_STATE_LEVELS,MENU_PAGE_LEVELS);
	menuLevelsList = CUI_List(menuWindow, [340,180],[20,80], GAME_STATE_LEVELS,MENU_PAGE_LEVELS);
	local int i;
	for(i=0;i<MENU_LEVELS_TOT;i++){
		if(menuLevels[i]!= ""){
			//more readable for humans, then re-add complete path in Level_Load func
			menuLevels[i] = strreplace(strcat("data/",FILE_PATH_LEVELS),"",menuLevels[i]);
			menuLevels[i] = strreplace(".level","",menuLevels[i]);
			CUI_ListChildAdd(menuLevelsList,menuLevels[i],File_LevelLoad);
		}
	}
}

void Menu_SpriteEdList()
{
	menuSpriteEdList = CUI_List(menuWindow, [150,200],[5,40], GAME_STATE_SPRITEED,MENU_PAGE_NULL);
	local int i;
	for(i=0;i<MENU_LEVELS_TOT;i++){
		if(menuSpriteEd[i]!= ""){
			spriteEdNameChosen = menuSpriteEd[i];
			CUI_ListChildAdd(menuSpriteEdList,menuSpriteEd[i],File_SpriteEdReadList);
		}
	}
}

void Menu_SpriteEdSaveArtwork()
{
	menuPage = MENU_PAGE_SPRITEED_SAVE;
	menuCondition = MENU_CONDITION_SPRITEEDSAVE;
}

void Menu_LevelSave()
{
	Game_StateLevelSave();
	menuCondition = MENU_CONDITION_LEVELSAVE;
}

void Menu_PageOptions()
{
	menuPage = MENU_PAGE_OPT;
}

void Menu_PageQuit()
{
	menuPage = MENU_PAGE_QUIT;
}

void Menu_PageMain()
{
	menuPage = MENU_PAGE_NULL;
}

void Menu_Init()
{
	local float minx = getviewprop(VF_MIN_X);
	local float miny = getviewprop(VF_MIN_Y);
	local float sizex = getviewprop(VF_SIZE_X);
	local float sizey = getviewprop(VF_SIZE_Y);
	//basic elems
	menuWindow = CUI_Window(menuWindow,[sizex,sizey],[minx,miny],[1,1,1],0,8,MENU_PAGE_NULL);
	//ed
	menuEdHeader = CUI_Window(menuWindow,[sizex,24],[0,0],[0.28,0.28,0.285],1,GAME_STATE_ED,MENU_PAGE_ED);
	menuEdButTiletype = CUI_Button(menuEdHeader,CUI_TYPE_BUTTON_ED,[0,0,0],Ed_TileTypeSwitch,strcat(MENU_IMG_PATH_ED,"tiletype.png"),"tile type",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdButTiledel = CUI_Button(menuEdButTiletype,CUI_TYPE_BUTTON_ED,[0,0,0],Ed_SelRemove,strcat(MENU_IMG_PATH_ED,"tiledel.png"),"remove tile",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdButToLevels = CUI_Button(menuEdButTiledel,CUI_TYPE_BUTTON_ED,[0,0,0],Game_StateLevels,strcat(MENU_IMG_PATH_ED,"backtolevels.png"),"level load",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdLevelSave = CUI_Button(menuEdButToLevels,CUI_TYPE_BUTTON_ED,[0,0,0],Menu_LevelSave,strcat(MENU_IMG_PATH_ED,"level_save.png"),"level save",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdLevelNew = CUI_Button(menuEdLevelSave,CUI_TYPE_BUTTON_ED,[0,0,0],Ed_LevelClear,strcat(MENU_IMG_PATH_ED,"level_new.png"),"level new",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdSpriteEd =  CUI_Button(menuEdLevelNew,CUI_TYPE_BUTTON_ED,[0,0,0],Game_StateSpriteEd,strcat(MENU_IMG_PATH_ED,"sprite_ed.png"),"Artwork editor",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdToMenu =  CUI_Button(menuEdSpriteEd,CUI_TYPE_BUTTON_ED,[sizex-200,0,0],Game_StateMenu,strcat(MENU_IMG_PATH_ED,"exit.png"),"level new",GAME_STATE_ED,MENU_PAGE_ED);
	menuCredits = CUI_Credits([sizex-80,4],GAME_STATE_ED,MENU_PAGE_ED);
	//ed sidebar
	menuWindowSidebar = CUI_Window(menuWindow,[UI_SIDEBAR_LEFT,sizey-24],[sizex-UI_SIDEBAR_LEFT,24],[0.28,0.28,0.285],1,GAME_STATE_ED,MENU_PAGE_ED);
	menuEdCboxLayerGround = CUI_Cbox(menuWindowSidebar,edLayerGround,[10,10,0],Ed_LayerGroundToggle,"Layer ground",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdCboxLayerEnt = CUI_Cbox(menuEdCboxLayerGround,edLayerEnt,[0,20,0],Ed_LayerEntToggle,"Layer entities",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdCboxLayerChar = CUI_Cbox(menuEdCboxLayerEnt,edLayerNpc,[0,20,0],Ed_LayerCharToggle,"Layer NPCs",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdCboxLayerPlayer = CUI_Cbox(menuEdCboxLayerChar,edLayerPlayer,[0,20,0],Ed_LayerPlayerToggle,"Layer player",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdCboxLayerPart = CUI_Cbox(menuEdCboxLayerPlayer,edLayerPart,[0,20,0],Ed_LayerPartToggle,"Layer particles",GAME_STATE_ED,MENU_PAGE_ED);
	menuEdCboxLayerArtwork = CUI_Cbox(menuEdCboxLayerPart,edLayerArtwork,[0,20,0],Ed_LayerArtworkToggle,"Layer artworks",GAME_STATE_ED,MENU_PAGE_ED);
	//ed level save
	menuEdSaveLevCont = CUI_Window(menuWindow,[0,0],[0,0],[0.28,0.28,0.285],0,GAME_STATE_LEVELSAVE,MENU_PAGE_NULL);
	menuEdSaveLevText = CUI_InputArea(menuWindow,menuEdSaveLevCont,"Level name:",[300,100],[20,20],GAME_STATE_LEVELSAVE,MENU_PAGE_NULL,MENU_CONDITION_LEVELSAVE);
	menuEdSaveLevSubmit = CUI_InputSubmit(menuWindow,menuEdSaveLevCont,[330,20],GAME_STATE_LEVELSAVE,MENU_PAGE_NULL,MENU_CONDITION_LEVELSAVE);
	menuEdSaveLevExit = CUI_Button(menuWindow,CUI_TYPE_BUTTON_ED,[sizex-40,10,0],Game_StateEd,strcat(MENU_IMG_PATH_ED,"backtoed.png"),"Go to editor",GAME_STATE_LEVELSAVE,MENU_PAGE_NULL);
	menuLevelButToEd = CUI_Button(menuWindow,CUI_TYPE_BUTTON_ED,[sizex-40,10,0],Game_StateEd,strcat(MENU_IMG_PATH_ED,"exit.png"),"Go to editor",GAME_STATE_LEVELS,MENU_PAGE_LEVELS);
	//menu main
	menuMainStart = CUI_Button(menuWindow,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,20,0],Game_StateRunning,"Start game","",GAME_STATE_MENU,MENU_PAGE_NULL);
	menuMainToEd = CUI_Button(menuMainStart,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,60,0],Game_StateEd,"Editor","",GAME_STATE_MENU,MENU_PAGE_NULL);
	menuMainOpt = CUI_Button(menuMainToEd,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,100,0],Menu_PageOptions,"Options","",GAME_STATE_MENU,MENU_PAGE_NULL);
	menuMainQuit = CUI_Button(menuMainOpt,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,280,0],Menu_PageQuit,"Quit","",GAME_STATE_MENU,MENU_PAGE_NULL);
	//menu options
	menuOptTitle = CUI_Title("Options",GAME_STATE_MENU,MENU_PAGE_OPT);
	menuOptBack = CUI_Button(menuMainOpt,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,280,0],Menu_PageMain,"Back","",GAME_STATE_MENU,MENU_PAGE_OPT);
	//menu quit (y/n)
	menuQuitTitle = CUI_Title("Quitting?",GAME_STATE_MENU,MENU_PAGE_QUIT);
	menuQuitYes =  CUI_Button(menuWindow,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,20,0],Game_Quit,"Yes","",GAME_STATE_MENU,MENU_PAGE_QUIT);
	menuQuitNo =  CUI_Button(menuWindow,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,60,0],Game_StateMenu,"No","",GAME_STATE_MENU,MENU_PAGE_QUIT);
	//paused
	menuButPauseResume = CUI_Button(menuWindow,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,20,0],Game_StateRunning,"Resume","",GAME_STATE_PAUSED,MENU_PAGE_NULL);
	menuPauseToEd = CUI_Button(menuWindow,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,100,0],Game_StateEd,"Editor","",GAME_STATE_PAUSED,MENU_PAGE_NULL);
	//sprite ed
	menuSpEdNewCanvas = CUI_Button(menuWindow,CUI_TYPE_BUTTON_ED,[0,0],Game_StateSpriteEd,strcat(MENU_IMG_PATH_ED,"level_new.png"),"Reset artwork",GAME_STATE_SPRITEED,MENU_PAGE_NULL);
	menuSpEdSaveCanvas = CUI_Button(menuSpEdNewCanvas,CUI_TYPE_BUTTON_ED,[0,0],Menu_SpriteEdSaveArtwork,strcat(MENU_IMG_PATH_ED,"level_save.png"),"Save artwork",GAME_STATE_SPRITEED,MENU_PAGE_NULL);
	menuSpEdQuit = CUI_Button(menuSpEdSaveCanvas,CUI_TYPE_BUTTON_ED,[0,0],Game_StateEd,strcat(MENU_IMG_PATH_ED,"exit.png"),"Back to editor",GAME_STATE_SPRITEED,MENU_PAGE_NULL);
	//sprite ed save menu
	menuSpEdSaveCont = CUI_Window(menuWindow,[0,0],[0,0],[0.28,0.28,0.285],0,GAME_STATE_SPRITEED,MENU_PAGE_SPRITEED_SAVE);
	menuSpEdSaveText = CUI_InputArea(menuWindow,menuEdSaveLevCont,"Artwork name:",[300,100],[20,20],GAME_STATE_SPRITEED,MENU_PAGE_SPRITEED_SAVE,MENU_CONDITION_SPRITEEDSAVE);
	menuSpEdSaveSubmit = CUI_InputSubmit(menuWindow,menuEdSaveLevCont,[330,20],MENU_PAGE_SPRITEED_SAVE,MENU_PAGE_SPRITEED_SAVE,MENU_CONDITION_SPRITEEDSAVE);
	//sprite ed palette
	menuPaletteWin = CUI_Window(menuWindow,[300,sizey-50],[sizex-320,50],[0.28,0.28,0.285],0,GAME_STATE_SPRITEED,MENU_PAGE_NULL);
	menuPalGreenBright =  CUI_ButtonPalette(menuPaletteWin,UI_COLOR_GREEN_BRIGHT);
	menuPalGreenMid =  CUI_ButtonPalette(menuPalGreenBright,UI_COLOR_GREEN_MID);
	menuPalGreenDark =  CUI_ButtonPalette(menuPalGreenMid,UI_COLOR_GREEN_DARK);
	menuPalGreenVeryDark =  CUI_ButtonPalette(menuPalGreenDark,UI_COLOR_GREEN_VERYDARK);
	menuPalBrownBright =  CUI_ButtonPalette(menuPalGreenVeryDark,UI_COLOR_BROWN_BRIGHT);
	menuPalBrownMid =  CUI_ButtonPalette(menuPalBrownBright,UI_COLOR_BROWN_MID);
	menuPalBrownDark =  CUI_ButtonPalette(menuPalBrownMid,UI_COLOR_BROWN_DARK);
	menuPalBrownVeryDark =  CUI_ButtonPalette(menuPalBrownDark,UI_COLOR_BROWN_VERYDARK);
	//lose
	menuLoseTitle = CUI_Title("You lose",GAME_STATE_LOSE,MENU_PAGE_NULL);
	menuLoseRestart = CUI_Button(menuWindow,CUI_TYPE_BUTTON_MENU,[(sizex/2)-128,20,0],Game_StateRunning,"Restart game","",GAME_STATE_LOSE,MENU_PAGE_NULL);
}

void Menu_Popup()
{
	menuPopup = TRUE;
	switch(menuPopup){
		case MENU_POPUP_LEVELOVERWRITE:
			menuPopupText = strcat("Level ",levelNameOverwrite," already taken. Overwrite? y / n");
		break;
	}
}

void Menu_PopupClose()
{
	menuPopup = FALSE;
}

void Menu_PopupDraw(float w,float h)
{
	if(menuPopup == TRUE){
		local float wd = stringwidth(menuPopupText,0,[8,8]),ht=h/8,m = 4;
		drawfill([w/2-wd,h/2-ht],[w/4+m,ht+m], [1,1,1],1);
		drawfill([w/2-wd+(m/2),h/2-ht+(m/2)],[w/4,ht], UI_COLOR_AZURE,1);
		drawstring([(m/2-1)+2,h-40-(m/2-1)],menuPopupText,[8,8],[0.1,0.1,0.1], 1, 0);
		drawstring([(m/2),h-40-(m/2-1)],menuPopupText,[8,8],[1,1,1], 1, 0);
	}
}


void Menu_Condition(float w,float h)
{
	if(menuCondition != 0){
		drawfill([0,0,0],[w,h], UI_COLOR_GREY_DARK,1);
	}
}

void Menu_ConditionOff()
{
	if(menuCondition != 0){
		menuCondition = 0;
		inputTextEntity = world;
		inputText = "";
		Game_StateEd();
	}
}

void Menu_Bg(float w,float h)
{
	if(gameState == GAME_STATE_MENU || gameState == GAME_STATE_PAUSED){
		drawpic([0,0],"gfx/bg.png",[w,h],[1,1,1],1);
	}
}

void Menu_Submit()
{
	if(menuCondition == MENU_CONDITION_LEVELSAVE){
		//Level_SaveSimple();
		File_LevelSave();
	}
	else if(menuCondition == MENU_CONDITION_SPRITEEDSAVE){
		//Level_SaveSimple();
		File_SpriteEdWriteArtwork();
	}
	Menu_ConditionOff();
}

void Menu_PostUpdate(float w, float h)
{
	Menu_Bg(w,h);
	Menu_Condition(w,h);
	
	switch(gameState){
		case GAME_STATE_ED:
			drawline(1,[0,24],[w,24],[0.6,0.6,0.6],0.5);
		break;
	}
	Menu_PopupDraw(w,h);
}