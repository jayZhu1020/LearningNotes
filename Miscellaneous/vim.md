# VIM commands

## Normal mode
Switch to edit mode 
* `i` insert before cursor
* `SHIFT + i` insert at the beginning of the line
* `o` append a new line below and insert
* `SHIFT + o` append a new line above the current line
* `a` insert after cursor
* `SHIFT + a` insert at the end of the line

Moving cusor on scrren
* `SHIFT + H` move to top of screen
* `SHIFT + M` move to middle of screen
* `SHIFT + L` move to bottom of screen

Moving cursor on the same line
* `w` or `SHIFT + RIGHT` jump forward to the start of the next word
* `e` jump forward to the end of the next word
* `b` or `SHIFT + LEFT` jump backward to the start of a word
* `ge` jump backward to the end of a word
* `0` jump to the start of the line
* `$` jump to the end of the line

Cut delete and paste
* `dd` delete current line
* `NUM + dd` delete `NUM` lines * `dd` delete current line

## Edit mode
* `r + CHAR` replace current character with `CHAR`
* `R + TEXT + ESC` replcae next few chracters with text untile `ESC`