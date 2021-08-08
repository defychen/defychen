#include "cache_sim.h"

cache_sim::cache_sim()
{
	reset();
}

cache_sim::~cache_sim()
{
}

void cache_sim::reset()
{
	for (int i = 0; i < MAX_CACHELINE_NUM; i++) {
		m_cache_item[i].reset();
		m_lru_priority[i] = 0;
	}

	m_current_line = 0;
	m_current_set = 0;
	m_cache_size = 0;
	m_cacheline_size = 0;
	m_set_num = 0;
	m_way_num = 0;

	m_cacheline_bit_num = 0;
	m_set_bit_num = 0;
	m_direct_mapped_bit_num = 0;
	m_tag_bit_num = 0;

	m_assoc_type = DIRECT_MAPPED;
	m_replace_type = NONE;
	m_write_type = WRITE_BACK;

	m_access_num = 0;
	m_load_num = 0;
	m_store_num = 0;
	m_hit_num = 0;
	m_load_hit_num = 0;
	m_store_hit_num = 0;
	m_space_num = 0;

	m_hit_rate = 0.0;
	m_load_hit_rate = 0.0;
	m_store_hit_rate = 0.0;
}

void cache_sim::set_cache_info(uint64_t cache_size, uint64_t cacheline_size, 
	uint32_t assoc_type, uint32_t way_num, uint32_t replace_type, uint32_t write_type)
{
	m_cache_size = cache_size;
	m_cacheline_size = cacheline_size;
	m_way_num = way_num;
	switch (assoc_type) {
	case 1:
		m_assoc_type = DIRECT_MAPPED;
		break;
	case 2:
		m_assoc_type = SET_ASSOCIATIVE;
		break;
	case 3:
		m_assoc_type = FULL_ASSOCIATIVE;
		break;
	default:
		cout << "assoc type error" << endl;
		exit(1);
	}

	switch (replace_type) {
	case 1:
		m_replace_type = FIFO;
		break;
	case 2:
		m_replace_type = LRU;
		break;
	case 3:
		m_replace_type = LFU;
		break;
	case 4:
		m_replace_type = Random;
		break;
	default:
		cout << "replace type error" << endl;
		exit(1);
	}

	switch (write_type) {
	case 1:
		m_write_type = WRITE_THROUGH;
		break;
	case 2:
		m_write_type = WRITE_BACK;
		break;
	default:
		cout << "write type error" << endl;
		exit(1);
	}
	calc_cache_info();

	/* create cache */
	for (int i = 0; i < m_cacheline_num; i++) {
		m_cache_item[i][31] = true;
	}
}

void cache_sim::calc_cache_info(void)
{
	assert(m_cache_size != 0);
	m_cacheline_num = (m_cache_size << 10) / m_cacheline_size;
	uint64_t temp = 0;

	/* number of bits occupied by cacheline */
	temp = m_cacheline_size;
	while (temp) {
		temp >>= 1;
		m_cacheline_bit_num++;
	}
	m_cacheline_bit_num--; /* 64 shift right will be 7, so must be sub 1 */
	if (m_assoc_type == DIRECT_MAPPED) {
		m_set_bit_num = 0; /* DIRECT_MAPPED don't need set */
		temp = m_cacheline_num;
		while (temp) {
			temp >>= 1;
			m_direct_mapped_bit_num++;
		}
		m_direct_mapped_bit_num--; /* must be sub 1 */
	} else if (m_assoc_type == FULL_ASSOCIATIVE) {
		/* FULL_ASSOCIATIVE don't need set */
		m_set_bit_num = 0;
		m_direct_mapped_bit_num = 0;
	} else if (m_assoc_type == SET_ASSOCIATIVE) {
		m_direct_mapped_bit_num = 0;
		assert(m_way_num != 0);
		assert(m_cacheline_num > m_way_num);
		m_set_num = m_cacheline_num / m_way_num;
		temp = m_set_num;

		while (temp) {
			temp >>= 1;
			m_set_bit_num++;
		}
		m_set_bit_num--; /* must be sub 1 */
	}

	m_tag_bit_num = 32 - m_cacheline_bit_num - m_direct_mapped_bit_num - m_set_bit_num;
	assert(m_tag_bit_num <= 29); /* 32-valid-hit-dirty */
	cout << "cache size: " << m_cache_size << "KB" << endl;
	cout << "cacheline size: " << m_cacheline_size << "B" << endl;

	if (m_assoc_type == DIRECT_MAPPED) {
		cout << "direct mapped--->direct_mapping_bit_num: " << m_direct_mapped_bit_num << endl;
	} else if (m_assoc_type == FULL_ASSOCIATIVE) {
		cout << "full associative--->all bit is tag" << endl;
	} else if (m_assoc_type == SET_ASSOCIATIVE) {
		cout << "set associative--->way number: " << m_way_num << ", set_bit_num: " << m_set_bit_num << endl;
	}

	cout << "tag_bit_num: " << m_tag_bit_num << endl;
}

