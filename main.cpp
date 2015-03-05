/*
 ---------------------------------------------------------------------------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
---------------------------------------------------------------------------
*/
/*
Made By: Patrick J. Rye
Purpose: A game I made as an attempt to teach myself c++, just super basic, but going to try to keep improving it as my knowledge increases.
Current Revision: 1.2e
Change Log---------------------------------------------------------------------------------------------------------------------------------------------------
Date	Revision	Changed By			Changes
------  ---------   ------------		---------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================			
-------------------------------------------------------------------------------------------------------------------------------------------------------------									
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXPERIEMENTAL VERISON~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-------------------------------------------------------------------------------------------------------------------------------------------------------------
=============================================================================================================================================================	
3/3/15	1.0e		Patrick Rye			-Added arrow key movement controlling.
=============================================================================================================================================================
3/3/15	1.1e		Patrick Rye			-Merged new code with V2.3b-dev1
=============================================================================================================================================================
3/4/15	1.2e		Patrick Rye			-Changed all system("pause") to getch.
										-Changed all cout to printf
										-Replaced all cout << string(X, '\n'); with refresh();
										-Made enum of letters on the keyboard
=============================================================================================================================================================			
*/

/*********************************************************************************************************/
#include <iostream>
#include <fstream>
#include "curses.h"
#include <string>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <locale>
#include <cstdio>
#include <ctime>
/*********************************************************************************************************/
#include "basic.h" //Functions that hold change the case of chars and strings
#include "battle.h" //Functions that deal with battling, levelling up and making a player.
#include "rooms.h" //Functions that deal with generating a dungeon
/*********************************************************************************************************/
using namespace std;
Dungeon d; //Define the dungeon class as 'd' so I can use function in there anywhere later in the code.
/*********************************************************************************************************/
//Make all the global variables that I need.
int intMainLevel; //The level of the dungeon.
int intLevelStart = 1; //The level that the game starts at. Will be 1 unless loading from a save.
const string CurrentVerison = "1.2e"; //The current version of this program, stored in a save file later on.
/*********************************************************************************************************/
//These functions have to be up here as functions in save.h use them.
//These values are used to pass values to the save header so that they may be saved.
//Or to set values from a load.
int getmainvalue(int intvalue)
{
	if(intvalue == 0 ) {return intMainLevel;}
	else if (intvalue == 1) {return intLevelStart;}
	else {return 1;}
}

int setmainvalue(int intlocation, int intvalue)
{
	if(intlocation != 0) {return 1;}
	else {intLevelStart = intvalue; return 0;}
}
#include "save.h" //A header to hold functions related to saving and loading.
/*********************************************************************************************************/
enum 
{
	
	KEYBOARD_KEY_A = 97,
	KEYBOARD_KEY_B, 
	KEYBOARD_KEY_C, 
	KEYBOARD_KEY_D, 
	KEYBOARD_KEY_E, 
	KEYBOARD_KEY_F, 
	KEYBOARD_KEY_G, 
	KEYBOARD_KEY_H, 
	KEYBOARD_KEY_I, 
	KEYBOARD_KEY_J, 
	KEYBOARD_KEY_K, 
	KEYBOARD_KEY_L, 
	KEYBOARD_KEY_M, 
	KEYBOARD_KEY_N, 
	KEYBOARD_KEY_O, 
	KEYBOARD_KEY_P, 
	KEYBOARD_KEY_Q, 
	KEYBOARD_KEY_R, 
	KEYBOARD_KEY_S, 
	KEYBOARD_KEY_T, 
	KEYBOARD_KEY_U, 
	KEYBOARD_KEY_V, 
	KEYBOARD_KEY_W, 
	KEYBOARD_KEY_X, 
	KEYBOARD_KEY_Y,
	KEYBOARD_KEY_Z
};
/*********************************************************************************************************/


void initialize()
{

	initscr();
	raw();
	keypad(stdscr, TRUE);
	//wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(stdscr);
	//noecho();
}

void finalize()
{
	refresh();
	getch();
	endwin();
}


