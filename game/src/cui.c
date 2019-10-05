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

//craFTEr User Interface functions

void CUI_HoverOn(entity e)
{
	//if(e.cuiClass == CUI_CLASS_BUTTON){
		e.cuiHover = TRUE;
	//}
}

void CUI_HoverOff(entity e)
{
	//if(e.cuiClass == CUI_CLASS_BUTTON && e.cuiActive == FALSE){
		e.cuiHover = FALSE;
	//}
}

void CUI_Hover(entity e)
{
	local float xaxis = e.cuiOrg_x + e.cuiDim_x;
	local float yaxis = e.cuiOrg_y + e.cuiDim_y;
	
	if(inputCursor == TRUE){
		switch(e.cuiClass){
			case CUI_CLASS_BUTTON:
				if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > e.cuiOrg_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > e.cuiOrg_y){
					CUI_HoverOn(e);
					if(e.cuiType == CUI_TYPE_BUTTON_ED){
						e.cuiTooltipDraw = TRUE;
					}
				}
				else{
					CUI_HoverOff(e);
					if(e.cuiType == CUI_TYPE_BUTTON_ED){
						e.cuiTooltipDraw = FALSE;
					}
				}
			break;
			case CUI_CLASS_BUTTON_PALETTE:
				if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > e.cuiOrg_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > e.cuiOrg_y){
					CUI_HoverOn(e);
				}
				else{
					CUI_HoverOff(e);
				}
			break;
			case CUI_CLASS_CREDITS:
				if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > e.cuiOrg_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > e.cuiOrg_y){
					CUI_HoverOn(e);
				}
				else{
					CUI_HoverOff(e);
				}
			break;
			case CUI_CLASS_LIST:
				local vector upOrg=e.cuiListUp.cuiOrg,upDim=e.cuiListUp.cuiDim;
				local vector dwOrg=e.cuiListDown.cuiOrg,dwDim=e.cuiListDown.cuiDim;
				local vector io = inputCursorOrigin;
				//list child
				local vector childOrg,childDim;
				local int k;
				for(k=0;k<e.cuiListChildTot;k++){
					if(e.cuiListChild[k]!=world){
						childOrg = e.cuiListChild[k].cuiOrg;
						childDim = e.cuiListChild[k].cuiDim;
						if(io_x < (childOrg_x + childDim_x) && io_x > childOrg_x && 
							io_y < (childOrg_y + childDim_y) && io_y > childOrg_y){
							e.cuiListChild[k].cuiHover = TRUE;
						}
						else{
							e.cuiListChild[k].cuiHover = FALSE;
						}
					}
				}
				//list up
				if(io_x < (upOrg_x + upDim_x) && io_x > upOrg_x && 
					io_y < (upOrg_y + upDim_y) && io_y > upOrg_y){
					e.cuiListUp.cuiHover = TRUE;
				}
				else{
					e.cuiListUp.cuiHover = FALSE;
				}
				//list down
				if(io_x < (dwOrg_x + dwDim_x) && io_x > dwOrg_x && 
					io_y < (dwOrg_y + dwDim_y) && io_y > dwOrg_y){
					e.cuiListDown.cuiHover = TRUE;
				}
				else{
					e.cuiListDown.cuiHover = FALSE;
				}
			break;
			case CUI_CLASS_INPUTAREA:
				if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > e.cuiOrg_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > e.cuiOrg_y){
					CUI_HoverOn(e);
				}
				else{
					CUI_HoverOff(e);
				}
			break;
			case CUI_CLASS_INPUTSUBMIT:
				if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > e.cuiOrg_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > e.cuiOrg_y){
					CUI_HoverOn(e);
				}
				else{
					CUI_HoverOff(e);
				}
			break;
		}
	}
}

