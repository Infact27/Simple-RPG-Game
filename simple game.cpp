#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct{
	char className[200];
	int damage;
	int maxHealth;
}classes;

typedef struct{
	char monsterName[200];
	int damage;
	int maxHealth;
	int expGained;
	int goldGained;
}monster;

classes playerClass[] = {
	{
		"Warrior",
		5,
		150
	},
	{
		"Rogue",
		10,
		75
	},
	{
		"Archer",
		7,
		100
	}
};

monster monsters[] = {
	{
		"Goblin",
		5,
		20,
		10,
		5
	},
	{
		"Orc",
		3,
		25,
		12,
		7
	},
	{
		"Wizard",
		10,
		15,
		15,
		10
	}
};
FILE *fp;
char name[200];
int classIndex;
int level = 1;
int gold = 0;
int exp = 0;
int health;

void fightScreen(int monsterIndex){
	int input;
	int monsterHealth = monsters[monsterIndex].maxHealth;
	do{
		system("cls");
		printf("%s\n", monsters[monsterIndex].monsterName);
		printf("Health\t:\t%d\n", monsterHealth);
		printf("Damage\t:\t%d\n", monsters[monsterIndex].damage);
		printf("\n");
		printf("%s\n", name);
		printf("Health\t:\t%d\n", health);
		printf("Damage\t:\t%d\n", playerClass[classIndex].damage);
		printf("\n");
		printf("1. Attack\n");
		printf("2. Run\n>> ");
		scanf("%d", &input);
		getchar();
		if(input == 1){
			monsterHealth -= playerClass[classIndex].damage;
			if(monsterHealth <= 0)
			break;
			health -= monsters[monsterIndex].damage;
		}else{
			printf("You Ran away!");
		}
	}while(monsterHealth >= 1 && health >= 1 && input !=2);
	if(monsterHealth <= 0){
		printf("You won!!\n");
		printf("You gained %d exps and %d golds\n", monsters[monsterIndex].expGained, monsters[monsterIndex].goldGained);
		gold += monsters[monsterIndex].goldGained;
		exp += monsters[monsterIndex].expGained;
	}
	if(health<=0){
		printf("Your got injured badly! you need to heal!!");
	}
	return;
}

void opponentScreen(){
	system("cls");
	int input;
	do{
		printf("Choose Your opponent!\n");
		printf("===============\n");
		printf("1. Goblin\n");
		printf("2. Orc\n");
		printf("3. Wizard\n");
		printf("4. Return\n>> ");
		scanf("%d", &input);
		getchar();
	}while(input != 4 && input != 3 && input != 2 && input != 1);
		switch(input){
			case 1:
				fightScreen(0);
				printf("fight done");
				getchar();
				break;
			
			case 2:
				fightScreen(1);
				printf("fight done");
				getchar();
				break;
				
			case 3:
				fightScreen(2);
				printf("fight done");
				getchar();
				break;
			case 4:
				return;
		}
}

void mainMenu(){
	int input;
	do{
		system("cls");
		if(exp >= 100){
			level += 1;
			exp -= 100;
			printf("You Leveled up!!\n");
		}
		printf("%s's Status\n", name);
		printf("===============\n");
		printf("Level %d\n", level);
		printf("Class\t: %s\n", playerClass[classIndex].className);
		printf("Gold\t: %d\n", gold);
		printf("Exp\t: %d/100\n", exp);
		printf("Health\t: %d/%d\n", health, playerClass[classIndex].maxHealth);
		printf("1. Fight\n");
		printf("2. Heal\n");
		printf("3. Save\n");
		printf("4. Exit\n>> ");
		scanf("%d", &input);
		getchar();
		switch(input){
			case 1:
				opponentScreen();
				break;
			case 2:
				if(gold<=20){
					printf("Not enough Gold!!\n");
				}else if(health == playerClass[classIndex].maxHealth){
					printf(" your health is already full!!");
					getchar();
				}else{
					gold -= 20;
					health = playerClass[classIndex].maxHealth;
					printf("you healed!!");
					getchar();
				}
				break;
			case 3:
				fp = fopen("data.txt", "w");
				fprintf(fp, "%s class%d level%d gold%d exp%d health%d", name, classIndex, level, gold, exp, health);
				fclose(fp);
				
				printf("File Saved!!");
				getchar();
				break;
		}
	}while(input != 4);
}

void newGame(){
	char classInput[200];
	
	printf("Input your Character's name : ");
	scanf("%s", name);
	getchar();
	
	do{
		printf("Choose your class [Warrior | Rogue | Archer] ");
		scanf("%s", classInput);
		getchar();
	}while(strcmp(classInput , "Warrior") != 0 && strcmp(classInput , "Archer") != 0 && strcmp(classInput , "Rogue") != 0);
	
	if(strcmp(classInput , "Warrior") == 0){
		classIndex = 0;
	}else if(strcmp(classInput , "Rogue") == 0){
		classIndex = 1;
	}else if(strcmp(classInput , "Archer") == 0){
		classIndex = 2;
	}
	
	health = playerClass[classIndex].maxHealth;
	mainMenu();
}

void continueGame(){
	
//	Loading file
	char textFile[300];
	fp = fopen("data.txt", "r");
	fgets(textFile, sizeof(textFile), fp);
    fclose(fp);
    
    // Parse the content of textFile into variables
    sscanf(textFile, "%s class%d level%d gold%d exp%d health%d",
           name, &classIndex, &level, &gold, &exp, &health);
	
	getchar();
	mainMenu();
}

int main(){
	int input;
	do{
		system("cls");
		printf("1. Start New Game\n2. Continue Game\n3. Exit\n>> ");
		scanf("%d", &input);
		getchar();
	}while(input!=3 && input!=2 && input!=1);
//	printf("out of do while");
		switch(input){
			case 1: 
				newGame();
			break;
			case 2:
				fp = fopen("data.txt", "r");
				if(fp != NULL){
					fclose(fp);
					continueGame();
				}else{
					printf("saved file not found!!");
					getchar();
				}
			break;
		}
	
	return 0;
}
