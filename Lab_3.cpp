#include <vector>
#include <iostream> 
#include <cmath> 
using namespace std; 
int bigo = 0;
int partition(vector<int>& vec, int low, int high)
{
	int pivot = vec[high]; int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		++bigo;
		if (vec[j] >= pivot)
		{
			i++;
			swap(vec[i], vec[j]);
		}
	}
	swap(vec[i + 1], vec[high]); return (i + 1);
}
void quickSort(vector<int>& vec, int low, int high)
{
	++bigo;
	if (low < high)
	{
		int pi = partition(vec, low, high); quickSort(vec, low, pi - 1); quickSort(vec, pi + 1, high);
	}

}
void print_dvector(const vector<vector<int>>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		cout << i + 1 << ") | ";
		for (int j = 0; j < vec[i].size(); ++j)
		{
			cout << vec[i][j] << " | ";
		}
		cout << "\n";
	}
}
void NFA(vector<int>& elements, const bool det, const int max_size)
{
	if (det) quickSort(elements, 0, elements.size() - 1); vector<vector<int>> containers(1);
	int current_size = 0;
	for (int i = 0; i < elements.size(); ++i)
	{
		++bigo;
		if (current_size + elements[i] > max_size)
		{
			current_size = 0; containers.push_back(vector<int>(0));
		}
		current_size += elements[i];
		containers[containers.size() - 1].push_back(elements[i]);
	}
	cout << "NFA:" << "\n"; print_dvector(containers);
	cout << "O(n) : " << bigo << "\n";
}

