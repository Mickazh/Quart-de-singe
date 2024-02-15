# Quart-de-singe
Jeu du quart de singe en C++.

Le jeu peut être jouer par des humains ou par des "robots"
Pour compiler le projet :
>cd .\src
> gcc *.cpp -o sae
> ./sae *Paramètres*

Les paramètres sont H pour un humain et R pour un robot.
Par exemple :
> ./sae HRR

La partie commencera avec un humain, puis deux robots joueront.

# Règles
Les joueurs annoncent à tour de rôle une lettre qui vient compléter un mot. Un joueur donnant une lettre terminant un mot existant (de plus de deux lettres) perd la manche et est gratifié d’un quart de singe. Le joueur courant devant annoncer une lettre peut préférer demander au joueur précédant à quel mot il pense. Si ce dernier est incapable de donner un mot existant et qui soit cohérent avec les lettres déjà annoncées, il perd la manche. Dans le cas contraire, c’est le joueur qui a posé la question qui perd la manche. Le premier joueur ayant récolté quatre quarts de singe perd la partie.

Admettons que, lors des tours précédents d’une manche, les lettres ’A’, ’B’, ’A’ et ’C’ ont été annoncées dans cet ordre. Si le joueur courant annonce ’A’, il perd la manche car le mot ”ABACA” est un mot existant (c’est une matière textile). Si par contre, il joue ’U’ et que le joueur suivant lui demande à quel mot il pense, il pourra répondre ”ABACULE” (c’est un petit élément cubique d’une mosaïque) et ce joueur écopera d’un quart de singe. Les mots retenus sont ceux acceptés au Scrabble, les accents sont ignorés et les verbes peuvent être conjugués.
