#include <stdio.h>
#include <stdlib.h>

#include "snek.h"

void draw_borders(int length, int height)
{
    for (int i = 0; i < length + 1; i++) {
        cursor_to(0 , i);
        putchar('*');
        cursor_to(height + 1, i + 1);
        putchar('*');
    }

    for (int i = 0; i < height + 1; i++) {
        cursor_to(i, 0);
        putchar('*');
        cursor_to(i, length + 1);
        putchar('*');
    }
}


char* title[] =  {
    "  /$$$$$$  /$$   /$$ /$$$$$$$$ /$$   /$$",
    " /$$__  $$| $$$ | $$| $$_____/| $$  /$$/",
    "| $$  \\__/| $$$$| $$| $$      | $$ /$$/ ",
    "|  $$$$$$ | $$ $$ $$| $$$$$   | $$$$$/  ",
    " \\____  $$| $$  $$$$| $$__/   | $$  $$  ",
    " /$$  \\ $$| $$\\  $$$| $$      | $$\\  $$ ",
    "|  $$$$$$/| $$ \\  $$| $$$$$$$$| $$ \\  $$",
    " \\______/ |__/  \\__/|________/|__/  \\__/",
};

char* end_title[] = {
"  /$$$$$$                                  ",
" /$$__  $$                                 ",
"| $$  \\__/ /$$$$$$  /$$$$$$/$$$$   /$$$$$$ ",
"| $$ /$$$$|____  $$| $$_  $$_  $$ /$$__  $$",
"| $$|_  $$ /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$",
"| $$  \\ $$/$$__  $$| $$ | $$ | $$| $$_____/",
"|  $$$$$$/  $$$$$$$| $$ | $$ | $$|  $$$$$$$",
 "\\______/ \\_______/|__/ |__/ |__/ \\_______/",
"  /$$$$$$                                  ",
" /$$__  $$                                 ",
"| $$  \\ $$ /$$    /$$/$$$$$$   /$$$$$$     ",
"| $$  | $$|  $$  /$$/$$__  $$ /$$__  $$    ",
"| $$  | $$ \\  $$/$$/ $$$$$$$$| $$  \\__/    ",
"| $$  | $$  \\  $$$/| $$_____/| $$          ",
"|  $$$$$$/   \\  $/ |  $$$$$$$| $$          ",
 "\\______/     \\_/   \\_______/|__/          "
};


void draw_title(void)
{
    system("clear");

    for (int i = 0; i < 8; i++)
    {
        cursor_to(3 + i, 20);
        printf("%s\n",title[i]);
    }
    
    cursor_to(15, 20);
    printf("press anu key to start...\n");
    int any_key;
    scanf("%d", &any_key);
}

void draw_end_title(void)
{
    for (int i = 0; i < 16; i++)
    {
        cursor_to(3 + i, 20);
        printf("%s\n",end_title[i]);    
    }
}