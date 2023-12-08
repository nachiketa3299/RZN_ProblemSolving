/// @date 2023-11-16T15:16
/// ���� 10816(���� ī�� 2, S4)

/// ���� ī��� ���� �ϳ��� ������ �ִ� ī���̴�.
/// ���� ī�� `N` ���� ������ �ִ�.
/// ���� `M` ���� �־����� ��, �� ���� �����ִ� ���� ī�带 ����̰� �� �� ������ �ִ��� ���ϴ� ���α׷��� �ۼ��Ѵ�.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Count_T = unsigned int;
using Integer_T = int;
using IntegerVIT_T = vector<Integer_T>::iterator;

int main()
{
    Count_T N; cin >> N; //< [1, 5e5]

    vector<Integer_T> cards(N);
    for (Integer_T& card : cards) cin >> card;


    sort(cards.begin(), cards.end());

    Count_T M; cin >> M; //< [1, 5e5]

    vector<Integer_T> targets(M);
    for (Integer_T& target : targets) cin >> target;

    for (Integer_T& target : targets)
    {
        auto range = equal_range(cards.begin(), cards.end(), target);
        Count_T cnt = distance(range.first, range.second);
        cout << cnt << ' ';
    }


    return 0;
}