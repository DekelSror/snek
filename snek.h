#ifndef snek_h
#define snek_h


#define frame_duration_ms (100)

typedef enum {dir_right = (1), dir_down = (2), dir_left = (3), dir_up = (4) } direction_e;

static inline void cursor_to(int x, int y) {printf("\033[%d;%dH", x + 1, y + 1);}

void draw_borders(int length, int height);
void draw_title(void);
void draw_end_title(void);

void reset_input(void);
void prepare_input(void);
int get_input(void);

#endif // snek_h