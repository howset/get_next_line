# get_next_line

## Content
1. get_next_line.c
>	1. char *get_next_line(int fd);
>	2. char	*read_line(int fd, char *stock);
>	3. char	*extract_line(char *stock);
>	4. char	*clean_up(char *stock);
2. get_next_line_utils.c
>	1. char	*null_malloc(size_t nmemb, size_t size);
>	2. size_t	ft_strlen(const char *str);
>	3. char	*freebuf_join(char *s1, char *s2);
>	4. char	*ft_strchr(const char *s, int c);
3. get_next_line.h
>	1. just declare default BUFFER_SIZE

## Flow
- The ```get_next_line``` function first starts with a control sequence to check either invalid <kbd>BUFFER_SIZE</kbd> or <kbd>fd</kbd> (if so, returns NULL, and make sure <kbd>stock</kbd> is freed).
- Then the ```read_line``` function is called to populate <kbd>stock</kbd> (with whatever is leftover in itself from previous run) and the result of a ```read``` function that is called in this part. A variable <kbd>line_fr_read</kbd> is allocated (with ```null_malloc```) as the buffer to which the ```read``` function puts its result beside the number of bytes sucessfully read (to <kbd>bytes</kbd>). 
- The ```read``` function is called only while there is no <kbd>\n</kbd> character in the <kbd>stock</kbd>. The resulting <kbd>line_fr_read</kbd> is then terminated by a <kbd>\0</kbd>.
- Finally, <kbd>stock</kbd> is then filled by joining <kbd>line_fr_read</kbd> and itself (still empty in the first run). Then the ```read``` buffer (<kbd>line_fr_read</kbd>) is freed.
- Then the ```extract_line``` function is called on the variable <kbd>stock</kbd>. This function traverses <kbd>stock</kbd> until a <kbd>\n</kbd> is found. Everything is then stored in the variable <kbd>extracted</kbd> that was allocated accordingly by ```null_malloc```, and then terminated by a <kbd>\0</kbd>. 
- The extraction result from ```extract_line``` (<kbd>extracted</kbd>) is a full line terminated by a <kbd>\n</kbd> character. This is the return value of the ```get_next_line``` function.
- The next step is to ```clean_up``` the <kbd>stock</kbd> by removing the extracted parts (everything up to <kbd>\n</kbd>) and return the leftovers in <kbd>remains</kbd>.
- Back to the ```get_next_line``` function, the <kbd>stock</kbd> variable is then set to contain only <kbd>remains</kbd>

## Notes
- In ```read```, the pointer to the buffer remains where it last completed its read, because it is associated with the file descriptor of that file.
- Bonus ```ulimit -n``` - soft limit fd
- Another way would be by defining it in the header file by adding:
``` c
# ifndef FD_MAX
#  define FD_MAX whatevernumber
# endif
```
- Then adjust during compilation via the '-D FD_MAX=n' flag.
- Adjust BUFFER_SIZE also with -D flag like above.
- To let the program to read from stdin, pipe the output of cat/echo to the program. (fd in main has to be set to 0!)
```
$ cat whatevertestfile.txt | ./a.out 
```
- Fails francinette --strict

## Valgrind (to test)
```
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c get_next_line.h && valgrind --tool=memcheck -q --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./a.out | cat -e
```
```
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c get_next_line_bonus.h && valgrind --tool=memcheck -q --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./a.out | cat -e
```
## Diagram
```
                                                                                         ┌─────────┐
                                                                                     ┌──►│ft_strchr│
                                                                                     │   └─────────┘
                                                                                     │
                                         ┌───────────────────────────────────┐       │
                                   ┌────►│read_line                          │       │
                                   │     │ malloc line_fr_read ├─────────────┼──┐    │
                                   │     │ loop along stock for '\n' ├───────┼──┼────┘
                                   │     │  read & put to buffer line_fr_read│  │        ┌──────────────┐     ┌─────────┐
                                   │     │  put line_fr_read to stock by join├──┼───────►│freestock_join├────►│ft_strlen│
                                   │     │ free line_fr_read                 │  │        │ join         │     └─────────┘
                                   │     │ return stock                      │  │        │ free stock   │
                                   │     └───────────────────────────────────┘  │        └──────────────┘
                                   │                                            │
                                   │     ┌──────────────────────────┐           │        ┌────────────────┐
                                   │ ┌──►│extract_line              │           │      ┌►│null_malloc     │
                                   │ │   │ malloc extracted ├───────┼───────────┴──────┤ │ malloc         │
                                   │ │   │ traverse stock up to '\n'│                  │ │ set[0] to '\0' │
                                   │ │   │ copy it to extracted     │                  │ └────────────────┘
                                   │ │   │ return extracted         │                  │
┌────────────────────────────────┐ │ │   └──────────────────────────┘                  │
│get_next_line                   │ │ │                                                 │
│ starting seq                   │ │ │   ┌────────────────────────────┐                │
│ stock = read_line(fd, stock)   ├─┘ │ ┌►│clean_up                    │                │
│ extracted = extract_line(stock)├───┘ │ │ malloc remains ├───────────┼────────────────┘
│ stock = clean_up(stock)        ├─────┘ │ remains = stock - extracted│
│ return(extracted)              │       │ empty stock                │
└────────────────────────────────┘       │ set stock as remains       │
                                         └────────────────────────────┘
```

## Flow of filling stock with line_fr_read to return extracted
![read_line](./pres/gnl_flow1.png "read_line")
![read_line](./pres/gnl_flow2.png "read_line")
![read_line](./pres/gnl_flow3.png "read_line")
![read_line](./pres/gnl_flow4.png "read_line")
![read_line](./pres/gnl_flow5.png "extract_line and clean_up")