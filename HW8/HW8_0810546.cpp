#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

const int MAX_SIZE = 17;

enum MazeState
{
    WALL = 0,
    ROAD = 1,
    TRAP = 2
};

struct Coordinate
{
    int x;
    int y;
};

void GotoLine(ifstream &file, int num)
{
    file.seekg(ios::beg);
    for (int i = 0; i < num - 1; ++i)
    {
        file.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
}

void printCoordinates(const vector<Coordinate> &tempCoordinates)
{
    for (const Coordinate &coordinate : tempCoordinates)
    {
        cout << "(" << coordinate.x << "," << coordinate.y << ")" << endl;
    }
}

void printSteps(const vector<vector<int>> &steps)
{
    int size = steps.size();
    for (int i = 1; i < size; i++)
    {
        for (int j = 1; j < size; j++)
        {
            cout << steps[i][j] << " ";
        }
        cout << endl;
    }
}

int findShortestPath(const vector<vector<MazeState>> &maze) // 這邊只是確認真的有path，所以功能跟printShortestPath的功能有部分相同，詳細請看printShortestPath function
{
    // 上下左右
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // 紀錄是否被visit過
    vector<vector<bool>> visited(MAX_SIZE + 1, vector<bool>(MAX_SIZE + 1, false));
    // 紀錄在此座標時，累計到此的step為和
    vector<vector<int>> steps(MAX_SIZE + 1, vector<int>(MAX_SIZE + 1, 0));
    queue<Coordinate> q;

    Coordinate start = {1, 1};
    Coordinate end = {MAX_SIZE, MAX_SIZE};

    visited[start.x][start.y] = true;
    steps[start.x][start.y] = 0;
    q.push(start);
    // BFS
    while (!q.empty())
    {
        Coordinate current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y) // 真的有path的話就回傳總step數
        {

            return steps[current.x][current.y];
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 1 && nx <= MAX_SIZE && ny >= 1 && ny <= MAX_SIZE && !visited[nx][ny])
            {

                if (maze[nx][ny] != WALL)
                {
                    if (maze[nx][ny] == TRAP) // 遇到trap，step要+2
                    {
                        visited[nx][ny] = true;
                        steps[nx][ny] = steps[current.x][current.y] + 2;
                    }
                    else
                    {
                        visited[nx][ny] = true;
                        steps[nx][ny] = steps[current.x][current.y] + 1;
                    }
                    q.push({nx, ny});
                }
            }
        }
    }

    return -1; // 沒有path，回傳-1
}

pair<int, vector<Coordinate>> printShortestPath(const vector<vector<MazeState>> &maze)
{
    // 上下左右
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int total_steps;

    // 紀錄是否被visit過
    vector<vector<bool>> visited(MAX_SIZE + 1, vector<bool>(MAX_SIZE + 1, false));
    // 紀錄在此座標時，累計到此的step為和
    vector<vector<int>> steps(MAX_SIZE + 1, vector<int>(MAX_SIZE + 1, 0));
    // 起始點
    Coordinate start = {1, 1};
    Coordinate end = {MAX_SIZE, MAX_SIZE};
    Coordinate temp;
    vector<Coordinate> tempCoordinates;

    // 初始點 visit = true，累計step = 0
    visited[start.x][start.y] = true;
    steps[start.x][start.y] = 0;

    queue<Coordinate> q;
    q.push(start);

    // BFS
    while (!q.empty())
    {
        Coordinate current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y) // 抵達終點
        {
            total_steps = steps[current.x][current.y];              // 最後一個點的累計步數
            while (!(current.x == start.x && current.y == start.y)) // 還沒到終點
            {
                temp = {current.x, current.y};
                tempCoordinates.push_back(temp); // 回朔軌跡
                int step = steps[current.x][current.y];
                if (maze[current.x][current.y] == TRAP) // 遇到trap的情況，條件需改為steps[nx][ny] == step - 2，因為前一步是現在這步-2
                {
                    temp = {current.x, current.y};
                    tempCoordinates.push_back(temp);
                    for (int i = 0; i < 4; i++) // 找上下左右，誰符合下面的if條件
                    {
                        int nx = current.x + dx[i];
                        int ny = current.y + dy[i];

                        if (nx >= 1 && nx <= MAX_SIZE && ny >= 1 && ny <= MAX_SIZE && steps[nx][ny] == step - 2 && maze[nx][ny] != WALL)
                        {
                            current.x = nx;
                            current.y = ny;
                            break;
                        }
                    }
                }
                else // 遇到wall的情況
                {
                    for (int i = 0; i < 4; i++) // 找上下左右，誰符合下面的if條件
                    {
                        int nx = current.x + dx[i];
                        int ny = current.y + dy[i];

                        if (nx >= 1 && nx <= MAX_SIZE && ny >= 1 && ny <= MAX_SIZE && steps[nx][ny] == step - 1 && maze[nx][ny] != WALL)
                        {
                            current.x = nx;
                            current.y = ny;
                            break;
                        }
                    }
                }
            }
            temp = {start.x, start.y}; // 最後紀錄start coordinate
            tempCoordinates.push_back(temp);
            break;
        }

        for (int i = 0; i < 4; i++) // 找path
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 1 && nx <= MAX_SIZE && ny >= 1 && ny <= MAX_SIZE && !visited[nx][ny]) // 沒visit過且還在迷宮範圍內
            {
                if (maze[nx][ny] != WALL)
                {
                    if (maze[nx][ny] == TRAP) // 遇到trap，steps要+2
                    {
                        visited[nx][ny] = true;
                        steps[nx][ny] = steps[current.x][current.y] + 2;
                    }
                    else // 一般的路，steps _1
                    {
                        visited[nx][ny] = true;
                        steps[nx][ny] = steps[current.x][current.y] + 1;
                    }
                    q.push({nx, ny}); // 把現在的coordinate傳入queue中，做BFS
                }
            }
        }
    }
    reverse(tempCoordinates.begin(), tempCoordinates.end()); // 回朔是倒著走，所以最終的path要reverse
    return make_pair(total_steps, tempCoordinates);          // 將總步數與path的座標回傳
}

