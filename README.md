# get_next_line

This project was a difficult one for me. Spent too much time trying to come up with something by myself which resulted in nothing noteworthy. Something about how to make it work just didn't click in my head. So I ended up scouring the net for "inspiration". 

Version 1 has recursive function calls. Chosen solely because the author provided a very, very detailed comments on **each** line of the code. However due to the sophistication of the code, I was very hesitant to even try to reproduce it in my own way, even though it helped **a lot** in understanding the project and how the function is intended to work.

Therefore I tried again to scour the internet for codes that are more understandable to me. Ended up with this version (v2) that runs in a step-by-step manner. I managed to reproduce it with my own writing, using my own helper functions. Some minute details were smoothed out in many trial-and-errors. Seems to work well enough although didn't pass `francinette --strict`. My first evaluation went a bit rough because I was not prepared enough to explain the structure and flow of the function(s), despite having prepared a diagram of the organization of the functions. So for the next evaluations I prepared a couple of slides to explain the general idea of the project and the functions. This ended up being useless because the next evaluators were already so far more advanced than I was. The diagram & slides are put here for documentation purposes.
There were no significant problems in going for the bonus. An issue was however raised during one of the evaluations in regards to how the instruction for the bonus has to interpreted. I was not aware of this beforehand because the code passed the normal francinette tests, and I didn't even bother to make other checks. Still passed the machine evaluation in the end.

```
get_next_line
 ┣ gnl_v1
 ┃ ┣ README.md
 ┃ ┣ get_next_line.c
 ┃ ┣ get_next_line.h
 ┃ ┣ get_next_line_utils.c
 ┃ ┗ main.c
 ┣ gnl_v2
 ┃ ┣ clean_without_comments
 ┃ ┃ ┣ get_next_line.c
 ┃ ┃ ┣ get_next_line.h
 ┃ ┃ ┣ get_next_line_bonus.c
 ┃ ┃ ┣ get_next_line_bonus.h
 ┃ ┃ ┣ get_next_line_utils.c
 ┃ ┃ ┗ get_next_line_utils_bonus.c
 ┃ ┣ pres
 ┃ ┃ ┣ get_next_line1.svg
 ┃ ┃ ┣ get_next_line2.svg
 ┃ ┃ ┣ get_next_line3.svg
 ┃ ┃ ┣ get_next_line4.svg
 ┃ ┃ ┗ get_next_line5.svg
 ┃ ┣ txts
 ┃ ┃ ┣ HP_verylong.txt
 ┃ ┃ ┣ empty.txt
 ┃ ┃ ┣ lorem1.txt
 ┃ ┃ ┗ lorem2.txt
 ┃ ┣ README.md
 ┃ ┣ get_next_line.c
 ┃ ┣ get_next_line.h
 ┃ ┣ get_next_line_bonus.c
 ┃ ┣ get_next_line_bonus.h
 ┃ ┣ get_next_line_utils.c
 ┃ ┣ get_next_line_utils_bonus.c
 ┃ ┣ main.c
 ┃ ┗ main_bonus.c
 ┗ README.md
```