//bool cache_sim::proc_cache_access(string trace_str)
bool cache_sim::proc_cache_access(char * trace_str)
{
	bool is_store = false;
	bool is_load = false;
	bool is_space = false;
	bool hit = false;
	switch (trace_str[0]) {
	case 's':
		is_store = true;
		break;
	case 'l':
		is_load = true;
		break;
	case '\0':
		is_space = true; /* if a line has nothing, the first of it is a '\0' or a ' ' */
		break; /* in case of space lines */
	default:
		cout << "trace[0] is: " << trace_str[0] << endl;
		cout << "ERROR IN JUDGE!" << endl;
		return false;
	}

	//uint32_t access_addr = strtoul(trace_str.substr(2).c_str(), NULL, 16);
	uint32_t access_addr = strtoul(trace_str + 2, NULL, 16);
	bitset<32> access_addr_binary(access_addr);
	hit = check_cache_hit(access_addr_binary);

	if (hit && is_load) { /* hit and load operation */
		m_access_num++;
		m_load_num++;
		m_hit_num++;
		m_load_hit_num++;

		// cout << "Load hit!" << endl;
		if (m_replace_type == LRU) {
			cache_lru_hit_process();
		}
	} else if (hit && is_store) { /* hit and store operation */
		m_access_num++;
		m_store_num++;
		m_hit_num++;
		m_store_hit_num++;

		// cout << "Store hit!" << endl;
		m_cache_item[m_current_line][29] = true; /* set dirty bit */
		if (m_replace_type == LRU) {
			cache_lru_hit_process();
		}
	} else if (!hit && is_load) { /* miss and load operation */
		m_access_num++;
		m_load_num++;
		// cout << "Load miss!" << endl;
		cache_read_memory(access_addr_binary); /* read data from memory */
		if (m_replace_type == LRU) {
			cache_lru_hit_process();
		}
	} else if (!hit && is_store) { /* miss and store operation */
		m_access_num++;
		m_store_num++;
		// cout << "Store miss!" << endl;
		cache_read_memory(access_addr_binary); /* read data from memory */
		if (m_replace_type == LRU) {
			cache_lru_hit_process();
		}		
	} else if (is_space) {
		m_space_num++;
		cout << "There have " << m_space_num << " space lines" << endl;
	} else {
		return false;
	}
	return true;
}

bool cache_sim::check_cache_hit(bitset <32> access_addr_binary)
{
	bool ret = false;

	if (m_assoc_type == DIRECT_MAPPED) {
		bitset<32> line_binary;
		int i, j;
		for (i = 0, j = m_cacheline_bit_num; j < (m_cacheline_bit_num + m_direct_mapped_bit_num); i++, j++) {
			line_binary[i] = access_addr_binary[j];
		}
		m_current_line = line_binary.to_ulong();
		assert(m_cache_item[m_current_line][31] == true);
		if (m_cache_item[m_current_line][30] == true) {
			ret = true;
			/* check tag */
			for (i = 31, j = 28; i > (31 - m_tag_bit_num); i--, j--) {
				if (access_addr_binary[i] != m_cache_item[m_current_line][j]) {
					ret = false;
					break;
				}
			}
		}
	} else if (m_assoc_type == FULL_ASSOCIATIVE) {
		int i, j, k;
		for (k = 0; k < m_cacheline_num; k++) {
			if (m_cache_item[i][30] == true) {
				ret = true;
				/* check tag */
				for (i = 31, j = 28; i > (31 - m_tag_bit_num); i--, j--) {
					if (access_addr_binary[i] != m_cache_item[m_current_line][j]) {
						ret = false;
						break;
					}
				}
			}
			if (ret == true) {
				m_current_line = k;
				break;
			}
		}
	} else if (m_assoc_type = SET_ASSOCIATIVE) {
		bitset<32> line_binary;
		int i, j, k;
		for (i = 0, j = m_cacheline_bit_num; j < (m_cacheline_bit_num + m_set_bit_num); i++, j++) {
			line_binary[i] = access_addr_binary[j];
		}
		m_current_line = line_binary.to_ulong();
		for (k = m_current_set * m_way_num; k < (m_current_set + 1) * m_way_num; k++) {
			if (m_cache_item[k][30] == true) {
				ret = true;
				/* check tag */
				for (i = 31, j = 28; i > (31 - m_tag_bit_num); i--, j--) {
					if (access_addr_binary[i] != m_cache_item[k][j]) {
						ret = false;
						break;
					}
				}
			}
			if (ret = true) {
				m_current_line = k;
				break;
			}
		}
	}
	return ret;
}

