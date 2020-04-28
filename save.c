#include <gb/gb.h>
#include <stdio.h>
#include "assets/sprites/gamesprites.c"
#include "assets/background/background.c"
#include "assets/gui/titlescreen.c"
#include "assets/gui/black.c"
#include "assets/background/stars.c"
#include "assets/gui/splash.c"

UINT8 randomeffectvalue = 0;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void fadeout() {
	for(randomeffectvalue=0;randomeffectvalue<4;randomeffectvalue++) {
		switch(randomeffectvalue) {
			case 0:
				BGP_REG = 0xE4;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xFE;
				break;
			case 3:
				BGP_REG = 0xFF;
				break;
		}
		performantdelay(20);
	}
}

void fadein() {
	for(randomeffectvalue=0;randomeffectvalue<3;randomeffectvalue++) {
		switch(randomeffectvalue) {
			case 0:
				BGP_REG = 0xFE;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xE4;
				break;
		}
		performantdelay(10);
	}
}

void main() {
	//Values
	UINT8 player_x, player_y;
	UINT8 npc_x, npc_y;
	UINT8 npc2_x, npc2_y;
	UINT8 npc3_x, npc3_y;
	UINT8 star_x, star_y;
	const player_size = 8;
	const npc_size = 8;
	UINT8 paused = 0;
	UINT8 gameover = 0;
	UINT8 wait = 0;
	
	//Player Positionsetup
	player_x = 50;
	player_y = 90;
	
	//NPC_1 Positionsetup
	npc_x = 170;
	npc_y = 90;
	
	//NPC_2 Positionsetup
	npc2_x = 0;
	npc2_y = 90;
	
	//NPC_3 Positionsetup
	npc3_x = 0;
	npc3_y = 90;
	
	//Soundsetup
	NR52_REG = 0x80; //Turn Sound on
	NR50_REG = 0x77; //Turns Stereo on
	NR51_REG = 0xFF; //I dont know what this do :)
	
	set_bkg_tiles(0,0,20,18,blackscreen_map);
	performantdelay(50);
	
	//Creating the Background
	set_bkg_data(0, 69, TileLabel);
	set_bkg_tiles(0, 0, 20, 18, imute_data);
	SHOW_BKG;
	
	//imute logo fade in
	BGP_REG = 0xFF;
	fadein();
	
	performantdelay(50);
	
	//imutelogo fade out
	fadeout();
	set_bkg_tiles(0,0,20,18,blackscreen_map);
	
	performantdelay(20);
	
	//titlescreen fade in
	set_bkg_tiles(0,0,20,18,titlescreen_map);
	fadein();
	
	//Creating the star effect
	set_sprite_data(0,6,sPlayer);
	set_sprite_tile(4,5);
	star_x = 160;
	star_y = 20;
	move_sprite(4,star_x,star_y);
	SHOW_SPRITES;
	
	randomeffectvalue = 2;
	while(paused == 0) {
		switch(joypad()) {
			case J_START:
				paused = 1;
				break;
		}
		if(wait==50) {
			randomeffectvalue += 1;
			if(randomeffectvalue == 4) {
				randomeffectvalue = 2;
			}
			set_sprite_tile(4,randomeffectvalue);
			star_x -= 3;
			star_y += 3;
			move_sprite(4,star_x,star_y);
			if(star_x <= 40) {
				star_x = 160;
				star_y = 20;
				move_sprite(4,star_x,star_y);
				set_sprite_tile(4,5);
				wait = 0;
			}
		}
		else {
			wait += 1;
		}
		performantdelay(3);
	}
	paused = 0;
	set_sprite_tile(4,5);
	HIDE_SPRITES;
	
	//Fade titlescreen out
	fadeout();
	set_bkg_tiles(0,0,20,18,blackscreen_map);
	
	//Sprite data
	set_sprite_tile(0,0);
	set_sprite_tile(1,1);
	set_sprite_tile(2,1);
	set_sprite_tile(3,1);
	
	gl:
	
	//Player Positionsetup
	player_x = 50;
	player_y = 90;
	
	//NPC_1 Positionsetup
	npc_x = 170;
	npc_y = 90;
	
	//NPC_2 Positionsetup
	npc2_x = 0;
	npc2_y = 90;
	
	//NPC_3 Positionsetup
	npc3_x = 0;
	npc3_y = 90;
	
	gameover = 0;
	
	//Moving Sprites
	//Player
	move_sprite(0,player_x,player_y);
	//NPC_1
	move_sprite(1,npc_x,npc_y);
	//NPC_2
	move_sprite(2,npc2_x,npc2_y);
	//NPC_3
	set_sprite_tile(3,1);
	
	performantdelay(20);
	
	//Creating Gamebackground
	set_bkg_tiles(0,0,80,18,galaxy_background);
	
	//Show Graphics
	fadein();
	SHOW_SPRITES;
	DISPLAY_ON;
	
	performantdelay(20);
	//MainGameLoop
	while(gameover == 0) {
		
		//Joypadcheck
		switch(joypad()) {
			//Movement
			case J_LEFT:
				if(paused == 0) {
					if(player_x > 20) {
						player_x -= 5;
						scroll_sprite(0, -5, 0);
					}
				}
				break;
			
			case J_RIGHT:
				if(paused == 0) {
					if(player_x < 160) {
						player_x += 5;
						scroll_sprite(0, 5, 0);
					}
				}
				break;
			
			case J_UP:
				if(paused == 0) {
					if(player_y > 20) {
						player_y -= 5;
						scroll_sprite(0, 0, -5);
					}
				}
				break;
			
			case J_DOWN:
				if(paused == 0) {
					if(player_y < 145) {
						player_y += 5;
						scroll_sprite(0, 0, 5);
					}
					else {
						gameover = 1;
					}
				}
				break;
			//Attacs
			case J_A:
				if(paused == 0) {
					//Sound
					NR41_REG = 0x1C;
					NR42_REG = 0xF3;
					NR43_REG = 0x20;
					NR44_REG = 0xA0;
				}
				break;
			//Pause Game
			case J_START:
				if(paused == 0) {
					paused = 1;
				}
				else {
					paused = 0;
				}
		}
		//Moving NPCs
		if(paused == 0) {
			npc_x -= 3;
			npc2_x -= 4;
			npc3_x -= 2;
			if(npc_x <= 0) {
				npc_x = 170;
				npc_y = player_y;
			}
			
			if(npc2_x <= 0) {
				npc2_x = 170;
				npc2_y = player_y;
			}
			
			if(npc3_x <= 0) {
				npc3_x = 170;
				npc3_y = player_y;
			}
			
		}
		//set sprite positions
		move_sprite(1,npc_x,npc_y);
		move_sprite(2,npc2_x,npc2_y);
		move_sprite(3,npc3_x,npc3_y);
		
		//Backgroundscroll
		if(paused == 0) {
			scroll_bkg(1,0);
			//Alarmsound
			if(player_y >= 130) {
				NR10_REG = 0x00;
				NR11_REG = 0x40;
				NR12_REG = 0x73;
				NR13_REG = 0x00;
				NR14_REG = 0xD5;
			}
		}
		
		/*Colisiondetection
		if(npc_x >= player_x && npc_x <= player_x + player_size && npc_y >= player_y && npc_y <= player_y + player_size) {
			gameover = 1;
		}
		if(npc2_x >= player_x && npc2_x <= player_x + player_size && npc2_y >= player_y && npc2_y <= player_y + player_size) {
			gameover = 1;
		}
		*/
		if(npc3_x >= player_x && npc3_x <= player_x + player_size && npc3_y >= player_y && npc3_y <= player_y + player_size) {
			gameover = 1;
		}
		
		performantdelay(3); //performantdelay
	}
	move_bkg(0, 0, 40, 18);
	HIDE_SPRITES;
	//Gameoversound
	NR10_REG = 0x00;
	NR11_REG = 0x40;
	NR12_REG = 0x70;
	NR13_REG = 0x00;
	NR14_REG = 0xF0;
	
	printf("\n \n \n \n==== GAME OVER! ====");
	performantdelay(50);
	printf("\n \n \n \n \n \n \n \n \n \n \n \n    Press Start");
	paused = 0;
	while(paused == 0) {
		switch(joypad()) {
			case J_START:
				paused = 1;
				break;
		}
		performantdelay(1);
	}
	goto gl;
}