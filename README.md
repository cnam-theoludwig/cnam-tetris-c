# CNAM Tetris en C

## À propos

Développement d'une reproduction du jeu [Tetris](https://fr.wikipedia.org/wiki/Tetris) réalisé dans le cadre de la formation [Ingénieur en Informatique et Systèmes d'Information (SI), CNAM](https://www.itii-alsace.fr/formations/informatique-et-systemes-dinformation-le-cnam/), pour les modules d'Algorithmie et Structure de données en C.

[SUJET](./SUJET.md)

### Membres du groupe

- [Théo LUDWIG](https://github.com/theoludwig)
- [Vincent PETT](https://github.com/Vextriz)

## Prérequis

- [GNU coreutils](https://www.gnu.org/software/coreutils/)
- [GNU binutils](https://www.gnu.org/software/binutils/)
- [GNU gcc](https://gcc.gnu.org/)
- [GNU make](https://www.gnu.org/software/make/)
- [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
- [SDL 2](https://www.libsdl.org/) v2.32.2 (automatiquement installé avec `make`)
- [libcproject](https://github.com/theoludwig/libcproject) v5.1.0 (automatiquement installé avec `make`)

## Utilisation

```sh
# Compiler le programme
make

# Compiler et exécuter le programme
make run

# Vérification du formatage du code avec ClangFormat
make lint

# Nettoyage des fichiers générés
make clean
make clean-deps
# ou
make clean-all
```
