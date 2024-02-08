#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <time.h>

#include "snek.h"

#define height (40)
#define length (120)

char screen[height * length] = { 0 };
char snek[height * length] = { 0 };


int head_x = 15;
int head_y = 5;

char snek_direction = dir_right;
int snek_len = 0;

int growing = 0;
int next_food = -1;

int turn = 0;
int alive = 1;

// writes the snek to screen buffer starting from head
void put_snek(void)
{
    int x = head_x;
    int y = head_y;


    for (int i = 0; i < snek_len; i++)
    {
        screen[y * length + x] = "snek"[i % 4]; // muhaha
        switch (snek[i])
        {
        case dir_right:
            x--;
            break;
        case dir_down:
            y--;
            break;
        case dir_left:
            x++;
            break;
        case dir_up:
            y++;
            break;
        default:
            printf("\n\n\nsmallakwallakwallaksmallak!!!!! %d\n\n\n", snek[i]);
            break;
        }
    }
}

void update(void)
{
    switch (snek_direction)
    {
    case dir_right:
        head_x++;
        break;
    case dir_down:
        head_y++;
        break;
    case dir_left:
        head_x--;
        break;
    case dir_up:
        head_y--;
        break;
    default:
        break;
    }

    if (head_y == height || head_y < 0)
    {
        alive = 0;
    }
    if (head_x == length || head_x < 0)
    {
        alive = 0;
    }

    switch (screen[head_y * length + head_x])
    {
    case 's':
    case 'n':
    case 'e':
    case 'k':
        alive = 0;
        break;
    case 'f':
        growing = 3;
        screen[head_y * length + head_x] = 0;  
        next_food = -1;
        break;
    default:
        break;
    }

    memmove(snek + 1, snek, snek_len - (growing ? 0 : 1));
    snek[0] = snek_direction;
    
    if (growing)
    {
        snek_len++;
        growing--;
    }
}

int is_snek_part(char part)
{
    return part == 's' || part == 'n' || part == 'e' || part == 'k';
}

void draw(void)
{
    put_snek();

    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < length; j++) 
        {
            cursor_to(i + 1, j + 1); // translate the screen origin to (1, 1) 
            char spot = (screen[i * length + j]);

            if (is_snek_part(spot))
            {
                printf("\033[32m"); //green
                if (head_x == j && head_y == i)
                {
                    printf("\033[1m"); // bold snek head
                }
            }
            else if (spot == 'f')
            {
                printf("\033[31m"); // red food
            }
            
            putchar(spot ? spot : ' ');
            printf("\033[0m");
        }
    }

    cursor_to(height + 3, 1);
    printf("[%d] head [%d/%d] len %d direction %d growing %d", turn, head_x, head_y, snek_len, snek_direction, growing);
}

void final_draw(void)
{
    put_snek();

    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < length; j++) 
        {
            cursor_to(i + 1, j + 1);
            
            char spot = (screen[i * length + j]);
            int is_snek = is_snek_part(spot);
            if (is_snek) 
            {
                printf("\33[0;93m"); // high intensity yellow 
                printf("\33[40m"); // black background
                if (head_x == j && head_y == i)
                {
                    printf("\33[1;35m"); // bold purple
                }
            }
            
            putchar(is_snek ? spot : ' ');
            printf("\033[0m");
        }
    }

    cursor_to(height + 2, 1);
    printf("%d turns played; length %d\n", turn, snek_len);
}

void game(void)
{
    srand(time(NULL));
    system("clear");
    draw_borders(length, height);

    while (alive)
    {
        if (next_food == -1)
        {
            next_food = rand() % (length * height);
        }
        memset(screen, 0, length * height);
        screen[next_food] = 'f';

        draw();
        int key_pressed = get_input();
        if (key_pressed > 0)
        {
            snek_direction = key_pressed;
        }
        update();

        turn++;
    }

}



void setup(void)
{
    snek[0] = dir_down;
    snek[1] = dir_down;
    snek[2] = dir_down;
    snek[3] = dir_left;
    snek[4] = dir_left;
    snek[5] = dir_left;

    snek_len = 6;
}


int main(void)
{
    prepare_input();
    draw_title();
    setup();

    game();
    final_draw();
    memset(screen, 0, length * height);
    reset_input();
    draw_end_title();

    cursor_to(height + 3, 0);
    printf("\n\n");
    

    return 0;
}
