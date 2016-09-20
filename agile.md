## Agile

## Idea to Story
```
           .-------.    .---------.                         Mind Mapping
          -| WHY 1 |----| HOW 1-1 |
         / `-------'\   `---------'                   .----------------.
.-----. /            \                                |  Story 1-2-1   |
|     |/   .-------.  \ .---------.    .-----------.  | .------------. |
| WHO |----| WHY 2 |   -| HOW 1-2 |----| HOW 1-2-1 |----| WHAT 1-2-1 | |
|     |\   `-------'    `---------'\   `-----------'  | `------------' |
`-----' \                           \                 `----------------'
         \ .-------.                 \ .-----------.   | .-------------.
          -| WHY 3 |                  -| HOW 1-2-2 |   '>| Product Map |
           `-------'                   `-----------'     `-------------'
```

## (Dynamic) Requirements
```
.------------------.  Importance
| Requirement Pool |  Kano Model   satisfied ^        |         ___/
|------------------|                         |       /      ___/
|                  |                         |     _-   ___/
| Functional       |             DELIGHTERS  | ___- ___/   SATISFIERS
| Requirement      |                     ____|- ___/
|                  |  ___________--------    | /           perfection
|..................|  -----------------------+---------------------->
|                  |  lack              ___/ |    ________-----------
| Technical        |                ___/   __|----
| Requirement      |            ___/    _--  |  DISSATIFIERS
|                  |        ___/      _-     |
|..................|    ___/         /       |
|                  |   /            |        | unsatisfied
| Marketing        |  
| Requirement      |  Important  Important   Unimportant  Unimportant
|                  |  Urgent     Not Urgent  Urgent       Not Urgent
`------------------'  High -------------- Priority -------------> Low
```

## (Cursory) Plan
```
Ra 5u     ~50a  .---------.              u            unit(s)
Rb 2u     ~20a  | Rd      |              i   ideal man day(s)
Rc 2u     ~20a  | ...  1u |              a  actual man day(s)
Rd 1u ~5i ~10a  `---------'              w            week(s)
Re 3u     ~30a  .---------.   .---------.
Rf 2u     ~20a  | Rc      |   | Rf      |          a/i   ~50%
Rg 5u     ~50a  | ...  2u |   | ...  2u |          efficiency
                `---------'   `---------'
  .---------.   .---------.   .---------.   .---------.   ...
  | Ra      |   | Rb      |   | Re      |   | Rg      |   .
  | ...  5u |   | ...  2u |   | ...  3u |   | ...  5u |   .
  `---------'   `---------'   `---------'   `---------'   ...
    Plan A        Plan B        Plan C        Plan D
o=============>=============>=============>=============>=~~~
2016-8-1      10-10         12-19         2017-2-27     5-8
'-----10w-----'-----10w-----'-----10w-----'-----10w-----'-~~~
Start Up                    MileStone I          MileStone II
```

## (Iterative) Scrum
```
.------------------------------------------------------------------------------.
|                                   Product                                    |
|                                   Backlog                                    |
`------------------------------------------------------------------------------'
                                                         Explaining \.---------.
   .------.------.------.------.------.------.  Retelling            | Sprint  |
   | Task | Test | Task | Task | Task | Test |<----------------------| Backlog |
   `------'------'------'------'------'------'  Constructing         `---------'
>-============->-============->-============->-============->-============->  |
| Retelling    |         Daily Meeting & Burn Down          | Review       |  |
| Meeting      |              .              .              | Meeting      |  |
v..............v..............|. Developing .|..............v..............v  |
| Constructing |              '   Testing    '              | Explaining   |  |
| Meeting      |              Nightly Building              | Meeting      |<-'
5-============-4-============-3-============-2-============-1-============-0
```
