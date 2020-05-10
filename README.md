# corewar

Made with [thberrid](https://github.com/thberrid) and [johis](https://github.com/johis2808) 

**compilation**

le projet est séparé en deux parties.
- Le compilateur `asm`
- La VM `corewar`

Il est possible de compiler une partie avec la commande `make` suivie du nom de la partie voulue:
`make asm`
Un appel à make sans autre argument compilera les deux projets.

La vm possède deux option de compilations pouvant être activée ou non lors de l'appel à la commande `make`.
- `G` pour "graphique": Si cette variable est à `TRUE`, la vm sera compilée en version GUI(graphique). Version CLI(terminal) si non. (⚠ Cette option nécessite d'être sur la branche `visu` du repo et requiert les bibliotheques SDL2 et glm ainsi qu'une compatibilité OpenGL 3.2 au minimum).
- `ZAZ` pour activer la copie du comportement de zaz. Ce projet a été réalisé dans dans un cadre scolaire en respectant un sujet précis. néanmoins, certaines spécifications du sujet étaient incompatibles avec la vm d'exemple fournie. Si ce flag est à `TRUE`, la vm cherchera à correspondre à celle de zaz u détriment du sujet.

Par exemple, `make corewar ZAZ=TRUE G=TRUE` compilera la vm (corewar) de manière à reproduire le comportement de `zaz` et en version `graphique`

**composition**

- header : magic file (4 octets), name (PROG_NAME_LENGTH), prog_size (4 octets, ne tient pas compte du poids du header), commentaires (COMMENT_LENGTH)
- chaque instructions : son op_code (1 octet),  l'octet d'encodage (entre 0 et 1 octet), suivi des paramètres (de 1 à 3, chacun de 1, 2 ou 4 octets)


**instructions**

**l'octet d'encodage** : indique le type des arguments.

- REG (1 / 01)
- DIR (2 / 10)
- IND (3 / 11)

la dernière paire de bits est vide  
00 (P1), 00 (P2), 00 (P3), 00 (empty)
Par exemple : 
`r1, 23, %label` a pour octet d'encodage `01` `11` `10` `00` soit `0x78`

**note** : l'octet d'encodage est optionnel. Sa présence est indiquée par la variable booléenne t_op.ocp

---

**les paramètres**

- registre : 1 octet (rN)
- direct : 2 ou 4 octets, selon t_op.hdir, %valeur ou %:label
- indirect : 2 octets valeur ou :label

--- 

**résumé, exemples**

**and 42,%23,r1** devient

- op code: `6`

- octet d'encodage: `11 10 01 00 (0xe4)`

- paramètres: 
42      => `00 2a`
%23     => `00 00 00 17`
r1 => `01`

Soit au final
`06` `e4` `00 2a` `00 00 00 17`  `01`

 
**lldi 42,%23,r1** devient `0e` `e4` `00 2a` `00 17` `01`
- Ici le second parametre est encodé sur 2 octets seulement (t_op.hdir == 1)

**live %1** devient `01` `00 00 00 01`
- Ici, il n'y a pas d'ocp, seulement l'op_code suivit du parametre direct encodé sur 4 octets

---

**encodage des labels**

- à quoi correspond la valeur d'un label donné en parametre DIR || IND ? au nombre d'octets entre l'appel et sa déclaration 
Si la declaration précède l'appel : ff ff ff ff - N octets + 1 (ou ff ff - N octets + 1 s'il s'agit d'un parametre encodé sur 2 octets)
Si la declaration suit l'appel : 0 + N octets

Par exemple :

```
label1: ld %:label2,r1
label2: ld %:label2,r1
        ld %:label1,r1
```

donnera

```
02 90 00 00 00 07 01
02 90 00 00 00 00 01
02 90 ff ff ff f2 01
```
**Explication** : chaque instruction a ici une longueur de 7 octets. Le premier paramètre pointant sur l'instruction suivante vaut donc ```00 00 00 07```, le second pointant sur-lui même ```00 00 00 00```, et le dernier pointant sur deux instructions plus tôt ff ff ff ff - (2 * 7) + 1  donnant ```ff ff ff f2```
