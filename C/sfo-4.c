#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#define MAX_SHIP_LENGTH 3
#define MAX_ENEMY_LENGTH 3
#define NUM_PROJECTILES 100
#define NUM_ENEMIES 100
#define REFRESH_RATE 100

struct ship {
	unsigned int length;

	char body[MAX_SHIP_LENGTH + 1]; //+1 for null terminator
	char front[MAX_SHIP_LENGTH + 1];

	int y;
	int x;
};

struct projectile {
	int y;
	int x;
	unsigned int length;
	char body;
	unsigned int is_active;
};

struct enemy {
	int y;
	int x;
	unsigned int length;
	char body[MAX_ENEMY_LENGTH + 1];
	char front[MAX_ENEMY_LENGTH + 1];
	/* Indicates if the enemy is on screen or not */
	unsigned int is_active;
};

/* Draw the ship at the ship's current location */
void draw_ship(struct ship *my_ship) {
	mvprintw(0, 0, "%d, %d", my_ship->y, my_ship->x);
	mvprintw(my_ship->y, my_ship->x, "%s", my_ship->front);
	mvprintw(my_ship->y + 1, my_ship->x, "%s", my_ship->body);
}

/* Draw projectiles at their current locations */
void draw_projectiles(struct projectile projs[], unsigned int num_projs) {
	for(int i = 0; i < num_projs; i++) {
		struct projectile *proj = &projs[i];
		if(proj->is_active) {
			mvprintw(proj->y, proj->x, "%c", proj->body);
			proj->y -= 1;
			if(proj->y < 0) {
				proj->is_active = 0;
			}
		}
	}
}

/* Draw enemies at their current locations */
void draw_enemies(struct enemy enemies[], unsigned int num_enemies) {
	for(int i = 0; i < num_enemies; i++) {
		struct enemy *en = &enemies[i];
		if(en->is_active) {
			mvprintw(en->y, en->x, "%s", en->front);
			mvprintw(en->y + 1, en->x, "%s", en->body);
		}
	}
}

/* Move projectiles */
void move_projectiles(struct projectile projs[], unsigned int num_projs) {
	//TODO: decouple projectile movement from both drawing
	//and from the screen refresh rate
}

/* Move enemies */
void move_enemies(struct enemy enemies[], unsigned int num_enemies) {
	//TODO: implement
}

int main() {
	/* Populated by getch() */
	int input = 'a';

	/* Used to keep track of timings */
	clock_t prev_clock = 0;

	/* The ship, Space Force One */
	struct ship sfo;

	/* The projectiles */
	struct projectile my_projectiles[NUM_PROJECTILES];
	int proj_index = 0;

	/* The enemies */
	struct enemy my_enemies[NUM_ENEMIES];
	int enemy_index = 0;

	/* Initialize the ship */
	sfo.length = 3;						//number of characters across
	strcpy(sfo.body, "<0>");	//body is a null terminated string
	strcpy(sfo.front, " v ");	//front is a null terminated string
	sfo.y = LINES - 2;				//y-coordinate of the front of the ship
														//LINES is provided by ncurses
	sfo.x = 0;								//x-coordinate of the left side

	/* itialize the projectiles by setting them all inactive */
	for(int i = 0; i < NUM_PROJECTILES; i++) {
		my_projectiles[i].is_active = 0;
	}

	/* Initialize the enemies by setting them all inactive */
	for(int i = 0; i < NUM_ENEMIES; i++) {
		my_enemies[i].is_active = 0;
	}

	/* ncurses init functions */
	initscr();								//creates virtual window
	keypad(stdscr, TRUE);			//enables arrow keys, etc.
	curs_set(0); 							//hides cursor
	timeout(0);								//sets timeout for getch
	noecho();									//prevents printing of input



	while(1) {
		/* Get clock time, in number of CPU ticks */
		clock_t curr_clock = clock();
		/* Only draw if the time between refreshes has elapsed.
			 CLOCKS_PER_SEC comes from time.h. We defined REFRESH_RATE.
			 prev_clock represents the last time we refreshed. */
		if(curr_clock - prev_clock > CLOCKS_PER_SEC / REFRESH_RATE) {
			/* Update prev_clock to now. */
			prev_clock = curr_clock;
			/* ncurses func - clear the virtual screen */
			clear();
			draw_ship(&sfo);
			draw_projectiles(my_projectiles, NUM_PROJECTILES);
			//draw_enemies(my_enemies, NUM_ENEMIES);
			/* ncurses func - draw the virtual screen to the real screen */
			refresh();
		}

		/* Get character input as an int. This allows
			 ncurses to handle some non-ASCII characters, like
			 the arrow keys. */
		input = getch();
		/* Use < and > as movement. If shift is pressed, we do
			 get < and >. If shift is not pressed, we get , and ..
			 This allows us to "detect" multiple key presses - shift
			 and movement - allowing us to fire and move at the same
			 time. */
		if(input == ',' || input == '<') {
			sfo.x = sfo.x - 1;
		} else if(input == '.' || input == '>') {
			sfo.x = sfo.x + 1;
		}

		/* We can fire and move at the same time using shift, but
			 shift won't allow us to fire while standing still, because
			 ncurses can't detect shift alone (it's not terminal input).
			 Therefore, we also define spacebar as a firing button. */
		if(input == '<' || input == '>' || input == ' ') {
			my_projectiles[proj_index].length = 1;
			my_projectiles[proj_index].body = '|';
			/* Place the projectile at the middle of the ship */
			my_projectiles[proj_index].x = sfo.x + sfo.length / 2;
			/* And one line above it. */
			my_projectiles[proj_index].y = LINES - 3;
			my_projectiles[proj_index].is_active = 1;
			/* Keep track of which projectile in the array we are using. */
			//TODO: reset proj_index.
			proj_index++;
		}

		//We no longer want to use usleep. We're using clock() instead.
		/*if(input != ERR) {
			usleep(100000);
		}*/
	}

	/* ncurses func to tear down the virtual screen */
	endwin();
}
