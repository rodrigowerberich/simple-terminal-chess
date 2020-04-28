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
7| B-PA | B-PB | B-PC | B-PD | B-PE | B-PI | B-PG | B-PH | 
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
2| W-PA | W-PB | W-PC | W-PD | W-PE | W-PI | W-PG | W-PH | 
 |______|______|______|______|______|______|______|______| 
 |      |      |      |      |      |      |      |      | 
1| W-RA | W-kB | W-BC | W-Q  | W-K  | W-BF | W-kG | W-RH | 
 |______|______|______|______|______|______|______|______| 
     A      B      C      D      E      F      G      H    
  

```

## Scenario 1:  Normal moving example <a name="Scenario1"></a>

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

BF G2
```
[More Details](./scenarios_visualization.md#Scenario2)
