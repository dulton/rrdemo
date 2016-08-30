# Git

## Do / Undo
```
.--------------.   .-----------------------------------.
| Working      |   |                Repository         |
| Directory    |   |       Stage       ..    Branch    |
| .-----.   git add/rm     .-----. git commit  .-----. |
| | Chg | ===============> | Chg | ==========> | Chg | |
| `-----'      |   |       `-----'     ||      `-----' |
| .- - -.  git checkout -- .-----.     ||              |
| .  X  . <=============== |     |     ||              |
| `- - -'      |   |       `-----'     ||              |
| .- - -.      |    git checkout --    ||      .-----. |
| .  X  . <=================================== |     | |
| `- - -'      |   |                   ||      `-----' |
| .-----.  git reset HEAD  .- - -.     ||              |
| | Chg | <=============== . Chg .     ||  git status  |
| `-----'      |   |       `- - -'     ||  git diff    |
`--------------'   `-------------------''--------------'
```

## Go Ahead / Go Back
```
                HEAD>  6  <HEAD
           git log |   |   ^
git reset --hard 4 |   5   | git reset --hard 6
                   v   |   | git reflog
                HEAD>  4  <HEAD 
```

## Push / Pull
