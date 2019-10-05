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

//Input 

void Input_Cursor()
{
	if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		inputCursor = FALSE;
	}
	else{
		inputCursor = TRUE;
	}
	setcursormode(inputCursor);
}

void Input_Borders(float w,float h)
{
	if(gameState == GAME_STATE_ED){
		if(screenScrollEnabled == TRUE /*&& inputMouse3Pressed == TRUE*/){
			if(inputCursorOrigin_x <= 0){
				screenX+=edGridSize;
				screenScrollEnabled = FALSE;
			}
			else if(inputCursorOrigin_x >= w-2){
				screenX-=edGridSize;
				screenScrollEnabled = FALSE;	
			}
			else if(inputCursorOrigin_y <= 0){
				screenY+=edGridSize;
				screenScrollEnabled = FALSE;
			}
			else if(inputCursorOrigin_y >= h-2){
				screenY-=edGridSize;
				screenScrollEnabled = FALSE;
			}			
			screenScrollEnabled = FALSE;
		}
		else{
			screenTimer += frametime * 1;
			if(screenTimer > 0.1){
				screenTimer = 0;
				screenScrollEnabled = TRUE;
			}
		}
	}
	else if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		if(player != world){
			local float sizex = getviewprop(VF_SIZE_X);
			local float sizey = getviewprop(VF_SIZE_Y);
			screenX = (sizex/2)-player.spriteOrg_x;
			screenY = (sizey/2)-player.spriteOrg_y;
		}
	}
}

void Input_CursorDelta() 
{
	inputDirTime += frametime * 1;
	if(inputDirTime > 1){
		inputDirRead = TRUE;		
	}
	if(inputDirRead == TRUE){
		//deal with the horizontal case
		if (inputCursorDirOld_x < inputCursorOrigin_x) {
			inputCursorDelta_x = INPUT_CURSOR_DIR_RIGHT;
		}
		else {
			inputCursorDelta_x = INPUT_CURSOR_DIR_LEFT;
		}
		//deal with the vertical case
		if (inputCursorDirOld_y < inputCursorOrigin_y) {
			inputCursorDelta_y = INPUT_CURSOR_DIR_DOWN;
		} else {
			inputCursorDelta_y = INPUT_CURSOR_DIR_UP;
		}
		inputCursorDirOld_x = inputCursorOrigin_x;
		inputCursorDirOld_y = inputCursorOrigin_y;
		inputDirRead = FALSE;
		inputDirTime = 0;
		
	}
}

void Input_MouseButton1Pressed()
{
	inputMouse1Pressed = TRUE;
	
}

void Input_MouseButton2Pressed()
{
	inputMouse2Pressed = TRUE;
}

void Input_MouseButton3Pressed()
{
	inputMouse3Pressed = TRUE;
}

void Input_MouseWheelDownPressed()
{
	
}

void Input_MouseWheelUpPressed()
{
	
}

void Input_MouseButton1Released()
{
	inputMouse1Pressed = FALSE;
	CUI_TriggerButton1Released();
	Ed_TileSpawn();
	Ed_LoadedEnable();
	
	//Player_Attack();
}

void Input_MouseButton2Released()
{
	inputMouse2Pressed = FALSE;
	Ed_TileSel();
}


void Input_MouseButton3Released()
{
	inputMouse3Pressed = FALSE;
	
}

void Input_MouseWheelDownReleased()
{
	
}

void Input_MouseWheelUpReleased()
{
	
}

void Input_SpaceReleased()
{
	Ed_TileTypeSwitch();
	Player_Attack();
}

void Input_EscReleased()
{
	Ed_SelClear();
	Game_PausedToggle();
	Menu_ConditionOff();
}

