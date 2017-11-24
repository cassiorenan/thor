#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

using input_iterator = std::istreambuf_iterator<char>;
using output_iterator = std::ostreambuf_iterator<char>;

using std::cin;
using std::cout;

using std::copy;
using std::copy_if;

using std::string;

const input_iterator end_it{};

enum class mode { none, plain, code, getter};

struct boilerplate_t{string prefix; string suffix;};

template<mode M> const boilerplate_t boilerplate;
template<> const boilerplate_t boilerplate<mode::plain>{
	.prefix="io.write([====[\n",
	.suffix="]====])\n"
};
template<> const boilerplate_t boilerplate<mode::getter>{
	.prefix="io.write(tostring(",
	.suffix="))\n"
};
template<> const boilerplate_t boilerplate<mode::code>{
	.prefix="",
	.suffix="\n"
};

template<typename T1, typename T2, typename F>
void copy_while(T1& it, const T1& end_it, T2& out, F predicate) {
	while (it != end_it && predicate(*it)) {
		*out++ = *it++;
	}
}

template<typename T>
void ignore(T& it, const T& end, const typename T::value_type& value) {
	for(;*it == value && it != end;++it);
}

template<mode M>
mode read(input_iterator& it, const input_iterator& end, output_iterator& out) {
	while (it != end_it) {
		copy_while(it, end_it, out, [](char v){return v != '%';});
		if (it != end_it) {
			if (*++it == '>') {
				++it;
				return mode::plain;
			} else {
				*out++ = '%';
			}
		}
	}
	throw std::runtime_error("Unexpected end of buffer: expected \"%>\" token.");
}

template<>
mode read<mode::plain>(input_iterator& it, const input_iterator& end, output_iterator& out) {
	while (it != end_it) {
		copy_while(it, end_it, out, [](char v){return v != '<';});
		if (it != end_it) {
			if (*++it == '%') {
				if (*++it == '=') {
					++it;
					return mode::getter;
				} else {
					return mode::code;
				}
			} else {
				*out++ = '<';
			}
		}
	}
	return mode::none;
}

template<mode M, typename IN, typename OUT>
mode write_mode(IN& begin, const IN& end, OUT& out, char trim) {
	copy(boilerplate<M>.prefix.begin(), boilerplate<M>.prefix.end(), out);
	ignore(begin, end, trim);
	mode next_mode = read<M>(begin, end, out);
	copy(boilerplate<M>.suffix.begin(), boilerplate<M>.suffix.end(), out);
	return next_mode;
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
	input_iterator it{cin};
	output_iterator out{cout};
    mode current_mode{mode::plain};
    
	while(it != end_it) {
        switch(current_mode) {
        case mode::plain:
		    current_mode = write_mode<mode::plain>(it, end_it, out, 0);
            break;
        case mode::code:
		    current_mode = write_mode<mode::code>(it, end_it, out, 0);
            break;
        case mode::getter:
		    current_mode = write_mode<mode::getter>(it, end_it, out, ' ');
            break;
        default:
            throw std::domain_error("Invalid mode.");
        }
    }
}
