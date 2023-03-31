#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <random>

#define ever (;;)
#define range(container) container.begin(), container.end()

std::ostream& operator<<(std::ostream& os, std::vector<int>& v) {
	std::copy(range(v), std::ostream_iterator<int>(os, " "));
	return os;
}

std::istream& operator>>(std::istream& is, std::vector<int>& v) {
	std::copy(std::istream_iterator<int> (is), std::istream_iterator<int>(), std::back_inserter(v));
	return is;
}

int main() {
	// Создайте последовательность П1 целых чисел от 1 до 10;
	std::vector<int> seq1(10);
	std::iota(range(seq1), 1);  // std::generate(range(seq1), [](auto i) {return 1; });


	// Добавьте еще несколько чисел в конец П1 из cin;
	std::cin >> seq1;


	// Перемешайте П1 случайным образом;
	std::random_device d;
	std::mt19937_64 mt(d());
	std::shuffle(range(seq1), mt);
	std::cout << "sequence 1: " << seq1 << std::endl;


	// Удалите дубликаты из П1;
	seq1.erase(std::unique(range(seq1), [](auto a, auto b) {return a == b; }), end(seq1));
		// удалятся дубликаты, стоящие рядом
		// sort(range(seq1)); нужно сначала отсортировать, чтобы удалить все дубликаты, с помощью этой функции


	// Подсчитайте количество нечетных чисел в П1;
	std::cout << "amount of odd elements: " <<
		std::count_if(range(seq1), [](auto item) {return !(item % 2); }) << std::endl;
	   

	// Определите минимальное и максимальное значения в П1;
	auto result = std::minmax_element(range(seq1));
	std::cout << "minimum element: " << *result.first << ", maximum element: " << *result.second << std::endl;


	// Попробуйте найти хотя бы одно простое число в П1;
	auto it =
		std::find_if(range(seq1), [&](auto item) {
		int flag = true;
		for (int i = 2; i < sqrt(seq1.size()); i++) {
			if (item % i == 0) {
				flag = false;
			};
		};
		return flag;
			});
	std::cout << "first prime number: " << *it << std::endl;
	 

	// Замените все числа в П1 их квадратами;
	std::vector<int> squares;

	std::transform(range(seq1), std::back_inserter(squares), [](auto item) {
		return item * item;
		});

	std::cout << "sequence of squares: " << squares << std::endl;
	
	
	// Создайте последовательность П2 из N случайных чисел, где N - длина П1;
	std::vector<int> seq2(seq1.size());
	std::uniform_int_distribution<int> distribution(1, 100);
	std::generate(range(seq2), [&]() {return distribution(mt);});
	std::cout << "vector of random numbers: " << seq2 << std::endl;


	// Вычислите сумму чисел в П2;
	int init = 0;
	init = std::accumulate(range(seq2), init);
	std::cout << "sum of elements in sequence 2: " << init << std::endl;


	// Замените первые несколько чисел в П2 числом 1;
	int n = 4;
	std::fill(seq2.begin(), seq2.begin() + n, 1);
	std::cout << "modified sequence 2: " << seq2 << std::endl;


	// Создайте последовательность ПЗ как разность П1 и П2;
	size_t size = seq1.size();
	std::vector<int> seq3(size);
	for (int i = 0; i < size; i++) {
		seq3[i] = seq1[i] - seq2[i];
	}
	std::cout << "sequence 3: " << seq3 << std::endl;

	// Заменить каждый отрицательный элемент в ПЗ нулем;
	std::replace_if(range(seq3), [](auto& item) {return item < 0; }, 0);
	std::cout << "negative elements replaced with zero: " << seq3 << std::endl;

	// Удалите полностью все нулевые элементы из ПЗ;
	seq3.erase(std::remove_if(range(seq3), [](auto& item) {return item == 0; }), end(seq3));
	std::cout << "zeros deleted: " << seq3 << std::endl;

	// Измените порядок следования элементов в ПЗ на обратный;
	std::reverse(range(seq3));
	std::cout << "sequence 3 reversed: " << seq3 << std::endl;

	// Определите быстро топ - 3 наибольших элемента в ПЗ;
	std::sort(range(seq3), [](auto& a, auto& b) {return a > b; });
	auto iter = seq3.begin();
	std::cout << "max 1: " << *iter << "\n"
		<< "max 2: " << *(iter + 1) << "\n"
		<< "max 3: " << *(iter + 2) << std::endl;
		// быстрый для небольшого количества элементов

	// Отсортируйте полностью П1 и П2 по возрастанию;
	std::sort(range(seq1));
	std::sort(range(seq2));
	std::cout << "sorted sequence 1: " << seq1 << std::endl;
	std::cout << "sorted sequence 2: " << seq2 << std::endl;

	// Создайте последовательность П4 как слияние П1 и П2;
	std::vector<int> seq4(seq1.size() + seq2.size());
	std::merge(range(seq1), range(seq2), seq4.begin());
	std::cout << "merge of sequences 1 and 2: " << seq4 << std::endl;

	// Определите диапазон для упорядоченной вставки числа 1 в П4;
	int count = std::count_if(range(seq4), [](auto &iter) {return iter == 1; });
	std::cout << "range for the ordered insertion of the number 1 in sequence 4: [0, " << count << "]" << std::endl;

}