void CUI_EvMouseReleased(entity e)
{
	local float xaxis = e.cuiOrg_x + e.cuiDim_x;
	local float yaxis = e.cuiOrg_y + e.cuiDim_y;
	
	if(inputCursor == TRUE){
		if(inputCursorOrigin_x < xaxis && inputCursorOrigin_x > e.cuiOrg_x && inputCursorOrigin_y < yaxis && inputCursorOrigin_y > e.cuiOrg_y){
			//avoid click other cui elements on different cuiVis
			if(e.cuiClickable){
				if(e.cuiClass == CUI_CLASS_BUTTON){
					e.cuiOnRelease();
				}
				else if(e.cuiClass == CUI_CLASS_BUTTON_PALETTE){
					spriteEdChosenColor = e.cuiBgCol;
					e.cuiSelected = TRUE;
				}
				else if(e.cuiClass == CUI_CLASS_CBOX){
					e.cuiCboxActive = !e.cuiCboxActive;
					e.cuiOnRelease();
				}
				else if(e.cuiClass == CUI_CLASS_INPUTAREA){
					if(e.cuiCondition == menuCondition){
						inputTextEntity = e;
						e.cuiSelected = TRUE;
					}
				}
				else if(e.cuiClass == CUI_CLASS_INPUTSUBMIT){
					if(e.cuiCondition == menuCondition){
						//if(e.cuiContainer == inputTextEntity.cuiContainer){
							e.cuiOnRelease();
						//}
					}
				}
				else if(e.cuiClass == CUI_CLASS_LIST){
					//single click for every entry of the list
					local float sizey = getviewprop(VF_SIZE_Y);
					local vector io = inputCursorOrigin;
					local int k;
					for(k=0;k<e.cuiListChildTot;k++){
						local float ech_x = e.cuiListChild[k].cuiOrg_x + e.cuiListChild[k].cuiDim_x;
						local float ech_y = e.cuiListChild[k].cuiOrg_y + e.cuiListChild[k].cuiDim_y;
						if(io_x < ech_x && io_x > e.cuiListChild[k].cuiOrg_x && 
						io_y < ech_y && io_y > e.cuiListChild[k].cuiOrg_y){
							e.cuiListItemClicked = k;
							e.cuiListChild[k].cuiOnRelease();
						}
					}
					//listup	
					local float incr = e.cuiDim_y/CUI_LIST_ENTS_RENDERED;
					local float barwd = CUI_LIST_GRIPWIDTH;
					local vector upOrg=e.cuiListUp.cuiOrg,upDim=e.cuiListUp.cuiDim;
					local vector dwOrg=e.cuiListDown.cuiOrg,dwDim=e.cuiListDown.cuiDim;
					if(io_x < (upOrg_x + upDim_x) && io_x > upOrg_x && 
					io_y < (upOrg_y + upDim_y) && io_y > upOrg_y){
						//click on up arrow
						if(e.cuiListOffset > 0){						
							e.cuiListIncrY+=incr;
							e.cuiListOffset--;
						}
					}
					//listdown
					else if(io_x < (dwOrg_x + dwDim_x) && io_x > dwOrg_x && 
					io_y < (dwOrg_y + dwDim_y) && io_y > dwOrg_y){
						//click on down arrow
						if(e.cuiListOffset < e.cuiListChildTot - CUI_LIST_ENTS_RENDERED){
							e.cuiListIncrY-=incr;
							e.cuiListOffset++;
						}
					}
				}
			}
			CUI_HoverOn(e);
			e.cuiActive = TRUE;
		}
		else{
			if(e.cuiClass == CUI_CLASS_INPUTAREA){
				if(inputTextEntity == e){
					inputTextEntity = world;
				}
			}
			CUI_HoverOff(e);
			e.cuiActive = FALSE;
			e.cuiSelected = FALSE;
		}
	}
}

void CUI_TriggerButton1Released()
{
	local entity e = world;

	//cycle trough all the ui entities finding the one which is in the correct hover position while mouse button is clicking
	while ((e = nextent(e))){
		if(e.gameClass == GAME_CLASS_CUI){
			CUI_EvMouseReleased(e);
		}
	}
}

