/// @file BOJ_2343.cpp
/// ���� 2343(��Ÿ ����, S1) https://www.acmicpc.net/problem/2343
/// 2��, 128MB
/// @date 2023-11-15T22:22

/// @details
/// ��緹�̿� ��Ÿ ���� �������� �������� �Ѵ�.\n
/// - ��緹�̿��� �� `N`���� ���ǰ� ����.\n
/// - ���Ǹ� ���� �� ������ ������ �ٲ�� �ȵȴ�.\n
/// - `i`�� ���ǿ� `j`�� ���Ǹ� ���� ��緹�̿� ��ȭ�Ϸ���, `i`�� `j` ������ ��� ���ǵ� ���� ��緹�̿� ��ȭ�ؾ� �Ѵ�.\n
/// ��緹���� ������ `M`�� �ּ�ȭ �Ϸ��� �Ѵ�.
/// **��緹���� ũ��(��ȭ ����)�� �ּҷ� �Ϸ��� �Ѵ�.**
/// **`M` ���� ��緹�̴� ��� ���� ũ���̴�.**
/// �� ������ ���̰� �� ����(�ڿ���)�� �־�����.
/// **������ ��緹���� ũ�� �� �ּҸ� ���Ѵ�.**

/*! ���� �Է�
9 3
2 3 4 5 6 7 8 9

*/
/*! ���� ���
17
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;
using CourseCount_T = size_t;
using RayCount_T = size_t;
using Time_T = unsigned int;
using TimeVecIt_T = vector<Time_T>::iterator;

vector<Time_T> divide(TimeVecIt_T ptr_begin, TimeVecIt_T ptr_end, size_t k)
{
    static size_t recur_count = k;
    Time_T total_sum = accumulate(ptr_begin, ptr_end, 0);

    Time_T sub_sum = 0; 
    TimeVecIt_T ptr_half = ptr_begin;

    while (sub_sum < total_sum / 2)
        sub_sum += *(ptr_half++);

    /*! ptr_begin | ptr_half | ptr_end */

    TimeVecIt_T new_begin = ptr_half - ptr_begin > ptr_end - ptr_half ? 
}

int main()
{
    /// @short ��緹�� �ȿ� ���� ������ ��
    CourseCount_T N; cin >> N; //< [1, 1e5]

    /// @short ��緹���� ��
    RayCount_T M; cin >> M; //< [1, N]

    /// @short N���� ���ǰ� ���̰����� ������� ��. ������ �����Ǿ�� ��!
    vector<Time_T> courses(N);
    for (auto& course: courses)
        cin >> course;

    size_t k = static_cast<size_t>(log(M) / log(2));

    vector<Time_T> course_chunk = divide(course_chunk.begin(), course_chunk.end() - 1, k);

    return 0;
}

