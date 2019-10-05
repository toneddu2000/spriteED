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

//Sprite Editor (for artwork creations) 

void SpriteEd_GenerateRandomImg()
{
	local int i;
	
	spriteEdEntArtwork = spawn();
	spriteEdEntArtwork.gameClass = GAME_CLASS_SPRITEED;
	//let's create a dummy sprite with random colors
	spriteEdEntArtwork = spawn();
	spriteEdEntArtwork.gameClass = GAME_CLASS_SPRITEED;
	for(i=0;i<SPRITE_ED_PIX_MAX;i++){
		spriteEdEntArtwork.spriteEdPix[i] = [random(1),random(1),random(1)];
	}

}

void SpriteEd_ArtworkReset()
{
	local int i;
	
	spriteEdEntArtwork = spawn();
	spriteEdEntArtwork.gameClass = GAME_CLASS_SPRITEED;
	for(i=0;i<SPRITE_ED_PIX_MAX;i++){
		spriteEdEntArtwork.spriteEdPix[i] = UI_COLOR_GREY_DARK;
	}
}

void SpriteEd_Init()
{
	SpriteEd_ArtworkReset();
	spriteEdChosenColor = [0,1,0];
}

void SpriteEd_ArtworkDraw()
{
	if(spriteEdEntArtwork != world){
		local int i;
		local float h=0,v=0,tot=310;
		for(i=0;i<SPRITE_ED_PIX_MAX;i++){
			local vector pos = [200,50];
			drawfill([h+pos_x,v+pos_y],[10,10],spriteEdEntArtwork.spriteEdPix[i],1);
			spriteEdEntArtwork.spriteEdOrg[i] = [h+pos_x,v+pos_y];
			if(h < (tot)){
				h+=10;
			}
			else{
				h=0;
				v+=10;
			}
		}
	}
	//drawstring([5,400], vtos(spriteEdEntArtwork.spriteEdPix[14]),[10,10],[1,0,0],1,0);
}

void SpriteEd_CanvasPaint()
{
	if(gameState == GAME_STATE_SPRITEED){
		if(spriteEdEntArtwork != world){
			local int i;
			for(i=0;i<SPRITE_ED_PIX_MAX;i++){
				local vector v = spriteEdEntArtwork.spriteEdOrg[i];
				local vector io = inputCursorOrigin;
				local float d = 10;
				local float xaxis = v_x + d;
				local float yaxis = v_y + d;
				local vector pos = [io_x-screenX,io_y-screenY];
				
				if(inputMouse1Pressed){
					if(pos_x < xaxis && pos_x > v_x && 
					pos_y < yaxis && pos_y > v_y){
						spriteEdEntArtwork.spriteEdPix[i] = spriteEdChosenColor;
					}
				}
				else if(inputMouse2Pressed){
					if(pos_x < xaxis && pos_x > v_x && 
					pos_y < yaxis && pos_y > v_y){
						spriteEdEntArtwork.spriteEdPix[i] = UI_COLOR_GREY_DARK;
					}
				}
			}
		}
	}
}

void SpriteEd_DrawLoop()
{
	local entity e;
	e = world;
	
	while ((e = nextent(e))){
		if(e != world && e.gameClass == GAME_CLASS_SPRITEED){
			
		}
	}
}

void SpriteEd_Grid(float w,float h)
{
	if(gameState == GAME_STATE_SPRITEED){
		local float x,y;
		local vector pos = [200,50];
		for(x=0;x<320;x+=10){
			drawline(1,[0,x]+pos,[320,x]+pos,UI_COLOR_GREY_BRIGHT,1);
			for(y=0;y<320;y+=10){
				drawline(1,[y,0]+pos,[y,320]+pos,UI_COLOR_GREY_BRIGHT,1);
			}
		}
	}
}

void SpriteEd_PostUpdate(float w,float h)
{	
	if(gameState == GAME_STATE_SPRITEED){
		SpriteEd_DrawLoop();
		SpriteEd_ArtworkDraw();
		SpriteEd_CanvasPaint();
		SpriteEd_Grid(w,h);
	}
}
