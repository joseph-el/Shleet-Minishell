<h1 align="center">
	Shleet-Minishell
</h1>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/joseph-el/Shleet-Minishell?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/joseph-el/Shleet-Minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/joseph-el/Shleet-Minishell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/joseph-el/Shleet-Minishell?color=green" />

</p>
  <p align="center">
    <a href="https://github.com/anuraghazra/github-readme-stats/actions">
      <img alt="Tests Passing" src="https://github.com/anuraghazra/github-readme-stats/workflows/Test/badge.svg" />
    </a>
    <a href="https://github.com/anuraghazra/github-readme-stats/graphs/contributors">
      <img alt="GitHub Contributors" src="https://img.shields.io/github/contributors/anuraghazra/github-readme-stats" />
    </a>
    <a href="https://codecov.io/gh/anuraghazra/github-readme-stats">
      <img src="https://codecov.io/gh/anuraghazra/github-readme-stats/branch/master/graph/badge.svg" />
    </a>
  </p>
  
### About Shleet
- Shleet is a Unix-shell like [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)) written in C language by @joseph-el and (@ELkhalil)[https://github.com/ELkhalil]
### Features

###### Signal `Ctrl-D` `Ctrl-C` `Ctrl-\`
```bash
- Ctrl-D : This shortcut is used to signal the end of input or to "logout" of a shell.
- Ctrl-C : This shortcut is used to send a `SIGINT` signal to the currently running process, which usually causes it to terminate.
- Ctrl-\ : This shortcut is used to send a `SIGQUIT` signal to the currently running process, which will usually cause it to terminate and produce a core dump.
```

###### Conditionals (`&&` and `||`)
```bash
$> false && echo success || echo failure
```
###### Pipes `|`

```bash
$> cat /dev/random | cat -e | head | cat -e | head -n3 | cat -e | wc -l
```
###### Redirections (`<`, `<<`, `>` , `>>`)

```bash
$> < infile cat > outfile.txt
$> cat << "LIMIT" >> outfile.txt
```

###### Subshell ``( <cmdline> )``
```bash
$> ls -a && (ls -l || failed && sort) || (cat /dev/random | head -n4)
```

###### wildcard matching `*`

```bash
$> ls *.js
$> rm *T*L*S*.mp4
$> ls *
```
