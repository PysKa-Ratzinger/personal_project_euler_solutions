

#define MIN(a,b) ((a) < (b) ? (a) : (b))

std::map<std::pair<int, int>, int> cache;

int fast_res(int diff, int prev) {
	auto it = cache.find(std::make_pair(diff, prev));
	if (it == cache.end())
		return -1;

	return it->second;
}

void set_cache(int diff, int prev, int res) {
	auto it = cache.find(std::make_pair(diff, prev));
	if (it == cache.end()) {
		cache.insert(std::make_pair(std::make_pair(diff, prev), res));
	}
}

int count2(int diff, int prev) {
	if (diff <= 1) {
		return 1;
	}
	if (prev == 1) {
		return 1;
	}
	int res = fast_res(diff, prev);
	if (res != -1)
		return res;
	res = 0;
	for (int i=MIN(prev, diff); i>0; i--) {
		res += count2(diff-i, i);
	}
	set_cache(diff, prev, res);
	return res;
};

int count1(int num) {
	int res = 0;
	for (int i=num-1; i>0; i--) {
		res += count2(num-i, i);
	}
	return res;
}

int main (int argc, char* argv[]) {
}

