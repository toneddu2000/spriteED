void Game_StateTest()
{
	gameState = GAME_STATE_TEST;
	menuPage = MENU_PAGE_NULL;
	Input_Cursor();
}

void Game_StateRunning()
{
	gameState = GAME_STATE_RUNNING;
	menuPage = MENU_PAGE_NULL;
	Input_Cursor();
}

void Game_StateMenu()
{
	gameState = GAME_STATE_MENU;
	menuPage = MENU_PAGE_NULL;
	Input_Cursor();
}

void Game_StateLevels()
{
	gameState = GAME_STATE_LEVELS;
	menuPage = MENU_PAGE_LEVELS;
	Input_Cursor();
	File_LevelsFolderRead();
	Menu_Levels();
}

void Game_StateLevelSave()
{
	gameState = GAME_STATE_LEVELSAVE;
	menuPage = MENU_PAGE_NULL;
	Input_Cursor();
}

void Game_StateEd()
{
	gameState = GAME_STATE_ED;
	menuPage = MENU_PAGE_ED;
	edLoaded = 0;
	Input_Cursor();
	Ed_Reset();
}

void Game_StatePaused()
{
	gameState = GAME_STATE_PAUSED;
	menuPage = MENU_PAGE_NULL;
	Input_Cursor();
}
void Game_StateSpriteEd()
{
	gameState = GAME_STATE_SPRITEED;
	menuPage = MENU_PAGE_NULL;
	Input_Cursor();
	SpriteEd_Init();
	File_SpriteEdFolderRead();
	Menu_SpriteEdList();
}

void Game_StateTestToggle()
{
	if(gameState == GAME_STATE_TEST){
		Game_StateEd();
	}
	else if(gameState == GAME_STATE_ED){
		Game_StateTest();
	}
}

void Game_Init()
{
	Game_StateMenu();
	Screen_Init();
	Input_Init();
	Sprite_Init();
	Ed_Init();
	Menu_Init();
	UI_Init();
	Player_Init();
}

void Game_Quit()
{
	localcmd("quit\n");
}

void Game_Update()
{
	Input_Update();
	Ed_Update();
	Player_Update();
	Npc_Update();
	Screen_Update();
}

void Game_PausedToggle()
{
	if(gameState == GAME_STATE_RUNNING){
		Game_StatePaused();
	}
	else if(gameState == GAME_STATE_PAUSED){
		Game_StateRunning();
	}
}

void Game_PostUpdate(float w,float h)
{
	//clear screen
	drawfill([0,0],[w,h],[0.2,0.2,0.2],1);
	Input_PostUpdate(w,h);
	Sprite_PostUpdate();
	Ed_PostUpdate(w,h);
	SpriteEd_PostUpdate(w,h);
	Menu_PostUpdate(w,h);
	CUI_PostUpdate(gameState);
	UI_PostUpdate(w,h);
}