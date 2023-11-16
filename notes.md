# TOFIX

- QUOTES NON FERMES : ajouter un prompt puis strjoin avec la line d'avant
- $ tout seul sans variable : à traiter comme un char littéral
- Gérer les variables avec plusieurs :: pour ne pas perdre ces :: dans les values


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

		LITTERAL	--> (0)		An argument
		PIPE		-->	(1)		pipe (|)
		RI			-->	(2)		redirecting input (<)
		HEREDOC		-->	(3)		here documents (<<)
		RO			-->	(4)		redirecting output (>)
		ARO			-->	(5)		appending redirecting output (>>)

## Checker que les quotes sont bien fermées lors de l'input ?

## QUELQUES CAS PARTICULIERS

### RMQ : Multiples Redirecting Input

Quand on a de multiples redirecting input 
  --> cat <firstfile <secondfile
  Seul le dernier redirecting input de la commande est pris en compte

### RMQ : Comportement avec pipe et redirecting outputs

--> ls >> outfile | cat --> cat n'imprime rien car la sortie de ls est dans l'outfile, donc on n'envoie aucune entrée à la commande cat

# Environment

On a une structure qui stocke l'environnement : 
- char *key : La clef de la variable (ce qui se trouve avant le premier signe égal)
- char **values : les valeurs de la variable (séparées par ':' s'il y en a plusieurs)