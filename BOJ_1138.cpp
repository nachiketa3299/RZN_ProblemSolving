/// @date 2023-11-08T16:53 17:20
/// ���� 1138 �� �ٷ� ���� S2
/// 2��, 128MB, 60.7%

/*!
* N���� ������� �� �ٷ� ����.
* ������� �ڱ⺸�� ū ����� ���ʿ� �� �� �־������� ����Ѵ�.
* N���� ����� �ְ�, ������� Ű�� 1���� N���� ��� �ٸ���.
* �� ������� ����ϴ� ������ �־��� ��, ���� ��� ���� �ϴ��� ����ϴ� ���α׷��� �ۼ��Ѵ�.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <iterator>

using namespace std;

typedef int         CountType;
typedef CountType   HeightType;

/// @struct Person
/// @short ������� Ű(`height`)�� ���ʿ� ������ ū ����� �� ������(`left`)�� �����ϴ� ������ ����ü.
struct Person
{
    Person(HeightType height, CountType left_greater): height(height), left(left_greater) {}
    CountType left;
    HeightType height;
};

int main()
{
    CountType N; cin >> N; ///< ����� �� N [1, 10] 

    /// �Է����� ���� ������� ����(@ref Person)�� �����ϴ� ����.
    stack<Person> person_memories; 

    for (size_t i = 0; i < N; ++i)
    {
        HeightType theight = i + 1;
        CountType tleft; cin >> tleft;
        person_memories.push(Person(theight, tleft));
    }

    /// ���� ������� �� �ִ� ������ ������ ����Ʈ
    list<Person> persons;

    /// **���� ū ��**���� ���� ����� Ȯ�������� ���� �� ����
    while (!person_memories.empty())
    {
        /// ����Ʈ�� �� ���� ��� `cperson`�� ���ÿ��� �̾ƿ´�.
        /// LIFO �����̹Ƿ� *���� Ű�� ū ���*���� `cperson`�� ������ ���̴�.
        Person& cperson = person_memories.top(); 

        /// ���⼭ `cperson`�� `persons` ����Ʈ�� ��� �� �� ������
        /// @warning `std::list` �� �ݺ����� ��� **����� �ݺ���(Bidirectional Iterator)**�̹Ƿ�, `insert_pos + cperson.left` �� ���� ���·� ����� �� ����
        /// @todo �ٵ� �̰� ������ �� �ϱ�?
        auto insert_pos = persons.begin();
        advance(insert_pos, cperson.left);

        /// `cperson`�� ������ �ڸ��� ������ �ش�.
        persons.insert(insert_pos, cperson);

        person_memories.pop();
    }

    for (const Person& person : persons)
        cout << person.height << " ";

    return 0;
}