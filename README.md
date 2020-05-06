# Chess in Terminal 

The idea is to create a simple chess application

A regular chess terminal application for two players.

The game consists of 16 pieces on each side
2x Rook - RA, RB 
2x Knight - KB, KG
2x Bishop - BC, BE
1x Queen - Q
1x King - K
8x Pawn - PA,PB,PC,PD,PE,PF,PG,PH

```
  ______ ______ ______ ______ ______ ______ ______ ______ 
 |      |      |      |      |      |      |      |      | 
8| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
7| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
6|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
5|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
4|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
3|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
2| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
1| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH | 
 |______|______|______|______|______|______|______|______| 
     A      B      C      D      E      F      G      H    
  

```

## Scenario 1:  Normal moving <a name="Scenario1"></a>

```
Turn 1 - Player 1
PA A3
Moving PA to A3
Turn 2 - Player 2
PC C5
Moving PC to C5
``` 
[More Details](./scenarios_visualization.md#Scenario1)

## Scenario 2: Trying to move to a blocked space <a name="Scenario2"></a>

```
Turn X - Player 1
BF D3
Attempted move is not possible!
Blocked by W-PE!
BF G2
Moving BF to G2
```
[More Details](./scenarios_visualization.md#Scenario2)

## Scenario 3: Trying to do an invalid move <a name="Scenario3"></a>

```
Turn X - Player 1
kB B2
Attempted move is not allowed!
Knights can only move in a L shape movement.
Possible end positions for kB are:
C3
kB C3
Moving kB to C3
```
[More Details](./scenarios_visualization.md#Scenario2)

## Scenario 4: Trying to move to an out of bounds position <a name="Scenario4"></a>

Example 1:
```
Turn X - Player 1
kB B9
Attempted move is out of bounds!
kB C3
Moving kB to C3
```

Example 2:
```
Turn X - Player 1
kB P5
Attempted move is out of bounds!
kB C3
Moving kB to C3
```

[More Details](./scenarios_visualization.md#Scenario2)

## Scenario 5: Attempting to move non existent piece: <a name="Scenario5"></a>

```
Turn X - Player 1
kT C3
kT is not a valid chess piece.
Did you mean kB or kG?
kB C3
Moving kB to C3
```

## Scenario 6: Moving to an enemy occupied position (capturing): <a name="Scenario6"></a>

```
Turn X - Player 2
PC B4
B-PC is capturing W-PB!
W-PB was captured!

```



## Scenario 7: Castling <a name="Scenario7"></a>

Castling long
```
Turn X - Player 2
castling long
Moving B-K to C8
Moving B-RA to D8
```

Castling short
```
Turn X - Player 1
castling short
Moving W-K to G1
Moving W-RA to F1
```

However, there are a number of rules when castling is possible and when not. You can only castle, if:

1. Your king has not moved in the game yet.
2. Your king is not in check.
3. The king does not castle through a square which is controlled by an opponent’s piece.
4. The king is not in check after castling.
5. The rook has not been moved in the game yet.


## Scenario 8: Inserting invalid command <a name="Scenario8"></a>

Example:
```
Turn X - Player 1
kB JA3
Invalid command!
Did you mean kB A3?
kB A3
Moving kB A3
```

## Scenario 9: Asking to visualize the field <a name="Scenario8"></a>

Example:
```
Turn X - Player 1
visualize field
  ______ ______ ______ ______ ______ ______ ______ ______ 
 |      |      |      |      |      |      |      |      | 
8| B-RA | B-kB | B-BC | B-Q  | B-K  | B-BF | B-kG | B-RH | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
7| B-PA | B-PB | B-PC | B-PD | B-PE | B-PF | B-PG | B-PH | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
6|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
5|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
4|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
3|      |      |      |      |      |      |      |      | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
2| W-PA | W-PB | W-PC | W-PD | W-PE | W-PF | W-PG | W-PH | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
1| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH | 
 |______|______|______|______|______|______|______|______| 
     A      B      C      D      E      F      G      H    
PB A4
```
