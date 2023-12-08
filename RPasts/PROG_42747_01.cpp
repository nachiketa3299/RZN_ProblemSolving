/*!
* @date 2023.10.29
* � �����ڰ� ��ǥ�� �� `n`�� ��, `h`�� �̻� �ο�� ���� `h`�� �̻��̰�, ������ �� `h`�� ���� �ο�Ǿ��ٸ� `h`�� �ִ��� �� �������� H-Index�̴�.
* � �����ڰ� ��ǥ�� ���� �ο� Ƚ���� ���� �迭 `citations`�� �Ű������� �־��� ��, �� �������� H-Index�� ��ȯ�ϵ��� `solution` �Լ��� �ۼ��Ѵ�.
* - �����ڰ� ��ǥ�� ���� �� `n`�� [1, 1e3]�̴�.
* - ���� �ο� Ƚ���� [0, 1e4]�̴�.
*/

#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations)
{
    int answer = 0;

    int max_h = 0;
    sort(citations.begin(), citations.end(), less<int>());

    for (size_t p_idx = 0; p_idx < citations.size() - 1; ++p_idx)
    {
        int h = citations[p_idx]; //< p_idx �� ���� �ο� Ƚ��
        int p_geq_h = p_idx + 1;

        if (h - 1 > citations[p_idx + 1])
        {
            h--;
            p_geq_h++;
        }
        if (h <= p_geq_h)
        {
            max_h = h;
            break;
        }
    }

    answer = max_h;

    return answer;
}

#include "PGS.h"


int main(void)
{
    Solver<vector<int>, int> sol
    {
        {
            { {3, 0, 6, 1, 5}, 3 },
            { {0, 5, 6, 7, 8}, 4 }
        }
    }; 
    sol();
}

