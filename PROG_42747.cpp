/// H-Index -> �������� ���꼺�� ������� ��Ÿ���� ��ǥ. (`h`)
/// � �����ڰ� ��ǥ�� �� `n` ����, `h`�� �̻� �ο�� ���� `h`�� �̻��̰� ������ ���� `h`�� ���� �ο�Ǿ��ٸ�, `h`�� �ִ��� �� �������� H-Index�̴�.

/// ���� �� `n` �� [1, 1e3]
/// �� �� �ο� Ƚ�� `citation[n]s` �� [0, 1e4]
/// 

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

///  �ο� Ƚ���� ���� �迭 `citations`�� �־��� ��, H-Index�� ��ȯ�ϴ� �Լ� `solution`�� �ۼ��Ѵ�.
///  @short `CiteData` �� Ư�� �ο� Ƚ���� ���� ���� �� �� �ֳ� �����ϴ� ����ü
struct CiteData
{
    int n_papers_cnt = 0; ///< 
    int acc_cited = 0;
    bool operator<(const CiteData& r) { return this->n_papers_cnt < r.n_papers_cnt;  }
};

using PaperIdx = int; ///< ���� �ε���
using N_Cited = int; ///< �ο�� Ƚ��

/// @param[in] citatinos ���� �ο� Ƚ���� ���� ����. ũ��� `n`�̴�.
/// @return H-Index
int solution(vector<PaperIdx> citations) 
{
    int answer = 0;
    map<N_Cited, CiteData, greater<int>> cite_map;
    for (const auto& citation : citations)
    {
        cite_map[citation].n_papers_cnt++;
    }

    for (auto it = cite_map.begin(); it != cite_map.end(); ++it)
    {
        auto prev_it = prev(it);
        if (prev_it == cite_map.end()) it->second.acc_cited = it->second.n_papers_cnt;
        else
        {
            it->second.acc_cited = it->second.n_papers_cnt + prev_it->second.acc_cited;
        }

        /// `it->first` �� �ο�� ���� `it->first`�� �̻� �ο�� ���� ������(`it->second.acc_cited`) �����̴�.
        if (it->first <= it->second.acc_cited)
        {
            answer = it->first;
            break;
        }
    }

    return answer;
}

int main()
{
    vector<vector<int>> tcs =
    {
        //{3, 0, 6, 1, 5},
        {0, 1, 2, 2, 2},
        {1, 4, 5},
        {5, 6, 7}
    };
    vector<int> answs =
    {
        //3,
        2,
        2,
        3
    };

    for (size_t i = 0; i < tcs.size(); ++i)
    {
        if (solution(tcs[i]) == answs[i]) cout << "Correct\n";
        else
        {
            cout << solution(tcs[i]) << " != " << answs[i] << "(answer)\n";
        }
    }

}