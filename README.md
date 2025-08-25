# Git

### Recommendations

Try to work on different functionalities.

Use git branches and github merge request.

Push your branches to GitHub with working parts of your task regularly.

Have other teammate read and approve/disapprove the merge request (aka pull request) for it to merge for better code quality, shared understanding, and early detection of issues.

### Merging strategies for minishell

"Squash merge" with `git merge --squash` stages all changes from the feature branch as one commit. Run `git commit` afterward to finalize it.

"Simple merge" with `git merge` if you want to keep the commits plus a merge commit instead of only squash commit.

Avoid using `git rebase` onto main in this workflow — rebase applies commits one by one, which can lead to resolving the same conflicts multiple times. This is not ideal when teammates are working closely on the same files, as it slows everyone down. Rebase works better for keeping a personal branch history clean before sharing it.

Aim to merge/PR frequently. Only merge branches that compile.

### Example flow

```bash
# create branch off of main and switch to it
git checkout main
git pull origin main
git checkout -b feature-branch

# work on files
git add .
git commit -m "Implement feature XYZ"
# push branch to remote (github?)
git push -u origin feature-branch

# switch back to main and merge the feature branch onto it
git checkout main
git pull origin main
git merge --squash feature-branch
# or
#git merge feature-branch

# wait for merge approval -> delete branch
git branch -d feature-branch
```

### Warnings

Don't commit directly to `main` unless necessary.

Check what will be committed with `git status` before running `git add .`.

Use `git stash` to checkout other branches without having to commit your changes: `git stash push -m "WIP: a silly shell"` to stash all changes.

Never delete a branch until you are sure it’s merged and pushed.

### Link

freecodecamp git for pros: https://www.youtube.com/watch?v=Uszj_k0DGsg

# Minishell

### Subject

[EN] https://cdn.intra.42.fr/pdf/pdf/154328/en.subject.pdf

### Others' reference minishell implementations

https://github.com/decilap/groupdev/

https://github.com/ft-palourde/minishell

https://github.com/mli42/at42minishell

### Heredocs

Advice from 1 group : use forks for heredocs because to correctly handle either signals or correct exit codes

### Supress readline leaks

```sh
alias msv='valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp ./minishell'
```
