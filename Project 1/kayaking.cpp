#include <iostream>
#include <algorithm>
#include <vector>

bool possible(int v, int people, int strength, int speed, int sorted_people, int sorted_strength, int sorted_speed, std::vector<int> c) {
	std::sort(c.begin(), c.end());

	for (int i = 0; i < c.size(); i++) {
		if ( people >= 2 && c.at(i)*(sorted_people + sorted_people) >= v ) {
			people-=2;
		}
		else if ( people >= 1 && strength >= 1 && c.at(i)*(sorted_people + sorted_strength) >= v ) {
			people--;
			strength--;
		}
		else if ( (sorted_people + sorted_speed) < (sorted_strength + sorted_strength) ) {
			if ( people >= 1 && speed >= 1 && c.at(i)*(sorted_people + sorted_speed) >= v) {
				people--;
				speed--;
			}
			else if (strength >=2 && c.at(i)*(sorted_strength + sorted_strength) >= v) {
				strength-=2;
			}
			else if (strength >=1 && speed >= 1 && c.at(i)*(sorted_strength + sorted_speed) >= v) {
				strength--;
				speed--;
			}
			else if (speed >= 2 && c.at(i)*(sorted_speed + sorted_speed) >= v) {
				speed-=2;
			}
			else {
				return false;
			}
		}
		else if (strength >=2 && c.at(i)*(sorted_strength + sorted_strength) >= v) {
			strength-=2;
		}
		else if (people >=1 && speed >=1 && c.at(i)*(sorted_people + sorted_speed) >= v) {
			people--;
			speed--;
		}
		else if (strength >=1 && speed>=1 && c.at(i)*(sorted_strength + sorted_speed) >= v) {
			strength--;
			speed--;
		}
		else if (speed >= 2 && c.at(i)*(sorted_speed + sorted_speed) >= v) {
			speed-=2;
		}
		else {
			return false;
		}
	}	
	
	return true;
}

int find_min_v(int people, int strength, int speed, int sorted_people, int sorted_strength, int sorted_speed, std::vector<int> c) {
	
	std::vector<int> speeds;
	for (int i = 0; i < c.size(); i++) {
		speeds.push_back(c.at(i)*(sorted_people+sorted_people));
		speeds.push_back(c.at(i)*(sorted_people+sorted_strength));
		speeds.push_back(c.at(i)*(sorted_people+sorted_speed));
		speeds.push_back(c.at(i)*(sorted_strength+sorted_strength));
		speeds.push_back(c.at(i)*(sorted_strength+sorted_speed));
		speeds.push_back(c.at(i)*(sorted_speed+sorted_speed));
	}
	std::sort(speeds.begin(), speeds.end());

	int beg = 0;
	int end = speeds.size() - 1;
	int result = -1;

	while (beg <= end) {
		int mid = (beg + end)/2;
		if (possible(speeds.at(mid),people,strength,speed,sorted_people,sorted_strength,sorted_speed,c)) {
			beg = mid + 1;
			result = speeds.at(mid);
		}
		else {
			end = mid - 1;
		}
	}
		
	return result;
}

int main() {
	int people;
	int strength;
	int speed;
	int sorted_people;
	int sorted_strength;
	int sorted_speed;
	std::vector<int> c;

	std::cin >> people >> strength >> speed;
	std::cin >> sorted_people >> sorted_strength >> sorted_speed;
	int m = (people + strength + speed)/2;
	for(int i = 0; i < m; i++) {
		int j;
		std::cin>>j;
		c.push_back(j);
	}

	std::cout << find_min_v(people,strength,speed,sorted_people,sorted_strength,sorted_speed,c) << std::endl;

	return 0;
}