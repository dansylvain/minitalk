# minitalk

état actuel du projet:
le serveur et le client démarrent sans problemes. Il ne semble pas y avoir de problemes de gestion de la mémoire non plus.
Je suis en train de mettre un protocole de transmission entre le serveur et le clienta au cours duquel je fais appel à l'allocation dynamique de la mémoire:
- une première transmission de signal depuis le client vers le serveur pour vérifier la disponibilité de celui-ci (TODO: ajouter la logique pour boucler et répéter les appels en cas de don disponibilité)
- le transfert de la longeur de la chaine de caracteres à afficher.
- le transfert des caractères
- une confirmation de réception par le serveur une fois la transmission terminée.

La derniere etape de la transmission va etre la plus laborieuse. Transmettre les caracteres bit par bit depuis le client. Avec tout ce que ca implique de confirmations de la part du serveur...