#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>

char menu[465];
void viewCursor() {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 1;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void writeStringToBuffer(const char* string, int x, int y)
{
	int i=0;
	while (i<strlen(string))
	{
        system("cls");
        viewCursor();
		menu[i+x+31*y]=string[i];
		printf("%s\n", menu);
        Sleep(16);
		i++;
	}
}
void setThemeColor(unsigned textColor, unsigned backColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | (backColor << 4));
}
#define MAP_WIDTH 30
#define MAP_HEIGHT 15

typedef struct {
    int x;
    int y;
} Character;

Character character;
char map[MAP_HEIGHT][MAP_WIDTH];

int progress = 0;
int playtime = 0;

void clearMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map[i][j] = ' ';
        }
    }
}

void drawMap() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(hConsole, cursorPos);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == character.y && j == character.x) {
                printf("@ ");
            } else {
                printf("%c ", map[i][j]);
            }
        }
        printf("\n");
    }
}




int mineOre() {
    int progress = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // 주변 1x1 영역만 확인
            if ((i == 0 && j == 0) || i != 0 && j != 0) {
                continue;
            }
            int newX = character.x + i;
            int newY = character.y + j;

            if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != ' ') {
                char oreType = map[newY][newX];

                switch (oreType) {
                    case 'S':
                        progress += 0.1;
                        break;
                    case 'P':
                        progress += 0.5;
                        break;
                    case 'I':
                        progress += 1;
                        break;
                    case 'G':
                        progress += 3;
                        break;
                    case 'D':
                        progress += 5;
                        break;
                    case 'T':
                        progress += 30;
                        break;
                }

                map[newY][newX] = ' ';
            }
        }
    }

    return progress;
}

void moveCharacter(int direction) {
    int newX = character.x;
    int newY = character.y;

    if (direction == -1) {
        newX--;
    } else if (direction == 1) {
        newX++;
    } else if (direction == 0) {
        newY--;
    } else if (direction == 2 && character.y < MAP_HEIGHT - 2) {
        newY++;
    } else if (direction == 3) {
        // 스페이스바 입력 처리
        int progress = mineOre();
        // 여기에서 진행도를 처리하는 로직을 추가할 수 있습니다.
        return;
    }

    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != '#') {
        map[character.y][character.x] = ' ';
        character.x = newX;
        character.y = newY;
        map[character.y][character.x] = '@';
    }
}
void initializeGame() {
    srand(time(NULL));

    clearMap();

    character.x = MAP_WIDTH / 2;
    character.y = MAP_HEIGHT - 5;
    map[character.y][character.x] = '@';
}

typedef enum {
    Stone,
    Graphite,
    Iron,
    Gold,
    Diamond,
    Tungsten
} OreType;

OreType getRandomOreType() {
    int randomNumber = rand() % 1000 + 1;
    if (randomNumber <= 729) {
        return Stone;
    } else if (randomNumber <= 879) {
        return Graphite;
    } else if (randomNumber <= 954) {
        return Iron;
    } else if (randomNumber <= 984) {
        return Gold;
    } else if (randomNumber <= 999) {
        return Diamond;
    } else {
        return Tungsten;
    }
}

void generateRandomBlocks() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map[i][j] = ' ';
        }
    }

    for (int i = 0; i < MAP_WIDTH; i++) {
        OreType oreType = getRandomOreType();
        char oreSymbol;

        switch (oreType) {
            case Stone:
                oreSymbol = 'S';
                break;
            case Graphite:
                oreSymbol = 'P';
                break;
            case Iron:
                oreSymbol = 'I';
                break;
            case Gold:
                oreSymbol = 'G';
                break;
            case Diamond:
                oreSymbol = 'D';
                break;
            case Tungsten:
                oreSymbol = 'T';
                break;
        }

        map[MAP_HEIGHT-1][i] = oreSymbol;
    }
}



