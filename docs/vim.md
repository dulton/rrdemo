## [*Vim*](http://vim.org/)

**References**
- [*Vimdoc*](http://vimdoc.sf.net/)<sub> [cmn-Hans](http://vimcdoc.sf.net/)</sub>
    - [<sup>*Vim documentation* </sup>*quickref*](http://vimdoc.sf.net/htmldoc/quickref.html)<sub> [cmn-Hans](http://vimcdoc.sf.net/doc/quickref.html)</sub>
    - [<sup>*Vim documentation* </sup>*intro*](http://vimdoc.sf.net/htmldoc/intro.html)<sub> [cmn-Hans](http://vimcdoc.sf.net/doc/intro.html)</sub>
    - [<sup>*Vim documentation* </sup>*help*](http://vimdoc.sf.net/htmldoc/help.html)<sub> [cmn-Hans](http://vimcdoc.sf.net/doc/help.html)</sub>
    - [<sup>*Vim documentation* </sup>*helphelp*](http://vimdoc.sf.net/htmldoc/helphelp.html)<sub> [cmn-Hans](http://vimcdoc.sf.net/doc/helphelp.html)</sub>
    - <sup>*Vim documentation* </sup>*index*<sub> [cmn-Hans](http://vimcdoc.sf.net/doc/index.html)</sub>

**Notes**
```
Moving

< gT                                  #gt                                   gt >

.------------------------------------ FILE ------------------------------------.
| gg                                                                           |
|                                                                              |
Z #G ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Z
|                                                                              |
. - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - CTRL-B .
|                                                                    Backwards |
|                              CTRL-O  ``  CTRL-I                              |
|                                                                              |
|                                                                              |
|                                m@  :marks  `@                         CTRL-U |
|                                                                      Upwards |
|                                                                              |
|                                 ?  N   n  /                                  |
|                                                                       CTRL-Y |
.----------------------------------- SCREEN -----------------------------------.
| H Home                                                                    zt |
|                                      %                                       |
|                      Backward  goto-    Word  End                            |
|                             B  gE    k     W  E                              |
| M Middle       0        ^         h     l              $                  zz |
|                             b  ge    j     w  e                              |
|                      backward  goto-    word  end                            |
|                              F  T  ,   ;  t  f                               |
| L Last                                                                    zb |
`------------------------------------------------------------------------------'
|                                                                       CTRL-E |
|                                      v    o                            Extra |
|                                      V                                       |
|                                 O    CTRL-V                                  |
|                         VISUAL                                        CTRL-D |
|                                 a-    sentence   paragraph         Downwards |
|                                 i-  -w  -W  -s  -p                           |
|                             inner   -b  -B  -t                               |
|                                  block Block tag                             |
' - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - CTRL-F '
|                                                                     Forwards |
Z #% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Z
|                                                                              |
| G                                                                            |
`------------------------------------------------------------------------------'
```

```
Editing                                                                u  CTRL-R
                     k                                                 U  .
LEGEND      0  ^  h     l  $  LINE  OTHER
                     j

                     O                                       dk
INSERT         I  i     a  A            DELETE   d  d0 d^ X     x  D  dd    J
                     o                                       dj

                     ck
CHANGE   c  c0 c^ ch    s  C  cc        REPLACE  R              r
                     cj       S

                     yk                                      P            BUFFER
COPY     y  y0 y^ yh    yl y$ yy        PASTE             P     p         "
                     yj       Y                              p            "+ SYS
```
