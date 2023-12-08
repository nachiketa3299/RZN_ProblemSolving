/*!
* @file BOJ_1021_231205.cpp
* @date 2023-12-05T18:03
* ���� 1021 ȸ���ϴ� ť S3
*/

/*!
* �����̴� N���� ���Ҹ� �����ϰ� �ִ� ����� ��ȯ ť�� ������ �ִ�.
* �����̴� �� ť���� �� ���� ���Ҹ� �̾Ƴ����� �Ѵ�.
* �����̴� �� ť���� ������ ���� 3���� ������ ������ �� �ִ�.
* - (1) ���Ҹ� �̾Ƴ���
* - (2) �������� �� ĭ �̵���Ű��
* - (3) ���������� �� ĭ �̵���Ű��
* ť�� ó���� ���ԵǾ� �ִ� �� N�� �־�����.
* �����̰� �̾Ƴ����� ������ ��ġ�� �־�����. (���� ó���� ť ��ġ)
* �� ���Ҹ� �־��� ������� �̾Ƴ��µ� ��� 2, 3�� ������ �ּڰ��� ����ϴ� ���α׷��� �ۼ��Ѵ�.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /// @short ���� ť�� ũ�� 
    /// @note [1, 50]
    size_t N; cin >> N;
    /// @short ���� ť���� �̾Ƴ����� �ϴ� ���� ����
    /// @note M <= N �� �ڿ���
    size_t M; cin >> M;

    deque<int> dq;
    for (size_t i = 1; i <= N; ++i)
        dq.push_back(i);


    return 0;
}