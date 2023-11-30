/// @date 2023-11-16T15:00
/// ���� 1920(�� ã��, S4)
/// 128MB, 1��

/// `N` ���� ���� `A[1]`, `A[2]`, ..., `A[N]`�� �־��� ��, �� �ȿ� `X`��� ������ �����ϴ��� �˾Ƴ��� ���α׷��� �ۼ��Ѵ�.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using NaturalNumber_T = unsigned int;
using IntegerNumber_T = int;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    NaturalNumber_T N; cin >> N; ///< [1, 1e5]
    vector<IntegerNumber_T> to_find(N);
    for (auto& v : to_find) cin >> v;
    sort(to_find.begin(), to_find.end());
    NaturalNumber_T M; cin >> M; ///< [1, 1e5]
    vector<IntegerNumber_T> targets(M);
    for (auto& v : targets) cin >> v;

    for (auto& target : targets)
    {
        cout << binary_search(to_find.begin(), to_find.end(), target) << '\n';
    }

    return 0;
}
