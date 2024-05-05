#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int table[4][4] = { 0 };
int temptable[4][4] = { 0 };
int blank[16] = { 0 };
int score = 0;

typedef struct data {
	char user[20];
	int score;
}data;

int compare(const void* a, const void* b) {
	data* dataA = (data*)a;
	data* dataB = (data*)b;
	return (dataB->score - dataA->score);
}

int comparetable() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] != temptable[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

int random24() {				// 랜덤 숫자 생성 함수 (2, 4)
	int random = 0;
	random = rand() % 8;
	
	if (random != 0) {
		return 2;
	}
	else {
		return 4;
	}
}

int randomwhere() {
	int random = rand() % 16;

	for (int i = 0; i < 16; i++) {
		if (blank[random] != 0) {
			return random;
		}
		random = (random + 1) % 16;
	}
	
	return -1;
}

void wControl() {
	int merge[4][4] = { 0 };

	// 위로 올림
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] == 0) continue;
			else {
				int k = i;
				while (k > 0 && table[k - 1][j] == 0) {
					table[k - 1][j] = table[k][j];
					table[k][j] = 0;
					k--;
				}
			}
		}
	}

	// 합침
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] != 0 && table[i - 1][j] == table[i][j] && merge[i - 1][j] == 0 && merge[i][j] == 0) {
				table[i - 1][j] *= 2;
				score += table[i][j];
				table[i][j] = 0;
				merge[i - 1][j] = 1;
			}
		}
	}

	// 다시 위로 올림
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] == 0) continue;
			else {
				int k = i;
				while (k > 0 && table[k - 1][j] == 0) {
					table[k - 1][j] = table[k][j];
					table[k][j] = 0;
					k--;
				}
			}
		}
	}
}

void aControl() {
	int merge[4][4] = { 0 };

	// 왼쪽으로 밀음
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			if (table[i][j] == 0) continue;
			else {
				int k = j;
				while (k > 0 && table[i][k - 1] == 0) {
					table[i][k - 1] = table[i][k];
					table[i][k] = 0;
					k--;
				}
			}
		}
	}

	// 합침
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			if (table[i][j] != 0 && table[i][j - 1] == table[i][j] && merge[i][j - 1] == 0 && merge[i][j] == 0) {
				table[i][j - 1] *= 2;
				score += table[i][j];
				table[i][j] = 0;
				merge[i][j - 1] = 1;
			}
		}
	}

	// 다시 왼쪽으로 밀음
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			if (table[i][j] == 0) continue;
			else {
				int k = j;
				while (k > 0 && table[i][k - 1] == 0) {
					table[i][k - 1] = table[i][k];
					table[i][k] = 0;
					k--;
				}
			}
		}
	}
}

void sControl() {
	int merge[4][4] = { 0 };

	// 아래로 내림
	for (int i = 2; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] == 0) continue;
			else {
				int k = i;
				while (k < 3 && table[k + 1][j] == 0) {
					table[k + 1][j] = table[k][j];
					table[k][j] = 0;
					k++;
				}
			}
		}
	}

	// 합침
	for (int i = 2; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] != 0 && table[i + 1][j] == table[i][j] && merge[i + 1][j] == 0 && merge[i][j] == 0) {
				table[i + 1][j] *= 2;
				score += table[i][j];
				table[i][j] = 0;
				merge[i + 1][j] = 1;
			}
		}
	}

	// 다시 아래로 내림
	for (int i = 2; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] == 0) continue;
			else {
				int k = i;
				while (k < 3 && table[k + 1][j] == 0) {
					table[k + 1][j] = table[k][j];
					table[k][j] = 0;
					k++;
				}
			}
		}
	}
}

void dControl() {
	int merge[4][4] = { 0 };

	// 오른쪽으로 밀음
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (table[i][j] == 0) continue;
			else {
				int k = j;
				while (k < 3 && table[i][k + 1] == 0) {
					table[i][k + 1] = table[i][k];
					table[i][k] = 0;
					k++;
				}
			}
		}
	}

	// 합침
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (table[i][j] != 0 && table[i][j + 1] == table[i][j] && merge[i][j + 1] == 0 && merge[i][j] == 0) {
				table[i][j + 1] *= 2;
				score += table[i][j];
				table[i][j] = 0;
				merge[i][j + 1] = 1;
			}
		}
	}

	// 다시 오른쪽으로 밀음
	for (int i = 0; i < 4; i++) {
		for (int j = 2; j >= 0; j--) {
			if (table[i][j] == 0) continue;
			else {
				int k = j;
				while (k < 3 && table[i][k + 1] == 0) {
					table[i][k + 1] = table[i][k];
					table[i][k] = 0;
					k++;
				}
			}
		}
	}
}

