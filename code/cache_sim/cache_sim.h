#ifndef __CACHE_SIM_H__
#define __CACHE_SIM_H__

#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdio.h>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

#define MAX_CACHELINE_NUM (65536)	/* 65536(2^16) */
//#define MAX_CACHELINE_NUM (268435456) /* The max num of gcc array support 268435456(2^28) */

/* 内存地址与Cache地址的关联方式: 直接映射、组相联、全相联 */
enum associativity_type {
	DIRECT_MAPPED = 1,
	SET_ASSOCIATIVE = 2,
	FULL_ASSOCIATIVE = 3
};

/* 替换策略: NONE(直接替换)、FIFO(先进先出算法)、LRU(最近最少使用算法)、
	LRU(最不经常使用替换算法)、Random(随机替换算法) */
enum replace_type {
	NONE = 0,
	FIFO = 1,
	LRU = 2,
	LFU = 3,
	Random = 4,
	PLRU = 5
};

/* 写策略: write_through(全写法)、write_back(回写法) */
enum write_type {
	WRITE_THROUGH = 1,
	WRITE_BACK = 2
};

class plru_replace {
public:
	vector<bool> plru_bit_vector;
public:
	plru_replace() {}
	~plru_replace() {}
	void reset_plru()
	{
		for (uint32_t i = 0; i < plru_bit_vector.size(); i++) {
			plru_bit_vector.at(i) = false;
		}
	}

	uint32_t flip_plru()
	{
		uint32_t i = 0;
		uint32_t j = 0; /* j represent the number of binary tree layer */
		while ((i * 2 + 1) < plru_bit_vector.size()) {
			plru_bit_vector.at(i) = !plru_bit_vector.at(i);
			j += 1;
			if (plru_bit_vector.at(i)) { /* indicate it's left subtree if plru bits is true after flip plru */
				i = i * 2 + 1;
			} else { /* indicate it's right subtree if plru bits is false after flip plru */
				i = i * 2 + 2;
			}
		}
		plru_bit_vector.at(i) = !plru_bit_vector.at(i);
		j += 1;

		if (plru_bit_vector.at(i)) { /* left subtree */
			i = i * 2 + 1;
		} else { /* right subtree */
			i = i * 2 + 2;
		}
		return (i - ((j << 1) - 1));
	}

	void reverse_flip_plru(uint32_t index)
	{
		uint32_t n = floor(log2(plru_bit_vector.size() + 1)) - 1; /* n represent the number of binary tree layer */
		uint32_t i = 0; /* node number */

		i = (1 << n) - 1 + (index / 2); /* the leaf node */
		n -= 1;
		if (index % 2 == 0) { /* left subtree */
			plru_bit_vector.at(i) = true;
		} else { /* right subtree */
			plru_bit_vector.at(i) = false;
		}

		index = i;
		while (n != 0) {
			i = (index - 1) / 2;
			if (index % 2 == 0) { /* right subtree */
				plru_bit_vector.at(i) = false;
			} else { /* left subtree */
				plru_bit_vector.at(i) = true;
			}
			n -= 1;
			index = i;
		}

		if (index == 1) {
			plru_bit_vector.at(0) = true;
		} else {
			plru_bit_vector.at(0) = false;
		}
	}
};

class cache_sim {
public:
	cache_sim();
	~cache_sim();
	void reset();
	void set_cache_info(uint64_t cache_size, uint64_t cacheline_size, uint32_t assoc_type,
			uint32_t way_num, uint32_t replace_type, uint32_t write_type);
	void calc_cache_info(void);
	bool proc_cache_access(char *trace_str);
	bool check_cache_hit(bitset<32> access_addr_binary);
	void cache_lru_hit_process();
	void cache_lru_unhit_process(bool need_evict);
	void cache_read_memory(bitset<32> access_addr_binary);
	void cache_write_memory();
	void cache_replace(bitset<32> access_addr_binary);
	void calc_hit_rate();
public:
	std::bitset<32> m_cache_item[MAX_CACHELINE_NUM]; /* 0b[31]:valid,0b[30]:hit,0b[29]:dirty,0b[28:0]:data */
	uint64_t m_lru_priority[MAX_CACHELINE_NUM]; /* lru policy's priority */
	uint64_t m_current_line; /* indicate the line num which is processing */
	uint64_t m_current_set; /* indicate the set num which is processing */
	uint64_t m_cache_size; /* cache size(uint: KB) */
	uint64_t m_cacheline_size; /* cacheline size(uint: B) */
	uint64_t m_cacheline_num; /* cacheline number */
	uint64_t m_set_num; /* set number of the cache */
	uint64_t m_way_num; /* way number in each set */

	uint32_t m_cacheline_bit_num; /* number of bits occupied by cacheline */
	uint32_t m_set_bit_num; /* number of bits occupied by set number */
	uint32_t m_direct_mapped_bit_num; /* number of bits occupied by direct mapped */
	uint32_t m_tag_bit_num; /* number of bits occupied by tag */

	associativity_type m_assoc_type;
	replace_type m_replace_type;
	write_type m_write_type;

	uint64_t m_access_num; /* number of cache access */
	uint64_t m_load_num; /* number of cache load */
	uint64_t m_store_num; /* number of cache store */
	uint64_t m_hit_num; /* number of cache hit */
	uint64_t m_load_hit_num; /* number of cache load hit */
	uint64_t m_store_hit_num; /* number of cache store hit */
	uint64_t m_space_num; /* number of space line */

	float m_hit_rate; /* averate cache hit rate */
	float m_load_hit_rate; /* hit rate for load */
	float m_store_hit_rate; /* hit rate for store */
};

#endif