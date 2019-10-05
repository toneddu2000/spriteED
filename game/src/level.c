/*
MIT License

Copyright (c) 2018 Antonio "toneddu2000" Latronico

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

void Level_Clear()
{
	levelEntity = world;
	while ((levelEntity = nextent(levelEntity))){
		if(levelEntity.levelSaveThis == TRUE){
			if(levelEntity != world){
				remove(levelEntity);
			}
		}
	}
}

void Level_Overwrite()
{
	local float f;
	local entity head;
	local string entdat = "";
	
	head = levelEntity;
	levelEntity = world;
	f = fopen(strcat("levels/",levelNameOverwrite,".level"), FILE_WRITE);
	while ((levelEntity = nextent(levelEntity))){
		if(levelEntity.levelSaveThis == TRUE){
			entdat = generateentitydata(levelEntity);
			fputs(f,entdat,"\n");
		}
	}
	fclose(f);
	uiMessage =strcat("Map name ",levelNameOverwrite, " succesfully overwritten.");
	levelOverwrite = FALSE;
	levelNameOverwrite = "";
}

void Level_OverwriteOn()
{
	levelOverwrite = TRUE;
	//reset stuff
	levelSave = FALSE;
	//UI_PopupClose();
}

void Level_OverwriteOff()
{
	levelOverwrite = FALSE;
}

void Level_Save()
{
	local entity head;
	local float f;
	local string entdat = "";
	local float fsearch = search_begin(strcat("data/levels/","*.level"),TRUE,FALSE);
	local float fsize = search_getsize(fsearch);
	local int i;
	local string levname;
	
	//name already exists in levels folder?
	if (fsearch != -1){
		for(i=0;i<fsize;i++){
			levname = search_getfilename(fsearch,i);
			levname = strreplace("data/levels/","",levname);
			levname = strreplace(".level","",levname);
			if(levname == inputText){
				levelNameOverwrite = levname;
				uiWarning = strcat("Map name ",levname, " already exists. Overwrite?");
				Level_OverwriteOn();
				return;
			}
		}
	}
	search_end(fsearch);
	//cycle trough entities to save
	head = levelEntity;
	levelEntity = world;
	f = fopen(strcat("levels/",levelNameChosen,".level"), FILE_WRITE);
	while ((levelEntity = nextent(levelEntity))){
		if(levelEntity.levelSaveThis == TRUE){
			entdat = generateentitydata(levelEntity);
			fputs(f,entdat,"\n");
		}
	}
	fclose(f);
	//display save message
	uiMessage = strcat("Map name ",levelNameChosen, " succesfully saved.");
	//reset stuff
	levelSave = FALSE;
	//UI_PopupClose();
}

void Level_SaveSimple()
{
	if(inputText != ""){
		levelEntity= world;
		local string entdat = "";
		local float f = fopen(strcat(FILE_PATH_LEVELS,inputText,".level"), FILE_WRITE);
		while ((levelEntity = nextent(levelEntity))){
			if(levelEntity.levelSaveThis == TRUE){
				entdat = generateentitydata(levelEntity);
				fputs(f,entdat,"\n");
			}
		}
		fclose(f);
		//display save message
		uiMessage = strcat("Level ",inputText, " succesfully saved.");
	}
	else{
		uiWarning = "Level name cannot be empty";
	}
}

/*
void Level_LoadOld()
{
	levelNameChosen=  strcat("data/",FILE_PATH_LEVELS,menuLevels[menuLevelsList.cuiListItemClicked],".level");
	local float file = fopen(levelNameChosen, FILE_READNL);
	
	//level exists
	if (file >= 0){
		Level_Clear();
		local string thefilecontents = fgets(file);
		local float offset = 0;
		fclose(file);
		local entity e;
		//(by Spike)
		while ((offset=parseentitydata((e=spawn()), thefilecontents, offset))){
			
			//if its from a different map / version of the mod / etc, make sure its modelindex is still correct for its model.
			if (e.model != ""){
				setmodel(e, e.model);
			}
			//make sure its linked
			else{
				setorigin(e, e.origin);
			}
			
		}
		//last one failed to parse but we had already created an ent for it.
		remove(e);
	}
	//level doesn't exist
	else{
		uiWarning= strcat("Map ",menuLevels[menuLevelsIdx]," doesn't exist");
		menuLevels[menuLevelsIdx] = "";
		return;
	}
	uiMessage = strcat("Level ",menuLevels[menuLevelsIdx]," opened successfully");
	menuLevels[menuLevelsIdx] = "";
}

*/
/*
void Level_Load()
{
	levelNameChosen=  strcat("data/",FILE_PATH_LEVELS,menuLevels[menuLevelsList.cuiListItemClicked],".level");
	local float file = fopen(levelNameChosen, FILE_READNL);
	
	//level exists
	if (file >= 0){
		Level_Clear();
		local string thefilecontents = fgets(file);
		local float offset = 0;
		fclose(file);
		local entity e;
		//(by Spike)
		while ((offset=parseentitydata((e=spawn()), thefilecontents, offset))){
			//if its from a different map / version of the mod / etc, make sure its modelindex is still correct for its model.
			if (e.model != ""){
				setmodel(e, e.model);
			}
			//make sure its linked
			else{
				setorigin(e, e.origin);
			}
		}
		//last one failed to parse but we had already created an ent for it.
		remove(e);
	}
	//level doesn't exist
	else{
		uiWarning= strcat("Map ",menuLevels[menuLevelsIdx]," doesn't exist");
		menuLevels[menuLevelsIdx] = "";
		return;
	}
	uiMessage = strcat("Level ",menuLevels[menuLevelsIdx]," opened successfully");
	menuLevels[menuLevelsIdx] = "";
	//go back to ed
	Game_StateEd();
}
*/

void Level_Init()
{
	levelSave = FALSE;
	levelNew = FALSE;
	levelOpen = FALSE;
}
