

### commit

usage: git commit

A commit in  a git repository records a snapshot of all the (tracked) files in your directory.

### branch

usage:	git branch <new_branch_name> + git checkout <new_branch_name>

alias: git checkout -b <new_branch_name>

branches are simply pointers to a specific commit. Branch early, and branch often. A new branch will include the work of current commit and all parent commits. Checkout command can change to another branch.

git branch -f <branch_name> <sha1-commit-hash>: moving a non-checked out branch pointer to another commit.

### merge

usage: git merge <branch_name>

combine the work from two different branches together. This will allow us to branch off, develop a new feature, and then combine it back in.

### rebase

usage: git rebase <branch_name>

The second way of combining work between branches is rebasing. Rebasing essentially takes a set of commits, "copies" them, and plops them down somewhere else. The advantage of rebasing is that it can be used to make a nice linear sequence of commits. The commit log of the repo will be a lot cleaner if only