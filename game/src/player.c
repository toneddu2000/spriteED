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

//Player stub functions 

void Player_Attack()
{
	if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		if(player != world){
			player.spriteFrame = 0;
			player.charAttacking = TRUE;
			player.charState = CHAR_STATE_ATTACK;
			Char_AttackRadius(player);
		}
	}
}

void Player_Init()
{
	playerSpawned = FALSE;
	//TEMP
	player.charAttackFinished  = TRUE;
}

void Player_Update()
{
	if(player != world){
		if(player.charState == CHAR_STATE_ATTACK){
			//TEMP
			if(player.spriteFrame >= player.spriteActionCurrentEnd-1){
				player.charAttacking = FALSE;
				player.charState = CHAR_STATE_IDLE;
			}
		}
	}
}

void Player_PostUpdate(float w,float h)
{
	
}