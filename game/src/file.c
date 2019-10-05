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

//File management 

float File_SubfolderRead(entity e,float class)
{
	local float entryfile = 0;
	if(class == SPRITE_CLASS_GROUND){
		return 0;
	}
	switch(class){
		case SPRITE_CLASS_ENT:
			entryfile = fopen(strcat(e.spriteImgSubfolder,e.spriteImgName,"_top.png"), FILE_READ);
			if (entryfile != -1){
				fclose(entryfile);
				return TRUE;
			}
			else{
				return FALSE;
			}	
		break;
		case SPRITE_CLASS_PLAYER:
			entryfile = fopen(strcat(e.spriteImgSubfolder,e.spriteImgName,"_idle0_up.png"), FILE_READ);
			if (entryfile != -1){
				fclose(entryfile);
				return TRUE;
			}
			else{
				return FALSE;
			}	
		break;
	}
	return FALSE;
}

void File_EntSubPartsRead(entity e)
{
	
	if(e != world){
		local string exttop = "_top.png",extshdw="_shdw.png";
		//top
		local float ftop = fopen(strcat(e.spriteImgSubfolder,exttop), FILE_READ);
		if (ftop != -1){
			e.spriteEntTop = spawn();
			e.spriteEntTop.spriteImgPath = strcat(e.spriteImgSubfolder,exttop);
			//save shdw path to master entities for easier loading
			e.spriteEntTopImgPath = e.spriteEntTop.spriteImgPath;
			fclose(ftop);
		}
		else{
			//tempSubFolder = e.spriteImgName;
		}
		//shdw
		local float fshdw = fopen(strcat(e.spriteImgSubfolder,extshdw), FILE_READ);
		if (fshdw != -1){
			e.spriteEntShdw = spawn();
			e.spriteEntShdw.spriteImgPath = strcat(e.spriteImgSubfolder,extshdw);
			//save top path to master entities for easier loading
			e.spriteEntShdwImgPath = e.spriteEntShdw.spriteImgPath;
			fclose(fshdw);
		}
	}
}

void File_ActionRead(entity e)
{
	local float f = fopen(strcat(e.spriteImgSubfolder,".act"), FILE_READ);
	local string ln = "";
	
	if (f != -1){
		ln = fgets(f);
		while(ln != __NULL__){
			if(strstrofs(ln,"idle:") != -1){
				ln = strreplace("idle:","",ln);
				e.spriteActionIdleEnd = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"walk:") != -1){
				ln = strreplace("walk:","",ln);
				e.spriteActionWalkEnd = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"attack:") != -1){
				ln = strreplace("attack:","",ln);
				e.spriteActionAttackEnd = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"animation:") != -1){
				ln = strreplace("animation:","",ln);
				e.spriteActionAnimationEnd = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"speed:") != -1){
				ln = strreplace("speed:","",ln);
				e.charSpeed = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"aggr:") != -1){
				ln = strreplace("aggr:","",ln);
				e.charAggr = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"health:") != -1){
				ln = strreplace("health:","",ln);
				e.charHealth = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"damage:") != -1){
				ln = strreplace("damage:","",ln);
				e.charDamage = stof(ln);
				ln = fgets(f);
			}
			else{
				ln = fgets(f);
			}				
		}
		fclose(f);
	}
}

void File_PartRead(entity e)
{
	local float f = fopen(strcat(e.spriteImgSubfolder,".act"), FILE_READ);
	local string ln = "";
	
	if (f != -1){
		ln = fgets(f);
		while(ln != __NULL__){
			if(strstrofs(ln,"animation_end:") != -1){
				ln = strreplace("animation_end:","",ln);
				e.spriteActionAnimationEnd = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"life:") != -1){
				ln = strreplace("life:","",ln);
				e.partLife = stof(ln);
				ln = fgets(f);
			}
			else{
				ln = fgets(f);
			}				
		}
		fclose(f);
	}
}

