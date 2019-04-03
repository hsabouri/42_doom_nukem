 #!/bin/bash
if [[ $# -lt 1 ]]
then
    echo "Nombre d'argument incorrect"
    echo "Utilisation $0 dossier1 dossier2 dossiern"
    exit 1
fi
for dossier in $*
do
    if [[ -d $dossier ]]
    then
        echo "Liste des fichiers du dossier $dossier"
        i=0
        extention=".tga"
        for fichier in `ls $dossier`
        do
			nfichier=$dossier$i$extention
            echo "$fichier"
			convert $dossier/$fichier -alpha on -channel rgba -flop -negate $dossier/$nfichier && rm $dossier/$fichier
            i=$(($i + 1))
        done
    fi
done
exit 0