#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <list>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "graph/dijkstra.hpp"

#define DEBUG 0

using map_type = std::map< char, std::pair< std::set< char >, std::set< char >>>;

void print_usage( const char* program_name ) {
	printf("Usage: %s [--file|-f] FILENAME\n", program_name);
	printf("\n");
	printf("Flags:\n");
	printf("  --file / -f   The name of the file to crack\n");
}

std::set< std::list< char > > read_input( const char* filename ) {
	int fd = open( filename, O_RDONLY );
	if ( fd == -1 ) {
		fprintf( stderr, "Cannot open %s", filename );
		exit( EXIT_FAILURE );
	}

	std::set< std::list< char > > result;
	std::list< char > curr;

	char buffer[512];
	ssize_t nread;
	while ( (nread = read(fd, buffer, 512)) > 0 ) {
		for ( ssize_t i = 0; i < nread; i++ ) {
			char c = buffer[i];
			if ( c == '\n' ) {
				result.insert( curr );
				curr.clear();
			} else {
				curr.push_back(c);
			}
		}
	}

	close(fd);

	return result;
}

map_type create_map(std::set<std::list<char>> input)
{
	map_type result;

	for ( auto buffer : input ) {
		auto it = buffer.begin();
		char prev = '\0';
		map_type::iterator map_it = result.end();

		while (it != buffer.end()) {
			char curr = *it;

			// Insert next element, if exists
			if (prev && map_it != result.end()) {
				map_it->second.second.insert(curr);
			}

			map_it = result.find(curr);
			if (map_it == result.end()) {
				auto res = result.insert(std::make_pair(curr, std::pair<std::set<char>, std::set<char>>()));
				if (!res.second) {
					throw std::runtime_error("Internal error #1");
				}
				map_it = res.first;
			}

			// Insert previous element
			if (prev) {
				map_it->second.first.insert(prev);
			}

			prev = curr;
			it++;
		}
	}

	return result;
}

void print_map(map_type digits)
{
	for (auto p : digits) {
		printf("P: %c\n", p.first);

		printf("  prev: [");
		bool prev = false;
		for (char p2 : p.second.first) {
			printf("%s%c", prev ? ", " : "", p2);
			prev = true;
		}
		printf("]\n");

		printf("  next: [");
		prev = false;
		for (char p2 : p.second.second) {
			printf("%s%c", prev ? ", " : "", p2);
			prev = true;
		}
		printf("]\n");
	}
}

bool solve_impl(map_type digits, std::set<char>& visited, std::list<char>& result)
{
	bool ret = false;
	for (auto p : digits) {
		if (visited.find(p.first) != visited.end())
			continue;
		auto prev_chars = p.second.first;
		if (std::includes(
					visited.begin(), visited.end(),
					prev_chars.begin(), prev_chars.end()
					)) {
			auto res = visited.insert(p.first);
			if (!res.second)
				throw std::runtime_error("Internal error #2");
			result.push_back(p.first);
			if (p.second.second.empty()) {
				// End condition
				printf("Found solution: ");
				for (char c : result) {
					printf("%c", c);
				}
				printf("\n");
				ret = true;
			} else {
				ret |= solve_impl(digits, visited, result);
			}
			result.pop_back();
			visited.erase(res.first);
		}
	}
	return ret;
}

bool solve(map_type digits)
{
	std::set<char> visited;
	std::list<char> result;
	return solve_impl(digits, visited, result);
}

int main(int argc, char **argv)
{
	int c;
	int digit_optind = 0;

	const char* filename_option = nullptr;

	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"file",    required_argument, 0, 'f'},
			{0,         0,                 0,  0 }
		};

		c = getopt_long(argc, argv, "f:",
				long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			switch (option_index) {
			case 0:
				filename_option = optarg;
				break;
			}

		case 'f':
			filename_option = optarg;
			break;

		default:
			print_usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	if (!filename_option) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	std::set< std::list< char > > input = read_input(filename_option);
	auto digits = create_map(input);
#if DEBUG
	print_map(digits);
#endif
	if (!solve(digits)) {
		printf("No solutions found");
	}

	exit(EXIT_SUCCESS);
}