int  endcheck() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (table[i][j] == 0) {
				return 0;
			}
			if (j < 3 && table[i][j] == table[i][j + 1]) {
				return 0;
			}
			if (i < 3 && table[i][j] == table[i + 1][j]) {
				return 0;
			}
		}
	}

	return 1;
}

void printrank() {
	char name[20];
	data scores[100];
	int count = 0;

	printf("\nEnter your name: ");
	scanf_s("%19s", name, sizeof(name));

	FILE* fp = fopen("scoreboard.txt", "r+");
	while (fread(&scores[count], sizeof(data), 1, fp) == 1) {
		count++;
		if (count >= 100) break;
	}

	strcpy(scores[count].user, name);
	scores[count].score = score;
	count++;

	qsort(scores, count, sizeof(data), compare);

	freopen("scoreboard.txt", "w", fp);

	printf("\n\n--------------------------------------------------\n\n");
	printf("_________ _______  _______    __    _______\n");
	printf("\\__   __/(  ___  )(  ____ )  /  \\  (  __   )\n");
	printf("   ) (   | (   ) || (    )|  \\/) ) | (  )  |\n");
	printf("   | |   | |   | || (____)|    | | | | /   |\n");
	printf("   | |   | |   | ||  _____)    | | | (/ /) |\n");
	printf("   | |   | |   | || (          | | |   / | |\n");
	printf("   | |   | (___) || )        __) (_|  (__) |\n");
	printf("   )_(   (_______)|/         \\____/(_______)\n");
	printf("\n\n                name           |    highscore\n\n");

	for (int i = 0; i < count && i < 10; i++) {
		printf("%30s | %12d\n", scores[i].user, scores[i].score);
		fwrite(&scores[i], sizeof(data), 1, fp);
	}

	printf("\n\n                                See you next time!\n");
	printf("--------------------------------------------------\n\n");

	fclose(fp);
}

int main() {
	srand(time(NULL));

	printf(" _____  _____    ___  _____\n");
	printf("/ __  )|  _  |  /   ||  _  |\n");
	printf("`' / / | |/' | / /| | \\ V /\n");
	printf("  / /  |  /| |/ /_| | / _ \\\n");
	printf("./ /___\\ |_/ /\\___  || |_| |\n");
	printf("\\_____/ \\___/     |_/\\_____/\n\n\n");

	while (1) {

		for (int i = 0; i < 4; i++) {		// table에 빈 공간 있으면 blank 표에 값 1 저장
			for (int j = 0; j < 4; j++) {
				if (table[i][j] == 0) {
					blank[4 * i + j] = 1;
				}
				else {
					blank[4 * i + j] = 0;
				}
			}
		}

		int temp = randomwhere();		// 빈 칸 위치 랜덤으로 호출
		table[temp / 4][temp % 4] = random24();		// 랜덤으로 호출한 빈 칸에 2 또는 4 입력
		
		printf("\n-----------------------\n");
		printf("score: %d\n\n", score);

		for (int i = 0; i < 4; i++) {		// table 출력
			for (int j = 0; j < 4; j++) {
				if (table[i][j] == 0) {
					printf("%4s ", "-");
				}
				else {
					printf("%4d ", table[i][j]);
				}
			}
			printf("\n");
		}

		for (int i = 0; i < 4; i++) {		// temptable에 값 저장
			for (int j = 0; j < 4; j++) {
				temptable[i][j] = table[i][j];
			}
		}

		char control = 0;							// wasd 중 조작 선택
		printf("\nPress (w/a/s/d) to move: ");

		while (1) {
			scanf(" %c", &control);
			if (control == 'w' || control == 'a' || control == 's' || control == 'd') {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						temptable[i][j] = table[i][j];
					}

				}if (control == 'w') {
					wControl();
					int end = endcheck();
					if (end == 1) {
						printf("Game Over\n");
						printrank();
						return 0;
					}
				}
				else if (control == 'a') {
					aControl();
					int end = endcheck();
					if (end == 1) {
						printf("Game Over\n");
						printrank();
						return 0;
					}
				}
				else if (control == 's') {
					sControl();
					int end = endcheck();
					if (end == 1) {
						printf("Game Over\n");
						printrank();
						return 0;
					}
				}
				else if (control == 'd') {
					dControl();
					int end = endcheck();
					if (end == 1) {
						printf("\n\nGame Over\n");
						printrank();
						return 0;
					}
				}

				int check = comparetable();

				if (check == 1) {
					printf("Cannot move in %c direction. Press right button (w/a/s/d): ", control);
					continue;
				}
				else {
					break;
				}
			}
			else {
				printf("Press right button (w/a/s/d): ");
			}
		}
	}
}