vector<vector<MazeState>> readMazeFromFile(const string &filename, int start)
{

    string test;
    ifstream inputFile(filename);
    GotoLine(inputFile, start);

    vector<vector<MazeState>> maze(MAX_SIZE + 1, vector<MazeState>(MAX_SIZE));

    if (inputFile.is_open())
    {
        for (int i = 1; i <= MAX_SIZE; i++)
        {
            for (int j = 1; j <= MAX_SIZE; j++)
            {
                int state;
                inputFile >> state;
                maze[i][j] = static_cast<MazeState>(state);
            }
        }
    }
    else
    {
        cerr << "Failed to open input file." << endl;
    }
    inputFile.close();

    return maze;
}

void output(ofstream &out, vector<int> &stepArray, vector<vector<Coordinate>> &pathArray, int total_num)
{

    for (int i = 0; i < total_num; i++)
    {
        if (stepArray[i] == -1)
        {
            out << "there is no path in pattern " << i + 1 << " !" << endl;
        }
        else
        {
            out << "pattern " << i + 1 << endl;
            out << "step=" << stepArray[i] << endl;
            for (int j = 0; j < stepArray[i] + 1; j++)
            {
                out << "(" << pathArray[i][j].x << "," << pathArray[i][j].y << ")" << endl;
            }
            out << endl;
        }
    }
}

int main()
{
    ofstream out("0810546_output.txt");
    ifstream inputFile("input.txt"); // Open the file for reading
    string line;
    vector<vector<Coordinate>> pathArray;
    vector<Coordinate> temp;
    pair<int, vector<Coordinate>> result;
    vector<int> stepArray;
    int check;
    int total_steps;
    int lineCount = 0;

    // 讀input file有幾行
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, line))
        {
            lineCount++;
        }
        inputFile.close(); // Close the file
    }
    // 計算總共有幾個迷宮
    int totalMaze = lineCount / 17 - 1;

    for (int i = 0; i < totalMaze; i++)
    {
        if (18 * i + 1 == lineCount)
        {
            break;
        }
        vector<vector<MazeState>> maze = readMazeFromFile("input.txt", 18 * i + 1);
        // 計算是否有path從(1,1)到(17,17)
        check = findShortestPath(maze);
        if (check == -1) // 如果沒有path, 則會再output file輸入 "-1"
        {
            stepArray.push_back(-1);
        }
        else
        {
            // 有path則push back到pathArray
            result = printShortestPath(maze);
            total_steps = result.first;
            temp = result.second;
            pathArray.push_back(temp);
            stepArray.push_back(total_steps);
        }
    }
    // 寫output
    output(out, stepArray, pathArray, totalMaze);

    return 0;
}
