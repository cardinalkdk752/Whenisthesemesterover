#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>

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

void hideCursor() {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 1;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
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
    }

    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT && map[newY][newX] != '#') {
        map[character.y][character.x] = ' ';
        character.x = newX;
        character.y = newY;
        map[character.y][character.x] = '@';
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
    int timeElapsed = playtime; // 플레이 시간으로 간격 조절

    int blocksPerGeneration;
    if (timeElapsed % 3 == 0) { // 3초마다 블록 변경
        blocksPerGeneration = timeElapsed / 3;
    } else {
        blocksPerGeneration = 0;
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
void playMusic() {
    PlaySound("main2sound.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void stopMusic() {
    PlaySound(NULL, NULL, 0);
}

int main() {
    initializeGame();
    generateRandomBlocks();
    hideCursor();
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
                } else if (input == 'a') {
                    moveCharacter(-1);
                } else if (input == 'd') {
                    moveCharacter(1);
                } else if (input == 'w') {
                    moveCharacter(0);
                } else if (input == 's') {
                    moveCharacter(2);
                }
            }

            if (playtimeTimer >= playtimeDelay) {
                playtime++;
                playtimeTimer = 0.0f;
            }

            progress += mineOre();
            updateBlockGeneration();

            drawMap();
            printf("Progress: %d/100\n", progress);
            printf("Playtime: %d sec\n", playtime);

            accumulatedTime -= frameDelay;
        }
    }
    stopMusic();
    printf("Game Clear!\n");
    printf("Playtime: %d sec\n", playtime);

    return 0;
}


















































