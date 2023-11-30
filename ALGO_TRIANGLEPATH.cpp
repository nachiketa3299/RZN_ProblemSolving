/*!
* @date 2023-10-31T12:58
* ALGOSPOT �ﰢ�� ���� �ִ� ���(TRIANGLEPATH)
* Dynamic Programming?
*/

/*!
* 6
* 1 2
* 3 7 4
* 9 4 1 7
* 2 7 5 9 4
*/

/*!
* �ﰢ�� ������� ��ġ�� �ڿ������� �ִ�.
* �� �� ���ڿ������� ������, �� ���� �� ĭ�� �Ʒ��� ������ �� �Ʒ��ٷ� �������� ��θ� �����.
* ��δ� �Ʒ��ٷ� ������ ������ �ٷ� �Ʒ� ����, Ȥ�� ������ �Ʒ� ���ڷ� ������ �� �ִ�.
* ��� ��� �� ���Ե� ������ �ִ� ���� ã�� ���α׷��� �ۼ��Ѵ�.
* 
* �Է��� ù �ٿ��� �׽�Ʈ ���̽��� �� `C` (`C` <= 50)�� �־�����.
* �׽�Ʈ ���̽��� ù �ٿ��� �ﰢ���� ũ�� `n` (2 <= `n` <= 100)�� �־�����.
* �� �� `n` �ٿ��� 1 ~ `n` ���� ���ڷ� �ﰢ�� �����ٿ� �ִ� ���ڰ� ���ʺ��� �־�����.
* �� ���ڴ� 1 �̻� 1e5 ������ �ڿ����̴�.
* 
* �� �׽�Ʈ ���̽����� �� �ٿ� �ִ� ����� ���� ���� ����Ѵ�.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define CMP_LOWEST -1

class Triangle
{
private:
    /// @short �ﰢ���� �� ���ڵ��� ������.
    vector<vector<int>> t_numbers; 

    /// @short `p_cache[i][j]`�� `t_numbers[i][j]` ������ ����� �ִ���. 
    /// @see @ref Triangle::populate_p_cache
    vector<vector<int>> p_cache;
public:
    /// @short �Է��� �޾� �ﰢ���� �����ϰ�, �ִ� �� ��ο� ���� ĳ��(@ref Triangle::p_cache)�� ä���.
    /// @param[in] n �ﰢ�� �� ���� ũ��
    Triangle(int n): t_numbers(n), p_cache(n) 
    {
        /// �Է��� ���� �޴´�
        for (int i = 0; i < n; ++i)
        {
            t_numbers[i].resize(i + 1);
            p_cache[i].resize(i + 1);
            for (int& t_number : t_numbers[i]) cin >> t_number;
        }
        /// ĳ�ø� ä���
        populate_p_cache();
        return;
    };

    /// @short �ִ� �� ��ο� ���� ĳ�ø� ä���.
    void populate_p_cache()
    {
        /// �ʱ갪 ����. T(0, 0)���� �ִ� �� ��δ� �翬�� T(0, 0)
        p_cache[0][0] = t_numbers[0][0];

        /// `i`�� `j`���� �ִ� �ﰢ���� ���ڴ� `t_numbers[i][j]` �̴�. (`i >= 0 && j >= 0 && i >= j`)
        /// `p_cache[i][j]`�� `t_numbers[i][j]` ��ġ �ִ� �� ����̴�.
        /// `p_cache[i][j]` �� ���� ������ �� ������ ����ؾ� �Ѵ�.
        /// - (1) ����(`vu`)����  ������ ��� -> `p_cache[i - 1][j]`
        /// - (2) �밢��(`du`)���� ������ ��� -> `p_cache[i - 1][j - 1]`
        /// �׸����� �׷����� �Ʒ��� ����. (`p_cache`�� `p`���, `t_numbers`�� `t`�� �Ѵ�)
        /// `p[0][0]=t[0][0]`
        /// `p[1][0]=max(-1, p[0][0]+t[1][0])`, `p[1][1]=max(p[0][0]+t[1][1], -1)`
        /// `p[2][0]=max(-1, p[1][0]+t[2][0])`, `p[2][1]=max(p[1][0]+t[2][1], p[1][1]+t[2][1])`, `p[2][2]=max(p[1][1]+t[2][2], -1)`
        /// `p[3][0]=max(-1, p[2][0]+t[3][0])`, `p[3][1]=max(p[2][0]+t[3][1], p[2][1]+t[3][1])`, `p[3][2]=max(p[2][1]+t[3][2], p[2][2]+t[3][2])`, `p[3][3]=max(p[2][2]+t[3][3], -1)`
        /// ...
        /// `p[i][j]=max(p[i-1][j-1]+t[i][j], p[i-1][j]+t[i][j])` �� �Ϲ�ȭ �� �� �ִ�. ��, `i >= 0 && j >= 0 && i >= j` �� �ƴ϶�� `p[i][j] = -1`
        /// @short **�ٽ��� ������ �밢�� ��� Ÿ�� �������� �� �ִ� �� ��ο� ������ ���� ��� Ÿ�� ���������� �ִ� �� ��� �� ū �� ����� ���� �ִ� �� ��θ� ���ϴ� ��**.
        /// @note ��ο��� �׻� �ִ� ���ڸ� �����Ѵٰ� �ؼ� �� ��ΰ� ��ü ����߿��� �ִ� ���� �����°� �ƴ�! (not a optimal substructure problem)
        /// @note �ﰢ���� ���� ������ ���� �����ִ� �׵鿡 ���ؼ��� ���� `vu`�� `du`�� ������ �� ����. ������ �� ���°� -1(`CMP_LOWEST`)�� �ʱ�ȭ�Ѵ�.

        /// �ﰢ���� �ι�° ����� �ִ� �� ��θ� ä��������.
        for (int i = 1; i < p_cache.size(); ++i)
        {
            for (int j = 0; j < p_cache[i].size(); ++j)
            {
                int vu = is_valid_idx(i - 1, j)     ? p_cache[i - 1][j]     : CMP_LOWEST;
                int du = is_valid_idx(i - 1, j - 1) ? p_cache[i - 1][j - 1] : CMP_LOWEST;
                p_cache[i][j] = max(vu + t_numbers[i][j], du + t_numbers[i][j]);
            }
        }
    }
    bool is_valid_idx(int i, int j) const
    {
        return i >= 0 && j >= 0 && i >= j;
    }

    int get_max_path_sum() const
    {
        /// ĳ���� ������ �࿡�� �ִ��� ã�� �� ���� ��ȯ�ϸ� ��.
        return *max_element(p_cache.back().begin(), p_cache.back().end());
    }
};

int main()
{
    int C; cin >> C; ///< C [1, 50]
    for (size_t tc = 0; tc < C; ++tc)
    {
        int n; cin >> n; ///< n [2, 100]

        Triangle t(n); 
        cout << t.get_max_path_sum() << '\n';
    }
    return 0;
}