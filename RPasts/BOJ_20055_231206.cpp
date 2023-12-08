/*!
* @file BOJ_20055_231206.cpp
* @date 2023-12-06 T 16:35
* ���� 20055 �����̾� ��Ʈ ���� �κ� G5
* 1��, 512MB
*/

/*!
* ���̰� N�� �����̾� ��Ʈ�� �ְ�, ���̰� 2N�� ��Ʈ�� �� �����̾� ��Ʈ�� ���Ʒ��� ���ΰ� ���� �ִ�.
* ��Ʈ�� ���� 1 �������� 2N���� ĭ���� ������ �ִ�.
* �� ĭ���� ����ó�� 1 ~ 2N ������ ��ȣ�� �Ű��� �ִ�.
* ->
* | 1**  | 2    | 3    |  ... | N-1  | N** |
* | 2N   | 2N-1 | 2N-2 |  ... | N+1  | N+1 |
* <-
* ��Ʈ�� �� ĭ ȸ���ϸ� 1 ~ 2N-1 ��° ĭ�� ���� ĭ�� ��ġ�� �̵��ϰ�, 2N�� ĭ�� 1�� ĭ�� ��ġ�� �̵��Ѵ�.
* i�� ĭ�� �������� A_i�̴�.
* 1�� ĭ�� ��ġ�� *�ø��� ��ġ*, N�� ĭ�� ��ġ�� *������ ��ġ*��� �Ѵ�.
* 
* *�ø��� ��ġ* �� �ڽ� ��� �κ��� �ϳ��� �ø����� �Ѵ�.
* �������� �κ��� *������ ��ġ*�� �����ϸ� ��� ������.
* �κ��� ��Ʈ ������ ������ �̵��� �� �ִ�.
* �κ��� *�ø��� ��ġ*�� �ø��ų�, �κ��� � ĭ���� �̵��ϸ� �� ĭ�� �������� ��� 1��ŭ �����Ѵ�.
* 
* �����̾� ��Ʈ�� �̿��� �κ��� �ǳ������� �ű���� �Ѵ�.
* �ű�� �������� ������ ���� ������� �Ͼ��.
* (1) ��Ʈ�� �� ĭ���� �ִ� �κ��� �Բ� �� ĭ ȸ���Ѵ�.
* (2) ���� ���� ��Ʈ�� �ö� �κ�����, ��Ʈ�� ȸ���ϴ� �������� �� ĭ �̵��� �� �ִٸ� �̵��Ѵ�.
*     ���� �̵��� �� ���ٸ�, ������ �ִ´�.
*       �κ��� �̵��Ϸ��� �̵��Ϸ��� ĭ�� �κ��� ������, �� ĭ�� �������� 1 �̻� �����־�� �Ѵ�.
* (3) *�ø��� ��ġ*�� �ִ� ĭ�� �������� 0�� �ƴϸ�, �ø��� ��ġ�� �κ��� �ø���.
* (4) �������� 0�� ĭ�� ������ K�� �̻��̸�, ������ �����Ѵ�. �׷��� ������ 1������ ���ư���.
* 
* ������ ����Ǿ��� ��, �� ��° �ܰ谡 ���� ���̾����� ���Ѵ�.
* ���� ó�� ����Ǵ� �ܰ�� (1) ��° �ܰ��̴�.
*/
#define PS_DEBUG
//#undef PS_DEBUG

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;
#define IS_STOPPED bool
#define NOT_STOPPED false
#define STOPPED true

class Conveyer
{
public:
    struct Node
    {
        Node(int durability):durability(durability) {};
        Node* next = nullptr;
        Node* prev = nullptr;
        int durability;
        bool occupied = false;
#ifdef PS_DEBUG
        int id;
#endif

    };
public:
    Conveyer(int N, int K): size(2 * N), robot_pos(0), K(K)
    {
        std::vector<Node*> nodes(2 * N);

        for (size_t i = 0; i < 2 * N; ++i)
        {
            int durability; cin >> durability;
            nodes[i] = new Node(durability);
#ifdef PS_DEBUG
            nodes[i]->id = i + 1;
#endif 
        }

        this->ptr_push = nodes[0];
        this->ptr_pop = nodes[N - 1];

        for (size_t i = 0; i < nodes.size(); ++i)
        {
            if (i == 0)
            {
                nodes[i]->prev = nodes[2 * N - 1];
                nodes[i]->next = nodes[i + 1];
            }
            else if (i == nodes.size() - 1)
            {
                nodes[i]->prev = nodes[i - 1];
                nodes[i]->next = nodes[0];
            }
            else
            {
                nodes[i]->prev = nodes[i - 1];
                nodes[i]->next = nodes[i + 1];
            }
        }
    };

    IS_STOPPED Move()
    {
        ptr_push = (ptr_push->prev);
        ptr_pop = (ptr_pop->prev);

        if (robot_pos.size() == 0)
            return NOT_STOPPED;

        if (robot_pos.front() == ptr_pop)
        {
            robot_pos.front()->occupied = false;
            robot_pos.pop_front();
        }

        return NOT_STOPPED;
    }