void updateBlockGeneration() {
    int timeElapsed = playtime / 3;

    int blocksPerGeneration;
    if (timeElapsed < 1) {
        blocksPerGeneration = 1;
    } else if (timeElapsed < 3) {
        blocksPerGeneration = 2;
    } else if (timeElapsed < 5) {
        blocksPerGeneration = 3;
    } else {
        blocksPerGeneration = 5;
    }

    for (int i = 0; i < blocksPerGeneration; i++) {
        int randomX = rand() % MAP_WIDTH;
        OreType oreType = getRandomOreType();
        char oreSymbol;

        switch (oreType) {
            case Stone:
                oreSymbol = 'S';
                break;
            case Graphite:
                oreSymbol = 'P';
                break;
            case Iron:
                oreSymbol = 'I';
                break;
            case Gold:
                oreSymbol = 'G';
                break;
            case Diamond:
                oreSymbol = 'D';
                break;
            case Tungsten:
                oreSymbol = 'T';
                break;
        }

        map[MAP_HEIGHT - 1][randomX] = oreSymbol;
    }
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

void playMusic() {
    PlaySound("main2sound.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void stopMusic() {
    PlaySound(NULL, NULL, 0);
}
#define true 1
#define false 0
int main() {
    clock_t start, end;
    start = clock();
    int cpu_time;
    int inputValue = 0;
    int game_fk = 1;
    int game_play = 1;
    setThemeColor(15, 0);
    fixed_screen();
    writeStringToBuffer("Loading...", 6, 6);
    Sleep(2000);

    while (game_fk) {
        setThemeColor(15, 0);
        fixed_screen();

        if (game_fk == 1) {
            writeStringToBuffer("Tungsten", 9, 2);
            writeStringToBuffer("1. Start Game", 5, 7);
            writeStringToBuffer("2. How to Play", 5, 8);
            writeStringToBuffer("3. Exit", 5, 9);
        }
        else if (game_fk == 2) {
            writeStringToBuffer("Dig up the ore", 6, 6);
            writeStringToBuffer("Press the WASD Key to move", 2, 8);
            writeStringToBuffer("Return to menu?", 8, 11);
            writeStringToBuffer("1. Yes 2. No", 10, 12);
        }
        else if (game_fk == 3) {
            writeStringToBuffer("Are you sure Exit?", 6, 6);
            writeStringToBuffer("1. Yes 2. No", 10, 7);
        }

        scanf("%d", &inputValue);
        system("cls");

        // 메인메뉴에서 입력을 처리함
        if (game_fk == 1) {
            if (inputValue == 1) {
                // 게임 실행
                initializeGame();
                generateRandomBlocks();
                viewCursor();
                clock_t previousTime = clock();
                float frameDelay = 0.016f;
                float accumulatedTime = 0.0f;
                float playtimeTimer = 0.0f;
                const float playtimeDelay = 1.0f;
                playMusic();

                while (progress < 100) {
                    clock_t currentTime = clock();
                    float deltaTime = (float)(currentTime - previousTime) / CLOCKS_PER_SEC;
                    previousTime = currentTime;

                    accumulatedTime += deltaTime;
                    playtimeTimer += deltaTime;

                    if (accumulatedTime >= frameDelay) {
                        int input;
                        if (_kbhit()) {
                            input = _getch();
                            if (input == 'q') {
                                break;
                            }
                            else if (input == 'a') {
                                moveCharacter(-1);
                            }
                            else if (input == 'd') {
                                moveCharacter(1);
                            }
                            else if (input == 'w') {
                                moveCharacter(0);
                            }
                            else if (input == 's') {
                                moveCharacter(2);
                            }else if (input == ' ') {
                                moveCharacter(3);  // 스페이스바 입력
                            }
                        }

                        if (playtimeTimer >= playtimeDelay) {
                            playtime++;
                            playtimeTimer = 0.0f;
                        }

                        progress += mineOre();
                        updateBlockGeneration();

                        drawMap();
                        printf("Progress of assignment: %d/100\n", progress);
                        printf("Time to do homework: %d sec\n", playtime);

                        accumulatedTime -= frameDelay;
                    }
                }

                stopMusic();
                printf("final examinations!!!!!\n");
                printf("Playtime: %d sec\n", playtime);
                setThemeColor(15, 0);

                while (true) {
                    printf("Return to game? (1. Yes 2. No 3. Go to main)\n");
                    scanf("%d", &inputValue);
                    system("cls");

                    if (inputValue == 1) {
                        // 게임 재실행
                        // 추가된 부분: 게임 초기화 및 블록 생성
                        initializeGame();
                        generateRandomBlocks();
                        viewCursor();
                        clock_t previousTime = clock();
                        float frameDelay = 0.016f;
                        float accumulatedTime = 0.0f;
                        float playtimeTimer = 0.0f;
                        const float playtimeDelay = 1.0f;
                        progress = 0; // 게임 진행도 초기화
                        break;
                    }
                    else if (inputValue == 2) {
                        // 완전히 종료
                        game_fk = 0;
                        break;
                    }
                    else if (inputValue == 3) {
                        // 메인화면으로 돌아감
                        game_fk = 1;
                        break;
                    }
                    else {
                        printf("Invalid input. Please try again.\n");
                    }
                }
            }
            else if (inputValue == 2) {
                game_fk = 2;
            }
            else if (inputValue == 3) {
                game_fk = 3;
            }
        }
        else if (game_fk == 2) {
            if (inputValue == 1)
                game_fk = 1;
            else if (inputValue == 2)
                game_fk = 2;
            else
                game_fk = 2;
        }
        else if (game_fk == 3) {
            if (inputValue == 1) {
                fixed_screen();
                writeStringToBuffer("Game Exit...", 6, 5);
                Sleep(2000);
                game_fk = 0;
            }
            else if (inputValue == 2)
                game_fk = 1;
            else
                game_fk = 3;
        }
    }

    return 0;
}

















































