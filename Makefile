cc := clang++

flags := -O0 -std=c++14 -stdlib=libc++ -g -Wall -Wextra \
-fsanitize=address -fno-omit-frame-pointer \
-fsanitize=undefined-trap -fsanitize-undefined-trap-on-error

# execs := chapter_two chapter_three chapter_three_double_list
# Just keep it simple
.PHONY: all clean

# all: ${execs}

# chapter_two:chapter_two.cpp; ${cc} ${flags} $< -o $@

# chapter_three:single_list.cpp; ${cc} ${flags} $< -o $@

# chapter_three_double_list:double_list.cpp; ${cc} ${flags} $< -o $@

# chapter_five_hash_tables:hash_table.cpp; ${cc} ${flags} $< -o $@

chapter_six_binary_trees:binary_trees.cpp; ${cc} ${flags} $< -o $@

clean:;$(foreach src, $(execs), $(shell rm $(src))) @true
