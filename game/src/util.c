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

//Util functions 

//https://www.gamedev.net/forums/topic/515816-distance-between-two-vectors/?do=findComment&comment=4357285
float Util_Vec2Dist(vector v1,vector v2)
{
	local vector v = [v1_x - v2_x,v1_y - v2_y];
	return sqrt(v_x*v_x + v_y*v_y);
}

void  Util_Remove(entity e)
{
	if(e != world){
		//add here all classes and fields
		if(e.gameClass == GAME_CLASS_NULL){
			remove(e);
		}
		else if(e.gameClass == GAME_CLASS_SPRITE){
			e.spriteImgPath = "";
			e.spriteImgFolder = "";
			remove(e);
		}
	}
}

void  Util_RemoveSelf()
{
	if(self != world){
		//add here all classes and fields
		if(self.gameClass == GAME_CLASS_NULL){
			remove(self);
		}
		else if(self.gameClass == GAME_CLASS_SPRITE){
			self.spriteImgPath = "";
			self.spriteImgFolder = "";
			remove(self);
		}
	}
}