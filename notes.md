MINISHELL

# Parsing & Tokenization

Afin de traiter les données entrées dans l'invite de commande, il faut séparer les éléments envoyés en différents **TOKENS**

## Séparation des éléments

- Les différents arguments envoyés sont séparés par des *espace*
- Cependant, les espaces ne sont pas pris en compte lorsqu'ils se situent entre des quotes (" ou ')
  - "yo yo" 		--> 1 TOKEN
  - yo yo 			--> 2 TOKENS
  - "yo yo" yo		--> 2 TOKENS
  - yo"yo""yo"yoyo 	--> 1 TOKEN (car pas d'espace entre les arguments)

Pour séparer les arguments, il faut donc ignorer les espaces quand on est entre quotes, et marquer la rupture quand on trouve un espace en dehors des quotes

RMQ : on n'a pas à prendre en compte le backslash qui nous amènerait à devoir traiter littérallement les espaces.

## Différents types de TOKENS

## Checker que les quotes sont bien fermées lors de l'input ?

## RMQ : Multiples Redirecting Input

- Quand on a de multiples redirecting input 
  --> cat <firstfile <secondfile
  Seul le dernier redirecting input de la commande est pris en compte