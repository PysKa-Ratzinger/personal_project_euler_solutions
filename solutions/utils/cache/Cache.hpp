#include <map>
#include <list>

template <typename BaseClass, typename K, typename V>
class Cache {
public:
	std::map<K, typename std::list<std::pair<K, V>>::iterator> mp;
	size_t cp;
	std::list<std::pair<K, V>> data;
	V invalid_value;

	Cache(size_t capacity, const V invalid_value) :
		cp(capacity),
		invalid_value(invalid_value)
	{

	}

	void set(const K& key, const V& value) {
		static_cast<BaseClass&>(*this).set_impl(key, value);
	}

	const V& get(const  K& key) {
		return static_cast<BaseClass&>(*this).get_impl(key);
	}
};

template <typename K, typename V>
class LRUCache_T : public Cache<LRUCache_T<K, V>, K, V>
{
public:
	using Cache<LRUCache_T<K, V>, K, V>::Cache;

	void set_impl(const K& key, const V& value) {
		auto it = this->mp.find(key);
		if (it != this->mp.end()) {
			this->data.splice(this->data.begin(), this->data, it->second);
			it->second = this->data.begin();
			this->data.front().second = value;
		} else {
			if (this->data.size() == this->cp) {
				auto it = this->mp.find(this->data.back().first);
				this->mp.erase(it);
				this->data.pop_back();
			}
			this->data.push_front({key, value});
			this->mp.insert({key, this->data.begin()});
		}
	}

	const V& get_impl(const K& key) {
		auto it = this->mp.find(key);
		if (it != this->mp.end()) {
			return it->second->second;
		} else {
			return this->invalid_value;
		}
	}
};

class LRUCache : public LRUCache_T<int, int>
{
public:
	using LRUCache_T<int, int>::LRUCache_T;
};

