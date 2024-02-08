#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <errno.h>

#include "snek.h"

struct pollfd polled[1] = {{.fd = STDIN_FILENO, .events = POLLIN}};

#define upval  (4283163)
#define downval  (4348699)
#define rightval  (4414235)
#define leftval  (4479771)

void prepare_input() 
{
    // canonical mode - get input wihtout hitting enter
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    printf("\33[?25l"); // hide cursor
}

void reset_input() 
{
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    printf("\33[?25h"); // show cursor
}


int get_input(void)
{
    int poll_res = poll(polled, 1, frame_duration_ms);

    int log_fd = open("dir_log", O_CREAT | O_WRONLY, 0666);
    char log_buffer[1024] = { 0 };

    if (poll_res < 0)
    {
        sprintf(log_buffer, "poll trouble! %d\n", errno);
        write(log_fd, log_buffer, 1024);
        return 0;
    }

    if (polled[0].revents & POLLIN)
    {
        int buf = 0;
        int were_read = read(STDIN_FILENO, &buf, 4);

    //
        char c[4] = { 0 };
        sprintf(c, "%d", buf);
        write(log_fd, c, 4);
        write(log_fd, "\n", 1);
        close(log_fd);
    //

        if (were_read > 0)
        {
            switch (buf)
            {
            case upval:
                return dir_up;
            case downval:
                return dir_down;
            case rightval:
                return dir_right;
            case leftval:
                return dir_left;
            default:
                return 0;
            }
        }
    }

    return 0;
}

