#include <stdio.h>

void generate_map(char (* m)[8][10]){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 10; j++){
			if(i == 0 || i == 7 || j == 0 || j == 9){
				(*m)[i][j] = '#';
			}else{
				(*m)[i][j] = '.';
			}
		}
	}
	return;
};

void print_map(char (* m)[8][10], int posR, int posC){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 10; j++){
			if(i == posR && j == posC){
				printf("@");
			}else{
				printf("%c", (*m)[i][j]);
			}
		}
		printf("\n");
	}
	return;
};

void read_command(char * cmd){
	char c;
	while(scanf("%c", &c)){
		if(c == '\n'){
			if(cmd[0] == '\0'){
				cmd[0] = 'x';
				break;
			}else if(cmd[0] == 't' && cmd[1] == '\0'){
				cmd[0] = 'x';
				break;
			}else{
				break;
			}
		}else if(cmd[0] == '\0'){
			if(c == 'w' || c == 'a' || c == 's' || c == 'd' || c == 't' || c == 'q'){
				cmd[0] = c;
				continue;
			}else{
				cmd[0] = 'x';
				continue;
			}
		}else if(cmd[0] == 't' && cmd[1] == '\0'){
			if(c == 'p'){
				cmd[1] = c;
				continue;
			}else{
				cmd[0] = 'x';
				continue;
			}
		}else{
			cmd[0] = 'x';
			continue;
		}
	}
	return;
};

void read_tp_position(int * x, char limitL, char limitR){
	char c;
	while(scanf("%c", &c)){
		if(c == '\n'){
			break;
		}else if(*x == -1){
			if(c >= limitL && c <= limitR){
				*x = (int)c - 48;
				continue;
			}else{
				*x = -2;
				continue;
			}
		}else{
			*x = -2;
			continue;
		}
	}
	return;
};

int main(){
	char map[8][10];
	char command[2];
	int positionR = 1;
	int positionC = 1;
	generate_map(&map);
	print_map(&map, positionR, positionC);
	while(1){
		do{
			printf("Command: ");
			command[0] = command[1] = '\0';
			read_command(command);
			if(command[0] == 'x'){
				printf("I don't know what that means.\n");
			}
		}while(command[0] == 'x');
		if(command[0] == 'q'){
			return 0;
		}else if(command[0] == 'w'){
			if(map[positionR - 1][positionC] == '#'){
				printf("Ouch! Mind the walls!\n");
				continue;
			}else{
				positionR--;
				print_map(&map, positionR, positionC);
				continue;
			}
		}else if(command[0] == 'a'){
			if(map[positionR][positionC - 1] == '#'){
				printf("Ouch! Mind the walls!\n");
				continue;
			}else{
				positionC--;
				print_map(&map, positionR, positionC);
				continue;
			}
		}else if(command[0] == 's'){
			if(map[positionR + 1][positionC] == '#'){
				printf("Ouch! Mind the walls!\n");
				continue;
			}else{
				positionR++;
				print_map(&map, positionR, positionC);
				continue;
			}
		}else if(command[0] == 'd'){
			if(map[positionR][positionC + 1] == '#'){
				printf("Ouch! Mind the walls!\n");
				continue;
			}else{
				positionC++;
				print_map(&map, positionR, positionC);
				continue;
			}
		}else if(command[0] == 't'){
			int tpR = -1;
			int tpC = -1;
			printf("Which row to go?> ");
			read_tp_position(&tpR, '0', '7');
			if(tpR < 0){
				printf("Transporting to the void would be unwise.\n");
				continue;
			}
			printf("Which column to go?> ");
			read_tp_position(&tpC, '0', '9');
			if(tpC < 0){
				printf("Transporting to the void would be unwise.\n");
				continue;
			}
			if(tpR == 0 || tpR == 7 || tpC == 0 || tpC == 9){
				printf("Ouch! Mind the walls!\n");
				continue;
			}else{
				positionR = tpR;
				positionC = tpC;
				print_map(&map, positionR, positionC);
				continue;
			}
		}
	}
};