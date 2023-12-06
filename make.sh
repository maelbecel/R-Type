#!/usr/bin/env bash

make() {
    local compile_type="$1"

    git submodule update --init --recursive

    # Vérifier si le répertoire "build" n'existe pas
    if [ ! -d "build" ]; then
        # Créer le répertoire "build" s'il n'existe pas
        mkdir build
    fi

    # Se déplacer dans le répertoire "build"
    cd build

    echo "compile_type: $compile_type"

    # Exécuter les commandes cmake et ninja
    if [ "$compile_type" == "debug" ]; then
        cmake .. -G Ninja -DCOMPILE_DEBUG=ON --preset=vcpkg
    elif [ "$compile_type" == "examples" ]; then
        cmake .. -G Ninja -DCOMPILE_EXAMPLES=ON --preset=vcpkg
    elif [ "$compile_type" == "sandbox" ]; then
        cmake .. -G Ninja -DCOMPILE_SANDBOX=ON --preset=vcpkg
    else
        cmake .. -G Ninja --preset=vcpkg
    fi

    ninja

    # Revenir au répertoire parent
    cd ..
}

makeexamples() {
    make "examples"
}

makedebug() {
    make "debug"
}

makesandbox() {
    make "sandbox"
}

makesandbox() {
    mkdir build ; cd build ; cmake .. -DCOMPILE_SANDBOX=ON -G Ninja ; ninja ; cd ..
}

makeclean() {
    rm -rf *.log
}

makefclean() {
    makeclean
    rm -rf build
    rm -rf lib
    rm -rf bin_examples
    rm -rf r-type_client
    rm -rf r-type_server
}

makere() {
    local compile_type="$1"
    makefclean
    make "$compile_type"
}

# Fonction pour afficher le menu principal
display_menu() {
    echo "Menu Make:"
    echo "1. make"
    echo "2. make re"
    echo "3. make debug"
    echo "4. make clean"
    echo "5. make fclean"
    echo "6. Examples"
    echo "7. Sandbox"
    echo "0. Quitter"
}

# Fonction pour afficher le menu Examples
display_examples_menu() {
    echo "Menu Examples:"
    echo "1. make"
    echo "2. make re"
    echo "3. make clean"
    echo "4. make fclean"
    echo "0. Retour au menu principal"
    echo "00. Quitter"
}

# Fonction pour afficher le menu Sandbox
display_sandbox_menu() {
    echo "Menu Sandbox:"
    echo "1. make"
    echo "2. make re"
    echo "3. make clean"
    echo "4. make fclean"
    echo "0. Retour au menu principal"
    echo "00. Quitter"
}

# Boucle principale
while true; do
    display_menu

    # Demander à l'utilisateur de choisir une option
    read -p "Choisissez une option (0-6): " choice

    case $choice in
        0)
            echo "Au revoir!"
            break
            ;;
        1)
            make
            exit
            ;;
        2)
            makere
            exit
            ;;
        3)
            makedebug
            exit;;
        4)
            makeclean
            ;;
        5)
            makefclean
            ;;
        6)
            # Menu Examples
            while true; do
                display_examples_menu
                read -p "Choisissez une option (0-4): " examples_choice

                case $examples_choice in
                    0)
                        break
                        ;;
                    1)
                        makeexamples
                        exit
                        ;;
                    2)
                        makere "examples"
                        exit
                        ;;
                    3)
                        makeclean
                        ;;
                    4)
                        makefclean
                        ;;
                    00)
                        exit
                        ;;
                    *)
                        echo "Option invalide. Veuillez choisir une option valide."
                        ;;
                esac
            done
            ;;
        6)
            # Menu Sandbox
            while true; do
                display_sandbox_menu
                read -p "Choisissez une option (0-4): " sandbox_choice

                case $sandbox_choice in
                    0)
                        break
                        ;;
                    1)
                        makesandbox
                        exit
                        ;;
                    2)
                        makere "sandbox"
                        exit
                        ;;
                    3)
                        makeclean
                        ;;
                    4)
                        makefclean
                        ;;
                    00)
                        exit
                        ;;
                    *)
                        echo "Option invalide. Veuillez choisir une option valide."
                        ;;
                esac
            done
            ;;
        *)
            echo "Option invalide. Veuillez choisir une option valide."
            ;;
    esac
done
