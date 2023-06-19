#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>


char menu[465];
void writeStringToBuffer(const char* string, int x, int y)
{
	int i=0;
	while (i<strlen(string))
	{
		Sleep(16);
		menu[i+x+31*y]=string[i];
		printf("%s\n", menu);
		i++;
	}
}
void setConsoleColor(unsigned textColor, unsigned backColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | (backColor << 4));
}
int fixed_screen()
{
	int i=0;
	// 가로가 0부터 30까지 칸은 총 31개 31번째는 계행문자
	
	while(i<465)
	{
		int x=i%31;
		int y=i/31;

		if(x==30)
		{
			menu[i]='\n';
		}
		else if(x==0 || x==29 || y==0 || y==14)
		{
			menu[i]='#';
		}
		else
		{
			menu[i]=' ';
		}
		i=i+1;
	}
	menu[464]='\0';
	return 0;
}


int main()
{
	clock_t start,end;
	start=clock();
	int cpu_time;
	int inputValue = 0;
	int game_state = 1;
	int game_play =1;
	setConsoleColor(15,0);
	fixed_screen();
	writeStringToBuffer("Loding...",6,6);
	Sleep(2000);

	while(game_state)
	{
		
		
		setConsoleColor(15,0);
		fixed_screen();

		
		if(game_state == 1){
			writeStringToBuffer("Eat Survival",9,2);
			writeStringToBuffer("V.0.1",12,3);
			writeStringToBuffer("1. Start Game",5,7);
			writeStringToBuffer("2. How to Play",5,8);
			writeStringToBuffer("3. Exit",5,9);
		}
		else if(game_state == 2){
			writeStringToBuffer("Survive from hunger",6,6);
			writeStringToBuffer("Press the arrow key to move",1,8);
			writeStringToBuffer("Retrun to menu?",8,11);
			writeStringToBuffer("1.yes 2.no",10,12);
		}
		else if(game_state == 3){
			writeStringToBuffer("Are you sure Exit?",6,6);
			writeStringToBuffer("1.yes 2.no",10,7);
		}
		
		scanf("%d", &inputValue);
		system("cls");
		
		
		
		// 메인메뉴에서 입력을 처리함
		if (game_state == 1){
			if (inputValue == 1){
				system("cls");
				drawMap();
				system("cls");
				setConsoleColor(15,0);
				game_state=1;
				
			}
				
			else if (inputValue == 2)
				game_state = 2;
			else if (inputValue == 3)
				game_state = 3;
		}
		else if (game_state == 2){
			if (inputValue == 1)
				game_state = 1;
			else if(inputValue==2)
				game_state = 2;
			else
				game_state =2;
				
		}
		else if (game_state == 3){
			if (inputValue == 1){
				fixed_screen();
				end = clock();
				cpu_time=((int)(end-start)/CLOCKS_PER_SEC);
				char time[20];
				sprintf(time,"%d",cpu_time);
				writeStringToBuffer("Program execution time",3,6);
				writeStringToBuffer(time,25,6);
				Sleep(1000);
				writeStringToBuffer("Exit...",6,9);
				Sleep(2000);
				game_state = 0;
			}
			else if (inputValue == 2)
				game_state = 1;
			else
				game_state =3;
		}

	}
    
	return 0;
}