entity CUI_Button(entity parent, float typebut, vector coord,void() onrelease,string lbl,string tip, float vis,float page)
{
	local entity e = spawn();
	
	e.cuiParent = parent;
	if(e.cuiParent.cuiClass != CUI_CLASS_WINDOW){
		e.cuiOrg = [e.cuiParent.cuiOrg_x + e.cuiParent.cuiDim_x + coord_x,e.cuiParent.cuiOrg_y + coord_y,0];
	}
	else{
		e.cuiOrg = [e.cuiParent.cuiOrg_x + coord_x,e.cuiParent.cuiOrg_y + coord_y,0];
	}
	e.cuiClass = CUI_CLASS_BUTTON;
	e.gameClass = GAME_CLASS_CUI;
	e.cuiVis = vis;
	e.cuiPage = page;
	e.cuiLbl = lbl;
	e.cuiTooltip = tip;
	e.cuiType = typebut;
	e.cuiAlpha = 1;
	e.cuiBgCol = [1,1,1];
	switch(e.cuiType){
		case CUI_TYPE_BUTTON_MENU:
			e.cuiDim_x = 128;
			e.cuiDim_y = 32;
			e.cuiOrg = [20,coord_y];
		break;
		case CUI_TYPE_BUTTON_BAROPTIONS:
			e.cuiDim_x = getviewprop(VF_SIZE_X);
			e.cuiDim_y = 12;
		break;
		case CUI_TYPE_BUTTON_ARROW:
			e.cuiDim_x = 32;
			e.cuiDim_y = 32;
		break;
		case CUI_TYPE_BUTTON_ED:
			e.cuiDim_x = 24;
			e.cuiDim_y = 24;
			e.cuiImg = lbl;
		break;
	}
	e.cuiOnRelease = onrelease;
	
	return e;
}

entity CUI_Credits(vector coord,float vis, float page)
{
	local entity e = spawn();
	
	e.cuiOrg = coord;
	e.gameClass = GAME_CLASS_CUI;
	e.cuiClass = CUI_CLASS_CREDITS;
	e.cuiVis = vis;
	e.cuiDim = [16,16];
	e.cuiPage = page;
	e.cuiLbl = "spriteED - created by Antonio 'toneddu2000' Latronico\n\n\rreleased under MIT license\n\n\rhttps://github.com/toneddu2000/spriteED";
	
	return e;
}

entity CUI_Title(string lbl,float vis,float page)
{
	local entity e = spawn();
	
	e.cuiOrg = [0,0];
	e.gameClass = GAME_CLASS_CUI;
	e.cuiClass = CUI_CLASS_TITLE;
	e.cuiVis = vis;
	e.cuiPage = page;
	e.cuiLbl = lbl;
	e.cuiAlpha = 1;	
	return e;
}

entity CUI_ButtonPalette(entity parent, vector col)
{
	local entity e = spawn();
	local float sizex = getviewprop(VF_SIZE_Y),m=10,y=0;
	
	e.cuiParent = parent;
	if(e.cuiParent.cuiClass != CUI_CLASS_WINDOW){
		if(e.cuiOrg_x > sizex - e.cuiDim_x *2){
			y*=2;
		}
		e.cuiOrg = [e.cuiParent.cuiOrg_x + e.cuiParent.cuiDim_x + m,e.cuiParent.cuiOrg_y + y,0];
	}
	else{
		e.cuiOrg = [e.cuiParent.cuiOrg_x + m,e.cuiParent.cuiOrg_y + y,0];
	}
	e.cuiClass = CUI_CLASS_BUTTON_PALETTE;
	e.cuiDim = [20,20];
	e.gameClass = GAME_CLASS_CUI;
	e.cuiVis = GAME_STATE_SPRITEED;
	e.cuiPage = MENU_PAGE_NULL;
	e.cuiAlpha = 1;
	e.cuiBgCol = col;
	//e.cuiOnRelease = CUI_ButtonPaletteOnRelease;
	
	return e;
}

