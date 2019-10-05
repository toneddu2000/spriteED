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

//definitions file

//game
float			gameState;
.float			gameClass;
const float		GAME_CLASS_NULL = 0;
const float		GAME_CLASS_SPRITE = 1;
const float		GAME_CLASS_CUI = 2;
const float		GAME_CLASS_SPRITEED = 2;
const float		GAME_STATE_MENU = 0;
const float		GAME_STATE_RUNNING = 1;
const float		GAME_STATE_ED = 2;
const float		GAME_STATE_TEST = 3;
const float		GAME_STATE_LEVELS = 4;
const float		GAME_STATE_PAUSED = 5;
const float		GAME_STATE_LEVELSAVE = 6;
const float		GAME_STATE_SPRITEED = 7;
const float		GAME_STATE_LOSE = 8;
const float		GAME_RETHINK = 0.02;
//sprite
entity			spriteEntity;
.entity			spriteEntTop,spriteEntShdw;
const float		SPRITE_LIBRARY_MAX = 32;
string 			spriteLibrary[SPRITE_LIBRARY_MAX],spriteArtworkSelected;
float			spriteLibraryIdx,spriteGroundLibrarySize;
.vector 		spriteDim,spriteCol,spriteOrg,spriteOrgUnstuck;
.float			spriteClass,spriteActive,spriteAlpha,spriteCharDir,spriteFrame;
.float			spriteActionWalkEnd;
.float			spriteActionIdleEnd;
.float			spriteActionAttackEnd;
.float			spriteActionAnimationEnd,spriteActionCurrentEnd;
.string			spriteImgPath,spriteImgFolder,spriteImgSubfolder,spriteImgName,spriteActionCurrent;
.string			spriteEntShdwImgPath,spriteEntTopImgPath,spriteArtworkName;
const float 	SPRITE_CLASS_GROUND = 0;
const float 	SPRITE_CLASS_ENT = 1;
const float 	SPRITE_CLASS_NPC = 2;
const float 	SPRITE_CLASS_PLAYER = 3;
const float 	SPRITE_CLASS_PART = 4;
const float 	SPRITE_CLASS_ARTWORK = 5;
const float 	SPRITE_CHAR_DIR_UP = 0;
const float 	SPRITE_CHAR_DIR_DOWN = 1;
const float 	SPRITE_CHAR_DIR_LEFT = 2;
const float 	SPRITE_CHAR_DIR_RIGHT = 3;
const string	SPRITE_FOLDER = "assets/sprites/";
const string	SPRITE_FOLDER_GROUND = "ground/";
const string	SPRITE_FOLDER_ENT = "ent/";
const string	SPRITE_FOLDER_CHAR = "npc/";
const string	SPRITE_FOLDER_PLAYER = "player/";
const string	SPRITE_FOLDER_PART = "part/";
//spriteEd
entity			spriteEdEntArtwork;
string			spriteEdNameChosen;
vector			spriteEdChosenColor;
const	float	SPRITE_ED_PIX_MAX = 1024;
.vector			spriteEdPix[SPRITE_ED_PIX_MAX],spriteEdOrg[SPRITE_ED_PIX_MAX];
//input
entity			inputTextEntity;
vector			inputCursorOrigin,inputCursorDelta,inputCursorDirOld;
string			inputText;
float			inputCursor,inputScan;
float			inputMouse1Pressed,inputMouse2Pressed,inputMouse3Pressed;
float 			inputDirTime,inputDirRead;
const float		INPUT_CURSOR_DIR_RIGHT = 0;
const float		INPUT_CURSOR_DIR_LEFT = 1;
const float		INPUT_CURSOR_DIR_DOWN = 2;
const float		INPUT_CURSOR_DIR_UP = 3;
//ui
const float		UI_HEADER_HEIGHT = 20;
const float		UI_SIDEBAR_LEFT = 140;
const vector	UI_FONT_SMALL = [8,8];
const vector	UI_FONT_MEDIUM = [10,10];
const vector	UI_FONT_BIG = [14,14];
const vector	UI_COLOR_AZURE = [0.252,0.553,0.912];
const vector	UI_COLOR_GREY_BRIGHT  = [0.35,0.35,0.35];
const vector	UI_COLOR_GREY_MID  = [0.285,0.285,0.285];
const vector	UI_COLOR_GREY_DARK  = [0.18,0.18,0.18];
const vector	UI_COLOR_AZURE_DIRT  = [0.282,0.502,0.595];
const vector	UI_COLOR_GREEN_BRIGHT  = [0.174,0.965,0.004];
const vector	UI_COLOR_GREEN_MID  = [0.056,0.815,0.006];
const vector	UI_COLOR_GREEN_DARK  = [0.033,0.480,0.004];
const vector	UI_COLOR_GREEN_VERYDARK  = [0.018,0.255,0.002];
const vector	UI_COLOR_BROWN_BRIGHT  = [0.970,0.456,0.002];
const vector	UI_COLOR_BROWN_MID  = [0.620,0.291,0.001];
const vector	UI_COLOR_BROWN_DARK  = [0.465,0.218,0.001];
const vector	UI_COLOR_BROWN_VERYDARK  = [0.260,0.122,0.001];
const vector	UI_COLOR_BLUE_BRIGHT  = [0.008,0.023,0.945];
const vector	UI_COLOR_BLUE_MID  = [0.005,0.014,0.595];
const vector	UI_COLOR_BLUE_DARK  = [0.002,0.007,0.290];
const vector	UI_COLOR_ORANGE  = [0.980,0.416,0.020];
const vector	UI_COLOR_VIOLET  = [0.940,0.003,0.699];
const vector	UI_COLOR_RED  = [1,0,0];
const vector	UI_COLOR_GREEN  = [0,1,0];
const vector	UI_COLOR_BLUE  = [0,0,1];
const vector	UI_COLOR_HOVER  = UI_COLOR_ORANGE;
//ui
entity			uiArtworkIcon;
float			uiMessageTime,uiWarningTime;
string 			uiMessage,uiWarning;
//ed
float			edGridSize,edTileType,edLayerGround,edLayerEnt,edLayerNpc,edLayerPlayer,edLayerPart,edLayerArtwork;
float			edSelection,edLoaded,edEntOnScreen;
.float			edSelected,edEntNum,edHealth;
.vector			edOrg;
vector			edGrid;
const float		ED_SEL_MAX=32;
entity			edSel[ED_SEL_MAX];
//cui
.entity			cuiParent,cuiListUp,cuiListDown,cuiContainer;
.vector			cuiDim,cuiOrg,cuiBgCol,cuiOrgFixed;
.string			cuiLbl,cuiImg,cuiTooltip;
.float			cuiClass,cuiClickable,cuiActive,cuiVis,cuiPage,cuiAlpha,cuiType,cuiListItemClicked,cuiSelected;
.float			cuiHover,cuiCboxActive,cuiListChildTot,cuiListOffset,cuiListIncrY,cuiListCharSize,cuiCondition,cuiTooltipDraw;
.void() 		cuiOnRelease,cuiOnPress;
const float		CUI_LIST_TOT = 50;
.entity			cuiListChild[CUI_LIST_TOT];
const float		CUI_CLASS_WINDOW = 1;
const float		CUI_CLASS_BUTTON = 2;
const float		CUI_CLASS_CBOX = 3;
const float		CUI_CLASS_LIST = 4;
const float		CUI_CLASS_LISTCHILD = 5;
const float		CUI_CLASS_LISTGRIP = 6;
const float		CUI_CLASS_LISTUP = 7;
const float		CUI_CLASS_LISTDOWN = 8;
const float		CUI_CLASS_INPUTAREA = 9;
const float		CUI_CLASS_INPUTSUBMIT = 10;
const float		CUI_CLASS_SLIDER = 11;
const float		CUI_CLASS_BUTTON_PALETTE = 12;
const float		CUI_CLASS_TITLE = 13;
const float		CUI_CLASS_CREDITS = 14;
const float		CUI_TYPE_BUTTON_MENU = 1;
const float		CUI_TYPE_BUTTON_BAROPTIONS = 2;
const float		CUI_TYPE_BUTTON_ARROW = 3;
const float		CUI_TYPE_BUTTON_ED = 4;
const float		CUI_TYPE_BUTTON_LIST = 5;
const float		CUI_LIST_ENTS_RENDERED = 5;
const float		CUI_LIST_GRIPWIDTH = 10;
const float		CUI_SUBMIT_MAX = 10;
const vector	CUI_COLOR_GREY_BRIGHT  = [0.35,0.35,0.35];
const vector	CUI_COLOR_AZURE_DIRT  = [0,0.8,1];
const vector	CUI_COLOR_AZURE  = [0.252,0.553,0.912];
//menu
entity			menuWindow,menuEdHeader,menuEdButTiletype,menuEdButTiledel;
entity			menuWindowSidebar,menuEdCboxLayerGround,menuEdCboxLayerEnt,menuEdCboxLayerChar;
entity			menuEdCboxLayerPlayer,menuEdCboxLayerPart,menuEdButToLevels,menuEdLevelSave,menuEdLevelNew;
entity			menuEdCboxLayerArtwork,menuLevelsList,menuSpriteEdList,menuLevelButToEd;
entity			menuMainToEd,menuButPauseResume,menuPauseToEd,menuMainStart;
entity			menuEdSaveLevCont,menuEdSaveLevText,menuEdSaveLevSubmit,menuEdSaveLevExit;
entity			menuEdSpriteEd,menuSpEdNewCanvas,menuSpEdSaveCanvas,menuSpEdSaveCont,menuSpEdSaveText;
entity			menuSpEdQuit,menuEdToMenu,menuSpEdSaveSubmit;
entity			menuPaletteWin,menuPalGreenBright,menuPalGreenMid,menuPalGreenDark,menuPalGreenVeryDark;
entity			menuPalBrownBright,menuPalBrownMid,menuPalBrownDark,menuPalBrownVeryDark;
entity			menuMainOpt,menuQuitTitle,menuMainQuit,menuQuitYes,menuQuitNo;
entity			menuOptTitle,menuOptBack,menuCredits,menuLoseTitle,menuLoseRestart,menuLevelsTitle;
float			menuPage,menuPopup,menuCondition;
const float		MENU_LEVELS_TOT = 50;
string			menuLevels[MENU_LEVELS_TOT],menuSpriteEd[MENU_LEVELS_TOT],menuPopupText;
const float		MENU_PAGE_NULL = 0;
const float		MENU_PAGE_ED = 1;
const float		MENU_PAGE_LEVELS = 2;
const float		MENU_PAGE_PAUSEMODE = 3;
const float		MENU_PAGE_MAINMENU = 4;
const float		MENU_PAGE_SPRITEED_SAVE = 5;
const float		MENU_PAGE_OPT = 6;
const float		MENU_PAGE_OPTVIDEO = 7;
const float		MENU_PAGE_OPTAUDIO = 8;
const float		MENU_PAGE_QUIT = 9;
const float		MENU_POPUP_LEVELOVERWRITE = 1;
const float		MENU_POPUP_QUIT = 2;
const float		MENU_POPUP_QUIT = 2;
const string	MENU_IMG_PATH = "gfx/";
const string	MENU_IMG_PATH_ED = "gfx/ed/";
const float		MENU_CONDITION_LEVELSAVE = 200;
const float		MENU_CONDITION_SPRITEEDSAVE = 300;
//player
entity			player;
float			playerSpawned;
//ent
//entity			entEnemy,entFriend,entBoss;
//phys
.float			physMoving,physColliding,physCollidingTime,physCollisionDist;
.vector			physDirection;
const float		PHYS_UNSTUCKTIME = 0.1;
//level
entity			levelEntity;
string			levelNameChosen,levelNameOverwrite;
float			levelSave,levelNew,levelOpen,levelOverwrite;
.float			levelSaveThis;
//file
const string	FILE_PATH_LEVELS = "levels/";
const string	FILE_PATH_ARTWORKS = "artworks/";
//debug
#define			DEBUG
float			debug;
//char
.entity			charTarget;
.vector			charVelocity;
.float			charState,charAttackFinished,charHealth,charDamage,charDamaged;
.float			charAttackTime,charDamageTime,charAttacking,charSpeed,charAggr;
.string			charOrientation;
const float 	CHAR_STATE_IDLE = 0;
const float 	CHAR_STATE_WALK = 1;
const float 	CHAR_STATE_ATTACK = 2;
const float 	CHAR_RADIUS_ATTACK = 50;
const float 	CHAR_RADIUS_IDLE = 256;
//part/
.float			partLife,partLifeCnt;
//screen
float			screenX,screenY,screenGlobalCoordX,screenGlobalCoordY,screenScrollEnabled,screenTimer;
//prototypes
float 			Sprite_Collision(entity p,entity e,vector dir);
float 			Sprite_CollisionMoz(entity subject, entity collider);
entity 			Sprite_Spawn(float cl,string imgname,vector org, vector dim,vector col,float a);
void 			Part_Spawn(vector pos,string name);
void 			Ed_SelAdd(entity e);
void			Game_PausedToggle();
void 			Game_StateTest();
void 			Game_StateRunning();
void 			Game_StateMenu();
void 			Game_StateEd();
void 			Game_StateTestToggle();
void 			Game_StateLevels();
void 			Game_StateLevelSave();
void 			Game_StateLose();
void 			Game_StateSpriteEd();
void 			Game_Quit();
void			Menu_ConditionOff();
void 			Menu_Submit();
