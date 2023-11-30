/// @file BOJ_23288_231130.cpp

#define DEBUG
#undef DEBUG

#ifdef DEBUG
#include <string>
#endif

/*!
* ũ�Ⱑ N x M�� ���� (������ ����, ������ ����)
* ������ ��ǥ�� (r, c), r�� �������κ��� ������ ĭ�� ����, c�� �������κ��� ������ ĭ�� ����.
* ���� ���ʿ� �ִ� ĭ�� ��ǥ�� (1, 1)
* ���� ������ �Ʒ��� �ִ� ĭ�� ��ǥ�� (N, M)
* �������� ���� �� ĭ�� �� ���� ũ�Ⱑ ���� �ֻ��� �ϳ�, �� �鿡 1~6 ���� ������ �ϳ��� ����. �������� �Ʒ��� ����.
*  2
* 413
*  5
*  6
* �ֻ����� ���� ���� ������ 1�̰�, ������ �ٶ󺸸� ������ 3�� ���·� ������ �ְ� ������ �ִ� ���� ��ǥ�� (1,1)
* ������ �� ĭ�� ������ ����
* ó�� �ֻ��� �̵� ������ ����
* �ֻ��� �̵� �� ���� ������ ���� �̷����
* - �ֻ����� �̵� �������� �� ĭ ��������. �̵� ���⿡ ĭ�� ������, �ݴ�� �ϰ� �� ĭ ��������.
* - �ֻ����� ������ ĭ (x, y)�� ���� ������ ȹ���Ѵ�.
* - �ֻ����� �Ʒ��鿡 �ִ� ���� A�� �ֻ����� �ִ� ĭ (x, y)�� �ִ� ���� B�� ���� �̵� ������ �����Ѵ�.
*   - A > B �� �̵� ������ 90�� �ð� �������� ȸ����Ų��.
*   - A < B �� �̵� ������ 90�� �ݽð� �������� ȸ����Ų��.
*   - A = B �� �̵� ���⿡ ��ȭ�� ����.
* ĭ (x, y)�� ���� ������ ������ ���� ���Ѵ�.
* (x, y)�� �ִ� ������ B��� �� ��, (x, y)���� �������� �������� ������ �̵��� �� �ִ� ĭ�� �� C�� ��� ���Ѵ�.
* �� �� �̵��� �� �ִ� ĭ���� ��� ���� B�� �־�� �Ѵ�. ���⼭ ������ B�� C�� ���� ���̴�.
* ������ ũ��� �� ĭ�� �ִ� ����, �ֻ����� �̵� Ƚ�� K�� �־��� ��, �� �̵����� ȹ���ϴ� ������ ���� ���Ѵ�.
*/

#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

using SizeType = int;
using CountType = int;
using ScoreType = int;

struct Position
{
public:
    Position(SizeType v = 0, SizeType h = 0):v(v), h(h) {}
public:
    void MoveToNorth() { this->v += -1; return; }
    void MoveToSouth() { this->v += +1; return; }
    void MoveToEast() { this->h += +1; return; }
    void MoveToWest() { this->h += -1; return; }
public:
    Position operator+(const Position& right) const { return Position(this->v + right.v, this->h + right.h); };
public:
    SizeType v = 0;
    SizeType h = 0;
};

enum EDiceDirection { East = 0, North, West, South, DirectionMax };
enum EDiceSides { Top = 0, Bottom, Right, Left, Up, Down, SideMax };

