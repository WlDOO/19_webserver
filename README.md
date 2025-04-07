ReadMe 07/04, ce qu'il reste a faire :

- 1 :
	
	Il faut faire l'autoindex on/off. Donc dans le config file, si il est off ;
		-    Pas de liste de répertoire : Lorsqu'un client accède à un répertoire qui ne contient pas de fichier index (comme index.html, index_post.html, etc.), Nginx ne générera pas de liste automatique des fichiers du répertoire. Au lieu de cela, il renverra :

        Une réponse 403 Forbidden (si aucun fichier index n'est trouvé et que autoindex est off).

        Ou la page d'erreur 404 si configurée (si le fichier index spécifié n'existe pas).

		Du coup imaginons la requete est "localhost:4242/post/", si c'est off et qu'il n'y a pas d'index dans le config file, on va retourner Error 403 forbidden.

	s'il est on ;
		-    Listage des fichiers :

        Lorsqu'un client accède à un répertoire qui ne contient pas de fichier index (comme index.html, index_post.html, etc.), Nginx génère une page HTML automatique listant tous les fichiers et sous-répertoires disponibles.

        Exemple :

            Accès à http://127.0.0.1:8001/post/ → affiche la liste des fichiers dans /home/adduser/WEbserv/post/.

		Priorité du fichier index :

			Si un fichier spécifié dans index (ex: index_post.html) existe, Nginx l'affichera au lieu de la liste auto-générée.

			Exemple :

				Si /home/adduser/WEbserv/post/index_post.html existe → Nginx affiche ce fichier.

				S'il n'existe pas → Nginx affiche la liste du répertoire.

		Style et formatage :

			La liste générée est une page HTML simple avec :

				Liens cliquables vers les fichiers/sous-répertoires.

				Taille des fichiers.

				Date de dernière modification.

		donc s'il est 'on', on peut faire une fiche avec tous les fichiers accessible, donc comment faire ? Je pense qu'on trouve une fonction qui check quels sont les fichiers dispo dans un repertoire, puis dans une fonction, on cree une reponse html, donc une page html, avec des lien cliquables ayant comme noms les noms des fichiers afin que le client puisse etre redirige vers le fichier juste en 1 click. Ce click va generer donc une requete GET.

- 2 :

	Page html automatise, donc pour le coup, dans le fichier read_send, tout en haut on a une fonction 'html_response' qui genere une page html avec le code 200. Je vais lister ici tous les codes qu'on m'a dit de faire : 
		200,201; 308 peut etre; 400, 403, 404, 405, 413, 500 si erreur cgi, 504 boucle infini cgi.
	Du coup pour les pages de base ca va pas etre complique, faut juste savoir quand envoyer le bon code, par contre pour les pages d'erreur, si le type ds le config file il nous met sa page 404, on doit faire pop la sienne, s'il met pas, on envoie la notre. Pour automatiser il faudrait faire une fct qui prend en parametre l'error code et qui l'associe a un msg et qui dans une std::string, il genere une page html et qui garde du coup le prototype de html_response, c'est pas tres complique.

- 3 :

	Il faut associer le parsing de la requete avec le config file, c'est ce que je suis entrain de faire dans parse request, du coup je vais faire un parsing qui a la fin, va set une variable _Error_code. si elle est set a 0, on fais la requete normale sinon, on va faire appel a la rep html en fonction de l'error code de la variable. Si pdt le parsing a un moment donne elle a la valeur 404, on envoie _Error_code, donc 404 ds la rep error et on regarde si le type a envoye une page 404 ds le config file ou pas.

- 4 : 
	
	Je vais changer un peu le parsing pour n'accepter qu'un seul type de requete, du coup que par html, et je dois proteger la cgi car si elle bug je n'ai pas fais de page et de retour d'erreur. Si j'update le point 4 c'est que je pense l'avoir fait donc si vous trouvew des bug dites moi.

- 5 : 

	tester le serveur avec stress, je ne pense pas m'occuper de ca mtn car jsp comment ca fonctionne, de plus, on m'a dit que si la cgi possede une boucle infini, il faut renvoyer 504, je me suis pas documente la dessus, je pense on va faire ca a la fin

- 6 :

	Gerer la requete flavico, le truc du logo parce que a chaque fois qu'une requete se passe, il y a une requete flavico donc c'est bizarre. Je vais essayer de patch ca. //Update, je pense avoire regle, pas besoin de check mtn

Donc voila, le point 1 est surement le plus long, je vais essayer de m'occuper du point 3 et 4, en ce qui concerne les autres points, pour merge sans se marcher sur les pieds, je vais faire un espace dans le .hpp reserve pour les fonctions que qqn va rajouter et svp mettez des nouveaux fichiers histoire de merge de maniere rapide. 

Du coup, voici un ex : 

	//autoindex (dans le hpp)
	-fct
	-fct...
	+ creation d'un fichier 'autoindex.cpp'

Voila, si qst hesitez pas, oubliez pas y'a pas de wifi a l'ecole donc il est preferable de taffer depuis la maison.

Si gros changement dans des fichiers existant, svp prevenez pour le merge

