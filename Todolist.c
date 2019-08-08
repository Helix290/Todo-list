#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100	//記憶するTodoリストの最大数
#define STR 256		//入力できる最大文字数

typedef struct
{
	int priority;	//使用状況&優先度 0:未使用or削除済み 1:使用中、優先度 Normal  2:優先度 High  3:優先度 Very high
	int tmp_num;	//表示する順番を一時的に保存しておく
	char data[STR];
}list;

list todolist[SIZE];
FILE *todolist_txt;

int digit(int size);
int discriminant_int_char(char input[STR]);
void help();
void initialization();
void display_todolist();
void file_write(int i);
void todolist_add(char input[STR]);
void change_priority_or_delete(int num);
char* remove_line_feed(char* data_tmp);
void help_color_info();

int main()
{
	char input[STR];
	int input_length, dig, input_int;
	
	dig = digit(SIZE);
	initialization();	//起動時、ファイル取り込み

	while (1) {
		display_todolist();
		printf("(helpと入力するとヘルプを表示します)\n");
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

void initialization()
{
	int i, check;
	char tmp[STR];

	todolist_txt = fopen("Todolist.txt", "rt");
	if (todolist_txt == 0) {	//何もしない
	}
	else {
		for (i = 0; ; i++) {
			check = fgets(tmp, STR, todolist_txt);
			if (check == NULL) {
				fclose(todolist_txt);
				break;
			}
			todolist[i].priority = atoi(tmp);
			fgets(tmp, STR, todolist_txt);
			todolist[i].tmp_num = atoi(tmp);
			fgets(tmp, STR, todolist_txt);
			strcpy(todolist[i].data, remove_line_feed(tmp));
		}
	}
	
}

char* remove_line_feed(char* data_tmp)	//改行を消す
{
	int i;
	char* ptr;	
	
	ptr = data_tmp;
	for(i = 0; i < STR; i++){
		if (*ptr == '\n') {
			*ptr = '\0';
			break;
		}
		ptr++;	//一つずつアドレスを移動させていく
	}
	return data_tmp;
}

void display_todolist()	//ファイル書き出しも含む
{
	int i, j;

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	//Todoリストが見やすいように改行
	todolist_txt = fopen("Todolist.txt", "wt");	//ファイルの中身を初期化
	fclose(todolist_txt);

	todolist_txt = fopen("Todolist.txt", "at");
	if (todolist_txt == 0) {
		printf("ファイルオープンエラー\n");
		exit(EXIT_FAILURE);
	}
	j = 1;
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 3) {
			printf("%d)　", j);
			printf("\x1b[31m");	//文字を赤に
			printf("%s\n", todolist[i].data);
			printf("\x1b[39m");	//文字をデフォルト色に
			todolist[i].tmp_num = j;
			file_write(i);
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
			file_write(i);
			j++;
		}
	}
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 1) {
			printf("%d)　%s\n", j, todolist[i].data);
			todolist[i].tmp_num = j;
			file_write(i);
			j++;
		}
	}
	printf("\n");
	fclose(todolist_txt);
}

void file_write(int i)
{
	/*　優先度(数字)
		todoリストの順番(数字)
		todoリストの内容(文字列)
			の順で書き込む
	*/
	fprintf(todolist_txt, "%d\n%d\n", todolist[i].priority, todolist[i].tmp_num);
	fputs(todolist[i].data, todolist_txt);
	fputs("\n", todolist_txt);
}

int discriminant_int_char(char input[STR])	//入力された文字列が、数字か文字か判別する
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

void todolist_add(char input[STR])
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
					printf("現在の文字：%s\n", todolist[i].data);
					printf("新しい文字を入力：");
					scanf("%s", todolist[i].data);
					printf("変更しました\n");
				}
				else {
					printf("変更しませんでした\n");
				}
			}
			else if(change_or_delete == 2){
				printf("'");
				printf("\x1b[33m");	//文字を黄色に
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//文字をデフォルト色に
				printf("' ");
				printf("の優先度を変更します。\n");	//優先度の変更
				scanf("%d", &yes_or_no);
					printf("現在の優先度：%d\n", todolist[i].priority);
					printf("新しい優先度(1,2,3)を入力：");
					scanf("%d", &todolist[i].priority);
					printf("変更しました\n");
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
					printf("削除しました\n");
				}
				else {
					printf("削除しませんでした\n");
				}
			}
			else {
				printf("1~3以外の文字が入力されました。リストに戻ります。\n");
			}
		}
	}
}

void help()
{
	int x;

	while (1) {
		printf("\nTodoリストの新規追加→'1' 文字の変更→'2' 優先度の変更→'3' 削除の仕方→'4'  helpを閉じる場合は'5'を入力：");
		scanf("%d", &x);
		if (x == 1) {
			printf("\nTodoリストへの追加\n\n");
			printf("　文字を入力すると処理が開始します。\n");
			printf("　次に優先度(1, 2, 3)を入力すると追加が完了します。");
			help_color_info();
			printf("\n　追加完了です\n\n\n");
		}
		else if (x == 2) {
			printf("\n文字の変更\n\n");
			printf("　まず、変更したいリストの番号(半角)を入力してください。\n");
			printf("　次に、番号 '1' を入力します。\n\n\n");
			printf("　変更完了です\n\n\n");
		}
		else if (x == 3) {
			printf("\n優先度の変更\n\n");
			printf("　まず、変更したいリストの番号(半角)を入力してください。\n");
			printf("　次に、番号 '2' を入力します。\n\n");
			printf("　新たな優先度を入力します。");
			help_color_info();
			printf("\n　変更完了です\n\n\n");
		}
		else if (x == 4) {
			printf("\n削除の処理の仕方\n\n");
			printf("　まず、削除したいリストの番号(半角)を入力してください。\n");
			printf("　次に、番号 '3' を入力します。\n\n");
			printf("　yes '1'を入力すると瞬時に削除します。\n\n\n");
		}
		else if (x == 5) {
			printf("\nヘルプを閉じます\n");
			break;
		}
		else {
			printf("\n表示されている番号を入力してください\n\n");
		}
	}
}

void help_color_info()
{
	printf("(1:Normal, 2:");
	printf("\x1b[33m");	//文字を黄色に
	printf("High");
	printf("\x1b[39m");	//文字をデフォルト色に
	printf(", 3:");
	printf("\x1b[31m");	//文字を赤色に
	printf("Very high");
	printf("\x1b[39m");	//文字をデフォルト色に
	printf("　優先度の高い順に上から表示します。)\n");
}