void cache_sim::cache_lru_hit_process()
{
	if (m_assoc_type == FULL_ASSOCIATIVE) {
		for (int i = 0; i < m_cacheline_num; i++) {
			if ((m_lru_priority[i] < m_lru_priority[m_current_line]) &&
				(m_cache_item[m_current_line][30] == true)) {
				m_lru_priority[i]++;
			}
		}
		m_lru_priority[m_current_line] = 0;
	} else if (m_assoc_type = SET_ASSOCIATIVE) {
		for (int i = m_current_set * m_way_num; i < (m_current_set + 1) * m_way_num; i++) {
			if ((m_lru_priority[i] < m_lru_priority[m_current_line]) &&
				(m_cache_item[m_current_line][30] == true)) {
				m_lru_priority[i]++;
			}
		}
		m_lru_priority[m_current_line] = 0;
	}
}

void cache_sim::cache_lru_unhit_process(bool need_evict)
{
	if (!need_evict) { /* dont evict, just allocate a new entry */
		if (m_assoc_type == FULL_ASSOCIATIVE) {
			for (uint64_t i = 0; i < m_cacheline_num; i++) {
				if (m_cache_item[i][30] == true) {
					m_lru_priority[i]++;
				}
			}
			m_lru_priority[m_current_line] = 0;
		} else if (m_assoc_type = SET_ASSOCIATIVE) {
			for (int i = m_current_set * m_way_num; i < (m_current_set + 1) * m_way_num; i++) {
				if (m_cache_item[i][30] == true) {
					m_lru_priority[i]++;
				}
			}
			m_lru_priority[m_current_line] = 0;
		}
	} else {
		if (m_assoc_type == FULL_ASSOCIATIVE) {
			uint32_t priority_temp = m_lru_priority[0];
			uint64_t evict_line = 0;
			for (uint64_t i = 0; i < m_cacheline_num; i++) {
				if (priority_temp <= m_lru_priority[i]) {
					priority_temp = m_lru_priority[i];
					evict_line = i;
				}
			}
			m_current_line = evict_line;
		} else if (m_assoc_type = SET_ASSOCIATIVE) {
			uint32_t priority_temp = m_lru_priority[m_current_set * m_way_num];
			uint64_t evict_line = 0;
			for (int i = m_current_set * m_way_num; i < (m_current_set + 1) * m_way_num; i++) {
				if (priority_temp <= m_lru_priority[i]) {
					priority_temp = m_lru_priority[i];
					evict_line = i;
				}
			}
			m_current_line = evict_line;
		}
	}
}

void cache_sim::cache_read_memory(bitset <32> access_addr_binary)
{
	if (m_assoc_type == DIRECT_MAPPED) {
		if (m_cache_item[m_current_line][30] == false) {
			// cout << "read data from memory to cache!" << endl;
			/* save tag into cache */
			int i, j;
			for (i = 31, j = 28; i > (31 - m_tag_bit_num); i--, j--) {
				m_cache_item[m_current_line][j] = access_addr_binary[i];
			}
			m_cache_item[m_current_line][30] = true;
		} else {
			cache_replace(access_addr_binary);
		}
	} else if (m_assoc_type == FULL_ASSOCIATIVE) {
		bool space = false;
		for (uint64_t i = 0; i < m_cacheline_num; i++) {
			if (m_cache_item[i][30] == false) {
				/* find a space entry */
				space = true;
				break;
			}
		}
		if (space == true) {
			m_current_line = space;
			int i, j;
			for (i = 31, j = 28; i > (31 - m_tag_bit_num); i--, j--) {
				m_cache_item[m_current_line][j] = access_addr_binary[i];
			}
			m_cache_item[m_current_line][30] = true;
			if (m_replace_type == LRU) {
				cache_lru_unhit_process(false);
			}
		} else {
			cache_replace(access_addr_binary);
		}
	} else if (m_assoc_type = SET_ASSOCIATIVE) {
		bool space = false;
		for (int i = m_current_set * m_way_num; i < (m_current_set + 1) * m_way_num; i++) {
			if (m_cache_item[i][30] == false) {
				/* find a space entry */
				space = true;
				break;
			}
		}
		if (space == true) {
			m_current_line = space;
			int i, j;
			for (i = 31, j = 28; i > (31 - m_tag_bit_num); i--, j--) {
				m_cache_item[m_current_line][j] = access_addr_binary[i];
			}
			m_cache_item[m_current_line][30] = true;
			if (m_replace_type == LRU) {
				cache_lru_unhit_process(false);
			}
		} else {
			cache_replace(access_addr_binary);
		}
	}
}

void cache_sim::cache_write_memory()
{
	m_cache_item[m_current_line][29] = false;
	m_cache_item[m_current_line][30] = false;	
}

