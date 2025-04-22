Objet :
Cree un simple lien entre 2 applications (PC1 et PC2).
Les 2 PC sont virtuels et échangent via la boucle locale en mode non connecté (UDP).
Exactement le PC1 envoie un message (une chaine de caractères sans espace) au PC2 qui le reçoit et l'affiche sur la sortie standard.

Compilation :
	make [cible]

Usage : 
	il faut lancer les 2 PC dans 2 terminaux différents :
	./PC2-recepteur
	./PC1-emetteur

	puis faire démarrer d'abord le PC2 (qui reçoit)
	avant le PC1 (qui envoie "nouveauBlabla")

	pour arrêter les programmes faire CTRL-C 

