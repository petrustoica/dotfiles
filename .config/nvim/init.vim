set nocompatible
set showmatch
set hlsearch
set tabstop=4
set softtabstop=4
set expandtab
set shiftwidth=4
set autoindent
set number
set relativenumber
set noswapfile

set shell=/usr/bin/zsh

set clipboard=unnamedplus
set fileformat=unix
set fileformats=unix,dos,mac
filetype on
syntax on

set ignorecase
set smartcase

set foldenable
set foldmethod=manual
set foldlevel=99

set wrap linebreak

set lazyredraw
set updatetime=300
set shortmess+=c
set whichwrap+=h,l

nnoremap j gj
nnoremap k gk
nnoremap gj j
nnoremap gk k

call plug#begin('~/.local/share/nvim/plugged')
Plug 'nvim-treesitter/nvim-treesitter', {'branch': 'master'} 
Plug 'cloudhead/neovim-fuzzy'
Plug 'xiyaowong/transparent.nvim'
Plug 'EdenEast/nightfox.nvim' 
" Plug 'SirVer/ultisnips'
Plug 'nvim-lualine/lualine.nvim'
" If you want to have icons in your statusline choose one of these
Plug 'nvim-tree/nvim-web-devicons'
Plug 'honza/vim-snippets'
Plug 'nvim-tree/nvim-tree.lua'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
call plug#end()

lua << EOF
require'nvim-treesitter.configs'.setup {
    highlight = {
        enable = true    
    }
}
require('lualine').setup()
require('nvim-tree').setup()
EOF

colorscheme carbonfox 

" let g:UltiSnipsExpandTrigger="<tab>"
" let g:UltiSnipsJumpForwardTrigger="<c-b>"
" let g:UltiSnipsJumpBackwardTrigger="<c-z>"
" let g:UltiSnipsEditSplit="vertical"

" inoremap <silent><expr> <Down>
      \ coc#pum#visible() ? coc#pum#next(1) :
      \ CheckBackspace() ? "\<Down>" :
      \ coc#refresh()
" inoremap <expr><Up> coc#pum#visible() ? coc#pum#prev(1) : "\<C-h>"

" Make <CR> to accept selected completion item or notify coc.nvim to format
" <C-g>u breaks current undo, please make your own choice
 inoremap <silent><expr> <TAB> 
    \coc#pum#visible() ? coc#pum#confirm() :
    \ "\<TAB>"

tnoremap <Esc> <C-\><C-n>

nnoremap <C-h> <C-w><C-<>
nnoremap <C-j> <C-w><C-+>
nnoremap <C-k> <C-w><C-->
nnoremap <C-l> <C-w><C->>

nmap <silent> gs : call CocAction('jumpDefinition', 'split')<CR>
nmap <silent> gv : call CocAction('jumpDefinition', 'vsplit')<CR>
nmap <silent> gt : call CocAction('jumpDefinition', 'tabe')<CR>
nmap <silent> gd : call CocAction('jumpDefinition')<CR>

function! CheckBackspace() abort
  let col = col('.') - 1
  return !col || getline('.')[col - 1]  =~# '\s'
endfunction


nnoremap <C-p> :FuzzyOpen<CR>
