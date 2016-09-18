## [*Git*](http://git-scm.com/) & [*GitHub*](http://github.org/)
**Guides**
- [<sup>*廖雪峰的官方网站* </sup>*Git教程*](http://liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000)

**Articles**
- [<sup>*Chris Beams* </sup>*How to Write a Git Commit Message*](http://chris.beams.io/posts/git-commit/)
- [<sup>*阮一峰的网络日志* </sup>*Commit message 和 Change log 编写指南*](http://ruanyifeng.com/blog/2016/01/commit_message_change_log.html)

### Tips
**Repository<sub> 仓库</sub>**

`git init`

`git status`

master

****

查看提交历史 `git log`

commit - commit - commit<sub> 提交</sub>

HEAD~3 HEAD^^ HEAD^ HEAD

`git reset <commit>`

for all command
查看命令历史 `git reflog`

### Working<sub> 工作区</sub>, Stage<sub> 暂存区</sub> & Branch<sub> 分支</sub>
```
.-----------.   .-----------.   .-----------.   git status
|  Working  |   |   Stage   |   |  Branch   |   git diff <file>
|           |   |           |   |           |
|  .-----.  |(1)|  .-----.  |   |           |
|  | WKG | ======> | WKG |  |   |           |   (1): git add/rm <file>
|  `-----'  |   |  `-----'  |   |           |
|  .-----.  |(2)|  .-----.  |   |           |
|  | STG | <====== | STG |  |   |           |   (2): git checkout -- <file>
|  `-----'  |   |  `-----'  |   |           |      |
|  .-----.  |   |    (2)    |   |  .-----.  |      |
|  | BR. | <====================== | BR. |  |   (2)/
|  `-----'  |   |           |   |  `-----'  |
|           |   |  .-----.  |(3)|  .-----.  |
|           |   |  | STG | ======> | STG |  |   (3): git commit
|           |   |  `-----'  |   |  `-----'  |
|  .-----.  |(4)|  .- - -.  |   |           |
|  | STG | <====== . STG .  |   |           |   (4): git reset HEAD <file>
|  `-----'  |   |  `- - -'  |   |           |
`-----------'   `-----------'   `-----------'
```

### Commits in Branch
```
.-----------.
|  Branch   |
|           |
|  Commit 1  |
                HEAD>  6  <HEAD
           git log |   |   ^                              git log --graph
git reset --hard 4 |   5   | git reset --hard 6
                   v   |   | git reflog
                HEAD>  4  <HEAD

git tag <tag>
git tag <tag> <commit>
git tag -d <tag>

git push <repository> <tagname>
git push <repository> --tags

git tag -d <tag>
git push <repository> :refs/tags/<tag>
```

### Branches in Repository
```
        mastar
1  2  3  4
         dev
         gh-gragh
         issue-n
         feature-xxx

git branch
git branch 
git checkout <branch>
git checkout -b <branch>
git merge <branch>
git merge --no-ff <branch>
git branch -d <branch>

git stash
git stash list
git stash apply [stash]
git stash drop
git stash pop
```

### Repositories
```
git clone <uri>

git remote [-v]
git remote add <repository> <uri>
git push <repository> <branch>
git pull

git branch --set-upstream <branch> <repository>/<branch>

git checkout -b <branch> <repository>/<branch>
```
