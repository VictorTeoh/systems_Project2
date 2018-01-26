#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

#define GUESSES    4
#define STRING     10
#define MAX_GUESS  15

#define red        'r'
#define green      'g'
#define yellow     'y'
#define blue       'b'
#define purple     'p'
#define white      'w'

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define PUR   "\x1B[35m"
#define WHT   "\x1B[37m"
#define RST   "\x1B[0m"

#define p1 '1'
#define p2 '2'

void get_player(int turn, char * player);
void make_code(char mastercode[GUESSES]);
void change_code(char mastercode[GUESSES], char codebreaker[GUESSES]);
void guess(char * pin);
int find_col(char guess);
char * add_color(int guess);
void check(char mastercode[GUESSES], char codebreaker[GUESSES], int * red_peg, int * white_peg);
void print(char codebreaker[GUESSES], int red_peg, int white_peg);
