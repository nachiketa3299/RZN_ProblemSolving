#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <sstream>
#include <chrono>
#include <cmath>
#include <stack>

using namespace std;
using CarID = string;
using FeePolicy = vector<int>;

enum class InOut { IN, OUT };
enum FP
{
    BASIC_TIME=0,
    BASIC_FEE,
    PER_MIN,
    PER_FEE
};

/// @short �ð� ������ ǥ���ϴ� ����ü�̴�. time_t�� ���� ���۷� �۵��Ѵ�.
/// @todo time_t�� chrono ������ ���� �����ϰ� ������ �����ؾ� �ڴٰ� �����ߴµ� �˾ƺ��� �� �� ����.
struct TimeRange
{
    /// @param[in] in_time_str ���� �ð��� ���� ���ڿ��̴�.
    /// @param[in] out_time_str ���� �ð��� ���� ���ڿ��̴�. ���� ���� �ð��� �������� �ʾҴٸ�, �⺻������ 23:59�� ������ ������ �����Ѵ�.
    TimeRange(const string& in_time_str, const string& out_time_str="23:59"): in_time(TimeRange::make_time(in_time_str)), out_time(TimeRange::make_time(out_time_str)) {};

    /// @param[in] io �������� ���������� ���� �����̴�.
    /// @param[in] time_str �ð��� ���� ���ڿ��̴�.
    /// @todo ���� io�� �׻� InOut::OUT�϶��� ���δ�.
    void SetTime(const InOut& io, const string& time_str)
    {
        switch (io)
        {
        case InOut::IN:
            in_time = TimeRange::make_time(time_str);
            break;
        default:
        case InOut::OUT:
            out_time = TimeRange::make_time(time_str);
            break;
        }
    }
    /// @short ���� �ð� ������ �� �ð�(out_time)���� ���� �ð�(in_time)�� �� ���� ������ ����ȯ �Ͽ� ��ȯ�Ѵ�.
    /// @return �� �ð��� ���� �ð��� �� (��)
    int GetTimeDiffInMin() const
    {
        auto min_diff = chrono::minutes(static_cast<int>(difftime(this->out_time, this->in_time) / 60));
        return min_diff.count();
    }
    time_t in_time;
    time_t out_time;
private:
    /// @param[in] time_str "HH:MM" ���·� �־����� �ð� ���ڿ��̴�.
    /// @return time_t ������ �ð� �����̴�.
    /// @todo tm, time_t, �̰� �ٽ� ã�ƺ� ��.
    static time_t make_time(const string& time_str)
    {
        struct tm t = {};
        istringstream ss(time_str); ss >> get_time(&t, "%H:%M");
        time_t time = mktime(&t);
        return time;
    }
};

///  @short � �Ϸù�ȣ�� ���� ������ ��� ������ ����� �����ϰ� �ִ� ����ü
struct ParkData
{
    /// @short ���ÿ� ����ִ� �ð� ������ ���� ��� ��å�� ���� ���� ��������� ����Ѵ�.
    /// @param[in] f ��� ��å. ���� ���� 4�� ���� �迭�̸�, �� �ε����� ������ ������ #FP�� �����Ѵ�.
    /// @see @ref FP
    int GetParkFee(const FeePolicy& f)
    {
        int total_fee = f[BASIC_FEE];
        int total_park_time = 0;

        /// ���� �ð� ������ ���� ������ �� �����ð��� ����Ѵ�.
        while (!this->time_ranges.empty())
        {
            total_park_time += this->time_ranges.top().GetTimeDiffInMin();
            this->time_ranges.pop();
        }

        /// ���� ��ü ���� �ð��� ��� ��å�� �⺻ ���� �ð��� �ʰ��ߴٸ� ������ �����ؼ� �߰������ ����Ѵ�.
        if (total_park_time > f[BASIC_TIME])
        {
            int over_time = total_park_time - f[BASIC_TIME];
            int over_fee = (int)(ceil((double)over_time / f[PER_MIN])) * f[PER_FEE];
            total_fee += over_fee;
        }

        return total_fee;
    }

    /// @param[in] io InOut::IN, InOut::OUT �� �� �ϳ��� ������ �����̴�.
    /// @param[in] time_str "HH:MM" ���·� ������ �ð� ���ڿ��̴�.
    /// @details ������ ��� TimeRange(����) ���·� time_ranges ���ÿ� Ǫ���Ѵ�. ������ ��� time_ranges ������ ž�� out_time�� �����Ѵ�. out_time�� �⺻������ 23:59�� �ʱ�ȭ �Ǿ� �ִ�.
    void SetTimeData(const InOut& io, const string& time_str)
    {
        switch (io)
        {
        case InOut::IN:
            this->time_ranges.push(TimeRange(time_str));
            break;
        default:
        case InOut::OUT:
            this->time_ranges.top().SetTime(io, time_str);
            break;
        }
        return;
    }

    /// @short �� ������ ������ ������ �� �� �ֱ� ������ �ð� ������ �����̳ʿ� ���� �Ѵ�.
    /// @todo ��� stack���� ������ �ǵ��� stack�� LIFO(Last-In First-Out) �����̱� �����̰�, �����Ͱ� �׻� ����->����->����->���� �� �Ͼ�� �����̾��µ� ��� �� ������ ������ �������� �� �ִ��� �߰��� �˾Ƽ� (����, ����)->(����, ����) ���°� �Ǿ���ȴ�. �̰� �ѹ� �ǹ̿� �°� �ٽ� �����غ���.
    stack<TimeRange> time_ranges;
};

namespace raw_len
{
    constexpr size_t time = 5;
    constexpr size_t id = 4;
}

vector<int> solution(FeePolicy fees, vector<string> records)
{
    vector<int> answer;

    /// ���� ��ȣ�� ���� ������������ ���ĵǾ�� �ϹǷ�, ���� ��ȣ(CarID)�� ���� �� �������� �����͸� ����
    /// @todo Lexiographical Order? ������ ���� ���� ������ �˾ƺ� ��
    map<CarID, ParkData> park_datas; 

    /// records�� ������ ���� ������ ���� ���ڿ����� �����̹Ƿ� ��ȸ�ϸ鼭 ������ ������
    for (const auto& record : records)
    {
        /// ���� ���� ������ "12:39 1234 In" �����̴�.
        /// records[0:5]�� ���� �ð��̴�. ��) "12:39"
        const string raw_time_str = record.substr(0                                  , raw_len::time);
        /// records[6:10]�� ���� ��ȣ(CarID)�̴�. ��) "1234"
        const string raw_id_str   = record.substr(raw_len::time + 1                  , raw_len::id  );
        /// records[11:-1]�� ���� ���� ������, ���� �������� ���� �����̴�. "In"�̸� IN����, "Out"�̸� OUT���� ó���Ѵ�.
        const InOut  io           = record.substr(raw_len::time + 1 + raw_len::id + 1, -1           ).front() == 'I' ? InOut::IN : InOut::OUT;

        /// Ư�� ���� ��ȣ�� ���� ������ �����ð� ������ �����Ѵ�. 
        park_datas[raw_id_str].SetTimeData(io, raw_time_str);
    }

    /// �� �������� park_datas�� ���� ��ȣ(CarID)�� ���� ���� �ð� ������ �Ϻ��ϰ� ������ �ְ� �ȴ�.
    for (auto& park_data : park_datas)
    {
        /// �� ������ ���ؼ� ��� ��å fees�� ����� ����Ѵ�.
        answer.push_back(park_data.second.GetParkFee(fees));
    }
    return answer;
}
