#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

using input_iterator = std::istreambuf_iterator<char>;
using output_iterator = std::ostreambuf_iterator<char>;
using buffer_t = std::stringstream;

using std::cin;
using std::cout;
using std::copy;
using std::copy_if;

const input_iterator end{};

const char s_prefix[] = "io.write([====[\n";
const char s_suffix[] = "]====])\n";

const char g_prefix[] = "io.write(tostring(";
const char g_suffix[] = "))\n";

template<typename T1, typename T2, typename F>
void copy_while(T1& it, const T1& end, T2& buf, F predicate) {
	while (it != end && predicate(*it)) {
		buf.put(*it++);
	}
}

char read(input_iterator& it, buffer_t& buf) {
	while (it != end) {
		copy_while(it, end, buf, [](char v){return v != '%';});
		if (it != end) {
			if (*++it == '>') {
				++it;
				return 's';
			} else {
				buf.put('%');
			}
		}
	}
	throw std::runtime_error("Unexpected end of buffer: expected \"%>\" token.");
}

char read_s(input_iterator& it, buffer_t& buf) {
	while (it != end) {
		copy_while(it, end, buf, [](char v){return v != '<';});
		if (it != end) {
			if (*++it == '%') {
				if (*++it == '=') {
					++it;
					return 'g';
				} else {
					return 'c';
				}
			} else {
				buf.put('<');
			}
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
	input_iterator it{cin};
	output_iterator out_it{cout};
    char mode{'s'};
    
	while(it != end) {
        buffer_t buf;
        switch(mode) {
        case 's':
		    mode = read_s(it, buf);
            if (buf.rdbuf()->in_avail() != 0) {
                cout.write(s_prefix, sizeof(s_prefix)-1);
                copy(input_iterator(buf), end, out_it);
                cout.write(s_suffix, sizeof(s_suffix)-1);
            }
            break;
        case 'c':
            mode = read(it, buf);
			copy(input_iterator(buf), end, out_it);
            cout.put('\n');
            break;
        case 'g':
		    mode = read(it, buf);
            cout.write(g_prefix, sizeof(g_prefix)-1);
			copy_if(input_iterator(buf), end, out_it, 
				    [](char v){return v != ' ';});
            cout.write(g_suffix, sizeof(g_suffix)-1);
            break;
        default:
            throw std::logic_error("Invalid mode.");
        }
    }
}
