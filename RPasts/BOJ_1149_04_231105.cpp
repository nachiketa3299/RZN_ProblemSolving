/// @date 2023-11-05
/// ���� 1149 RGB �Ÿ� https://www.acmicpc.net/problem/1149

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
enum class Color { Red=0, Green, Blue, Max };

int main()
{
    int N; cin >> N; ///< [2, 1e3]
    set<Color> all_colors = { Color::Red, Color::Green, Color::Blue };

    map<Color, vector<int>> i_prices;

    for (const Color& color : all_colors)
    {
        i_prices[color] = vector<int>(N);
    }

    for (int i = 0; i < N; ++i)
    {
        for (const Color& color : all_colors)
            cin >> i_prices[color][i];
    }

    /// @short i ��° ���� � ������ ĥ�ϴ� �ּ� ����� i - 1 ��° ���� 
    /// @short i ��° ���� �������� ĥ�ϴ� �ּ� ����� i - 1 ��° ���� �Ķ����� ĥ�� �ּ� ���� i - 1��° ���� �ʷ����� ĥ�� �ּ� ��� �� �� ���� �Ͱ� i��° ���� �������� ĥ�ϴ� ����� ���� �Ͱ� ����.

    map<Color, vector<int>> mincost_cache;
    for (const Color& color : all_colors)
    {
        mincost_cache[color].resize(N, 0);
        mincost_cache[color].front() = i_prices[color].front();
    }

    for (int i = 1; i < N; ++i)
    {
        for (const Color& color : all_colors)
        {
            set<Color> ccolor = { color };
            set<Color> ocolors;

            set_difference
            (
                all_colors.begin(), all_colors.end(),
                ccolor.begin(), ccolor.end(),
                inserter(ocolors, ocolors.begin())
            );

            priority_queue<int, vector<int>, greater<int>> candid_costs;
            for (const Color& ocolor : ocolors)
                candid_costs.push(mincost_cache[ocolor][i - 1] + i_prices[color][i]);

            mincost_cache[color][i] = candid_costs.top();
        }
    }
    priority_queue<int, vector<int>, greater<int>> total_min_candid;
    for (const Color& color : all_colors)
        total_min_candid.push(mincost_cache[color].back());

    cout << total_min_candid.top() << '\n';



    return 0;
}