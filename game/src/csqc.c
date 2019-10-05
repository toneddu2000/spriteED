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

//main entry

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
	cprint(zaz);
}