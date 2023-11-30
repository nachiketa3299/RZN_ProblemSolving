#include "PROG.h"

/// @file PROG_64062.cpp
/// @date 2023-11-16T22:36 - 2023-11-17T24:23 (FAIL)
/// ���α׷��ӽ� 64062 (¡�˴ٸ� �ǳʱ�, 2)
/// https://school.programmers.co.kr/learn/courses/30/lessons/64062

/// <¡�˴ٸ��� �ǳʴ� ��Ģ>
/// (1) ¡�˴ٸ��� �Ϸķ� ���� �ְ�, �� ¡�˴ٸ��� ��������� ��� ���ڰ� ���� ������, ������� ���ڴ� �� �� ���� ������ 1�� �پ���.
/// (2) ������� ���ڰ� 0�� �Ǹ� �� �̻� ���� �� ������, �̶��� �� ���� ������� �ѹ��� ���� ĭ �ǳ� �� �� �ִ�.
/// (3) ��, �������� ���� �� �ִ� ������� �������� ���, ������ ����� ������θ� �ǳ� �� �� �ִ�.

/// <�ϴ��� ģ������ ¡�˴ٸ��� �ǳʴ� ��Ģ>
/// (1) �ϴ��� ģ������ ������ ���ʿ� �ְ�, ������ ������ �ǳ��� �����ؾ� ¡�˴ٸ��� �ǳ� ������ �����Ѵ�.
/// (2) �ϴ��� ģ������ �� ���� �� �� ¡�˴ٸ��� �ǳʸ�, �� ���� ¡�˴ٸ��� ��� �ǳ� ��, �� ���� ģ���� �ǳʱ� �����Ѵ�.

/// ������� ���� ���ڰ� ������� ��� �迭 `stones`�� �� ���� �ǳʶ� �� �ִ� ������� �ִ� ĭ �� `k`�� �Ű������� �־��� ��, �ִ� �� ����� ¡�˴ٸ��� �ǳ� �� �ִ��� ��ȯ�ϵ��� `solution` �Լ��� �ϼ��Ѵ�.

/*!
* <���� ����>
* - ¡�˴ٸ��� �ǳʾ� �ϴ� �ϴ��� ģ������ ���� �������̶�� �����Ѵ�.
* - `stones` �迭�� ũ��� [1, 2e5]�̴�.
* - `stones` �迭 �� ������ ���� [1, 2e8]�� �ڿ����̴�.
* - `k` �� [1, `stones.size()`] �̴�.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using StoneHP_T = int;
using Count_T = int;
using WindowIt_T = vector<StoneHP_T>::iterator;

int solution(vector<StoneHP_T> stones, Count_T k)
{
    Count_T min_niniz_cnt;

    auto win_start = stones.begin();
    auto win_end = win_start + k - 1;

    Count_T niniz_cnt = *max_element(win_start, win_end);
    min_niniz_cnt = niniz_cnt;


    while (win_end + 1 != stones.end())
    {
        auto& to_pop_front = *(win_start);
        auto& to_push_back = *(win_end + 1);

        if (to_push_back > niniz_cnt)
        {

            win_start++;
            win_end++;
            continue;
        }
        else
        {
            niniz_cnt = *max_element(win_start + 1, win_end + 1);
            if (niniz_cnt < min_niniz_cnt) 
                min_niniz_cnt = niniz_cnt;
            win_start++;
            win_end++;
        }

    }


    return min_niniz_cnt;
}



int main()
{
    vector<int> vec = { 2, 4, 5, 3, 2, 1, 4, 2, 5, 1 };
    int k = 3;
    cout << solution(vec, 3);
    return 0;
}
