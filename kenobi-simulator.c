/*
 * kenobi-simulator.c
 * 
 * Copyright 2018 Stephen Stengel <stephen.stengel@cwu.edu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

//Purpose: To screw around with what I learned from intro to C.

//Neswest idea: Rewrite using ncurses.
//				Rewrite the get characters part using what I know now.

// NEW IDEAS:
//		The data structure is almost ok. Could just add a kinobi quote and the
//			order in which they are supposed to appear.
//		Each character is a data struct containing quotes for responding to each
//		other character. RNG picks two characters. Check which one goes first.
//		print.
//		
//		Format output to fit in 80 characters.

//TODO: Should I make this like a "what does the COW say: MEOW" toy?
//		Add more badguys.
//		Add character selection?
//		grevious and kenobi out of order qq
//		How to access struct variables with arrow sign? ->
//		What was that special thing you can put at the end of structs?
//		If ctrl-d  (end of file, EOF) is entered, the smartass error message
//			correctly displays, but it gets hung up on the munch_chars function
//			because the getchar in there will not have anything to munch. So it
//			waits for the next char to be entered.
//			Need to add an if loop to add a char to munch if user enters EOF.
//			Maybe when getting char, check if EOF and pass a true boolean to 
//			munch_chars().

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DONT_TRY_IT 0
#define DEW_IT 1
#define NUMBER_OF_BADGUYS 8
#define MAX_NAME_LENGTH 100
#define MAX_QUOTE_LENGTH 200

struct badguy
{
	char name[MAX_NAME_LENGTH];
	char quote[MAX_QUOTE_LENGTH];
};

int quote_print(struct badguy *badguy_array, int badguy_number);
int run_simulation(struct badguy *badguy_array);
int kenobi_say(struct badguy clone_of_badguy);
int choose_badguy(void);
int badguy_say(struct badguy clone_of_badguy);
int clear_screen(void);
int munch_chars(void);
//int print_badguy_info(struct badguy clone);

int main()
{
	srand(time(NULL));
	struct badguy badguy_array[NUMBER_OF_BADGUYS] =
	{
		{"Anakin", "I don't like sand.\n"},
		{"Grievous", "General Kenobi!\n"},
		{"The Senate","A surprise to be sure, but a welcome one.\n"},
		{"Count Dooku", "The Republic is currently being controlled by a"
						" sith lord named Sidious.\n"},
		{"Grieves", "General Misquoti!\n"},
		{"Elan Sleazebaggano", "You wanna buy some death sticks?\n"},
		{	"Jango Fett",
			"I'm just a simple man, trying to make my way in the universe.\n"},
		{"George Lucas", "Jar Jar is the key to all of this.\n"}
	};
	
	run_simulation(badguy_array);
	return DONT_TRY_IT;
}

//This function prints the badguy's quote and Kenobi's quote.
int quote_print(struct badguy *badguy_array, int badguy_number)
{
	badguy_say(badguy_array[badguy_number]);
	kenobi_say(badguy_array[badguy_number]);
	return DONT_TRY_IT;
}

//Prints a Kenobi quote depending on the badguy that was chosen.
//I made kenobi_string to reduce the amount I need to type.
//	Yeah.
//It might have been easier to read if I were to just include these quotes and 
//the badguy quotes in the same struct.
int kenobi_say(struct badguy clone_of_badguy)
{
	char *kenobi_string = "Kenobi:";
	if(!strcmp("Anakin", clone_of_badguy.name))
	{
		printf("%s I HAVE THE HIGH GROUND!\n", kenobi_string);
	}
	else if(!strcmp("Grievous", clone_of_badguy.name))
	{
		printf("%s Hello there!\n", kenobi_string);
	}
	else if(!strcmp("The Senate", clone_of_badguy.name))
	{
		printf(	"%s Oh no, I'm not brave enough for politics.\n",
				kenobi_string);
	}
	else if(!strcmp("Grieves", clone_of_badguy.name))
	{
		printf("%s Hi!\n", kenobi_string);
	}
	else if(!strcmp("Count Dooku", clone_of_badguy.name))
	{
		printf("%s Chancellor Palpatine is evil!\n"
				"###   Written and Directed by GEORGE LUCAS   ###\n",
				kenobi_string);
//Due to our current animosity I am not ever going to investigate this claim!
	}
	else if(!strcmp("Elan Sleazebaggano", clone_of_badguy.name))
	{
		printf("%s You don't want to sell me death sticks.\n", kenobi_string);
		printf("Elan Sleazebaggano: I don't wanna sell you death sticks.\n");
		printf("%s You want to go home and rethink your life.\n",kenobi_string);
		printf("Elan Sleazebaggano: I wanna go home and rethink my life.\n");
	}
	//Ever made your way as far into the interior as Coruscant?
	else if(!strcmp("Jango Fett", clone_of_badguy.name))
	{
		printf("%s Ever made your way as far into the interior as Coruscant?\n",
					kenobi_string);
	}
	else if(!strcmp("George Lucas", clone_of_badguy.name))
	{
		printf("Qui Gon's Force Ghost:"
				" Just because you can speak"
				" does not mean that you are intelligent.\n");
	}
	else
	{
		printf(	"Wait a minute, how did this happen?"
				" We're smarter than this! (An error happened)\n");
	}
	return DONT_TRY_IT;
}

//This prints the badguy's name and quote.
int badguy_say(struct badguy clone_of_badguy)
{
	printf("%s: %s", clone_of_badguy.name, clone_of_badguy.quote);
	return DONT_TRY_IT;
}

//This returns a random number from 1 to NUMBER_OF_BADGUYS.
int choose_badguy(void)
{
	return rand() % NUMBER_OF_BADGUYS;
}

//This prints a bunch of newlines so that the output is always at the bottom.
//There was an easier way to do this, I think.
int clear_screen(void)
{
	int NUMBER_OF_LINES_TO_SKIP = 60;
	int i;
	for(i = 0; i < NUMBER_OF_LINES_TO_SKIP; i++)
	{
		printf("\n");
	}
	return DONT_TRY_IT;
}

//This is called after a character is sent to the simulation. This steps through
//	the remaining unused characters that are still in stdin so that they don't
//	make the quote functions run more than once per button press.
int munch_chars(void)
{
	char char_ayy = '0';
	while((char_ayy = getchar()) != '\n' && char_ayy != EOF)
	{
		//NOTHING HEHE
	}
	
	//Old version that doesn't check for EOF.
	//I don't know how one would enter the EOF character on
	//	a standard keyboard but I saw an example online that
	//	checked for it.
	//OK, I found out how to enter EOF, ctrl + d, but both
	//	of these methods seem have the same effect.
	//~ while(getchar() != '\n')
	//~ {
		//~ //NOTHING HAHA
	//~ }
	
	return DONT_TRY_IT;
}

//This calls the little bits that make the simulation go.
int run_simulation(struct badguy *badguy_array)
{
	int dooku = DONT_TRY_IT;
	char isContinue = DEW_IT;
	while(isContinue != '0')//The ascii character zero
	{
		clear_screen();
		if(dooku > DONT_TRY_IT)
		{
			if(isContinue != '\n')
			{
				printf(	"Kenobi: You think that you can break my program by "
						"not following instructions?\n"
						"        Too bad! I knew that this could happen and "
						"I am smarter than that.\n\n");
				//Although it did take me many hours to make it work...				
				munch_chars();
			}
		}
		if(dooku == DONT_TRY_IT)
		{
			dooku++;
		}
		
		int badguy_number;
		badguy_number = choose_badguy();
		quote_print(badguy_array, badguy_number);
		printf("Press enter to continue. Enter 0 to quit.\n");
		isContinue = getchar();
	}
	return DONT_TRY_IT;
}

//~ //this was for testing
//~ int print_badguy_info(struct badguy clone)
//~ {
	//~ printf("Info about passed badguy. name: %s  quote: %s\n", 	clone.name, 
															//~ clone.quote);
	//~ return DONT_TRY_IT;
//~ }
