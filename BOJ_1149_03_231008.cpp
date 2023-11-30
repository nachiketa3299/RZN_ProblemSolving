// [2023-10-08T23:01, 2023-10-08T23:40] (39)

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

enum class HouseColor
{
	Red, Green, Blue
};

int main(void)
{
	// Input
	std::size_t HouseCount; 
	std::cin >> HouseCount; // [2, 1e3]

	std::map<HouseColor, std::vector<std::size_t>> CostsPerColor
	{
		{ HouseColor::Red, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Green, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Blue, std::vector<std::size_t>(HouseCount) },
	};

	for (std::size_t i = 0; i < HouseCount; ++i)
	{
		// [1, 1e3], Natural Number
		std::cin >> CostsPerColor[HouseColor::Red][i];
		std::cin >> CostsPerColor[HouseColor::Green][i];
		std::cin >> CostsPerColor[HouseColor::Blue][i];
	}

	// i ��° ���� ��ĥ�Ѵٰ� ���� (1 < i <= HouseCount)
	// i ��° ���� Red�� ĥ�Ѵٰ� �����ϸ� i - 1 ��°���� BlueȤ�� Green �� �� �ϳ��� ĥ�� ����
	// (�߿�) i ��° ���� Red�� ĥ�ϴµ� �� �������� �� ����� �ּҰ� �ǰ� �Ϸ���, i - 1 ��°�� �ּ� ������� ��. (���� ������ ĥ�߾����� �߿�ġ ����) 
	// (�� �������� �ּҺ���̾��ٸ� ���� Red/Blue/Green�� ĥ�� ������ �� ����� �������� ���ϸ� ��) - �̰� ���� �ȵǸ� �� ���� �� ǯ

	std::set<HouseColor> HouseColors { HouseColor::Red, HouseColor::Green, HouseColor::Blue };
	// i ��° ���� � ���� ĥ�� �� �ּҺ��
	std::map<HouseColor, std::vector<std::size_t>> MinCosts
	{
		{ HouseColor::Red, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Green, std::vector<std::size_t>(HouseCount) },
		{ HouseColor::Blue, std::vector<std::size_t>(HouseCount) },
	};
	
	// ù ��° ���� �׳� ó�� ���� �־��ָ� �װ� �ּҺ����
	for (HouseColor const& CurrentColor: HouseColors)
	{
		MinCosts[CurrentColor].front() = CostsPerColor[CurrentColor].front();
	}

	// �� ��° �� ���ʹ� ���� �ּ� ���� ���ؾ���
	for (std::size_t i = 1; i < HouseCount; ++i)
	{
		for (HouseColor const& CurrentColor : HouseColors)
		{
			// ���� ������ �ƴ� �� ���� �������� �޾ƿ�
			std::set<HouseColor> CurrentColorSet = { CurrentColor };
			std::set<HouseColor> OtherColors; 
			std::set_difference
			(
				HouseColors.begin(), HouseColors.end(),
				CurrentColorSet.begin(), CurrentColorSet.end(),
				std::inserter(OtherColors, OtherColors.begin())
			);
			HouseColor const& OtherColor1 = *(OtherColors.begin());
			HouseColor const& OtherColor2 = *(++OtherColors.begin());

			// �ٽ� ����
			std::size_t PrevMiminumCost = std::min(MinCosts[OtherColor1][i - 1], MinCosts[OtherColor2][i - 1]);
			MinCosts[CurrentColor][i] = PrevMiminumCost + CostsPerColor[CurrentColor][i];
		}
	}

	std::vector<std::size_t> CandidateMinimums
	{
		MinCosts[HouseColor::Red].back(),
		MinCosts[HouseColor::Green].back(),
		MinCosts[HouseColor::Blue].back(),
	};
	std::size_t TotalMinimum = *std::min_element(CandidateMinimums.begin(), CandidateMinimums.end());
	std::cout << TotalMinimum << std::endl;
	return 0;
}