entity CUI_InputArea(entity parent,entity container,string lbl,vector dim,vector org, float vis,float page,float cond)
{
	local entity e = spawn();
	
	e.cuiParent = parent;
	e.gameClass = GAME_CLASS_CUI;
	e.cuiClass = CUI_CLASS_INPUTAREA;
	e.cuiVis = vis;
	e.cuiPage = page;
	e.cuiLbl = lbl;
	e.cuiOrg = org;
	e.cuiDim = dim;
	e.cuiContainer = container;
	e.cuiAlpha = 1;
	e.cuiBgCol = UI_COLOR_GREY_DARK;
	e.cuiCondition = cond;
	
	return e;
}

entity CUI_InputSubmit(entity parent,entity container,vector org, float vis,float page,float cond)
{
	local entity e = spawn();
	
	e.cuiParent = parent;
	e.gameClass = GAME_CLASS_CUI;
	e.cuiClass = CUI_CLASS_INPUTSUBMIT;
	e.cuiVis = vis;
	e.cuiPage = page;
	e.cuiContainer = container;
	e.cuiOrg = org;
	e.cuiLbl = "Submit";
	e.cuiDim = [80,40];
	e.cuiAlpha = 1;
	e.cuiBgCol = UI_COLOR_GREY_DARK;
	e.cuiOnRelease = Menu_Submit;
	e.cuiCondition = cond;
	
	return e;
}

entity CUI_Cbox(entity parent, float active, vector coord,void() onrelease,string lbl, float vis,float page)
{
	local entity e = spawn();
	
	e.cuiParent = parent;
	e.cuiOrg = [e.cuiParent.cuiOrg_x + coord_x,e.cuiParent.cuiOrg_y + coord_y,0];
	e.cuiClass = CUI_CLASS_CBOX;
	e.gameClass = GAME_CLASS_CUI;
	e.cuiVis = vis;
	e.cuiPage = page;
	e.cuiLbl = lbl;
	e.cuiAlpha = 1;
	e.cuiDim_x = 8;
	e.cuiDim_y = 8;
	e.cuiCboxActive = active;
	e.cuiImg = strcat(MENU_IMG_PATH_ED,"cbox_on.png");
	e.cuiOnRelease = onrelease;
	
	return e;
}

entity CUI_Window(entity parent, vector dim, vector coord,vector bgcol,float a, float vis,float page)
{
	local entity e = spawn();
	
	e.cuiParent = parent;
	e.cuiOrg = [e.cuiParent.cuiOrg_x+coord_x,e.cuiParent.cuiOrg_y+coord_y,0];
	e.cuiClass = CUI_CLASS_WINDOW;
	e.gameClass = GAME_CLASS_CUI;
	e.cuiVis = vis;
	e.cuiPage = page;
	e.cuiDim_x = dim_x;
	e.cuiDim_y = dim_y;
	e.cuiBgCol = bgcol;
	e.cuiAlpha = a;
	
	return e;
}

