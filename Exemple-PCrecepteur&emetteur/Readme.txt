
// Formation de la couche basse de l'anneau (emulation couche physique)
// Chaque PC muni de 2 sockets :
// -> 1 oreille : socket serveur pour recevoir du PC precedent
// -> 1 bouche : socket client pour envoyer vers le PC suivant 
// Tous les PCs sur la boucle locale => différencies que pas leur port serveur
// Par ex. 3 PC, faire : 
//		port 8000 -> port 8001 -> port 8002 (-> reboucle sur port 8000)
//		circulation d'un message d'un PC à l'autre
// 		amorce : PC port 8000 envoie le tout 1er message  
// 		Executer d'abord les pc2 et pc3, et en dernier le pc1 

Compilation :
> make 

Lancement (dans 3 terminaux differents):
> ./pc3
> ./pc2
> ./pc1 (à lancer le dernier)

