#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100	//�L������Todo���X�g�̍ő吔
#define STR 256		//���͂ł���ő啶����

typedef struct
{
	int priority;	//�g�p��&�D��x 0:���g�por�폜�ς� 1:�g�p���A�D��x Normal  2:�D��x High  3:�D��x Very high
	int tmp_num;	//�\�����鏇�Ԃ��ꎞ�I�ɕۑ����Ă���
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
	initialization();	//�N�����A�t�@�C����荞��

	while (1) {
		display_todolist();
		printf("(help�Ɠ��͂���ƃw���v��\�����܂�)\n");
		printf("���́F");
		scanf("%s", input);
		input_length = discriminant_int_char(input);
		if (input_length == -1) {	//Todo���X�g�֒ǉ��̏���
			todolist_add(input);
		}
		else if(input_length == -2){	//"help"�\��
			help();
		}
		else if((input_length > 0) && (input_length < dig)){	//�D��x�ύXor�폜����
			input_int = atoi(input);
			change_priority_or_delete(input_int);
		}
		else {
			printf("�����܂���%d���ȉ��̐�������͂��Ă�������\n", dig);
			printf("'help'�Ɠ��͂���Ƒ�����@��\�����܂�\n");
		}
	}
}

int digit(int size)	//�L������Todo���X�g�̍ő吔(SIZE)���������v�Z����
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
	if (todolist_txt == 0) {	//�������Ȃ�
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

char* remove_line_feed(char* data_tmp)	//���s������
{
	int i;
	char* ptr;	
	
	ptr = data_tmp;
	for(i = 0; i < STR; i++){
		if (*ptr == '\n') {
			*ptr = '\0';
			break;
		}
		ptr++;	//����A�h���X���ړ������Ă���
	}
	return data_tmp;
}

void display_todolist()	//�t�@�C�������o�����܂�
{
	int i, j;

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	//Todo���X�g�����₷���悤�ɉ��s
	todolist_txt = fopen("Todolist.txt", "wt");	//�t�@�C���̒��g��������
	fclose(todolist_txt);

	todolist_txt = fopen("Todolist.txt", "at");
	if (todolist_txt == 0) {
		printf("�t�@�C���I�[�v���G���[\n");
		exit(EXIT_FAILURE);
	}
	j = 1;
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 3) {
			printf("%d)�@", j);
			printf("\x1b[31m");	//������Ԃ�
			printf("%s\n", todolist[i].data);
			printf("\x1b[39m");	//�������f�t�H���g�F��
			todolist[i].tmp_num = j;
			file_write(i);
			j++;
		}
	}
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 2) {
			printf("%d)�@", j);
			printf("\x1b[33m");	//���������F��
			printf("%s\n", todolist[i].data);
			printf("\x1b[39m");	//�������f�t�H���g�F��
			todolist[i].tmp_num = j;
			file_write(i);
			j++;
		}
	}
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 1) {
			printf("%d)�@%s\n", j, todolist[i].data);
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
	/*�@�D��x(����)
		todo���X�g�̏���(����)
		todo���X�g�̓��e(������)
			�̏��ŏ�������
	*/
	fprintf(todolist_txt, "%d\n%d\n", todolist[i].priority, todolist[i].tmp_num);
	fputs(todolist[i].data, todolist_txt);
	fputs("\n", todolist_txt);
}

int discriminant_int_char(char input[STR])	//���͂��ꂽ�����񂪁A���������������ʂ���
{
	int i, length, discriminant;

	length = strlen(input);
	discriminant = 0;
	for (i = 0; i < length; i++) {
		if (strcmp(input, "help") == 0) {
			discriminant = -2;	//"help"�Ƃ��������Ȃ��"-2"��Ԃ�
			break;
		}
		else if ((input[i] >= '0') && (input[i] <= '9')) {

		}
		else {
			discriminant = -1;	//�����������Ă���Ȃ��"-1"��Ԃ�
			break;
		}
	}
	if (discriminant == 0) {
		discriminant = length;	//�����݂̂Ȃ當���̒�����Ԃ�
	}
	return discriminant;
}

