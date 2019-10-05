void Player_Attack()
{
	if(gameState == GAME_STATE_TEST || gameState == GAME_STATE_RUNNING){
		if(player != world){
			/*if(player.physMoving == FALSE){
				if(player.charAttackFinished == TRUE){
					player.charAttackFinished = FALSE;
					player.charAttacking = TRUE;
					player.charState = CHAR_STATE_ATTACK;
				}
			}
			else{
				player.charAttacking = FALSE;
			}*/
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
		
		/*if(player.charAttackFinished == FALSE)
		{
			player.charAttackTime += frametime * 1;
			if(player.charAttackTime > 0.5){
				player.charAttackFinished = TRUE;
				player.charAttacking = FALSE;
			}
		}*/
	}
}

void Player_PostUpdate(float w,float h)
{
	
}