# PIPEX

Votre objectif est de coder le programme Pipex.
Il doit être exécuté de cette manière :

```$> ./pipex file1 cmd1 cmd2 file2```

file1 et file2 sont des noms de fichiers.
cmd1 et cmd2 sont des commandes shell avec leurs paramètres.

L’exécution du programme pipex a le même effet que la commande shell suivante :

```$> < file1 cmd1 | cmd2 > file2```

## FONCTIONS AUTORISEES

◦ access
◦ open
◦ unlink
◦ close
◦ read
◦ write
◦ malloc
◦ waitpid
◦ wait
◦ free
◦ pipe
◦ dup
◦ dup2
◦ execve
◦ fork
◦ perror
◦ strerror
◦ exit

### Open ()
``` int open(const char *pathname, int flags); ```
- Ouvrir ou créer éventuellement un fichier ou un périphérique 
- Étant donné le chemin pathname d'un fichier, open() renvoie un descripteur de fichier, un petit entier positif ou nul utilisable par des appels système ultérieurs (read(2), write(2), lseek(2), fcntl(2), etc.). Le descripteur de fichier renvoyé par un appel réussi sera le plus petit descripteur de fichier non encore ouvert pour le processus.
- Le paramètre flags doit inclure l'un des mode d'accès suivants : O_RDONLY, O_WRONLY ou O_RDWR (lecture seule, écriture seule, ou lecture-écriture).
- Les attributs de création de fichier sont O_CREAT, O_EXCL, O_NOCTTY et O_TRUNC

### Access()
```int access(const char *pathname, int mode);```
Vérifier les permissions d'utilisateur réel à un fichier.
L'appel renvoie 0 s'il réussit (toutes les requêtes sont autorisées), ou -1 s'il échoue.

### Pipe()
```int pipe(int pipefd[2]);```

- pipe() crée un tube, un canal unidirectionnel de données qui peut être utilisé pour la communication entre processus
- pipefd : tableau utilisé pour renvoyer deux files descriptors faisant référence à l'extrémité de lecture du tube.
pipefd[1] = extrémité d'écriture du tube
pipefd[0] = extrémité de lecture du tube
- renvoie 0 s'il réussit, ou -1 s'il échoue

pid_t data type stands for process identification and it is used to represent process ids. Whenever, we want to declare a variable that is going to be deal with the process ids we can use pid_t data type.

The type of pid_t data is a signed integer type

### Fork()
```pid_t fork(void); ```

- fork() crée un nouveau processus (fils) en dupliquant le processus appelant (père).
- Le fils a son propre identifiant de processus (PID).
- Le PPID (Parent Process ID) du fils est identique au PID du parent.
- En cas de succès, le PID du fils est renvoyé au processus parent, et 0 est renvoyé au processus fils. En cas d'échec -1 est renvoyé dans le contexte du parent.

### Dup2() 
```int dup2(int oldfd, int newfd);```

 Dupliquer un descripteur de fichier.
 dup() et dup2() renvoient le nouveau descripteur, ou -1 s'ils échouent.

### Execve()
```int execve(const char *fichier, char *const argv[], char *const envp[]); ```

- execve() exécute le programme correspondant au fichier. Celui-ci doit être un exécutable binaire ou bien un script.
- En cas de réussite, execve() ne revient pas, en cas d'échec il renvoie -1

### Wait() et Waitpid()
```pid_t waitpid(pid_t pid, int *status, int options);```
```int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);```

- L'appel système wait() suspend l'exécution du processus appelant jusqu'à ce que l'un de ses fils se termine.
- L'appel système waitpid() suspend l'exécution du processus appelant jusqu'à ce que le fils spécifié par son pid ait changé d'état. Par défaut, waitpid() n'attend que les fils terminés.

## ETAPES CODE

``` ./pipex infile cmd1 cmd2 outfile ```

1. Ouvrir/Créer les fichiers (open) 
2. Récupérer les commandes passées en entrée (split)
3. Récupérer le chemin menant aux commandes du terminal (substr, str_join, free)
4. Assigner une commande à un chemin, trouver les correspondances (access, str_join)
5. Créer un pipe entre les deux commandes (pipe, fork, dup2, execv, wait)
6. free / exit du programme


Dans le terminal :
env : 