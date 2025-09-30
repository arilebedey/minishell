#### Trailing ? after exitcode

🥸 💻 petitshell> echo $?
130?
🥸 💻 petitshell>

#### Backslash folie

🥸 💻 petitshell> echo \n hola
\n hola
🥸 💻 petitshell>

bash-5.3$ echo \n hola
n hola
bash-5.3$

🥸 💻 petitshell> echo \$HOME
\/Users/ari
🥸 💻 petitshell>

bash-5.3$ echo \$HOME
$HOME
bash-5.3$

#### Guillemets folie

🥸 💻 petitshell> ""''echo hola""'''' que""'' tal""''
/opt/homebrew/opt/ruby/bin/: Permission denied
🥸 💻 petitshell>

bash-5.3$ ""''echo hola""'''' que""'' tal""''
hola que tal
bash-5.3$

#### -n folie

🥸 💻 petitshell> echo -n -n SLT
-n SLT🥸 💻 petitshell>

bash-5.3$ echo -n -n SLT
SLTbash-5.3$

🥸 💻 petitshell> echo -nnnn
-nnnn
🥸 💻 petitshell>

bash-5.3$ echo -nnnnnn
bash-5.3$

#### Quotes folie

🥸 💻 petitshell> echo "$"

🥸 💻 petitshell>

bash-5.3$ echo "$"
$
bash-5.3$

($ manquant - incomprehensible)

#### On peut se faire exploser pour ce message en vrai

🥸 💻 petitshell> echo > <
error: what did u put next to > ??
🥸 💻 petitshell>