void todolist_add(char input[STR])
{
	int i;

	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 0) {
			strcpy(todolist[i].data, input);
			printf("�D��x(1,2,3)�F");
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
			printf("�����̕ύX��'1'or�D��x�̕ύX��'2'or�폜��'3'�����:");
			scanf("%d", &change_or_delete);
			if (change_or_delete == 1) {
				printf("'");
				printf("\x1b[33m");	//���������F��
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//�������f�t�H���g�F��
				printf("' ");
				printf("�̕�����ύX���܂�\n");	//������̕ύX
				printf("OK��1,NG��2����́F");
				scanf("%d", &yes_or_no);
				if (yes_or_no == 1) {
					printf("���݂̕����F%s\n", todolist[i].data);
					printf("�V������������́F");
					scanf("%s", todolist[i].data);
					printf("�ύX���܂���\n");
				}
				else {
					printf("�ύX���܂���ł���\n");
				}
			}
			else if(change_or_delete == 2){
				printf("'");
				printf("\x1b[33m");	//���������F��
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//�������f�t�H���g�F��
				printf("' ");
				printf("�̗D��x��ύX���܂��B\n");	//�D��x�̕ύX
				scanf("%d", &yes_or_no);
					printf("���݂̗D��x�F%d\n", todolist[i].priority);
					printf("�V�����D��x(1,2,3)����́F");
					scanf("%d", &todolist[i].priority);
					printf("�ύX���܂���\n");
			}
			else if(change_or_delete == 3){
				printf("'");
				printf("\x1b[33m");	//���������F��
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//�������f�t�H���g�F��
				printf("' ");
				printf("���폜���܂��B\n");	//�폜
				printf("OK��1,NG��2����́F");
				scanf("%d", &yes_or_no);
				if (yes_or_no == 1) {
					todolist[i].priority = 0;
					printf("�폜���܂���\n");
				}
				else {
					printf("�폜���܂���ł���\n");
				}
			}
			else {
				printf("1~3�ȊO�̕��������͂���܂����B���X�g�ɖ߂�܂��B\n");
			}
		}
	}
}

void help()
{
	int x;

	while (1) {
		printf("\nTodo���X�g�̐V�K�ǉ���'1' �����̕ύX��'2' �D��x�̕ύX��'3' �폜�̎d����'4'  help�����ꍇ��'5'����́F");
		scanf("%d", &x);
		if (x == 1) {
			printf("\nTodo���X�g�ւ̒ǉ�\n\n");
			printf("�@��������͂���Ə������J�n���܂��B\n");
			printf("�@���ɗD��x(1, 2, 3)����͂���ƒǉ����������܂��B");
			help_color_info();
			printf("\n�@�ǉ������ł�\n\n\n");
		}
		else if (x == 2) {
			printf("\n�����̕ύX\n\n");
			printf("�@�܂��A�ύX���������X�g�̔ԍ�(���p)����͂��Ă��������B\n");
			printf("�@���ɁA�ԍ� '1' ����͂��܂��B\n\n\n");
			printf("�@�ύX�����ł�\n\n\n");
		}
		else if (x == 3) {
			printf("\n�D��x�̕ύX\n\n");
			printf("�@�܂��A�ύX���������X�g�̔ԍ�(���p)����͂��Ă��������B\n");
			printf("�@���ɁA�ԍ� '2' ����͂��܂��B\n\n");
			printf("�@�V���ȗD��x����͂��܂��B");
			help_color_info();
			printf("\n�@�ύX�����ł�\n\n\n");
		}
		else if (x == 4) {
			printf("\n�폜�̏����̎d��\n\n");
			printf("�@�܂��A�폜���������X�g�̔ԍ�(���p)����͂��Ă��������B\n");
			printf("�@���ɁA�ԍ� '3' ����͂��܂��B\n\n");
			printf("�@yes '1'����͂���Əu���ɍ폜���܂��B\n\n\n");
		}
		else if (x == 5) {
			printf("\n�w���v����܂�\n");
			break;
		}
		else {
			printf("\n�\������Ă���ԍ�����͂��Ă�������\n\n");
		}
	}
}

void help_color_info()
{
	printf("(1:Normal, 2:");
	printf("\x1b[33m");	//���������F��
	printf("High");
	printf("\x1b[39m");	//�������f�t�H���g�F��
	printf(", 3:");
	printf("\x1b[31m");	//������ԐF��
	printf("Very high");
	printf("\x1b[39m");	//�������f�t�H���g�F��
	printf("�@�D��x�̍������ɏォ��\�����܂��B)\n");
}