void Input_TextManager(float scanx)
{
	if(menuCondition != 0)
	{
		if(inputTextEntity != world){
			//LETTER A
			if(scanx == 97){
				inputText = strcat(inputText,"a");
			}
			//LETTER B
			if(scanx == 98){
				inputText = strcat(inputText,"b");
			}
			//LETTER C
			if(scanx == 99){
				inputText = strcat(inputText,"c");
			}
			//LETTER D
			if(scanx == 100){
				inputText = strcat(inputText,"d");
			}
			//LETTER E
			if(scanx == 101){
				inputText = strcat(inputText,"e");
			}
			//LETTER F
			if(scanx == 102){
				inputText = strcat(inputText,"f");
			}
			//LETTER G
			if(scanx == 103){
				inputText = strcat(inputText,"g");
			}
			//LETTER H
			if(scanx == 104){
				inputText = strcat(inputText,"h");
			}
			//LETTER I
			if(scanx == 105){
				inputText = strcat(inputText,"i");
			}
			//LETTER J
			if(scanx == 106){
				inputText = strcat(inputText,"j");
			}
			//LETTER K
			if(scanx == 107){
				inputText = strcat(inputText,"k");
			}
			//letter L
			if (scanx == 108){
				inputText = strcat(inputText,"l");
			}
			//LETTER M
			if(scanx == 109){
				inputText = strcat(inputText,"m");
			}
			//LETTER N
			if(scanx == 110){
				inputText = strcat(inputText,"n");
			}
			//letter O
			if (scanx == 111){
				inputText = strcat(inputText,"o");
			}
			//letter P
			if (scanx == 112){
				inputText = strcat(inputText,"p");
			}
			//letter Q
			if (scanx == 113){
				inputText = strcat(inputText,"q");
			}
			//letter R
			if (scanx == 114){
				inputText = strcat(inputText,"r");
			}
			//letter S
			if (scanx == 115){
				inputText = strcat(inputText,"s");
			}
			//letter T
			if (scanx == 116){
				inputText = strcat(inputText,"t");
			}
			//letter U
			if (scanx == 117){
				inputText = strcat(inputText,"u");
			}
			//letter V
			if (scanx == 118){
				inputText = strcat(inputText,"v");
			}
			//letter W
			if (scanx == 119){
				inputText = strcat(inputText,"w");
			}
			//letter X
			if (scanx == 120){
				inputText = strcat(inputText,"x");
			}
			//letter Y
			if (scanx == 121){
				inputText = strcat(inputText,"y");
			}
			//letter Z
			if (scanx == 122){
				inputText = strcat(inputText,"z");
			}
			//backspace
			if (scanx == K_BACKSPACE){
				inputText = substring(inputText,0,strlen(inputText)-1);
			}
		}
		//enter
		if (scanx == K_ENTER){
			Menu_Submit();
		}
	}
}

float Input_Manager(float evtype, float scanx,float chary,float devid)
{
	switch(evtype){
		case IE_KEYDOWN:
			if (scanx == K_MOUSE1){
				Input_MouseButton1Pressed();
			}
			else if (scanx == K_MOUSE2){
				Input_MouseButton2Pressed();
			}
			else if (scanx == K_MOUSE3){
				Input_MouseButton3Pressed();
			}
		break;
		case IE_KEYUP:
			inputScan = scanx;
			if (scanx == K_MOUSE1){
				Input_MouseButton1Released();
			}
			else if (scanx == K_MOUSE2){
				Input_MouseButton2Released();
			}
			else if (scanx == K_MOUSE3){
				Input_MouseButton3Released();
			}
			else if (scanx == K_ESCAPE){
				Input_EscReleased();
			}
			if(menuCondition == 0){
				if (scanx == K_UPARROW){
				}
				else if (scanx == K_DOWNARROW){
				}
				else if (scanx == K_LEFTARROW){
				}
				else if (scanx == K_RIGHTARROW){
				}
				else if (scanx == K_TAB){
					Game_StateTestToggle();
					Input_Cursor();
				}
				else if (scanx == K_SPACE){
					Input_SpaceReleased();
				}
				else if (scanx == K_MWHEELUP){
					Ed_LibraryDown();
				}
				else if (scanx == K_MWHEELDOWN){
					Ed_LibraryUp();
				}
				//LETTER A
				if(scanx == 97){
					
				}
				//LETTER B
				else if(scanx == 98){

				}
				//LETTER C
				else if(scanx == 99){

				}
				//LETTER D
				else if(scanx == 100){

				}
				//LETTER E
				else if(scanx == 101){

				}
				//LETTER F
				else if(scanx == 104){

				}
				//LETTER X
				else if(scanx == 120){
					Ed_SelRemove();
				}
				//letter Q
				else if (scanx == 113){
					localcmd("quit");
				}
				else if (scanx == K_ENTER){
					//localcmd("map game.map");
				}
			}
			else{
				Input_TextManager(scanx);
			}
		break;
		case IE_MOUSEABS:
			inputCursorOrigin_x = scanx;
			inputCursorOrigin_y = chary;		
		return TRUE;
	}
	return 0;
}

void Input_Update(){/*Input_CursorDelta();*/}
void Input_PostUpdate(float w,float h){Input_Borders(w,h);}

void Input_Init(){screenScrollEnabled=TRUE;inputCursor = TRUE;}