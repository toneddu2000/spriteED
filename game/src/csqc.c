
void CSQC_Init(float apilevel, string enginename, float engineversion)
{
	Game_Init();
}

void CSQC_WorldLoaded(){}

noref float CSQC_ConsoleCommand(string cmd){return TRUE;}

float CSQC_InputEvent(float evtype,float scanx,float chary,float devid)
{
	float i=Input_Manager(evtype,scanx,chary,devid);return i;
}

void CSQC_Input_Frame()
{
	Phys_Move(player);
}

void CSQC_UpdateView(float vwidth, float vheight, float notmenu)
{
	clearscene();
	Game_Update();
	renderscene();
	Game_PostUpdate(vwidth,vheight);
	screenGlobalCoordX = screenX+edGrid_x;
	screenGlobalCoordY = screenY+edGrid_y;

	//cprint(spriteLibrary[spriteLibraryIdx]);
	//cprint(vtos(inputCursorOrigin)," - ",vtos([w,h]));
	//cprint(ftos(screenTimer)," - ",ftos(screenScrollEnabled));
	//cprint(player.spriteImgPath);
	//cprint(ftos(screenGlobalCoordX)," - ",ftos(screenGlobalCoordY));
	//cprint(strcat(player.spriteImgSubfolder,"_idle",ftos(rint(player.spriteFrame)),"_up",".png"));
	//cprint(ftos(edEntSpawnedCnt)," * ");
}