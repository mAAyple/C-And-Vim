#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#define bert_length 33
#define bert_height 4
#define bert_refresh 200
#define snake_length 14
#define snake_height 3
struct bert {
	unsigned int length;
	char body1[bert_length + 1];
	char body2[bert_length + 1];
	char body3[bert_length + 1];
	char body4[bert_length + 1];
	int x;
	int y;
	char time;
};

struct snake {
	unsigned int length;
	char body[snake_length + 1];
	char front[snake_height + 1];
	int x;
	int y;
};

struct proj {
	unsigned int length;
	char body;
	char front;
	int x;
	int y;
};

int bert_time(){
	time_t now = time(NULL);
	//struct tm *t = localtime(&now);
	return now;
}
void draw_bert(struct bert *the_bert) {
	mvprintw(0, 0, "%d, %d", the_bert->y, the_bert->x);
	mvprintw(the_bert->y, the_bert->x, "%s", the_bert->body1);
	mvprintw(the_bert->y + 1, the_bert->x, "%s", the_bert->body2);
	mvprintw(the_bert->y + 2, the_bert->x, "%s", the_bert->body3);
	mvprintw(the_bert->y + 3, the_bert->x, "%s", the_bert->body4);
}

int main() {
	int input = 'a';
	//int bert_time();
	//clock_t prev_clock = 0;
	struct bert brt;
	brt.length = 8;
	strcpy(brt.body1,"| ^^|");
	strcpy(brt.body2,"|  0 ___");
	strcpy(brt.body3,"|    ---");
	strcpy(brt.body4,"| /||");
	brt.y = LINES + 10;
	brt.x = 0;
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	timeout(0);
	noecho();


	while(1) {
		clock_t curr_clock = clock();
		clock_t prev_clock = 0;
		if(curr_clock - prev_clock > CLOCKS_PER_SEC / bert_refresh) {
			prev_clock = curr_clock;
			clear();

			draw_bert(&brt);



			refresh();
		}

		input = getch();
		if(input == 'a' || input == 'A') {
			brt.x = brt.x - 1;
		}
		else if(input == 'd' || input == 'D') {
			brt.x = brt.x + 1;
		}
		if(input == 'w' || input == 'W') {
			brt.y = brt.y + 1;
		}
		else if(input == 's' || input == 'S'){
			brt.y = brt.y - 1;
		}
	}
	endwin();
}
