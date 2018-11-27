#include <stdio.h>
#include <stdlib.h>

char * prompt(char * mesg){
	char * name;
	int size = 16;
	name = malloc(sizeof(char) * size);
	if(name == NULL){
		return NULL;
	}
	printf("%s", mesg);
	int pos = 0;
	char c;
	do{
		scanf("%c", &c);
		if(c != '\n'){
			name[pos] = c;
			pos++;
			if(pos > size - 1){
				char * tmp = malloc(sizeof(char) * (size + 16));
				if(tmp == NULL){
					free(name);
					return NULL;
				}
				for(int i = 0; i < size; i++){
					tmp[i] = name[i];
				}
				free(name);
				name = tmp;
				size += 16;
			}
		}
	}while(c != '\n');
	name[pos] = '\0';
	return name;
};

int main(){
	char * name = prompt("Who are you?\n");
	if(name == NULL){
		printf("Memory allocation failed.\n");
	}else{
		printf("Hello %s!\n", name);
		free(name);
	}
};