class Dice
{
public:
    Dice()
    {
        /*!
        * �ֻ����� �Ʒ�ó�� ���ǵȴ�.
        *          [  UP  ]
        * [ LEFT ] [ TOP  ] [ RIGHT]
        *          [ DOWN ]
        *          [BOTTOM]
        */
        this->sides[Top]    = 1;
        this->sides[Bottom] = 6;
        this->sides[Left]   = 4;
        this->sides[Right]  = 3;
        this->sides[Up]     = 2;
        this->sides[Down]   = 5;
        return;
    }
    Dice(const Dice& dice): 
        sides(dice.sides),
        position(dice.position),
        direction(dice.direction)
    {}
public:
    const Position& GetPosition() const { return this->position; };
    const ScoreType& GetBottomScore() const { return this->sides[Bottom]; };
private:
    const ScoreType GetCachedBottom() const { return this->bottom_cache; };
    void CacheBottom() { this->bottom_cache = this->GetBottomScore(); return; };
public:
    void InvertDirection()
    {
        switch (this->direction)
        {
        case East: 
            this->direction = West; 
            break;
        case North: 
            this->direction = South; 
            break;
        case West: 
            this->direction = East; 
            break;
        case South: 
            this->direction = North; 
            break;
        default:
        case DirectionMax:
            return;
        }
        return;
    }
    /*!
     * @brief �ֻ����� ������ �ð����(Clockwise)���� 90�� ������.
    */
    void RotateDirectionC90()
    {
        this->direction = (this->direction - 1 < 0 ? South : static_cast<EDiceDirection>(this->direction - 1));
        return;
    }
    /*!
     * @brief �ֻ����� ������ �ݽð����(Counter-Clockwise)���� ������.
    */
    void RotateDirectionCC90()
    {
        this->direction = (this->direction + 1 == DirectionMax ? East : static_cast<EDiceDirection>(this->direction + 1));
        return;
    }
    /*!
     * @brief �ֻ����� ������ �������� ������.
    */
    void Roll()
    {
        this->CacheBottom();
        switch (this->direction)
        {
        case East: 
            this->RollToEast(); 
            break;
        case North: 
            this->RollToNorth(); 
            break;
        case West: 
            this->RollToWest(); 
            break;
        case South: 
            this->RollToSouth(); 
            break;

        default:
        case DirectionMax:
            return;
        }
        return;
    }
#ifdef DEBUG
public:
    void PrintDice() const
    {
        cout << "** Dice State:\n";
        cout << "  " << this->sides[Up] << '\n';
        cout << this->sides[Left] << " " << this->sides[Top] << " " << this->sides[Right] << '\n';
        cout << "  " << this->sides[Down] << '\n';
        cout << "  " << this->sides[Bottom] << '\n';
        return;
    }
    string GetDirectionString() const
    {
        switch (this->direction)
        {
        case East: 
            return "East";
        case North: 
            return "North";
        case South: 
            return "South";
        case West: 
            return "West";
        default: 
            break;
        }
        return "ERROR";
    }
#endif

private:
    void RollToNorth() // ��
    {
        this->position.MoveToNorth();

        this->sides[Bottom]     = this->sides[Up];
        this->sides[Up]         = this->sides[Top];
        this->sides[Top]        = this->sides[Down];
        this->sides[Down]       = this->GetCachedBottom();
        return;
    }
    void RollToSouth() // ��
    {
        this->position.MoveToSouth();

        this->sides[Bottom]     = this->sides[Down];
        this->sides[Down]       = this->sides[Top];
        this->sides[Top]         = this->sides[Up];
        this->sides[Up]        = this->GetCachedBottom();
        return;
    }
    void RollToWest() // ��
    {
        this->position.MoveToWest();

        this->sides[Bottom]     = this->sides[Left];
        this->sides[Left]       = this->sides[Top];
        this->sides[Top]         = this->sides[Right];
        this->sides[Right]      = this->GetCachedBottom();
        return;
    }
    void RollToEast() // ��
    {
        this->position.MoveToEast();

        this->sides[Bottom]     = this->sides[Right];
        this->sides[Right]      = this->sides[Top];
        this->sides[Top]         = this->sides[Left];
        this->sides[Left]       = this->GetCachedBottom();
        return;
    }
private:
    Position position;
    EDiceDirection direction = East;
    array<ScoreType, SideMax> sides;
private:
    ScoreType bottom_cache =0;
};

class Map
{
public:
    Map(vector<vector<ScoreType>>& map_scores):
        map_scores(move(map_scores))
    { };
    /*!
     * @brief BFS ������� ���������鼭 ���� ���ڸ� ���� Ÿ���� Ž����
     * @param position ���� Ÿ���� ��ġ
     * @return ���� Ÿ�Ͽ��� ������������ �����Ͽ� ���������鼭 ���� Ÿ�ϰ� ������ ���� Ÿ���� ���� (���� Ÿ���� �����ϹǷ� �ּҴ� 1)
    */
    CountType GetAdjacentSameScoreCounts(const Position& position)
    {
        const ScoreType& score_target = this->GetScoreByPosition(position);

        queue<Position> to_visit; to_visit.push(position);
        vector<vector<bool>> visited(this->GetVSize(), vector<bool>(this->GetHSize(), false));

        vector<Position> hit_targets;
        hit_targets.push_back(position);

        while (!to_visit.empty())
        {
            const Position& visiting = to_visit.front();
            visited[visiting.v][visiting.h] = true;
            vector<Position> adjacents;
            adjacents.push_back(visiting + Position(0, -1));
            adjacents.push_back(visiting + Position(0, +1));
            adjacents.push_back(visiting + Position(+1, 0));
            adjacents.push_back(visiting + Position(-1, 0));

            for (const auto& adjacent : adjacents)
            {

                if (!this->IsInBound(adjacent)) continue;
                if (!(this->GetScoreByPosition(adjacent) == score_target)) continue;
                if (visited[adjacent.v][adjacent.h]) continue;

                visited[adjacent.v][adjacent.h] = true;
                to_visit.push(adjacent);
                hit_targets.push_back(adjacent);
            }
            to_visit.pop();
        }

        return hit_targets.size();
    }
public:
    const ScoreType& GetScoreByPosition(const Position& pos) const { return this->map_scores[pos.v][pos.h]; };
public:
    bool IsInBound(const Position& pos) const { return this->IsInHBound(pos) && this->IsInVBound(pos); };
private:
    bool IsInVBound(const Position& pos) const { return pos.v < this->GetVSize() && pos.v >= 0; };
    bool IsInHBound(const Position& pos) const { return pos.h < this->GetHSize() && pos.h >= 0; }
public:
    SizeType GetVSize() const { return this->map_scores.size(); }
    SizeType GetHSize() const { return this->map_scores.front().size(); };
#ifdef DEBUG
    void PrintMapWithPosition(const Position& pos) const
    {
        for (SizeType v = 0; v < this->GetVSize(); ++v)
        {
            for (SizeType h = 0; h < this->GetHSize(); ++h)
            {
                string del_start = " ";
                string del_end = " ";
                if (v == pos.v && h == pos.h)
                {
                    del_start = "[";
                    del_end = "]";
                }
                cout << del_start << this->GetMapScoreByPosition(Position(v, h)) << del_end;
            }
            cout << '\n';
        }
        return;
    }
#endif
private:
    vector<vector<ScoreType>> map_scores;
};

