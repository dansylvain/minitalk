# minitalk

état actuel du projet:
le serveur et le client démarrent sans problemes. Il ne semble pas y avoir de problemes de gestion de la mémoire non plus.
Je suis en train de mettre un protocole de transmission entre le serveur et le clienta au cours duquel je fais appel à l'allocation dynamique de la mémoire:
- une première transmission de signal depuis le client vers le serveur pour vérifier la disponibilité de celui-ci (TODO: ajouter la logique pour boucler et répéter les appels en cas de don disponibilité)
- le transfert de la longeur de la chaine de caracteres à afficher.
- le transfert des caractères
- une confirmation de réception par le serveur une fois la transmission terminée.


Refactor du code:
Il faut que je pense a une nouvelle facon d'organiser la sequentioalisation de la communication entre les processus.
les handler fonctions devraient appeler directement les fonctions responsables des actions sur les donnees. Ce n'est pas a elles de reagir aux signaux rentrant. Comment faire cela? Avec la manipulation de variables?
Mettre au point des fonctions pour manipuler des variables selon les signaux rentrant. Les tester, et les brancher entre elles.

Le travil de demain: faire un plan complet des fonctions et de leurs interdependances...