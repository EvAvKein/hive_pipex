# PIPEX

My 7th project at 42 Network's Hive Helsinki 🐝

Replicating shell's piping and redirection using child processes

> [!TIP]
> If you're at a 42 school and doing this project: It's genuinely so much better to ask fellow students instead of reading online solutions ✨

---

## Description

This project's about replicating the basic behavior of the following shell script:  
`< infile cmd1 | cmd2 > outfile`

The bonus is about:
- Handling more than two commands (e.g. `< infile cmd1 | cmd2 | cmd3 > outfile`)
- Replicating the basic behavior following shell script:  
`cm1 << limiter | cmd2 >> appendfile`  

> 
> 

---

## Usage

> [!NOTE]
> Code was written and tested for Linux (using Hive's Ubuntu iMacs)

### Basic
- Run `make` (or even `make neat`!)
- Run the program as `./pipex <infile> <cmd1> <cmd2> <outfile>`

### Bonus
- Run `make bonus`
- Run the program as:
	- `./pipex_bonus <infile> <cmd1> <cmd2> <optionally, even more commandss!> <outfile>`
	- `./pipex_bonus here_doc <heredoc limiter> <cmd1> <cmd2> <optionally, even more commandss!> <appendfile>`

(Running the `pipex` or `pipex_bonus` without extra arguments will show this info along with the equivalent shell functionalities)

---

## Credits

- [Eve Keinan](https://github.com/EvAvKein)