class Game
{
public:
    Game(Map* map, Dice* dice):
        map(map), dice(dice)
    {};
public:
    void CalculateScore(CountType& moving_count) 
    {
#ifdef DEBUG
        cout << "=== INITIAL STATE ===\n";
        map->PrintMapWithPosition(dice->GetPosition());
        dice->PrintDice();
        cout << '\n';
#endif
        for (CountType c = 0; c < moving_count; ++c)
        {
            /// (1) MOVE DICE
            Dice tdice(*this->dice);
            tdice.Roll();
            /// �ֻ����� �ӽ÷� �̸� ��������, ���� �� ������ ������ ����(Invert)��Ų��.
            if (!this->IsInMapBound(tdice.GetPosition()))
                this->dice->InvertDirection();
            this->dice->Roll();

            /// (2) CALCULATE SCORE
            const Position& dice_pos = this->dice->GetPosition();
            const ScoreType& map_score = this->map->GetScoreByPosition(dice_pos);
            const CountType same_count = this->map->GetAdjacentSameScoreCounts(dice_pos);

            this->total_score += map_score * same_count;

            /// (3) SET DIRECTION
            const ScoreType& A = this->dice->GetBottomScore();
            const ScoreType& B = map_score;
            if (A > B)
                this->dice->RotateDirectionC90();
            else if (A < B)
                this->dice->RotateDirectionCC90();
            else /* Do Nothing */;
#ifdef DEBUG
            cout << "=== MovingNumber(" << c + 1 << ")===\n";
            map->PrintMapWithPosition(dice->GetPosition());
            dice->PrintDice();
            cout << "- DicePosition: " << "(" << dice->GetPosition().v <<"/" << this->map->GetVSize() - 1 << ", " << dice->GetPosition().h << "/" << this->map->GetHSize() - 1 << ")\n";
            cout << "- DiceRollDirection: " << dice->GetDirectionString() << '\n';
            cout << "- A-dbottom(" << A << "), B-mapscore(" << B << ")\n\n";
#endif
        }
        return;
    };
    ScoreType GetTotalScore() const { return this->total_score; };
public:
    bool IsInMapBound(const Position& pos) const { return this->map->IsInBound(pos); };
private:
    Map* map;
    Dice* dice;
    ScoreType total_score = 0;
};

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /// === INPUT === ///
    SizeType map_v_size; cin >> map_v_size; //<  [2, 20]
    SizeType map_h_size; cin >> map_h_size; //<  [2, 20]
    CountType moving_count; cin >> moving_count; //< [1, 1e3]

    vector<vector<ScoreType>> tmap_scores(map_v_size, vector<ScoreType>(map_h_size));

    for (SizeType v = 0; v < map_v_size; ++v)
        for (SizeType h = 0; h < map_h_size; ++h)
            cin >> tmap_scores[v][h]; // [1, 10] Natural Number

    /// === PROCESS === ///
    Map map(tmap_scores); Dice dice;
    Game game(&map, &dice);
    game.CalculateScore(moving_count); //< ��κ��� ������ ���⿡ ����

    /// === OUTPUT === ///
    cout << game.GetTotalScore() << '\n';

    return 0;
}

