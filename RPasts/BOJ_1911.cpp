// [2023-10-09T13:45, 2023-10-09T14:45]
#include <iostream>
#include <vector>
#include <algorithm>

struct FHoleInfo
{
	long long StartPos;
	long long EndPos;
	static bool Compare(FHoleInfo const& Op1, FHoleInfo const& Op2)
	{
		return Op1.StartPos < Op2.StartPos;
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false); std::cin.tie(NULL); std::cout.tie(NULL);
	// HoleCount in [1, 1e4]
	// CoverCount in [1, 1e6]
	std::size_t HoleCount, CoverLength; std::cin >> HoleCount >> CoverLength;
	std::vector<FHoleInfo> HoleInfos(HoleCount);
	for (FHoleInfo& Info : HoleInfos)
	{
		std::cin >> Info.StartPos >> Info.EndPos;
		// ������ ���� ��ġ�� �ʴ´�
	}
	std::sort(HoleInfos.begin(), HoleInfos.end(), FHoleInfo::Compare);

	// ��ġ���� �Է��ֳ� �ƴϳ�
	std::vector<bool> IsHoled(HoleInfos.back().EndPos + 1, false);

	for (FHoleInfo const& Info : HoleInfos)
	{
		for (long long i = Info.StartPos; i < Info.EndPos; ++i)
		{
			IsHoled.at(i) = true;
		}
	}

	long long CoverCount = 0;
	for (long long i = 0; i < IsHoled.size();)
	{
		// ���� �ƴϸ� �� �Ѿ��
		if (!IsHoled[i])
		{
			++i;
			continue;
		}

		// �����̸� ... �κ��� ���� ������Ű��, i�� �κ��� ���� �ٷ� ��������
		CoverCount++;
		i += CoverLength;
	}
	std::cout << CoverCount << std::endl;
	return 0;
}