
void Part_Spawn(vector pos,string name)
{
	if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		spriteEntity = Sprite_Spawn(SPRITE_CLASS_PART,name,pos, [edGridSize,edGridSize],[1,1,1],1);
	}
}