void File_LibraryRead()
{
	local float folder=0;
	local float sz;
	local int i;
	local string sprname="",foldername="";
	
	//flush spriteLibrary
	spriteLibraryIdx = 0;
	for(i=0;i < SPRITE_LIBRARY_MAX;i++){
		spriteLibrary[i] = ""; 
	}
	
	switch(edTileType){
		case SPRITE_CLASS_GROUND:
			foldername = SPRITE_FOLDER_GROUND;
		break;
		case SPRITE_CLASS_ENT:
			foldername = SPRITE_FOLDER_ENT;
		break;
		case SPRITE_CLASS_NPC:
			foldername = SPRITE_FOLDER_CHAR;
		break;
		case SPRITE_CLASS_PLAYER:
			foldername = SPRITE_FOLDER_PLAYER;
		break;
		case SPRITE_CLASS_PART:
			foldername = SPRITE_FOLDER_PART;
		break;
	}
	if(edTileType != SPRITE_CLASS_ARTWORK){
		folder = search_begin(strcat(SPRITE_FOLDER,foldername,"*.png"),TRUE,FALSE);
		sz = search_getsize(folder);
		//library
		if (folder != -1){
			for(i=0;i<sz;i++){
				sprname = search_getfilename(folder,i);
				sprname = strreplace(strcat(SPRITE_FOLDER,foldername,"/"),"",sprname);
				if(sprname != ""){
					spriteGroundLibrarySize++;
					spriteLibrary[i] = sprname;
				}
			}
		}
	}
	else{
		local float artwsearch = search_begin(strcat(FILE_PATH_ARTWORKS,"*.sprite"),TRUE,FALSE);
		local float artwtot = search_getsize(artwsearch);
		local int j=0;
		local string artwname;
		if (artwsearch != -1){
			for(j = 0; j < artwtot ; j++){
				artwname = search_getfilename(artwsearch,j);
				if(artwname != ""){
					spriteLibrary[j]=search_getfilename(artwsearch,j);
					spriteArtworkSelected = spriteLibrary[j];
				}
			}
		}
	}
}

void File_LevelsFolderRead()
{
	local float levelsearch = search_begin(strcat("data/",FILE_PATH_LEVELS,"*.level"),TRUE,FALSE);
	local float levelstot = search_getsize(levelsearch);
	local int i;
	local string levname;
	if (levelsearch != -1){
		for(i = 0; i < levelstot ; i++){
			levname = search_getfilename(levelsearch,i);
			if(levname != ""){
				menuLevels[i]=search_getfilename(levelsearch,i);
			}
		}
	}
}

void File_LevelSave()
{
	local string ln = "",name = strcat(FILE_PATH_LEVELS,inputText,".level");
	local float f = fopen(name, FILE_WRITE);
	local entity e=world;
	
	if (f != -1){
		while ((e = nextent(e))){
			if(e.gameClass == GAME_CLASS_SPRITE){
				fputs(f,"{","\n");
				fputs(f,strcat("entnum:",etos(e)),"\n");
				fputs(f,strcat("class:",ftos(e.spriteClass)),"\n");
				fputs(f,strcat("orgx:",ftos(e.spriteOrg_x)),"\n");
				fputs(f,strcat("orgy:",ftos(e.spriteOrg_y)),"\n");
				fputs(f,strcat("dimx:",ftos(e.spriteDim_x)),"\n");
				fputs(f,strcat("dimy:",ftos(e.spriteDim_y)),"\n");
				fputs(f,strcat("imgpath:",e.spriteImgPath),"\n");
				
				if(e.spriteClass == SPRITE_CLASS_GROUND){
					
				}
				else if(e.spriteClass == SPRITE_CLASS_ENT){
					if(e.spriteEntTopImgPath != ""){
						fputs(f,strcat("imgtoppath:",e.spriteEntTopImgPath),"\n");
					}
					if(e.spriteEntShdwImgPath != ""){
						fputs(f,strcat("imgshdwpath:",e.spriteEntShdwImgPath),"\n");
					}
				}
				fputs(f,"}","\n");
			}
		}
		fclose(f);
		uiMessage = strcat("Level ",inputText," successfully created.");
	}
}

