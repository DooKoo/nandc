#include "stdafx.h"
#include "windows.h"
#include "conio.h"

enum type 
{
	nought,
	cross,
	none
};

struct action
{
	type board[9];
	void (*nought)(action*);
	void (*cross)(action*);
	void (*view)(action*);
	unsigned short (*check)(action*);
};

void tNought(action *self)
{
	char inp;
	bool check=false;
	while (check==false)
	{
		fflush(stdin);
		printf_s("Player 2:");
		inp=getchar();
		if ((inp>=49) && (inp<=58) && (self->board[int(inp)-49]==none) )
		{
			check=true;
			self->board[int(inp)-49]=nought;
		}
		else
		{
			check=false;
			printf_s("\nError. Press new data(1-9).\n");
		}
	}
};//Player 2;

void tCross(action *self)
{
	char inp;
	bool check=false;
	while (check==false)
	{
		fflush(stdin);
		printf_s("Player 1:");
		inp=getchar();
		if ((inp>=49) && (inp<=58) && (self->board[int(inp)-49]==none) )
		{
			check=true;
			self->board[int(inp)-49]=cross;
		}
		else
		{
			check=false;
			printf_s("\nError. Press new data(1-9).\n");
		}
	}
};//Player 1;

void tView(action *self)
{
	for (int i = 0; i < 9; i++)
	{
		if (self->board[i]==nought)
			printf_s(" 0 ");
		else if (self->board[i]==cross)
			printf_s(" x ");
		else
			printf_s(" %i ",i+1);

		if ((((i+1)%3)==0) && (i!=0))
			printf_s("\n\n");	
	}
	
};

unsigned short tCheck(action *self)//0-none, 1-cross, 2-nought;
{
	unsigned short winner=0;
	if	(
		(self->board[0]==nought && self->board[1]==nought && self->board[2]==nought) ||
		(self->board[0]==nought && self->board[3]==nought && self->board[6]==nought) ||
		(self->board[0]==nought && self->board[4]==nought && self->board[8]==nought) ||
		(self->board[3]==nought && self->board[4]==nought && self->board[5]==nought) ||
		(self->board[6]==nought && self->board[7]==nought && self->board[8]==nought) ||
		(self->board[1]==nought && self->board[4]==nought && self->board[7]==nought) ||
		(self->board[2]==nought && self->board[5]==nought && self->board[8]==nought) ||
		(self->board[2]==nought && self->board[4]==nought && self->board[6]==nought) 
		)//nought;
		winner=2;
	else if(
		(self->board[0]==cross && self->board[1]==cross && self->board[2]==cross) ||
		(self->board[0]==cross && self->board[3]==cross && self->board[6]==cross) ||
		(self->board[0]==cross && self->board[4]==cross && self->board[8]==cross) ||
		(self->board[3]==cross && self->board[4]==cross && self->board[5]==cross) ||
		(self->board[6]==cross && self->board[7]==cross && self->board[8]==cross) ||
		(self->board[1]==cross && self->board[4]==cross && self->board[7]==cross) ||
		(self->board[2]==cross && self->board[5]==cross && self->board[8]==cross) ||
		(self->board[2]==cross && self->board[4]==cross && self->board[6]==cross) 
		)//cross;
		winner=1;

	return winner;
};

void Init(action *self)
{
	self->nought=tNought;
	self->cross=tCross;
	self->view=tView;
	self->check=tCheck;
	for (int i = 0; i < 9; i++)
		self->board[i]=none;
};

void play()
{
	action *data=new action;
	Init(data);
	int i=0;
	unsigned short win=0;

	while ((i<9) && (win==0))
	{
		system("cls");
		data->view(data);
		if ((i%2)==0)
			data->cross(data);
		else
			data->nought(data);
		i++;
		win=data->check(data);
	}
	system("cls");
	if (win==1)
		printf_s(" --------------\n| Player 1 win |\n --------------\n");
	else if(win==2)
		printf_s(" --------------\n| Player 2 win |\n --------------\n");
	else 
		printf_s(" ----------------\n| Friendship win |\n ----------------\n");

	printf_s("Press any symbol");
	_getch();
	system("cls");
};

int main()
{
	char inp;
	bool check=false;
	printf_s("Hello, welcome for MY game =)\n");
	do{
	printf_s("Press 0 for game Player vs Player\n");
	//printf_s("Press 1 for information\n");
	printf_s("Press 2 for exit\nPress data:");
	while (check==false)
	{
		fflush(stdin);
		inp=getchar();
			
		if ((int(inp)>=48) && (int(inp)<=50))
			check=true;
		else
		{
			check=false;
			printf_s("Error. Press correct data\nPress data:");
		}
	}
	if (inp==48)
		play();

	check=false;
	}while(inp!=50);
	
	return 0;
}

