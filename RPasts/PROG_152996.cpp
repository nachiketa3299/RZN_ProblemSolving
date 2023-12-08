/// @date 2023-11-02T19:35
/// ���α׷��ӽ� 152996(Lv2, �ü� ¦��) 

#include <string>
#include <vector>
#include <map>
#include <array>
#include <set>

using namespace std;

typedef int         WeightType;
typedef long long   CountType;
typedef int         LengthType;

/// �üҿ� �¼��� 2m, 3m, 4m ���� �ִ�.
/// @param[in] weights ������� ������ ���. ���̴� [2, 1e5], ���Ҵ� [1e2, 1e3]
/// @return *�ü� ¦��* ���� ����
CountType solution(vector<WeightType> weights)
{
    /// @short �üҿ� �پ��ִ� �¼��� �Ÿ� ��ġ (2m, 3m, 4m �� ���� �迭)
    array<LengthType, 3> seats = { 2, 3, 4 };

    /// @short �ߺ� ���� ���Ե��� ���� 
    /// @details ��) `weights = { 100, 100, 200 }` �̸�, `unique_weight = { 100, 200 }`
    set<WeightType> u_weights;

    /// @short �� ���԰� � Ƚ���� ����ִ���
    /// @details ��) `weights = { 100, 100, 200 }` �̸�, `weight_cnts = { {100 : 2}, {200 : 1} }`
    map<WeightType, CountType> weight_cnts;

    /// (1) @ref unique_weight �� @ref weight_cnts ä���
    for (const WeightType& weight : weights) ///< O(N)
    {
        u_weights.insert(weight);
        weight_cnts[weight]++;
    }

    /// @short ������ �������� ������ ����
    /// @details ��) `weights = { 100, 100, 200 }` �̸�, `friends = {{100, 100}, {100, 200}}`

    set<pair<WeightType, WeightType>> homo_friends;
    set<pair<WeightType, WeightType>> hetero_friends;

    /// (2) ���԰� ���� �༮���� �������̸� ������ ������ `homo_friends` �� �־��ش�.
    /// ���� ��� 100 ���԰� 3�� �����Ѵٸ� (`weight_cnts[100] == 3`) `friends` �� `{100, 100}`�� �ϳ� �߰�.
    for (const auto& weight_cnt : weight_cnts) ///< O(N)
    {
        if (weight_cnt.second <= 1)
            continue;
        homo_friends.insert({ weight_cnt.first, weight_cnt.first });
    }

    /// (3) ¦�� �� �� �ִ� �༮���� `hetero_friends` �� �־��ش�.
    for (const WeightType& u_weight : u_weights) ///< O(N)
    {
        /// ���� ��ȸ�ϰ� �ִ� `u_weight`�� `current_seat`�� �ɾ��ִٰ� ����
        for (const auto& current_seat : seats) ///< O(3)
        {
            /// ¦�� �ĺ��� `other_seat`�� �ɾ��ִٰ� ����
            for (const auto& other_seat : seats) ///< O(3)
            {
                /// ���� �¼��� �ɴ� ���� (2)���� �̹� ó���Ͽ����Ƿ� �ѱ��.
                if (current_seat == other_seat)
                    continue;
                /// ���� �¼��� ��ũ�� ���ϰ�, �ٸ� �¼��� �Ÿ��� ���������� �������� �ִٸ� ¦���� ���Դ� ������ �ƴ�, �Ұ����� ����
                int torque = u_weight * current_seat;
                if (torque % other_seat != 0) 
                    continue;
                /// ������ ¦���� ���԰� ������ `weights`�� �־����� `weight_cnts`�� �̿��Ͽ� �Ǵ�
                WeightType candid_friend_weight = torque / other_seat;
                if (weight_cnts[candid_friend_weight] == 0)
                    continue;
                /// �־��ٸ� �ִ´�.
                hetero_friends.insert({ u_weight, candid_friend_weight });
            }
        }
    }

    /// `homo_friends = {{100, 100}}` �̰�, `weights = { 100, 100, 100, 100 }` �̾�����, 4�� ������ ���� ���� 2�� �̴°Ͱ� ���� 4C2
    /// �Ϲ�ȭ�ϸ� `homo_friends = {{w, w}}` ��, `homo_cnt = weight_cnts[w]C2` (������ ��)
    CountType homo_cnt = 0;
    for (const auto& hmf : homo_friends)
        homo_cnt += weight_cnts[hmf.first] * (weight_cnts[hmf.first] - 1) / 2;

    /// `hetero_friends`�� �׻� ¦�� ũ���� �ֳ��ϸ� ��Ī���� ����ֱ� ����. ���� ��� (100, 200)�� ��������� (200, 100)�� �������.
    /// ������ 100�� ���� Ƚ�� * 200�� ���� Ƚ�� �� 2�� ������ �־�� �������� ������ ����.
    /// **�ٵ� ���⼭ ������ ���� �� ���� 1�϶� 1 / 2 = 0 ���� ©���� ������ �������� �Ѳ����� ������ �־�� ��**.
    CountType hetero_cnt = 0;
    for (const auto& htf : hetero_friends)
        hetero_cnt += weight_cnts[htf.first] * weight_cnts[htf.second];

    CountType answer = homo_cnt + hetero_cnt / 2;
    return answer;
}

#include "PGS.h"

int main()
{

    Solver<vector<int>, int> s =
    {
        {
            { {100, 180, 360, 100, 270}, 4},
            { {100, 100, 100, 100}, 6},
            { {100, 400}, 0},
            { {200, 100, 100, 200, 100}, 10}

        }
    };
    s();
}