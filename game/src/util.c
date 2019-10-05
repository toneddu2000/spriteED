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