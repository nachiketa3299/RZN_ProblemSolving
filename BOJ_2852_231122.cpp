/// @file BOJ_2852.cpp
/// @date 2023-11-22T13:07 2023-11-12T14:24 1�ð� 17��
/// ���� 2852 (NBA ��)
/// 1�� / 128MB

/*!
* �����̴� NBA���� ���� �� ������
* - (1) ���� �� �ð�
* - (2) ���� ���� ��
* �� ���� �̻��� ��̸� ������ �ִ�.
* �� ���� 48�а� ����ȴ�. 
* �� ���� �� �е��� �̱�� �־��°��� ����ϴ� ���α׷��� �ۼ��Ѵ�.
*/

#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;
using CountType = size_t;
using RawStringTimeType = string;
using TeamNumberType = size_t;
using TimeType = int;

#define TEAM_NONE 0
#define TEAM_1 1
#define TEAM_2 2
#define MAX_TEAM_NUM 3

class Time
{
public:
    Time(): min(0), sec(0) {};
    Time(TimeType min, TimeType sec): min(min), sec(sec) {};
    Time(TimeType total_sec): min(total_sec / 60), sec(total_sec % 60) {};
public:
    TimeType GetTotalSec() const { return this->min * 60 + this->sec; };
    void Flush() { this->min = 0; this->sec = 0; };
public:
    Time& operator+=(const Time& oth)
    {
        TimeType total_sec = this->GetTotalSec() + oth.GetTotalSec();
        this->min = total_sec / 60;
        this->sec = total_sec % 60;
        return *this;
    }
    friend Time operator-(const Time& left, const Time& right)
    {
        return Time(left.GetTotalSec() - right.GetTotalSec());
    }
    friend Time operator+(const Time& left, const Time& right)
    {
        return Time(left.GetTotalSec() + right.GetTotalSec());
    }
    string ToString() const
    {
        return Time::PadTimeString(this->min) + ":" + Time::PadTimeString(this->sec);
    }
    static string PadTimeString(const TimeType& time)
    {
        return time < 10 ? "0" + to_string(time) : to_string(time);
    }
    static Time GetMaxTime()
    {
        return Time(48, 0);
    }
private:
    TimeType min = 0;
    TimeType sec = 0;
};


struct GoalData
{
    /// @short �Է��� �޾Ƽ� �� / �ð� ���·� �����Ѵ�.
    GoalData()
    {
        cin >> this->team_number;
        RawStringTimeType input_time_str; cin >> input_time_str;
        this->time = Time(stoi(input_time_str.substr(0, 2)), stoi(input_time_str.substr(3, 2)));
        return;
    }
    TeamNumberType team_number = 0;
    Time time;
};

void PrintWinningTimePerTeam(const vector<GoalData>& goals)
{
    /// @brief ���� ������ ���
    array<CountType, MAX_TEAM_NUM> scores; scores.fill(0);
    /// @brief ���� �̱�� �ð� ���
    array<Time, MAX_TEAM_NUM> winning_time; 
    /// @brief ������ �̱� �� ���. �ʱ⿣ �ƹ��� �̱�� ���� �����Ƿ� TEAM_NONE
    TeamNumberType last_winning_team = TEAM_NONE;
    /// @brief ������ ���� �ð� ��� (���� ��� �ʱⰪ 00:00)
    Time last_winning_team_time;
    /// @brief �̱�� ���� �ٲ�� �� ������ ���� @ref winning_time �� ��μ� �ջ�.
    Time winning_time_buffer;

    for (const GoalData& goal : goals)
    {
        /// �������ְ�
        ++scores[goal.team_number];

        /// @brief ���� �̱�� �ִ� ���� ����. (������ ��� TEAM_NON)
        TeamNumberType current_winning_team;
        if (scores[TEAM_1] > scores[TEAM_2])      current_winning_team = TEAM_1;
        else if (scores[TEAM_1] < scores[TEAM_2]) current_winning_team = TEAM_2;
        else                                      current_winning_team = TEAM_NONE;

        /// ���� �� ������Ʈ (������ �̱� ���̰� ����� �̱�� ���� �ʴ���, **���� �� ���� ����** �̱� ���̹Ƿ� ������Ʈ ���־����)
        winning_time_buffer += goal.time - last_winning_team_time;
        /// ������ ���� �ð� ������Ʈ
        last_winning_team_time = goal.time;

        /// ������ �̱�� ���� ���� �̱�� ���� �ٸ� ��� -> ���۸� ����ְ� ���ο� �����۾�
        if (last_winning_team != current_winning_team)
        {
            /// ������ �̱�� ���� �� �̱�� �ð��� ���� ���� �߰�����
            winning_time[last_winning_team] += winning_time_buffer;
            /// ���۸� �����
            winning_time_buffer.Flush();
            /// ������ �̱�� ���� ���� �̱��� ������ �ٲ���
            last_winning_team = current_winning_team;
        }
    }

    /// �������� ���۰� ������ �����ֱ� ������ ��� �־�� �Ѵ�.
    winning_time_buffer += Time::GetMaxTime() - last_winning_team_time;
    winning_time[last_winning_team] += winning_time_buffer;

    cout << winning_time[TEAM_1].ToString() << '\n';
    cout << winning_time[TEAM_2].ToString() << '\n';
    return;
}

int main()
{
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr); std::cout.tie(nullptr);
    }

    /// @brief ���� �� Ƚ�� N [1, 100]
    CountType input_goal_count; cin >> input_goal_count;
    vector<GoalData> goals;
    for (CountType i = 0; i < input_goal_count; ++i)
        goals.push_back(GoalData());

    ::PrintWinningTimePerTeam(goals);

    return 0;
}
 
 