void FFA(vector<int>& elements, const bool det, const int max_size)
{
	if (det) quickSort(elements, 0, elements.size() - 1); vector<vector<int>> containers(1);
	vector<int> sums(1); int current_size = 0;
	for (int i = 0; i < elements.size(); ++i)
	{
		bool find_container = true;
		++bigo;
		if (current_size + elements[i] > max_size)
		{
			for (int j = 0; j < containers.size() - 1; ++j)
			{
				++bigo;
				if (sums[j] + elements[i] <= max_size)
				{
					containers[j].push_back(elements[i]); sums[j] += elements[i]; find_container = false;
					break;
				}
			}
			if (find_container)
			{
				current_size = 0; containers.push_back(vector<int>(0)); sums.push_back(0);
			}
		}
		if (find_container)
		{
			current_size += elements[i];

			containers[sums.size() - 1].push_back(elements[i]); sums[sums.size() - 1] = current_size;
		}
	}
	cout << "FFA:" << "\n"; print_dvector(containers);
	cout << "O(n) : " << bigo << "\n";
}
void WFA(vector<int>& elements, const bool det, const int max_size)
{
	if (det) quickSort(elements, 0, elements.size() - 1); vector<vector<int>> containers(1);
	vector<int> sums(1); int current_size = 0;
	for (int i = 0; i < elements.size(); ++i)
	{
		bool find_container = true;
		++bigo;
		if (current_size + elements[i] > max_size)
		{
			int min = 0;
			for (int j = 1; j < containers.size() - 1; ++j)
			{
				++bigo;
				if (sums[j] < sums[min])
				{
					min = j;
				}
			}
			++bigo;
			if (sums[min] + elements[i] <= max_size)
			{
				containers[min].push_back(elements[i]);

				sums[min] += elements[i]; find_container = false;
			}
			if (find_container)
			{
				current_size = 0; containers.push_back(vector<int>(0)); sums.push_back(0);
			}
		}
		if (find_container)
		{
			current_size += elements[i];
			containers[sums.size() - 1].push_back(elements[i]); sums[sums.size() - 1] = current_size;
		}
	}
	cout << "WFA:" << "\n"; print_dvector(containers);
	cout << "O(n) : " << bigo << "\n";
}
void BFA(vector<int>& elements, const bool det, const int max_size)
{
	if (det) quickSort(elements, 0, elements.size() - 1); vector<vector<int>> containers(1);
	vector<int> sums(1); int current_size = 0;
	for (int i = 0; i < elements.size(); ++i)
	{
		bool find_container = false;
		++bigo;
		if (current_size + elements[i] > max_size)
		{

			int max = 0;
			for (int j = 0; j < containers.size() - 1; ++j)
			{
				++bigo;
				if (sums[j] + elements[i] <= max_size)
				{
					max = j; find_container = true; break;
				}
			}
			for (int j = max; j < containers.size() - 1 && find_container; ++j)
			{
				++bigo;
				if (sums[j] > sums[max] && sums[j] + elements[i] <= max_size)
				{
					max = j;
				}
			}
			if (find_container)
			{
				containers[max].push_back(elements[i]); sums[max] += elements[i];
			}
			if (!find_container)
			{
				current_size = 0; containers.push_back(vector<int>(0)); sums.push_back(0);
			}
		}

		if (!find_container)
		{
			current_size += elements[i];
			containers[sums.size() - 1].push_back(elements[i]); sums[sums.size() - 1] = current_size;
		}
	}
	cout << "BFA:" << "\n"; print_dvector(containers);
	cout << "O(n) : " << bigo << "\n";
}
int main()
{
	// без впорядкування
	vector<int> elements = { 51, 78, 9, 53, 81, 14, 38, 89, 26, 67, 47, 23, 87, 31, 32, 22, 81, 75, 50, 79 };
	vector<int> elements2 = { 90, 54, 50, 31, 13, 57, 94, 81, 81, 3, 20, 33, 82, 81, 87, 15, 96, 25, 4, 22 };
	vector<int> elements3 = { 92, 51, 97, 32, 34, 81, 6, 15, 57, 8, 95, 99, 62, 97, 83, 76, 54, 77, 9, 87 };
	vector<int> elements4 = { 51, 78, 9, 53, 81, 14, 38, 89, 26, 67, 47, 23, 87, 31, 32, 22, 81, 75, 50, 79, 90, 54,
	50, 31, 13, 57, 94, 81, 81, 3, 20, 33, 82, 81, 87, 15, 96, 25, 4, 22, 92, 51, 97, 32, 34, 81, 6, 15, 57, 8, 95, 99, 62,
	97, 83, 76, 54, 77, 9, 87 };


	// з впорядкованням
	vector<int> elements01 = { 89, 87, 81, 81, 79, 78, 75, 67, 53, 51, 50, 47, 38, 32, 31, 26, 23, 22, 14, 9 };
	vector<int> elements02 = { 96, 94, 90, 87, 82, 81, 81, 81, 57, 54, 50, 33, 31, 25, 22, 20, 15, 13, 4, 3 };
	vector<int> elements03 = { 99, 97, 97, 95, 92, 87, 83, 81, 77, 76, 62, 57, 54, 51, 34, 32, 15, 9, 8, 6 };
	vector<int> elements04 = { 89, 87, 81, 81, 79, 78, 75, 67, 53, 51, 50, 47, 38, 32, 31, 26, 23, 22, 14, 9, 96, 94,
	90, 87, 82, 81, 81, 81, 57, 54, 50, 33, 31, 25, 22, 20, 15, 13, 4, 3, 99, 97, 97, 95, 92, 87, 83, 81, 77, 76, 62, 57, 54,
	51, 34, 32, 15, 9, 8, 6 };


	// невпорядковані NFA(elements, false, 100);
	FFA(elements, false, 100);
	WFA(elements, false, 100);
	BFA(elements, false, 100);
	NFA(elements2, false, 100);

	FFA(elements2, false, 100);
	WFA(elements2, false, 100);
	BFA(elements2, false, 100);
	NFA(elements3, false, 100);
	FFA(elements3, false, 100);
	WFA(elements3, false, 100);
	BFA(elements3, false, 100);
	NFA(elements4, false, 100);
	FFA(elements4, false, 100);
	WFA(elements4, false, 100);
	BFA(elements4, false, 100);


	// впорядковані NFA(elements01, false, 100);
	FFA(elements01, false, 100);
	WFA(elements01, false, 100);
	BFA(elements01, false, 100);
	NFA(elements02, false, 100);
	FFA(elements02, false, 100);
	WFA(elements02, false, 100);
	BFA(elements02, false, 100);
	NFA(elements03, false, 100);
	FFA(elements03, false, 100);
	WFA(elements03, false, 100);
	BFA(elements03, false, 100);
	NFA(elements04, false, 100);
	FFA(elements04, false, 100);
	WFA(elements04, false, 100);
	BFA(elements04, false, 100);
	return 0;
}