entity CUI_List(entity parent, vector dim, vector pos, float vis,float page)
{
	local entity list = spawn();
	
	list.cuiParent = parent;
	list.cuiOrg = [list.cuiParent.cuiOrg_x+pos_x,list.cuiParent.cuiOrg_y+pos_y,0];
	list.cuiClass = CUI_CLASS_LIST;
	list.gameClass = GAME_CLASS_CUI;
	list.cuiVis = vis;
	list.cuiPage = page;
	list.cuiDim_x = dim_x;
	list.cuiDim_y = dim_y;
	list.cuiBgCol = UI_COLOR_GREY_DARK;
	list.cuiAlpha = 1;
	list.cuiListChildTot = 0;
	list.cuiListCharSize = 5;
	//list up
	list.cuiListUp = spawn();
	list.cuiListUp.cuiClass = CUI_CLASS_LISTUP;
	list.cuiListUp.cuiOrg_x = list.cuiOrg_x+list.cuiDim_x-CUI_LIST_GRIPWIDTH;
	list.cuiListUp.cuiOrg_y = list.cuiOrg_y;
	list.cuiListUp.cuiDim_x = CUI_LIST_GRIPWIDTH;
	list.cuiListUp.cuiDim_y = CUI_LIST_GRIPWIDTH;
	//list down
	list.cuiListDown = spawn();
	list.cuiListDown.cuiClass = CUI_CLASS_LISTDOWN;
	list.cuiListDown.cuiOrg_x = list.cuiOrg_x+list.cuiDim_x-CUI_LIST_GRIPWIDTH;
	list.cuiListDown.cuiOrg_y = list.cuiOrg_y+list.cuiDim_y-CUI_LIST_GRIPWIDTH;
	list.cuiListDown.cuiDim_x = CUI_LIST_GRIPWIDTH;
	list.cuiListDown.cuiDim_y = CUI_LIST_GRIPWIDTH;
	
	return list;
}

void CUI_ListChildResetHeight(entity list)
{
	if(list != world){
		local int i;
		local float ht = list.cuiDim_y/CUI_LIST_ENTS_RENDERED;
		for(i=list.cuiListOffset;i<list.cuiListChildTot;i++){
			if(list.cuiListChild[i]!=world){
				list.cuiListChild[i].cuiOrg_x = list.cuiOrg_x;
				list.cuiListChild[i].cuiOrg_y = list.cuiOrg_y+(ht*i)+list.cuiListIncrY;
				list.cuiListChild[i].cuiDim_x = list.cuiDim_x-CUI_LIST_GRIPWIDTH;
				list.cuiListChild[i].cuiDim_y = ht;
			}
		}
	}
}

void CUI_ListChildAdd(entity list,string label, void() func)
{
	if(list.cuiListChildTot<CUI_LIST_TOT){
		local float i=list.cuiListChildTot;
		list.cuiListChild[i] = spawn();
		list.cuiListChild[i].cuiType = CUI_TYPE_BUTTON_LIST;
		list.cuiListChild[i].cuiParent = list;
		list.cuiListChild[i].cuiClass = CUI_CLASS_LISTCHILD;
		list.cuiListChild[i].cuiVis = list.cuiVis;
		list.cuiListChild[i].cuiPage = list.cuiPage;
		list.cuiListChild[i].cuiLbl = label;
		list.cuiListChild[i].cuiOnRelease = func;
		list.cuiListChildTot++;
	}
}

void CUI_ListChildModify(entity list,float index,string label, void() func)
{
	if(list != world){
		if(index<CUI_LIST_TOT-1){
			if(list.cuiListChild[index]!= world){
				list.cuiListChild[index].cuiType = CUI_TYPE_BUTTON_LIST;
				list.cuiListChild[index].cuiClass = CUI_CLASS_LISTCHILD;
				list.cuiListChild[index].cuiVis = list.cuiVis;
				list.cuiListChild[index].cuiPage = list.cuiPage;
				list.cuiListChild[index].cuiLbl = label;
				list.cuiListChild[index].cuiOnRelease = func;
			}
		}
	}
}

void CUI_DrawColor(vector comporg, vector compdim, vector compcolor, float compalpha)
{
	drawfill(comporg,compdim,compcolor,compalpha);
}

