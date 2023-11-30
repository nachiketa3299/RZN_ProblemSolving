///@date 2023-11-06
///���� 17615 �� ������
/// Greedy Algorithm (?)

/*!
* ������ ���� �Ķ��� ���� �������� ���� �ִ�.
* RBBBRBRRR
* ���� ��Ģ��� �Űܼ� **���� �� ������ �����ϰ� ���̵��� �Ϸ��� �Ѵ�.**
* ���� �ű�� ��Ģ�� �Ʒ��� ����.
* (1) �ٷ� ���� �ٸ� ���� ���� ������ �� ���� ��� �پ� �Ѿ� �ű� �� �ִ�.
* ���� ���, ������ ���� ���� �ִ� �Ķ��� �� �����⸦ �� ���� �پ�Ѿ� �ű� �� �ִ�.
* (2) �ű� �� �ִ� ���� ���� �� �����̴�.
* ���� ���, ������ ���� ó���� �Ű�����, �������� ������ ���� �ű� �� �ִ�.
* 
* �� �ű�� ��
* 1. RBBBRBRRR 4R�� 5B �ڷ� �ű� �� ����
* 2. RBBBBRRRR 0R�� 4B �ڷ� �ű� �� ����
* 3. BBBBRRRRR
* 
* ������ �� ���� �ִ� ���� ���� ������ �־��� ��, ��Ģ�� ���� ���� �̵��Ͽ� ���� ������ ������ �ּ� �̵�Ƚ���� ã�� ���α׷��� �ۼ��Ѵ�.
*/

#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct ColorChunk
{
    ColorChunk(char color, int cnt): is_red(color == 'R' ? true : false), cnt(cnt) {}
    bool is_red = true;
    int cnt = 0;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int N; cin >> N; ///< N [1, 5e5]

    /// RRRR �̳� BBBB���� �͵� ���� �� ������ �� ��� ���� 0
    string input; cin >> input; ///< R, B


    /// RBBBRBRRR�� (R1)(B3)(R1)(B1)(R3) ���·� ����� ����
    vector<ColorChunk> chunks;
    int r_cnt_sum = 0; int b_cnt_sum = 0;

    {
        char tprev; ///< �ٷ� ������ � ���ڿ��°�
        int tcnt = 0; ///< ���� ���� �ִ� ������ ����
        for (int i = 0; i < N; ++i)
        {
            /// ù ��Ҵ� ���ø�
            if (i == 0)
            {
                tprev = input[0];
                tcnt++;
            }
            /// ù ��� �ƴϸ�
            else
            {
                /// ���� �����ִ°� �����Ŷ� �ٸ���?
                if (tprev != input[i])
                {
                    /// �������� ���� Ǫ���ϰ�
                    chunks.push_back(ColorChunk(tprev, tcnt));
                    /// �ʱ�ȭ
                    tprev = input[i];
                    tcnt = 1;
                }
                /// ���� ���� �ִ°� �����Ŷ� ����?
                else
                    tcnt++; /// �׳� ������ ����
            }
            /// Ȥ�� ���� ������ ����ΰ�?
            if (i + 1 == N)
                /// �׳� ���� Ż���ϸ� �������� �ô� �͵��� `chunks`�� �ȵ��Ƿ� Ǫ������
                chunks.push_back(ColorChunk(tprev, tcnt));

            /// R�� �� ������ B�� �� ���� ������
            if (input[i] == 'R') r_cnt_sum++;
            else                 b_cnt_sum++;
        }
    }


    /// B�� ��� ��������, B�� ��� ��������, R�� ��� ��������, R�� ��� �������� �̵��ϴ� 4���� �������� �� ť�� �ְ� ž�� �̾Ƹ�������
    priority_queue<int, vector<int>, greater<int>> candid_counts;

    /// @short �� ������ �� ������ �����ִ� ûũ���� �̹� ������ �Ǿ������Ƿ� �̵��� �ʿ䰡 ����. �׷��� �׳� �� ���Ѵ㿡 ���ָ� ��.
    /// (R1)(B3)(R1)(B1)(R3) ��� �����ϸ�
    /// *R*�� ��� *����*���� �ű�� 1 + 1 + 3 - �� *����* ù��° `ColorChunk`�� *R*��� �� ûũ�� ����, �ƴ϶�� �ƹ��͵� �� ����
    /// *R*�� ��� *����*���� �ű�� 1 + 1 + 3 - �� *����* ù��° `ColorChunk`�� *R*��� �� ûũ�� ����, �ƴ϶�� �ƹ��͵� �� ����
    /// *B*�� ��� *����*���� �ű�� 3 + 1     - �� *����* ù��° `ColorChunk`�� *B*��� �� ûũ�� ����, �ƴ϶�� �ƹ��͵� �� ����
    /// *B*�� ��� *����*���� �ű�� 3 + 1     - �� *����* ù��° `ColorChunk`�� *B*��� �� ûũ�� ����, �ƴ϶�� �ƹ��͵� �� ����

    candid_counts.push(r_cnt_sum - ( chunks.front().is_red ? chunks.front().cnt : 0));
    candid_counts.push(r_cnt_sum - ( chunks.back ().is_red ? chunks.back ().cnt : 0));
    candid_counts.push(b_cnt_sum - (!chunks.front().is_red ? chunks.front().cnt : 0));
    candid_counts.push(b_cnt_sum - (!chunks.back ().is_red ? chunks.back ().cnt : 0));

    /// �� �ְ� top�� ������.

    cout << candid_counts.top() << '\n';

    return 0;
}

