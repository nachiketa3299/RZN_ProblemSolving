///@date 2023-11-03

/// (1) X�� 3���� ������ �������� 3���� ������
/// (2) X�� 2�� ������ �������� 2�� ������
/// (3) 1�� ����
/// ���� N�� �־����� ��, ���� ���� ���� 3���� *������* ����ؼ� ���� 1�� ���� ��, ������ ����ϴ� Ƚ���� �ּڰ���?
/// ���� ��� (10 -> 9 -> 3 -> 1)
/// 

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int IntType;
#define IO -1

class Int
{
public:
    Int(const IntType& N): N(N), cache(N <= 3 ? 3 : N) 
    {
        cache[1 IO] = 0; /// �׳�
        cache[2 IO] = cache[1 IO] + 1; /// 2�� �����°� Ȥ�� 1 ���°�
        cache[3 IO] = cache[1 IO] + 1; /// 3���� �����°�
    };
    int get_min_op_count()
    {
        if (N <= 3) return cache[N IO];

        for (int i = 4; i <= N; ++i)
        {
            vector<int> candid;

            if (i % 3 == 0) candid.push_back(i / 3);
            if (i % 2 == 0) candid.push_back(i / 2);
                            candid.push_back(i - 1);

            static auto cache_cmp = [this](const int& op1, const int& op2) { return cache[op1 IO] < cache[op2 IO]; };
            int min_case = *min_element(candid.begin(), candid.end(), cache_cmp);
            cache[i IO] = cache[min_case IO] + 1;
        }
        return cache[N IO];
    }
private:
    IntType N;
    vector<int> cache;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    IntType N; cin >> N; ///< N [1, 1e7]
    Int n(N);

    cout << n.get_min_op_count() << '\n';

    return 0;
}