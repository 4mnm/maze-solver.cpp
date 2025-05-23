#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

struct Cell {
    bool visited = false;`
    bool topWall = true;
    bool bottomWall = true;
    bool leftWall = true;
    bool rightWall = true;
};

Cell maze[HEIGHT][WIDTH];

struct Pos {
    int x, y;
};


int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

bool isValid(int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

// Recursive backtracking maze generation
void generateMaze(int x, int y) {
    maze[y][x].visited = true;

    int dirs[] = {0, 1, 2, 3};
    random_device rd;
mt19937 g(rd());
shuffle(dirs, dirs + 4, g);


    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dirs[i]];
        int ny = y + dy[dirs[i]];

        if (isValid(nx, ny) && !maze[ny][nx].visited) {
            if (dirs[i] == 0) {
                maze[y][x].topWall = false;
                maze[ny][nx].bottomWall = false;
            } else if (dirs[i] == 1) {
                maze[y][x].bottomWall = false;
                maze[ny][nx].topWall = false;
            } else if (dirs[i] == 2) {
                maze[y][x].leftWall = false;
                maze[ny][nx].rightWall = false;
            } else if (dirs[i] == 3) {
                maze[y][x].rightWall = false;
                maze[ny][nx].leftWall = false;
            }

            generateMaze(nx, ny);
        }
    }
}

// DFS stack-based solver
bool solveMaze(int sx, int sy, int ex, int ey, vector<vector<bool>>& visited) {
    stack<Pos> s;
    s.push({sx, sy});
    visited[sy][sx] = true;

    while (!s.empty()) {
        Pos cur = s.top();
        s.pop();

        if (cur.x == ex && cur.y == ey) {
            maze[cur.y][cur.x].visited = true;
            return true;
        }

        maze[cur.y][cur.x].visited = true;

        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];

            if (!isValid(nx, ny) || visited[ny][nx])
                continue;

            if ((d == 0 && !maze[cur.y][cur.x].topWall) ||
                (d == 1 && !maze[cur.y][cur.x].bottomWall) ||
                (d == 2 && !maze[cur.y][cur.x].leftWall) ||
                (d == 3 && !maze[cur.y][cur.x].rightWall)) {
                visited[ny][nx] = true;
                s.push({nx, ny});
            }
        }
    }

    return false;
}

// Console visualization
void printMaze() {
    for (int y = 0; y < HEIGHT; y++) {
        // Top walls
        for (int x = 0; x < WIDTH; x++) {
            cout << (maze[y][x].topWall ? "+---" : "+   ");
        }
        cout << "+\n";

        // Left walls and visited path
        for (int x = 0; x < WIDTH; x++) {
            cout << (maze[y][x].leftWall ? "| " : "  ");
            cout << (maze[y][x].visited ? "*" : " ");
        }
        cout << "|\n";
    }

   
    for (int x = 0; x < WIDTH; x++) {
        cout << "+---";
    }
    cout << "+\n";
}

int main() {
    srand(time(nullptr));

    generateMaze(0, 0);

    vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
    solveMaze(0, 0, WIDTH - 1, HEIGHT - 1, visited);

    printMaze();

    return 0;
}