    IS_STOPPED ProceedRobots()
    {
        for (size_t i = 0; i < robot_pos.size(); ++i)
        {
            // ���� ������ ĭ���� Ȯ���Ѵ�
            if (robot_pos.at(i) == ptr_pop)
            {
                robot_pos.at(i)->occupied = false;
                assert(robot_pos.at(i) == robot_pos.front());
                robot_pos.pop_front();
                continue;
            }

            // �� ĭ�� ���� �ִٸ� �� ������
            if (robot_pos.at(i)->next->occupied) continue;
            // �� ĭ�� �������� 0�̸� �� ������
            if (robot_pos.at(i)->next->durability == 0) continue;

            // �� ĭ ���� ������ �� �ִ� ��Ȳ
             
            // �����̰� ���� occupy ��Ȳ ó�� �ϰ�
            robot_pos.at(i)->occupied = false;
            robot_pos.at(i) = robot_pos.at(i)->next;
            robot_pos.at(i)->occupied = true;

            // �����̸� ������ ���� ����� �߻��ϹǷ� ������ ���� �˻�
            if (--robot_pos.at(i)->durability == 0)
            {
                ++durability_count;
                // ����, �������� ����ġ �̻��̸� ������ ����
                if (TestDurabilities() == STOPPED) 
                    return STOPPED;
            }

            // ������� �Դٴ°� �������µ�, ���������� ó���ߴµ��� �ߴ� �ȵƴٴ°�
            // �ٵ� ���� ������ ĭ�� ������ ĭ���� �Ǵ��ϴ� ������ ����

            // �����̰� �� ĭ�� ������ ĭ�̸� ������. occupy ��Ȳ ó��
            if (robot_pos.at(i) == ptr_pop)
            {
                assert(robot_pos.at(i) == robot_pos.front());
                robot_pos.at(i)->occupied = false;
                robot_pos.pop_front();
            }
        }
        return NOT_STOPPED;
    }

    IS_STOPPED PushRobot()
    {
        Node* current_push_pos = ptr_push;

        // ������ ������ ���ø�
        if (ptr_push->durability == 0)
            return NOT_STOPPED;

        // ���� ������ ���ø�
        if (ptr_push->occupied)
            return NOT_STOPPED;

        // �ø� �� �ִ� ��Ȳ
        robot_pos.push_back(ptr_push);
        ptr_push->occupied = true;
        if (--ptr_push->durability == 0)
        {
            ++durability_count;
            if (TestDurabilities() == STOPPED)
                return STOPPED;
        }
        return NOT_STOPPED;
    }

    IS_STOPPED TestDurabilities() 
    {
        if (durability_count >= K) return STOPPED;
        else return NOT_STOPPED;
    }

#ifdef PS_DEBUG
public:
    void PrintConveyer(int step_count) const
    {
        cout << "===Conveyer State "<< step_count << " ===\n";
        Node* i = ptr_push;

        for (size_t n = 0; n < size; ++n)
        {
            string pad;
            if (i->id <= 9) pad = "  ";
            else if (i->id <= 99) pad = " ";
            else if (i->id <= 999) pad = "";

            cout << pad << i->id;
            if (i == ptr_pop) cout << "||";
            else cout << "|";
            i = i->next;
        }
        cout << '\n';
        for (size_t n = 0; n < size; ++n)
        {
            string pad;
            if (i->durability <= 9) pad = "  ";
            else if (i->durability <= 99) pad = " ";
            else if (i->durability <= 999) pad = "";

            cout << pad << i->durability;
            if (i == ptr_pop) cout << "||";
            else cout << "|";
            i = i->next;
        }
        cout << '\n';
        for (size_t n = 0; n < size; ++n)
        {
            string pad = "   ";
            if (i->occupied) pad = "  R";

            cout << pad;
            if (i == ptr_pop) cout << "||";
            else cout << "|";
            i = i->next;
        }
        
        cout << "\n\n";
    }
#endif //!PS_DEBUG
public:
    Node* ptr_push = nullptr;
    Node* ptr_pop = nullptr;
    deque<Node*> robot_pos;
    int size;
    int durability_count = 0;
    int K;
};


class Director
{
public:
    Director(Conveyer* conv): conv(conv) {};
    int Process() 
    {
        static int step_count = 0;
        while (true)
        {

#ifdef PS_DEBUG
            conv->PrintConveyer(step_count);
#endif // PS_DEBUG
            ++step_count;
            if (conv->Move() == STOPPED) break;
#ifdef PS_DEBUG
            cout << "== After Move\n";
            conv->PrintConveyer(step_count);
#endif // PS_DEBUG
            if (conv->ProceedRobots() == STOPPED) break;
#ifdef PS_DEBUG
            cout << "== After Proceeding Robots\n";
            conv->PrintConveyer(step_count);
#endif // PS_DEBUG
            if (conv->PushRobot() == STOPPED) break;
#ifdef PS_DEBUG
            cout << "== After Pushing Robot\n";
            conv->PrintConveyer(step_count);
            cout << "=========================\n";
#endif // PS_DEBUG

        };

        return step_count;
    }
private:
    Conveyer* conv;
};

#ifdef PS_DEBUG
#include <fstream>
#endif


int main(void)
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

#ifdef PS_DEBUG
        std::ofstream out("BOJ_20055_231206_out.txt");
        std::streambuf* counbuf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());
#endif

    int N; cin >> N; // [1, 100]
    int K; cin >> K; // [1, 2N]

    Director director(new Conveyer(N, K));
    cout << director.Process() << '\n';
    return 0;
}