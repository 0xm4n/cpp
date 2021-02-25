

### commit

usage: git commit

A commit in  a git repository records a snapshot of all the (tracked) files in your directory.

### branch

usage:	git branch <new_branch_name> + git checkout <new_branch_name>

alias: git checkout -b <new_branch_name>

branches are simply pointers to a specific commit. Branch early, and branch often. A new branch will include the work of current commit and all parent commits. Checkout command can change to another branch.

git branch -f <branch_name> <sha1-commit-hash>: moving a non-checked out branch pointer to another commit.

git branch -f main HEAD~3

moves (by force) the main branch to three parents behind HEAD.

### merge

usage: git merge <branch_name>

combine the work from two different branches together. This will allow us to branch off, develop a new feature, and then combine it back in.

### rebase

usage: git rebase <branch_name>

The second way of combining work between branches is rebasing. Rebasing essentially takes a set of commits, "copies" them, and plops them down somewhere else. The advantage of rebasing is that it can be used to make a nice linear sequence of commits. The commit log of the repo will be a lot cleaner if only.

specifying commits by their hash isn't the most convenient thing ever, which is why Git has relative refs. They are awesome! With relative refs, you can start somewhere memorable (like the branch `bugFix` or `HEAD`) and work from there.

rebase -i = cherry-pick



### HEAD

HEAD is the symbolic name for the currently checked out commit -- it's essentially what commit you're working on top of. HEAD always points to the most recent commit which is reflected in the working tree. 

Detaching HEAD just means attaching it to a commit instead of a branch. This is what it looks like beforehand: HEAD -> main -> C1 (git checkout C1) then it's HEAD -> C1.



### Relative Refs

the Caret (^) operator. Each time you append that to a ref name, you are telling Git to find the parent of the specified commit. So saying `main^` is equivalent to "the first parent of `main`". main^^` is the grandparent (second-generation ancestor) of `main

The tilde operator (optionally) takes in a trailing number that specifies the number of parents you would like to ascend.

### log

usage: git log

use git log to  see hashes. The upside is that Git is smart about hashes. It only requires you to specify enough characters of the hash until it uniquely identifies the commit.

### reset

usage: git reset <commit>

`git reset` reverts changes by moving a branch reference backwards in time to an older commit. In this sense you can think of it as "rewriting history;" `git reset` will move a branch backwards as if the commit had never been made in the first place.

While resetting works great for local branches on your own machine, its method of "rewriting history" doesn't work for remote branches that others are using.

### revert

In order to reverse changes and *share* those reversed changes with others, we need to use `git revert`. Let's see it in action. a new commit plopped down below the commit we wanted to reverse. That's because this new commit `C2'` introduces *changes* -- it just happens to introduce changes that exactly reverses the commit of `C2`. With reverting, you can push out your changes to share with others.



### cherry-pick

usage: git cherry-pick <Commit1> <Commit2> <...>

It's a very straightforward way of saying that you would like to copy a series of commits below your current location (`HEAD`). I personally love `cherry-pick` because there is very little magic involved and it's easy to understand.



### checkout

usage: git checkout <branch_name>

​			git checkout <commit>

​			git checkout <tag_name>

### tag

usage: git tag <tag_name> <commit>

they (somewhat) permanently mark certain commits as "milestones" that you can then reference like a branch. More importantly though, they never move as more commits are created. You can't "check out" a tag and then complete work on that tag -- tags exist as anchors in the commit tree that designate certain spots.



### clone

### fetch

`git fetch` performs two main steps, and two main steps only. It:

- downloads the commits that the remote has but are missing from our local repository, and...
- updates where our remote branches point (for instance, `o/main`)

`git fetch` essentially brings our *local* representation of the remote repository into synchronization with what the *actual* remote repository looks like (right now).

`git fetch`, however, does not change anything about *your* local state. It will not update your `main` branch or change anything about how your file system looks right now.

### pull

once you have new commits available locally, you can incorporate them as if they were just normal commits on other branches. This means you could execute commands like:

- `git cherry-pick o/main`
- `git rebase o/main`
- `git merge o/main`

In fact, the workflow of *fetching* remote changes and then *merging* them is so common that git actually provides a command that does both at once! That command is `git pull`.