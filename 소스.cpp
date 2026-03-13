/*
	* 2x2x2 큐브 해법 탐색기
	* 작성자 : 이경원 (2025-10-06)
	* 이 코드는 2x2x2 큐브의 입력을 받아 해결하는 회전 공식을 제공한다.
	* 
	* 알고리즘은 BFS + parentNode 이다. 
	* 각각의 큐브 회전 결과를 CubeState에 저장한다
	* 만약 완성된 큐브가 있다면 부모 노드로 올라가며 회전 공식을 출력한다.
	* 
	* BFS를 선택한 이유 : 최단 회전 수로 완성된 큐브를 구하기 위해서
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

using namespace std;

//nodes를 위한 type 정의
//여기서 CubeState() { memset(cube, 0, sizeof(cube)); parent = -1; move = -1; } 는 굉장히 중요하다. 왜인지 모르나 없으면 작동을 안한다.
struct CubeState {
	int cube[24];
	int parent;
	int move;
	CubeState() { memset(cube, 0, sizeof(cube)); parent = -1; move = -1; }
};

//함수 return을 위한 type 정의
//여기서 fun_data() { memset(arr, 0, sizeof(arr)); } 는 굉장히 중요하다. 왜인지 모르나 없으면 작동을 안한다.
struct fun_data {
	int arr[24] = {};
	fun_data() { memset(arr, 0, sizeof(arr)); }
};

queue <int> qu; //nodes index
vector <CubeState> nodes; //큐브의 상태(cube, parent, move) 저장
int input[24] = {};
string corres[12] = { "U", "U_", "R", "R_", "F", "F_", "D", "D_", "L", "L_", "B", "B_" }; //int -> 문자형 변환
unordered_set <string> visited; //vistied 처리

//회전 함수의 permitation table
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

//permitation table에 따른 큐브 회전 시행
fun_data do_per(const int perm[24], int cube[24]) {
	fun_data tmp;

	for (int i = 0; i < 24; i++) {
		tmp.arr[i] = cube[perm[i]];
	}
	return tmp;
}


//visited에 표현하기 위해 string 형태로 변환
string serialize(int cube [24]) {
	char buf[25];
	for (int i = 0; i < 24; i++) buf[i] = '0' + cube[i];
	buf[24] = '\0';
	return string(buf);
}

// 큐브가 다 맞춰졌는지 확인
int check(CubeState& map) {
	for (int i = 0; i < 6; i++) {
		int k = map.cube[i * 4];
		for (int j = 1; j < 4; j++) {
			if (map.cube[i * 4 + j] != k) {
				return 0;
			}
		}
	}
	return 1;
}

//BFS
void BFS() {
	CubeState start;
	//cnt는 실질적으로 사용되지 않는다
	int cnt = 0;

	for (int i = 0; i < 24; i++) {
		start.cube[i] = input[i];
	}

	nodes.push_back(start);
	qu.push(0);
	visited.insert(serialize(start.cube));

	while (!qu.empty()) {
		cnt++;
		int _cur = qu.front();
		CubeState cur = nodes[_cur];
		qu.pop();
	
		//만약 큐브가 완성되었다면
		if (check(cur)) {
			printf("\n");
			vector <int> path;
			int num = _cur;
			for (;;) {
				if (nodes[num].move == -1) {
					printf("\n%d\n", cnt);
					break;
				}
				else {
					path.push_back(nodes[num].move);
					int k = nodes[num].parent;
					num = k;
					if (num == -1) {
						printf("\n%d\n", cnt);
						break;
					}
				}
			}

			reverse(path.begin(), path.end());

			for (int i = 0; i < path.size(); i++) {
				cout << corres[path[i]] << " ";
			}
			return ;
		}
		fun_data result;
		for (int i = 0; i < 12; i++) {
			result = do_per(moveDefs[i], cur.cube);
			string key = serialize(result.arr);
			if (visited.find(key) == visited.end()) { //만약 기존에 없던 큐브 조합이라면
				CubeState next;
				memcpy(next.cube, result.arr, sizeof(next.cube));
				next.parent = _cur; //신규 큐브의 부모 _cur 지정
				next.move = i; //신규 큐브의 회전 i 지정
				nodes.push_back(next);
				qu.push((int)nodes.size() - 1);
				visited.insert(key);
			}	
		}
	}
	printf("No solution found\n");
}	

//main
int main() {
	printf("Cube solve program\n");
	printf("enter [U -> L -> F -> R -> B -> D]\n");
	for (int i = 0; i < 24; i++) {
		scanf("%d", &input[i]);
	}
	BFS();
	return 0;
}
