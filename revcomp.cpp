// The Computer Language Benchmarks Game
// https://salsa.debian.org/benchmarksgame-team/benchmarksgame/
// Contributed by Paul Kitchin

#include <iostream>
#include <iterator>
#include <list>

#define LIKELY(x)      __builtin_expect(!!(x), 1) 
#define UNLIKELY(x)    __builtin_expect(!!(x), 0)

char complement(char character) {
   static char const complement_map[] = {
      '\0', 'T', 'V', 'G', 'H', '\0',
      '\0', 'C', 'D', '\0', '\0', 'M',
      '\0', 'K', 'N', '\0', '\0', '\0',
      'Y', 'S', 'A', 'A', 'B',
      'W', '\0', 'R'
   };
   
   return complement_map[character & 0x1f];
}

constexpr size_t basepairs_in_line = 60;
constexpr size_t lines_in_chunk = 1074;
constexpr size_t chunk_size = (basepairs_in_line + 1) * lines_in_chunk;

struct chunk {
    
    char* before_begin() {
        return data - 1;
    }
    
    char* begin() {
        return data;
    }

    char* end() {
        return data + length;
    }

    char* last() {
        return data + length - 1;
    }

    size_t length = 0;
    char data[chunk_size];
};

template<typename ForwardIterator, typename BackwardIterator>
void do_reverse_complement(ForwardIterator front_chnk, BackwardIterator back_chnk) {    
    char* front_ptr = front_chnk->begin();
    char* back_ptr = back_chnk->last();

    while (front_chnk != back_chnk or front_ptr < back_ptr) {
        {
            char tmp = complement(*front_ptr);
            *front_ptr++ = complement(*back_ptr);
            *back_ptr-- = tmp;
        }

        if (UNLIKELY(*front_ptr == '\n')) {
            ++front_ptr;

            if (front_ptr == front_chnk->end()) {
                front_chnk++;
                front_ptr = front_chnk->begin();
            }
        }
        
        if (*back_ptr == '\n') {
            --back_ptr;
        } else if (back_ptr == back_chnk->before_begin()) {
            back_chnk--;
            back_ptr = back_chnk->last();
            --back_ptr;  // skip newline
        }
    }
}

chunk read_chunk() {
    chunk ret;

    char* cursor = ret.data;
    for (int line = 0;
         line < lines_in_chunk and not std::cin.eof() and std::cin.peek() != '>';
         ++line) {
        
        std::cin.getline(cursor, basepairs_in_line + 1);
        cursor += std::cin.gcount();
        cursor[-1] = '\n';
    }
    ret.length = cursor - ret.data;

    return ret;
}

int main() {
   std::cin.sync_with_stdio(false);
   std::cout.sync_with_stdio(false);

   while (not std::cin.eof()) {
       std::list<chunk> v;
       {
           std::string header;
           std::getline(std::cin, header);
           std::cout << header << '\n';
       }

       while (not std::cin.eof() and std::cin.peek() != '>') {
           v.emplace_back(read_chunk());
       }
       
       if (v.size() > 0) {
           --v.back().length;
       }
       
       do_reverse_complement(v.begin(), --v.end());

       for (const auto& chnk : v) {
           std::cout.write(chnk.data, chnk.length);
       }
       std::cout.put('\n');
   }
}
