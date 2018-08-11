"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"
"目标：新建的.sh文件，自动插入头文件

autocmd BufNewFile *.sh exec ":call SetTitle()"
""定义函数SetTitle(), 用于自动插入头文件
func SteTitle()
    if &filetype == 'sh' 
        call setline(1, "#                           hello! world!                               ")
        call setline(2, "########################################################################")
        call setline(3, "#--------> File Name:".expand("%"))
        call setline(4, "#--------> Version: 1.0")
        call setline(5, "#--------> Author: peranda")
        call setline(6, "#--------> Mail: 1365227825@qq.com")
        call setline(7, "#--------> Created Time:" .strftime("%F %T"))
        call setline(8, "########################################################################")
        call setline(9, "#!/bin/bash")
        call setline(10, "")
    endif
endfunc
