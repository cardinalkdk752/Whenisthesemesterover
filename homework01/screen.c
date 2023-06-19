#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#endif
#define WIDTH 31
#define HEIGHT 15
#define _CRT_SECURE_NO_WARNINGS

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
#endif
}

void clearBuffer(char* screenBuf, int width, int height) {
    int i, j;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
                screenBuf[i + (j * width)] = '#';
            } else {
                screenBuf[i + (j * width)] = ' ';
            }
        }
        screenBuf[(j + 1) * width - 2] = '#';
        screenBuf[(j + 1) * width - 1] = '\n';
    }
    screenBuf[width * height - 2] = '#';
    screenBuf[width * height - 1] = '\0';
    clearScreen();
}

void writeStringToBufferAnimated(const char* string, char* screenBuf, int width, int height, int x, int y) {
    int len = strlen(string);
    int i;

    if (x < 0 || x + len >= width || y < 0 || y >= height) {
        return;
    }

    for (i = 0; i < len; i++) {
        screenBuf[x + i + (y * width)] = string[i];
    }

    Sleep(100);
}


void setLoadingToScreenBufferAnimated(char* screenBuf, int width, int height) {
    clearBuffer(screenBuf, width, height);
    writeStringToBufferAnimated("Loading...", screenBuf, width, height, 9, 8);
}

void setTitleToScreenBuffer(char* screenBuf, int width, int height) {
    clearBuffer(screenBuf, width, height);
    writeStringToBufferAnimated("Tungsten", screenBuf, width, height, 10, 3);
    writeStringToBufferAnimated("1.Play Game", screenBuf, width, height, 3, 6);
    writeStringToBufferAnimated("2.How To Play?", screenBuf, width, height, 3, 9);
    writeStringToBufferAnimated("3.Exit", screenBuf, width, height, 3, 12);
}
void setsc1ToScreenBuffer(char* screenBuf, int width, int height) {
    clearBuffer(screenBuf, width, height);

}



void setsc2ToScreenBuffer(char* screenBuf, int width, int height) {
    clearBuffer(screenBuf, width, height);
    writeStringToBufferAnimated("How To Play Game?", screenBuf, width, height, 6, 3);
    writeStringToBufferAnimated("Press your space bar", screenBuf, width, height, 2, 7);
    writeStringToBufferAnimated("to be able to dig up ore", screenBuf, width, height, 2, 8);
    writeStringToBufferAnimated("Press 4 to back", screenBuf, width, height, 5, 9);
}

void setsc3ToScreenBuffer(char* screenBuf, int width, int height) {
    clearBuffer(screenBuf, width, height);
    writeStringToBufferAnimated("Are you really going to", screenBuf, width, height, 3, 3);
    writeStringToBufferAnimated("end the game?", screenBuf, width, height, 3, 4);
    writeStringToBufferAnimated("1. Yes", screenBuf, width, height, 3, 8);
    writeStringToBufferAnimated("2. No", screenBuf, width, height, 3, 9);
}



#ifdef _YUHAN_C_WINDOW_USER
void showLoadingScreen() {
    clock_t start = clock();
    int i;

    char screenBuf[WIDTH * HEIGHT + 1];
    setLoadingToScreenBufferAnimated(screenBuf, WIDTH, HEIGHT);

    for (i = 0; i < 30; i++) {
        COORD pos = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("%s\n로딩 중... %d%%", screenBuf, (i + 1) * 100 / 30);
        Sleep(100);
    }

    clock_t end = clock();
    printf("\n로딩이 완료되었습니다.\n");
    printf("로딩 시간: %dms\n", (int)(end - start));
}
#endif

int main(void) {
    char screen[WIDTH * HEIGHT + 1];
    int input;
    int currentState = 0;

#ifdef _YUHAN_C_WINDOW_USER
    showLoadingScreen();
#else
    setLoadingToScreenBufferAnimated(screen, WIDTH, HEIGHT);
    printf("%s\n", screen);
#endif

    setTitleToScreenBuffer(screen, WIDTH, HEIGHT);

    while (1) {
        printf("%s\npress key-->\n", screen);
        scanf("%d", &input);

        if (currentState == 0) {
            if (input == 1) {
                setsc1ToScreenBuffer(screen, WIDTH, HEIGHT);
                currentState = 1;
            } else if (input == 2) {
                setsc2ToScreenBuffer(screen, WIDTH, HEIGHT);
                currentState = 2;
            } else if (input == 3) {
                setsc3ToScreenBuffer(screen, WIDTH, HEIGHT);
                currentState = 3;
            }
        } else if (currentState == 1) {
            if (input == 4) {
                setTitleToScreenBuffer(screen, WIDTH, HEIGHT);
                currentState = 0;
            }
        } else if (currentState == 2) {
            if (input == 4) {
                setTitleToScreenBuffer(screen, WIDTH, HEIGHT);
                currentState = 0;
            }
        } else if (currentState == 3) {
            if (input == 1) {
                break;
            } else if (input == 2) {
                setTitleToScreenBuffer(screen, WIDTH, HEIGHT);
                currentState = 0;
            }
        }
    }

    printf("Program terminated.\n");

    return 0;
}



