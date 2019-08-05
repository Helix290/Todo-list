#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100	//�L������Todo���X�g�̍ő吔

typedef struct
{
	int priority;	//�g�p��&�D��x 0:���g�por�폜�ς� 1:�g�p���A�D��x Normal  2:�D��x High  3:�D��x Very high
	int tmp_num;	//�\�����鏇�Ԃ��ꎞ�I�ɕۑ����Ă���
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

void display_todolist()
{
	int i, j;

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	//Todo���X�g�����₷���悤�ɉ��s
	j = 1;
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 3) {
			printf("%d)�@", j);
			printf("\x1b[31m");	//������Ԃ�
			printf("%s\n", todolist[i].data);
			printf("\x1b[39m");	//�������f�t�H���g�F��
			todolist[i].tmp_num = j;
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
			j++;
		}
	}
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		if (todolist[i].priority == 1) {
			printf("%d)�@%s\n", j, todolist[i].data);
			todolist[i].tmp_num = j;
			j++;
		}
	}
	printf("\n");
}

int discriminant_int_char(char input[256])	//���͂��ꂽ�����񂪁A���������������ʂ���
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

void todolist_add(char input[256])
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
					printf("�V������������́F");
					scanf("%s", todolist[i].data);
					printf("�ύX���܂���");
				}
				else {
					printf("�ύX���܂���ł���");
				}
			}
			else if(change_or_delete == 2){
				printf("'");
				printf("\x1b[33m");	//���������F��
				printf("%s", todolist[i].data);
				printf("\x1b[39m");	//�������f�t�H���g�F��
				printf("' ");
				printf("�̗D��x��ύX���܂��B\n");	//�D��x�̕ύX
				printf("OK��1,NG��2����́F");
				scanf("%d", &yes_or_no);
				if (yes_or_no == 1) {
					printf("�V�����D��x(1,2,3)����́F");
					scanf("%d", &todolist[i].priority);
					printf("�ύX���܂���");
				}
				else {
					printf("�ύX���܂���ł���");
				}
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
					printf("�폜���܂���");
				}
				else {
					printf("�폜���܂���ł���");
				}
			}
			else {
				printf("1~3�ȊO�̕��������͂���܂����B���X�g�ɖ߂�܂��B");
			}
		}
	}
}

void help()
{
	printf("Todo���X�g�ւ̒ǉ�\n\n");
	printf("�@��������͂��Ă��������B\n");
	printf("�@���ɗD��x(1, 2, 3)����͂���ƒǉ����������܂��B(1:Normal(���ŕ\��), 2:High(���F�ŕ\��), 3:Very high(�ԕ����A���X�g�̈�ԏ�ɕ\��))\n\n");
	
	printf("�D��x�̕ύX�╶���̕ύX�A�폜�̏����̎d��\n\n");
	printf("�@�܂��A�ύXor�폜���������X�g�̔ԍ�(���p)����͂��Ă��������B\n");
	printf("�@���ɁA�����̕ύX�Ȃ�'1', �D��x�̕ύX�Ȃ�'2', �����̍폜�Ȃ�'3'����͂��܂��B\n\n");
	printf("�@�@'1'����͂����ꍇ...�V���ȗD��x����͂��܂��B(1:Normal(���ŕ\��), 2:High(���F�ŕ\��), 3:Very high(�Ԃŕ\��))\n");
	printf("�@�@'2'����͂����ꍇ...�u���ɍ폜���܂��B(���̌�̑���͕K�v����܂���B)\n\n\n");

	printf("help�Ɠ��͂���ƃw���v��\�����܂��B\n");
}