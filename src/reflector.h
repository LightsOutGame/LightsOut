#include <unordered_map>
#include <string>
#include <type_traits>
#include <iostream>

using namespace std;

struct reflector {

	template <class T>
	static void getAllFields()
	requires (is_same<decltype(T::field_data), const unordered_map<string, string>>::value)
	{
		for (auto& it: T::field_data) {
			cout << it.first << endl;
		}
	}

};