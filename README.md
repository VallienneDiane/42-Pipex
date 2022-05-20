# PIPEX

## Lancer le programme

```$> ./pipex file1 cmd1 cmd2 file2```

file1 et file2 sont des noms de fichiers.
cmd1 et cmd2 sont des commandes shell avec leurs paramètres.

L’exécution du programme pipex a le même effet que la commande shell suivante :

```$> < file1 cmd1 | cmd2 > file2```
