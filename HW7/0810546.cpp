#include <iostream>
#include <vector>
#include <limits>

void optimalBST(const std::vector<double> &un_p, const std::vector<double> &q, int n, std::vector<std::vector<double>> &e, std::vector<std::vector<double>> &w, std::vector<std::vector<int>> &root)
{

    std::vector<double> p;
    p.push_back(0);
    p.insert(p.end(), un_p.begin(), un_p.end());
    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            e[i][j] = std::numeric_limits<double>::infinity();
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++)
            {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printBSTStructure(const std::vector<std::vector<int>> &root, int i, int j, int parent = 0, bool isLeftChild = false)
{
    if (i > j)
    {
        return;
    }

    int currentRoot = root[i][j];

    if (parent != 0)
    {
        std::cout << parent << (isLeftChild ? " (L)" : " (R)") << " -> " << currentRoot << std::endl;
    }
    else
    {
        std::cout << currentRoot << " is the root" << std::endl;
        std::cout << "Tree structure :" << std::endl;
    }

    printBSTStructure(root, i, currentRoot - 1, currentRoot, true);
    printBSTStructure(root, currentRoot + 1, j, currentRoot, false);
}

int main()
{

    // HW7測試資料
    std::vector<double> p = {0.05, 0.04, 0.02, 0.07, 0.08, 0.09, 0.04, 0.08, 0.03};
    std::vector<double> q = {0.08, 0.06, 0.04, 0.04, 0.03, 0.06, 0.07, 0.06, 0.04, 0.02};

    // 討論題測試資料
    // std::vector<double> p = {0.05, 0.15, 0.15, 0.1, 0.1};
    // std::vector<double> q = {0.05, 0.1, 0.05, 0.1, 0.05, 0.1};

    int n = p.size();

    // Define and initialize tables
    std::vector<std::vector<double>> e(n + 2, std::vector<double>(n + 1));
    std::vector<std::vector<double>> w(n + 2, std::vector<double>(n + 1));
    std::vector<std::vector<int>> root(n + 1, std::vector<int>(n + 1));

    optimalBST(p, q, n, e, w, root);

    // 印出expected value table
    //  std::cout << "e table:\n";
    //  for (int i = 1; i <= n + 1; i++)
    //  {
    //      for (int j = 0; j <= n; j++)
    //      {
    //          std::cout << e[i][j] << " ";
    //      }
    //      std::cout << std::endl;
    //  }

    // 印出weight table
    //  std::cout << "w table:\n";
    //  for (int i = 1; i <= n + 1; i++)
    //  {
    //      for (int j = 0; j <= n; j++)
    //      {
    //          std::cout << w[i][j] << " ";
    //      }
    //      std::cout << std::endl;
    //  }

    // 印出root table
    //  std::cout << "\nroot table:\n";
    //  for (int i = 1; i <= n; i++)
    //  {
    //      for (int j = 1; j <= n; j++)
    //      {
    //          std::cout << root[i][j] << " ";
    //      }
    //      std::cout << std::endl;
    //  }
    std::cout << "Smallest Expected Search Cost = " << e[1][n] << std::endl;

    printBSTStructure(root, 1, root.size() - 1);

    return 0;
}