void File_LevelLoad()
{
	local string ln = "",name=strcat("data/",FILE_PATH_LEVELS,menuLevels[menuLevelsList.cuiListItemClicked],".level");
	local float f = fopen(name, FILE_READ);
	local entity e =world;
	if (f != -1){
		ln = fgets(f);
		while(ln != __NULL__){
			if(strstrofs(ln,"{") != -1){
				e = spawn();
				e.spriteAlpha = 1;
				e.spriteCol = [1,1,1];
				ln = fgets(f);
			}
			else if(strstrofs(ln,"entnum:") != -1){
				ln = strreplace("entnum:","",ln);
				ln = strreplace("entity ","",ln);
				e.edEntNum = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"class:") != -1){
				ln = strreplace("class:","",ln);
				e.spriteClass = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"orgx:") != -1){
				ln = strreplace("orgx:","",ln);
				e.spriteOrg_x = stof(ln);
				e.edOrg_x = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"orgy:") != -1){
				ln = strreplace("orgy:","",ln);
				e.spriteOrg_y = stof(ln);
				e.edOrg_y = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"dimx:") != -1){
				ln = strreplace("dimx:","",ln);
				e.spriteDim_x = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"dimy:") != -1){
				ln = strreplace("dimy:","",ln);
				e.spriteDim_y = stof(ln);
				ln = fgets(f);
			}
			else if(strstrofs(ln,"imgpath:") != -1){
				ln = strreplace("imgpath:","",ln);
				e.spriteImgPath = ln;
				ln = fgets(f);
			}
			else if(strstrofs(ln,"imgtoppath:") != -1){
				ln = strreplace("imgtoppath:","",ln);
				e.spriteEntTop = spawn();
				e.spriteEntTop.spriteImgPath = ln;
				//e.spriteEntTopImgPath = ln;
				ln = fgets(f);
			}
			else if(strstrofs(ln,"imgshdwpath:") != -1){
				ln = strreplace("imgshdwpath:","",ln);
				e.spriteEntShdw = spawn();
				e.spriteEntShdw.spriteImgPath = ln;
				//e.spriteEntShdwImgPath = ln;
				ln = fgets(f);
			}
			else if(strstrofs(ln,"}") != -1){
				if(e.spriteClass != SPRITE_CLASS_PLAYER){
					spriteEntity = Sprite_Spawn(e.spriteClass,e.spriteImgPath,[e.spriteOrg_x,e.spriteOrg_y],[32,32],[1,1,1],1);
				}
				else{
					if(playerSpawned == FALSE){
						player = Sprite_Spawn(e.spriteClass,e.spriteImgPath,[e.spriteOrg_x,e.spriteOrg_y],[32,32],[1,1,1],1);
					}
				}
				remove(e);
				ln = fgets(f);
			}		
		}
		fclose(f);
		uiMessage = strcat("Level ",menuLevels[menuLevelsList.cuiListItemClicked]," successfully loaded.");
	}
	//go back to ed
	Game_StateEd();
}

void File_SpriteEdWriteArtwork()
{
	if(spriteEdEntArtwork != world){
		local float f = fopen(strcat("sprites/",inputText,".sprite"), FILE_WRITE);
		local int i;
		if (f != -1){
			for(i=0;i<SPRITE_ED_PIX_MAX;i++){
				fputs(f,strcat(vtos(spriteEdEntArtwork.spriteEdPix[i]),"\n"));
			}				
			fclose(f);
		}
		uiMessage = strcat("Sprite ",inputText, " succesfully created");
	}
}

void File_SpriteEdReadList()
{
	local float f = fopen(strcat(menuSpriteEd[menuSpriteEdList.cuiListItemClicked]), FILE_READ);
	local int i;
	local string ln = "";
	if (f != -1){
		ln = fgets(f);
		for(i=0;i<SPRITE_ED_PIX_MAX;i++){
			spriteEdEntArtwork.spriteEdPix[i] = stov(ln);
			ln = fgets(f);
		}					
		fclose(f);
	}
}

void File_ArtworkReadSingleEnt(entity e,string name)
{
	//local float f = fopen(strcat("sprites/",name,".sprite"), FILE_READ);
	local float f = fopen(spriteLibrary[spriteLibraryIdx], FILE_READ);
	local int i;
	local string ln = "";
	if (f != -1){
		ln = fgets(f);
		for(i=0;i<SPRITE_ED_PIX_MAX;i++){
			e.spriteEdPix[i] = stov(ln);
			ln = fgets(f);
		}					
		fclose(f);
	}
}

void File_SpriteEdFolderRead()
{
	local float levelsearch = search_begin(strcat(FILE_PATH_ARTWORKS,"*.sprite"),TRUE,FALSE);
	local float levelstot = search_getsize(levelsearch);
	local int i;
	local string sprdname;
	if (levelsearch != -1){
		for(i = 0; i < levelstot ; i++){
			sprdname = search_getfilename(levelsearch,i);
			if(sprdname != ""){
				menuSpriteEd[i]=search_getfilename(levelsearch,i);
			}
		}
	}
}