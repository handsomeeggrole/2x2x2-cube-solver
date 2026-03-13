# 2x2 Cube Solver
2x2x2 Rubik's Cube solver using BFS in C++

2x2x2 큐브(포켓 큐브)의 현재 상태를 입력하면 최단 해법을 출력하는 C++ 프로그램입니다.

## 알고리즘

- **BFS (너비 우선 탐색)** + 부모 노드 추적
- 최단 회전 수로 해결되는 경로를 보장
- `unordered_set`으로 방문 상태 관리 (중복 탐색 방지)

## 사용법

큐브 각 면의 색상을 숫자로 입력합니다.  
입력 순서: **U → L → F → R → B → D** (각 면 4칸씩, 총 24개)
```
$ ./cube_solver
Cube solve program
enter [U -> L -> F -> R -> B -> D]
1 1 1 1 2 2 2 2 ...
```

출력 예시:
```
R U R_ U_ F R_
```

## 회전 기호

| 기호 | 의미 |
|------|------|
| U / U_ | 윗면 시계/반시계 |
| R / R_ | 오른면 시계/반시계 |
| F / F_ | 앞면 시계/반시계 |
| D / D_ | 아랫면 시계/반시계 |
| L / L_ | 왼면 시계/반시계 |
| B / B_ | 뒷면 시계/반시계 |

## 빌드 환경

- Visual Studio 2022
- C++ (x64)

## 참고

- moveDefs 회전 테이블: [py222 by MeepMoop](https://github.com/MeepMoop/py222)
