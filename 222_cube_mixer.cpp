/*
	* 2x2x2 큐브 스크램블
	* 작성자 : 이경원 (2025-10-06)
	* 이 코드는 2x2x2 큐브를 섞는 역할을 한다.
	*
	* 알고리즘은 BFS이다.
	* rotate_num을 지정하면 그 수만큼 큐브를 랜덤하게 회전하여 섞는다.
	*
	* moveDefs는 github의 MeepMoop이 만든 py222를 사용함(https://github.com/MeepMoop/py222)
	*
	* 최근 수정 : 2025-10-06
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<queue>
#include <unordered_set>
#include <string>	
#include<time.h>
#include<stdlib.h>
#include<random>

#define rotate_num 5 //큐브를 섞기 위해 회전 함수를 실행할 횟수

using namespace std;
int map [24] = {}; //큐브의 상태

struct fun_data {
	int arr[24] = {};
	fun_data() { memset(arr, 0, sizeof(arr)); }
};

string corres[12] = { "U", "U_", "R", "R_", "F", "F_", "D", "D_", "L", "L_", "B", "B_" };

const int moveDefs[12][24] = {

	{ 2, 0, 3, 1, 20, 21, 6, 7, 4, 5, 10, 11, 12, 13, 14, 15, 8, 9, 18, 19, 16, 17, 22, 23 }, //U
	{ 1, 3, 0, 2, 8, 9, 6, 7, 16, 17, 10, 11, 12, 13, 14, 15, 20, 21, 18, 19, 4, 5, 22, 23 }, //U_

	{ 0, 9, 2, 11, 6, 4, 7, 5, 8, 13, 10, 15, 12, 22, 14, 20, 16, 17, 18, 19, 3, 21, 1, 23 }, //R
	{ 0, 22, 2, 20, 5, 7, 4, 6, 8, 1, 10, 3, 12, 9, 14, 11, 16, 17, 18, 19, 15, 21, 13, 23 }, //R_

	{ 0, 1, 19, 17, 2, 5, 3, 7, 10, 8, 11, 9, 6, 4, 14, 15, 16, 12, 18, 13, 20, 21, 22, 23 }, //F
	{ 0, 1, 4, 6, 13, 5, 12, 7, 9, 11, 8, 10, 17, 19, 14, 15, 16, 3, 18, 2, 20, 21, 22, 23 }, //F_

	{ 0, 1, 2, 3, 4, 5, 10, 11, 8, 9, 18, 19, 14, 12, 15, 13, 16, 17, 22, 23, 20, 21, 6, 7 }, //D
	{ 0, 1, 2, 3, 4, 5, 22, 23, 8, 9, 6, 7, 13, 15, 12, 14, 16, 17, 10, 11, 20, 21, 18, 19 }, //D_

	{ 23, 1, 21, 3, 4, 5, 6, 7, 0, 9, 2, 11, 8, 13, 10, 15, 18, 16, 19, 17, 20, 14, 22, 12 }, //L
	{ 8, 1, 10, 3, 4, 5, 6, 7, 12, 9, 14, 11, 23, 13, 21, 15, 17, 19, 16, 18, 20, 2, 22, 0 }, //L_

	{ 5, 7, 2, 3, 4, 15, 6, 14, 8, 9, 10, 11, 12, 13, 16, 18, 1, 17, 0, 19, 22, 20, 23, 21 }, //B
	{ 18, 16, 2, 3, 4, 0, 6, 1, 8, 9, 10, 11, 12, 13, 7, 5, 14, 17, 15, 19, 21, 23, 20, 22 }, //B_

};

void do_perm(const int perm[24]) { //move Defs에 따른 회전 진행
	fun_data tmp;
	for (int i = 0; i < 24; i++) {
		tmp.arr[i] = map[perm[i]];
	}
	for (int i = 0; i < 24; i++) {
		map[i] = tmp.arr[i];
	}
}

int main() {
	int t = 1;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			map[i * 4 + j] = t;
		}
		t++;
	}

	srand(time(NULL)); //랜덤

	for (int i = 0; i < rotate_num; i++) {
		int num = rand() % 12;
		do_perm(moveDefs[num]);
		cout << corres[num] << " ";

	}

	printf("\n");
	for (int i = 0; i < 24; i++) { //출력
		printf("%d ", map[i]);
	}
	return 0;
}
