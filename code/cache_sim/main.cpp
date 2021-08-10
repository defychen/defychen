#include <string>
#include "cache_sim.h"

int main(int argc, char *argv[])
{
	cache_sim *cache_sim_test = new cache_sim();
	cache_sim_test->set_cache_info(4, 64, 2, 4, 2, 2);
	string file_path = "./gcc.trace";
	ifstream fp(file_path, ios::in);
	// string trace_str;
	char trace[13];

	while (!fp.eof()) {
		fp.getline(trace, 13);
		cache_sim_test->proc_cache_access(trace);
	}
	cache_sim_test->calc_hit_rate();
	cout << "hit_rate: " << cache_sim_test->m_hit_rate << endl;
	cout << "load hit rate: " << cache_sim_test->m_load_hit_rate << endl;
	cout << "store hit rate: " << cache_sim_test->m_store_hit_rate << endl;
}
