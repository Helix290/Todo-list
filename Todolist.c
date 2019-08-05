#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100	//記憶するTodoリストの最大数

typedef struct
{
	int priority;	//使用状況&優先度 0:未使用or削除済み 1:使用中、優先度 Normal  2:優先度 High  3:優先度 Very high
	int tmp_num;	//表示する順番を一時的に保存しておく
	char data[256];
}list;

list todolist[SIZE];

int digit(int size);
int discriminant_int_char(char input[256]);
void help();
void display_todolist();
void todolist_add(char input[256]);
void change_priority_or_delete(int num);

int main()
{
	char input[256];
	int input_length, dig, input_int;

	dig = digit(SIZE);
	while (1) {
		display_todolist();
		printf("入力：");
		scanf("%s", input);
		input_length = discriminant_int_char(input);
		if (input_length == -1) {	//Todoリストへ追加の処理
			todolist_add(input);
		}
		else if(input_length == -2){	//"help"表示
			help();
		}
		else if((input_length > 0) && (input_length < dig)){	//優先度変更or削除処理
			input_int = atoi(input);
			change_priority_or_delete(input_int);
		}
		else {
			printf("文字または%d桁以下の数字を入力してください\n", dig);
			printf("'help'と入力すると操作方法を表示します\n");
		}
	}
}

int digit(int size)	//記憶するTodoリストの最大数(SIZE)が何桁か計算する
{
	int dig = 0;
	double a = size;

	while (a >= 1) {
		a /= 10;
		dig++;
	}
	return dig;
}

void display_todolist()
{
	int i, j;

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	//Todoリストが見やすいように改行
	j = 1;
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 3) {
			printf("%d)　", j);
			printf("\x1b[31m");	//文字を赤に
			printf("%s\n", todolist[i].data);
			printf("\x1b[39m");	//文字をデフォルト色に
			todolist[i].tmp_num = j;
			j++;
		}
	}
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 2) {
			printf("%d)　", j);
			printf("\x1b[33m");	//文字を黄色に
			printf("%s\n", todolist[i].data);
			printf("\x1b[39m");	//文字をデフォルト色に
			todolist[i].tmp_num = j;
			j++;
		}
	}
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 1) {
			printf("%d)　%s\n", j, todolist[i].data);
			todolist[i].tmp_num = j;
			j++;
		}
	}
	printf("\n");
}

int discriminant_int_char(char input[256])	//入力された文字列が、数字か文字か判別する
{
	int i, length, discriminant;

	length = strlen(input);
	discriminant = 0;
	for (i = 0; i < length; i++) {
		if (strcmp(input, "help") == 0) {
			discriminant = -2;	//"help"という文字ならば"-2"を返す
			break;
		}
		else if ((input[i] >= '0') && (input[i] <= '9')) {

		}
		else {
			discriminant = -1;	//文字が入っているならば"-1"を返す
			break;
		}
	}
	if (discriminant == 0) {
		discriminant = length;	//数字のみなら文字の長さを返す
	}
	return discriminant;
}

void todolist_add(char input[256])
{
	int i;

	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 0) {
			strcpy(todolist[i].data, input);
			printf("優先度(1,2,3)：");
			scanf("%d", &todolist[i].priority);
			break;
		}
	}
}

void change_priority_or_delete(int num)
{
	int i, change_or_delete, yes_or_no;

	for (i = 0; i < SIZE; i++) {
		if (todolist[i].tmp_num == num) {
			printf("文字の変更→'1'or優先度の変更→'2'or削除→'3'を入力:");
			scanf("%d", &change_or_delete);
			if (change_or_delete == 1) {
				printf("'");
				printf("\x1b[33m");	//文字を黄色に
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//文字をデフォルト色に
				printf("' ");
				printf("の文字を変更します\n");	//文字列の変更
				printf("OK→1,NG→2を入力：");
				scanf("%d", &yes_or_no);
				if (yes_or_no == 1) {
					printf("新しい文字を入力：");
					scanf("%s", todolist[i].data);
					printf("変更しました");
				}
				else {
					printf("変更しませんでした");
				}
			}
			else if(change_or_delete == 2){
				printf("'");
				printf("\x1b[33m");	//文字を黄色に
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//文字をデフォルト色に
				printf("' ");
				printf("の優先度を変更します。\n");	//優先度の変更
				printf("OK→1,NG→2を入力：");
				scanf("%d", &yes_or_no);
				if (yes_or_no == 1) {
					printf("新しい優先度(1,2,3)を入力：");
					scanf("%d", &todolist[i].priority);
					printf("変更しました");
				}
				else {
					printf("変更しませんでした");
				}
			}
			else if(change_or_delete == 3){
				printf("'");
				printf("\x1b[33m");	//文字を黄色に
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//文字をデフォルト色に
				printf("' ");
				printf("を削除します。\n");	//削除
				printf("OK→1,NG→2を入力：");
				scanf("%d", &yes_or_no);
				if (yes_or_no == 1) {
					todolist[i].priority = 0;
					printf("削除しました");
				}
				else {
					printf("削除しませんでした");
				}
			}
			else {
				printf("1~3以外の文字が入力されました。リストに戻ります。");
			}
		}
	}
}

void help()
{
	printf("Todoリストへの追加\n\n");
	printf("　文字を入力してください。\n");
	printf("　次に優先度(1, 2, 3)を入力すると追加が完了します。(1:Normal(白で表示), 2:High(黄色で表示), 3:Very high(赤文字、リストの一番上に表示))\n\n");
	
	printf("優先度の変更や文字の変更、削除の処理の仕方\n\n");
	printf("　まず、変更or削除したいリストの番号(半角)を入力してください。\n");
	printf("　次に、文字の変更なら'1', 優先度の変更なら'2', 文字の削除なら'3'を入力します。\n\n");
	printf("　　'1'を入力した場合...新たな優先度を入力します。(1:Normal(白で表示), 2:High(黄色で表示), 3:Very high(赤で表示))\n");
	printf("　　'2'を入力した場合...瞬時に削除します。(その後の操作は必要ありません。)\n\n\n");

	printf("helpと入力するとヘルプを表示します。\n");
}