void CUI_PostUpdate(float viscontext)
{
	local entity e= world;
	local float sizex = getviewprop(VF_SIZE_Y);
	local float sizey = getviewprop(VF_SIZE_Y);
	
	/*important for input popup (menuCondition), draw a background
	on top of everything, otherwise CUI elements and normal graphics
	will be rendered together*/
	if(menuCondition != 0){
		drawfill([0,0],[sizex,sizey],UI_COLOR_GREY_DARK,1);
	}
	//cycle trought all uientities in level
	while ((e = nextent(e))){
		//discard non-ui elements
		if(e.gameClass == GAME_CLASS_CUI){
			local vector eOrg=e.cuiOrg,eDim=e.cuiDim;
			local string eLbl = e.cuiLbl;
			//filter by visibility context
			if(e.cuiVis == viscontext && e.cuiPage == menuPage){
				CUI_Hover(e);
				//avoid clicking on elements placed in different contexts (and hidden, though)
				e.cuiClickable = TRUE;
				//differentiate by uielement type
				switch(e.cuiClass){
					case CUI_CLASS_WINDOW:
						CUI_DrawColor(eOrg,eDim,e.cuiBgCol,e.cuiAlpha);
					break;
					case CUI_CLASS_BUTTON:
						if(e.cuiType == CUI_TYPE_BUTTON_ED){
							drawpic(eOrg,e.cuiImg,eDim,e.cuiBgCol,e.cuiAlpha);
							if(e.cuiHover == TRUE){
								drawfill(eOrg,eDim,[1,1,1],0.2,0);
								drawfill(eOrg+[0,20],[eDim_x,4],UI_COLOR_HOVER,0.6,0);
							}
							if(e.cuiTooltipDraw == TRUE){
								drawfill(eOrg+[+28,+28],[stringwidth(e.cuiTooltip,0,[4,4])+4,12],UI_COLOR_GREY_DARK,0.7,0);
								drawstring(eOrg+[+30,+30,0],e.cuiTooltip,[4,4],[1,1,1],0.6,0);
							}
						}
						else if(e.cuiType == CUI_TYPE_BUTTON_MENU){
							local float cs = 10;
							if(e.cuiHover == TRUE){
								drawfill(eOrg+[-1,-1],eDim+[2,2],[1,1,1],1,0);
								drawfill(eOrg,eDim,UI_COLOR_HOVER,1,0);
							}
							else{
								drawfill(eOrg+[-1,-1],eDim+[2,2],UI_COLOR_GREY_MID,1,0);
								drawfill(eOrg,eDim,UI_COLOR_GREY_MID,1,0);
							}
							drawstring(eOrg+[10,10]
							,eLbl,[cs,cs],[1,1,1],1,0);
							
						}
					break;
					case CUI_CLASS_CBOX:
						if(e.cuiCboxActive == TRUE){
							drawpic(eOrg,strcat(MENU_IMG_PATH_ED,"cbox_on.png"),eDim,[1,1,1],1);
						}
						else{
							drawpic(eOrg,strcat(MENU_IMG_PATH_ED,"cbox_off.png"),eDim,[1,1,1],1);
						}
						drawstring(eOrg+[15,2,0],eLbl,[5,5],[1,1,1],0.8,0);
					break;
					case CUI_CLASS_LIST:
						local int i;
						local float barwd = CUI_LIST_GRIPWIDTH;
						CUI_ListChildResetHeight(e);
						for(i=e.cuiListOffset;i < e.cuiListChildTot;i++){
							if(e.cuiListChild[i]!=world){
								local float oddeven = mod((float)i,2);
								e.cuiListChild[i].cuiClickable = TRUE;
								local float charsz = e.cuiListCharSize;
								local vector lblpos = [4,e.cuiListChild[i].cuiDim_y/2-(charsz/2)];
								
								local string s = strcat(e.cuiListChild[i].cuiLbl);
								//truncate exceeding text
								local float margin=10;
								if(stringwidth(s,0,[charsz,charsz]) > eDim_x-barwd-margin){
									s = substring(s,0,10);
									s = strcat(s,"..");
								}
								//important:hide list ent when it reaches bottom end of container
								local float contht = eDim_y;
								if(e.cuiListChild[i].cuiOrg_y < contht){
									if(e.cuiListChild[i].cuiHover){
										drawfill(e.cuiListChild[i].cuiOrg,e.cuiListChild[i].cuiDim,UI_COLOR_HOVER,1,0);
									}
									else{
										if(oddeven == 0){
											drawfill(e.cuiListChild[i].cuiOrg,e.cuiListChild[i].cuiDim,UI_COLOR_GREY_BRIGHT,1,0);
										}
										else{
											drawfill(e.cuiListChild[i].cuiOrg,e.cuiListChild[i].cuiDim,UI_COLOR_GREY_MID,1,0);
										}
									}
									drawstring(e.cuiListChild[i].cuiOrg+lblpos,s,[charsz,charsz],[1,1,1],0.8,0);
								}
							}
						}
						local vector upOrg=e.cuiListUp.cuiOrg,upDim=e.cuiListUp.cuiDim;
						local vector dwOrg=e.cuiListDown.cuiOrg,dwDim=e.cuiListDown.cuiDim;
						//draw bar
						drawfill([upOrg_x,eOrg_y],[barwd,eDim_y],UI_COLOR_AZURE_DIRT,0.2,0);
						//draw list up/down
						upOrg_x = eOrg_x+eDim_x-barwd;
						dwOrg_y = eOrg_y+eDim_y-barwd;
						upOrg_x = eOrg_x+eDim_x-barwd;
						upOrg_y = eOrg_y;
						if(e.cuiListUp.cuiHover){
							drawfill(upOrg,[barwd,barwd],UI_COLOR_HOVER,1,0);
							
						}
						else{
							drawfill(upOrg,[barwd,barwd],UI_COLOR_GREY_BRIGHT,1,0);
						}
						if(e.cuiListDown.cuiHover){
							drawfill(dwOrg,[barwd,barwd],UI_COLOR_HOVER,1,0);
						}
						else{
							drawfill(dwOrg,[barwd,barwd],UI_COLOR_GREY_BRIGHT,1,0);
						}
						//line separators
						drawline(2,[upOrg_x,upOrg_y+upDim_y], [upOrg_x+upDim_x,upOrg_y+upDim_y],UI_COLOR_GREY_DARK,1);
						drawline(2,[dwOrg_x,dwOrg_y], [dwOrg_x+upDim_x,dwOrg_y],UI_COLOR_GREY_DARK,1);
						drawline(2,[upOrg_x,upOrg_y], [upOrg_x,upOrg_y+eDim_y],UI_COLOR_GREY_DARK,1);
						local float m = 2;
						//triangle arrow up
						drawline(2,[upOrg_x+m,upOrg_y+upDim_y-m], [upOrg_x+(upDim_x/2),upOrg_y+m],UI_COLOR_GREY_DARK,1);
						drawline(2,[upOrg_x+upDim_x-m,upOrg_y+upDim_y-m], [upOrg_x+(upDim_x/2),upOrg_y+m],UI_COLOR_GREY_DARK,1);
						drawline(2,[upOrg_x+m,upOrg_y+upDim_y-m], [upOrg_x-m+upDim_x,upOrg_y+upDim_y-m],UI_COLOR_GREY_DARK,1);
						//triangle arrow up
						drawline(2,[dwOrg_x+m,dwOrg_y+m], [dwOrg_x+(dwDim_x/2),dwOrg_y+dwDim_y-m],UI_COLOR_GREY_DARK,1);
						drawline(2,[dwOrg_x+dwDim_x-m,dwOrg_y+m], [dwOrg_x+(dwDim_x/2),dwOrg_y+dwDim_y-m],UI_COLOR_GREY_DARK,1);
						drawline(2,[dwOrg_x+m,dwOrg_y+m], [dwOrg_x-m+dwDim_x,dwOrg_y+m],UI_COLOR_GREY_DARK,1);
					break;
					case CUI_CLASS_INPUTAREA:
						if(e.cuiCondition == menuCondition){
							local float ac = e.cuiDim_x /30,aw = stringwidth(e.cuiLbl,0,[ac,ac]);
							e.cuiDim_y = ac*2;
							if(e.cuiSelected == TRUE){
								drawfill(e.cuiOrg+[-1,-1],e.cuiDim+[2,2],UI_COLOR_AZURE,1,0);
							}
							else{
								drawfill(e.cuiOrg+[-1,-1],e.cuiDim+[2,2],UI_COLOR_GREY_MID,1,0);
							}
							drawfill(e.cuiOrg,e.cuiDim,UI_COLOR_GREY_DARK,1,0);
							if(e.cuiHover == TRUE){
								drawfill(e.cuiOrg,e.cuiDim,UI_COLOR_HOVER,0.8,0);
							}
							drawstring(e.cuiOrg+[2,-8],e.cuiLbl,[5,5],UI_COLOR_GREY_BRIGHT,1,0);
							drawstring(e.cuiOrg+[ac,(e.cuiDim_y/2)-(ac/2)],inputText,[ac,ac],[1,1,1],1,0);
						}
					break;
					case CUI_CLASS_INPUTSUBMIT:
						local float ic = 8,iw = stringwidth(e.cuiLbl,0,[ic,ic]);
						if(e.cuiCondition == menuCondition){
							drawfill(e.cuiOrg+[-1,-1],e.cuiDim+[2,2],UI_COLOR_GREY_MID,1,0);
							drawfill(e.cuiOrg,e.cuiDim,UI_COLOR_GREY_DARK,1,0);
							if(e.cuiHover == TRUE){
								drawfill(e.cuiOrg,e.cuiDim,UI_COLOR_HOVER,0.8,0);
							}
							drawstring(e.cuiOrg+[e.cuiDim_x/2-(iw/2),(e.cuiDim_y/2)-(ic/2)],e.cuiLbl,[ic,ic],[1,1,1],1,0);
						}
					break;
					case CUI_CLASS_BUTTON_PALETTE:
						if(e.cuiHover == TRUE){
							drawfill(e.cuiOrg+[-1,-1],e.cuiDim+[2,2],[1,1,1],1,0);
						}
						else{
							if(e.cuiBgCol == spriteEdChosenColor){
								drawfill(e.cuiOrg+[-1,-1],e.cuiDim+[2,2],[1,1,1],1,0);
							}
							else{
								drawfill(e.cuiOrg+[-1,-1],e.cuiDim+[2,2],UI_COLOR_GREY_BRIGHT,1,0);
							}
						}
						drawfill(e.cuiOrg,e.cuiDim,e.cuiBgCol,1,0);
					break;
					case CUI_CLASS_TITLE:
						drawstring([sizex-stringwidth(e.cuiLbl,0,[12,12]),10]+[-2,-2],e.cuiLbl,[12,12],[0,0,0],1,0);
						drawstring([sizex-stringwidth(e.cuiLbl,0,[12,12]),10],e.cuiLbl,[12,12],[1,1,1],1,0);
					break;
					case CUI_CLASS_CREDITS:
						drawfill(e.cuiOrg,[16,16],UI_COLOR_AZURE,1,0);
						if(e.cuiHover == TRUE){
							drawfill([0,0],[sizex*2,sizey*2],UI_COLOR_GREY_DARK,0.6,0);
							drawstring([20,80]+[-1,-1],e.cuiLbl,[8,8],[0,0,0],1,0);
							drawstring([20,80],e.cuiLbl,[8,8],UI_COLOR_AZURE,1,0);
						}
					break;
					default:
					break;
				}
			}
			else{
				//ui element is in a different visibility context, so don't click on it
				e.cuiClickable = FALSE;
				local int j;
				for(j=0;j<CUI_LIST_TOT;j++){
					if(e.cuiListChild[j]!=world){
						e.cuiListChild[j].cuiClickable = FALSE;
					}
				}
			}
		}
	}
}
