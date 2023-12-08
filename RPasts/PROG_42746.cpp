// ���� ū �� [[2023-10-25T15:38, 2023-10-25T17:32]]
// 0 �Ǵ� ���� ������ �־���, ������ �̾ ���� �� �ִ� ���� ū ��
// ��) [6, 10, 2] ��� [6102, 6210, 1062, 1026, 2610, 2106]�� ���� �� �ִ�. ���⼭ ���� ū ���� 6210
// �־����� ������ ���� N�� [1, 1e5]��, ���� ���ͷ� �־���
// �־����� ���� e �� [0, 1e3]�̴�.
// ��ȯ�ϴ� ���� ū ������ ���ڿ���

// ���Ʈ ������?
// ������ ��� ������ N!���� �������� �翬�� �̰� ����µ� O(N!) ���⼭ ū�� ã�°� �Ƹ��� O(N) �׷��ϱ� O(N! + N)�ε� �̷��� Ǯ�� �ð� �ʰ��� ���;� ����
// >> �Ƹ���? ���� ū ���� ������ ��Ģ�� ���� <<
// ������ e��� �ϸ� e�� �ڸ����� ��� ���ٸ� e���� ������������ �׳� �����ϸ� �׸���
// �ٵ� e�� �ڸ����� �޶� ������ ������ [0, 1e3]�̸�, 0�� ������.
// e�� �ֻ��� �ڸ����� e.max_digit �̶�� �ϸ� e.max_digit ������ �����ϸ� ���� ������?

#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

struct Integer
{
public:
    Integer(int val): val(val) 
    {
        for (int i = this->val; i != 0; i /= 10) 
            this->all_digits.push(i % 10);
        return;
    };
public:
    int val;
    stack<int> all_digits;
public:
    friend bool operator<(const Integer& oth1, const Integer& oth2) 
    { 
        if (oth1.val == oth2.val) return false;

        stack<int> d1 = oth1.all_digits;
        stack<int> d2 = oth2.all_digits;

        auto cd1 = d1.top();
        auto cd2 = d2.top();

        while (true)
        {

            if (cd1 == cd2)
            {
                if (d1.size() <= 1) cd1 = cd1;
                else { d1.pop(); cd1 = d1.top(); }

                if (d2.size() <= 1) cd2 = cd2;
                else { d2.pop(); cd2 = d2.top(); }
            }
            else
            {
                return cd1 < cd2;
            }
        }
    };
};

string solution(vector<int> numbers)
{
    string answer = "";
    priority_queue < Integer, vector<Integer>, less<Integer>> pq;

    for (const auto& integers : numbers) 
        pq.push(Integer(integers));

    while (!pq.empty()) 
    { 
        // ó�� �ִµ� ���ڰ� �׳� 0�̸� �ϰ͵� ��������
        if (answer.empty() && pq.top().val == 0) pq.pop();
        else 
        {
            answer += to_string(pq.top().val); 
            pq.pop(); 
        }
    }
    // �� ���δ� 0�̸� 0 �������
    if (answer.empty()) answer = "0";
    return answer;
}

#include <iostream>

int main(void)
{

    vector<vector<int>> numbers_vec =
    {
        {6, 10, 2},
        {3, 30, 34, 5, 9},
        {30, 30},
        {0, 0, 0},
        {979, 97, 978, 81, 818, 817}
    };
    vector<string> answer_vec =
    {
        "6210",
        "9534330",
        "3030",
        "0",
        "9799797881881817"
    };
    int tc_cnt = numbers_vec.size();
    for (int i = 0; i < tc_cnt; ++i)
    {

        if (solution(numbers_vec[i]) == answer_vec[i]) 
            cout << "Correct\n";
        else 
            cout << "Incorrect: " << answer_vec[i] << " != " << solution(numbers_vec[i]) << "\n";
    }
    return 0;
}
