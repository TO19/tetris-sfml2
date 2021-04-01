## Instalation du projet

### **Linux:**

Installer conan, cmake et clang sur votre systeme (apt, brew, etc...).

**Projet testé avec les versions suivantes:**

Ubuntu 20.04.2 LTS:

- Clang version 10.0.0-4ubuntu1
- Cmake version 3.16.3
- Conan version 1.33.1

1. Ajouter les remote pour Conan

```bash
    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

2. Utiliser Clang pour conan

> Libre a vous de créer un profile spécifique pour ce projet et de modifier les valeurs

```bash
    conan profile update settings.compiler=clang default
    conan profile update settings.compiler.version=10 default
    conan profile update settings.compiler.libcxx=libstdc++11 default
    conan profile update env.CC=$(which clang) default
    conan profile update env.CXX=$(which clang++) default
```

3. Exécuter le script pour télécharger et installer les libs

> Il se peut que votre système est besoin de lib en plus utilisé apt ou autre pour les installé

```bash
    ./scripts/install.sh
```

4. Build le projet avec CMake

```bash
    ./scripts/build.sh
```

5. Lancé le projet

```bash
    ./scripts/launch.sh
```

### **Mac:**

Macbook pro 2017 Big Sur:

- Apple clang version 12.0.0 (clang-1200.0.32.27)
- Cmake version 3.18.4
- Conan version 1.32.1

Sur macos le lancement est le meme que sur ubuntu.
Pensez seulement a changer les configs de conan suivant l'exemple suivant:

```bash
    conan profile update settings.compiler=apple-clang default
    conan profile update settings.compiler.version=12.0 default
    conan profile update settings.compiler.libcxx=libc++ default
    conan profile update env.CC=$(which clang) default
    conan profile update env.CXX=$(which clang++) default
```

## Setup de VSCode/Codium

Sources:

- https://code.visualstudio.com/docs/cpp/cmake-linux
- https://code.visualstudio.com/docs/cpp/c-cpp-properties-schema-reference
- https://code.visualstudio.com/docs/languages/cpp

1. Install C/C++ extension

   - [Lien market place](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

2. Vérifier et/ou ajouter les configurations

Regarder le dossier .vscode au root du projet il contient les differente configuration pour l'ide.