int main()
{
	initialize();
	PassProgramVerison(CurrentVerison); //Pass current program version into the save header.
	refresh();
	char charPlayerDirection;
	char charBattleEnding;
	char charExitFind;
	bool blOldSave = false;
	char chrPlayerMade = 'F';
	bool blDebugMode = false;
	char chrSaveSuccess = 'N'; //N means that save has not been run.
	
	blDebugMode = fileexists("main.cpp"); //If source code exists, set game into debug mode.
	
	if (blDebugMode) {SetBattleDebugMode(true); SetRoomDebugMode(true);} //Sets debug mode for both Rooms.h & Battle.h
	
	if (fileexists("save.bif")) //Check if there is a save present.
	{
		blOldSave = LoadOldSave();
		if (blOldSave) {chrPlayerMade = 'T';}
	//End of if save exists.	
	}
	else {refresh();}
	
	if(!blOldSave) //If it is not an old save show welcome message.
	{
		cout<<"Welcome to the World of Attacker."<<endl<<"Your objective is to go through 10 randomly generated dungeons."<<endl;
		cout<<"You are looking for the stairs down ( > ). While you are represented by † ."<<endl;
		cout<<"Every step brings you closer to your goal, but there might be a monster there as well."<<endl;
		cout<<"Each level is harder than the last, do you have what it takes to win?"<<endl;
		cout<<"Good luck!"<<endl<<endl<<endl<<endl;
		do {chrPlayerMade = PlayerInitialize();} while (chrPlayerMade != 'T'); //Repeat initialization until player is made.
	}

	//refresh();
	for(intMainLevel = intLevelStart; intMainLevel <= 10; intMainLevel++)
	{
		//Do level up if new level.
		if (intMainLevel > intLevelStart) {LevelUpFunction();}
		charExitFind = 'F';
		cout<<endl;
		if (blOldSave && intMainLevel == intLevelStart) {/*d.playerfind();*/ d.showDungeon();} //If old save and the level of that save, just load old dungeon.
		else {Dungeon d;/*Generates dungeon.*/} //If it is not old game OR a different level of old game, make new dungeon.
		
		do
		{
			refresh();
			d.showDungeon();
			cout<<"Level "<<intMainLevel<<" of 10."<<endl;
			cout<<"Please enter a direction you would like to go ( N , E , S , W )."<<endl<<"Enter 'X' to exit, 'C' to get your current health and stats,";
			cout<<endl<<"'H' to heal, or 'P' to save."<<endl;
			if (blDebugMode) {cout<<"'O' to go straight to down stairs, or 'M' to force monster."<<endl;}
			int ch;
			ch = wgetch( stdscr );
			switch(ch)
			{
				case KEY_LEFT :
					charPlayerDirection = 'W';
					break;
				case KEY_UP :
					charPlayerDirection = 'N';
					break;
				case KEY_RIGHT :
					charPlayerDirection = 'E';
					break;
				case KEY_DOWN :
					charPlayerDirection = 'S';
					break;
				case KEYBOARD_KEY_H :
					charPlayerDirection = 'H';
					break;
				case KEYBOARD_KEY_X :
					charPlayerDirection = 'X';
					break;
				case KEYBOARD_KEY_P:
					charPlayerDirection = 'P';
					break;
				case KEYBOARD_KEY_M:
					charPlayerDirection = 'M';
					break;
				case KEYBOARD_KEY_O:
					charPlayerDirection = '&';
					break;
				case KEYBOARD_KEY_C:
					charPlayerDirection = 'C';
					break;
			}
			
			charExitFind = d.PlayerMovement(charPlayerDirection);
			if (charExitFind == 'E') {return 0;} //If we get an error exit program.
			if (charExitFind == 'S') {chrSaveSuccess = savefunction();} //Save the game.
			switch (chrSaveSuccess)
			{
				case 'T' :
					cout<<endl<<"Save succeeded."<<endl;
					getch();
					chrSaveSuccess = 'N'; //Set this back to N, so that player is not spammed with this message.
					break;
				case 'F' :
					cout<<endl<<"Save failed!"<<endl;
					getch();
					chrSaveSuccess = 'N'; //Set this back to N, so that player is not spammed with this message.
					break;
			}
			if (!(charExitFind=='S') && !(charPlayerDirection == 'C')) //If player did not save or did not check himself, see if player runs into monster.
			{
				if(rand() % 101 <= 10 || charExitFind == 'M') //Random chance to encounter monster, or debug code to force monster encounter.
				{
					refresh();
					charBattleEnding = startbattle(intMainLevel); //Starts battle.
					if(charBattleEnding == 'F') {return 0;} //Player lost battle.
				}
			}
		}while (charExitFind != 'T');
	}
	refresh();
	cout<<"You win!!";
	getch();
	finalize();
	return 0;
//End of main
}
