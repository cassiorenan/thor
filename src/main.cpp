#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

int main() {
    auto it = std::istreambuf_iterator<char>(std::cin);
    auto end = std::istreambuf_iterator<char>();
    auto mode = 's';
    while(it != end) {
        std::stringstream ss;
        switch(mode) {
        case 's':
            while (mode == 's' && it != end) {
                while (it != end && *it != '<') {
                    ss << *it++;
                }
                if (it != end) {
                    ++it;
                    if (*it == '%') {
                        char mode_c = *(++it);
                        if (mode_c == '-') {
                            mode = 'c';
                        } else if (mode_c == '=') {
                            mode = 'g';
                        } else {
                            throw std::runtime_error(std::string{"Unknown mode: "} + mode_c);
                        }
                        ++it;
                    } else {
                        ss << '<';
                    }
                }
            }
            std::cout << "io.write([====[";
            std::cout << ss.rdbuf();
            ss.str("");
            std::cout << "]====])\n";
            break;
        case 'c':
            while (mode == 'c' && it != end) {
                while (it != end && *it != '%') {
                    ss << *it++;
                }
                if (it == end) {
                    throw std::runtime_error("Unexpected end of buffer: expected \"%>\" token.");
                }
                ++it;
                if (*it == '>') {
                    mode = 's';
                    ++it;
                } else {
                    ss << '%';
                }
            }
            std::cout << ss.rdbuf();
            ss.str("");
            std::cout << '\n';
            break;
        case 'g':
            while (mode == 'g' && it != end) {
                while (it != end && *it != '%') {
                    ss << *it++;
                }
                if (it == end) {
                    throw std::runtime_error("Unexpected end of buffer: expected \"%>\" token.");
                }
                ++it;
                if (*it == '>') {
                    mode = 's';
                    ++it;
                } else {
                    ss << '%';
                }
            }
            std::cout << "io.write(tostring(";
            {
                auto buf = ss.str();
                std::copy_if(std::begin(buf), std::end(buf), std::ostream_iterator<char>(std::cout), [](auto& v){return v != ' ';});
                ss.str("");
            }
            std::cout << "))\n";
            break;
        default:
            it = end;
            break;
        }
    }
}
