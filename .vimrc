set colorcolumn=100

set makeprg=make\ -C\ build\ -j6
nnoremap <F3> :! clear; cd build; cmake ../src ; cd -<cr>
nnoremap <F4> :make!<cr>
nnoremap <F5> :!./build/proto2<cr>
