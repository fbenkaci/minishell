# minishell
Réimplémentation d'un shell Unix en C, réalisée dans le cadre du cursus 42. minishell interprète et exécute des commandes, gère les pipes, redirections, variables d'environnement et signaux, à l'image de bash. Un projet complet pour comprendre le fonctionnement interne d'un interpréteur de commandes.


# 🐚 Minishell

Un mini shell développé en C, reproduisant les fonctionnalités de base de bash.

![Status](https://img.shields.io/badge/status-terminé-brightgreen)
![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-MIT-blue)

## 📖 À propos

Minishell est un projet du cursus 42 consistant à recoder un interpréteur de commandes simplifié en C. Il gère l'exécution de commandes, les pipes, les redirections, les variables d'environnement et certaines built-ins, en s'appuyant uniquement sur la bibliothèque **readline** et les appels système POSIX.

## ✨ Fonctionnalités

- 🔧 Exécution de commandes externes (via `PATH` ou chemin absolu/relatif)
- 🔗 Pipes (`|`)
- 📤 Redirections (`<`, `>`, `>>`, `<<` heredoc)
- 💬 Gestion des quotes simples et doubles
- 🌱 Gestion des variables d'environnement (`$VAR`, `$?`)
- ⌨️ Builtins :
  - `echo` (avec option `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- 🚦 Gestion des signaux (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- 🧹 Gestion propre de la mémoire (pas de leaks)

## 🛠️ Stack technique

- **Langage** : C
- **Bibliothèque** : readline
- **Build** : Makefile

## 🚀 Installation

### Prérequis

- `gcc` ou `clang`
- `make`
- La bibliothèque `readline` installée

```bash
# Sur Linux (Debian/Ubuntu)
sudo apt-get install libreadline-dev
```

### Compilation

```bash
git clone https://github.com/votre-user/minishell.git
cd minishell
make
```

### Lancement

```bash
./minishell
```

## 🎮 Utilisation

```bash
minishell$ echo "Hello world"
Hello world

minishell$ ls -la | grep minishell

minishell$ cat < input.txt > output.txt

minishell$ export MY_VAR=42 && echo $MY_VAR
42

minishell$ exit
```

## 🧪 Commandes Makefile

| Commande | Description |
|----------|-------------|
| `make` | Compile le projet |
| `make clean` | Supprime les fichiers objets |
| `make fclean` | Supprime les objets et l'exécutable |
| `make re` | Recompile entièrement le projet |

## 👥 Auteurs

Projet réalisé dans le cadre du cursus **42**.

## 📜 Licence

Distribué sous licence MIT — voir le fichier `LICENSE`.
