#!/usr/bin/env bash

make() {
    local compile_type="$1"

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
        cmake .. -G Ninja -DCOMPILE_DEBUG=ON
    elif [ "$compile_type" == "examples" ]; then
        cmake .. -G Ninja -DCOMPILE_EXAMPLES=ON
    elif [ "$compile_type" == "sandbox" ]; then
        cmake .. -G Ninja -DCOMPILE_SANDBOX=ON
    elif [ "$compile_type" == "exodia" ]; then
        cmake .. -G Ninja -DCOMPILE_EDITOR=ON
    else
        cmake .. -G Ninja
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

makeexodia() {
    make "exodia"
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
    rm -rf exodia
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
    echo "8. Exodia"
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

# Fonction pour afficher le menu Sandbox
display_exodia_menu() {
    echo "Menu Exodia Editor:"
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
    read -p "Choisissez une option (0-8): " choice

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
        7)
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
        8)
            # Menu Exodia Editor
            while true; do
                display_exodia_menu
                read -p "Choisissez une option (0-4): " exodia_choice

                case $exodia_choice in
                    0)
                        break
                        ;;
                    1)
                        makeexodia
                        exit
                        ;;
                    2)
                        makere "exodia"
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
