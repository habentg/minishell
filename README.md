# littleshell

 ls >> zfolder/b >> zfolder/e  >> zfolder/c  >> zfolder/d >> zfolder/a (where a is an permission invalid file)
    * bash is creating the files
    * I am unlinking ever previous iofd, none of the files before "a" are created (remaining)
-> fixed : I was unlinking the files from my file system.
//
ሚ  ኒ ሸ ል $▸ << k < file cat
heredoc> k
minishell(55646,0x117347dc0) malloc: *** error for object 0x7fd3c5704210: pointer being freed was not allocated
minishell(55646,0x117347dc0) malloc: *** set a breakpoint in malloc_error_break to debug
[1]    55646 abort      ./minishell
➜  minishell git:(master) ✗ 

-> fixed : In removing the previous iofds, I was setting input file to NULL in when I checked for the presence of delimeter (stupid)
