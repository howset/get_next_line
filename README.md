# get_next_line

## Content
1. get_next_line.c
	1. char *get_next_line(int fd);
	2.	char *real_gnl_func(char **stock, int fd);
	3.	char *read_fd(int fd);
	4.	char *extract_line(char **stock);
2. get_next_line_utils.c
	1. size_t ft_strlen(const char *str);
	2. size_t ft_strlcpy(char *dst, const char *src, size_t size);
	3. char *ft_strdup(const char *s);
	4. char *ft_substr(char const *s, unsigned int start, size_t len);
	5. char *ft_strjoin(char const *s1, char const *s2);
3. get_next_line.h
	1. just declare default BUFFER_SIZE

## Flow
- The ```get_next_line``` and ```real_gnl_func``` are actually the result of one function, just too long ,so separated into 2 funcs. In this case, the ```get_next_line``` function serves:
	1. as a control for invalid inputs,
	2. to declare and contain the (only) static variable, <kbd>stock</kbd>
	3. to initialize the **stock** as empty in the very first call (before any line is read). The ```get_next_line``` function takes the **fd** as input and calls the ```real_gnl_func``` as the return by passing the **fd** and the initialized **stock**.
- The ```real_gnl_func``` starts by reading the **fd** (```read_fd```) and stores the result in the var **line_fr_read**.
	- The beginning part of the function (**extracted**) is not relevant in the first pass of the text file, because there is nothing yet to do. (Would contain some **remains** on subsequent runs).
	- The ```read_fd``` function allocates (malloc) an array with a size corresponding to **BUFFER_SIZE** + 1 (to accomodate a terminating null) in the variable **line_fr_read**. The string contained in this variable is return of the function (which may or may not contains a '\n' or '\0'). The ```read``` function is called from the **fd**, stored to the allocated array **line_fr_read**, using the read count of **BUFFER_SIZE**. The number/amount of bytes read by the ```read``` function is stored in the var **bytes**.
	- The **temp** variable stores the joined string from **stock** (initially empty) and **line_fr_read** (resulting from 1st run/line). Then switch the content, by first freeing **stock**, and set **stock** as **temp**. 
	- The return of the ```real_gnl_function``` is calling itself recursively.
- For the next run of the ```real_gnl_function``` function:
	- The ```extract_line``` function is called on **stock** (already contains something), and stores the result in the var **extracted**.
	- The ```extract_line``` function's job is to return a line __*IF*__ it exists. It basically iterates over the string in **stock** until '\n' (or '\0') is found. 
		- If found, by using ft_substr, extracts from **stock** up to '\n' and store it in **extracted**.
		- Extract the leftover from **stock** and store in **remains**.
		- Free the **stock** and set it as **remains**.
		- Returns **extracted**.
	- If not found, returns NULL. And initiate _again_ the ```read_fd``` line in the ```real_gnl_func```.
- Repeat until ```line_fr_read``` contains either '\n' or '\0'.
	- If yes, then **extracted** is returned.
- The ```get_next_line``` function ends here.
	- The ```main``` function would print the returned result to terminal.
	- However in the loop of the ```main``` function, the ```get_next_line``` will still be evaluated as **TRUE**, and repeats.
	- The ```read``` function remembers the last position and proceeds from there (next line).
- At the end of file (**EOF**), ```read_fd``` will return -1, which leads to the control sequence:
	- If **!line_fr_read**:
			- then set **extracted** as **stock** (leftover/**remains**), then free **stock** and set it as NULL to avoid leaks.
			- then returns **extracted**, and frees it.
	- This returns ```!real_gnl_func```, and subsequently ```!get_next_line```. 
- At this point, the loop in ```main``` would not evaluate, and stops.

## Notes
- In ```read```, the pointer to the buffer remains where it last completed its read, because it is associated with the file descriptor of that file.
- A static variable is necessary because repeated calls to ```read``` overwrites the buffer it points to everytime.
- No special trimming function, because the ```extract_line``` function already returns **extracted** from **stock** and set **stock** as the remains. 
- Bonus ```ulimit -n``` - soft limit fd

## Valgrind (to test)
```
cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 *.c && valgrind --tool=memcheck -q --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./a.out | cat -e
```

## Sources
- https://github.com/madebypixel02/get_next_line #hp
- https://github.com/iaurg/42-get-next-line
- https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line
