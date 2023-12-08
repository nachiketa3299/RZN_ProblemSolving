/// @file BOJ_13904_231123.cpp
/// @date 2023-11-23 (4:46 - 5:32)
/// @date 2023-11-23 (20:23 - )
/// ���� 13904(����, G3)
/// 1��, 256MB

/*!
* �Ϸ翡 �� ������ ���� �� �ִµ�, �������� �������� �־ ��� ������ ������ ���� ���� �ִ�.
* �������� ������ �� ���� �� �ִ� ������ �ִµ�, �������� ���� ������ ������ �� �޴´�.
* ������ ���� ���� ���� �� �ֵ��� ������ �����ϰ� �ʹ�.
* ���� �� �ִ� ������ �ִ���?

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ScoreType = int;
using DateCountType = int;
using CountType = int;

struct HData
{
    HData(DateCountType days_left, ScoreType score): days_left(days_left), score(score) {};
    DateCountType days_left;
    ScoreType score;
};

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    CountType N; cin >> N; /// [1, 1000]

    vector<HData> hws;
    DateCountType max_date = 1;

    for (CountType i = 0; i < N; ++i)
    {
        DateCountType days_left; cin >> days_left;
        if (days_left > max_date) max_date = days_left;
        ScoreType score; cin >> score;
        hws.push_back(HData(days_left, score));
    }

    sort(hws.begin(), hws.end(), [](const HData& l, const HData& r) { return l.score < r.score; });
    vector<ScoreType> plan(max_date + 1, 0);

    for (const HData& hw : hws)
    {
        for (DateCountType date = hw.days_left; date >= 1; --date)
        {
            if (plan[date] == 0)
            {
                plan[date] = hw.score;
                break;
            }
        }
    }

    ScoreType max_score_sum = 0;
    for (DateCountType date = 1; date <= max_date; ++date)
    {
        max_score_sum += plan[date];
    }
    cout << max_score_sum << '\n';

    return 0;
}
