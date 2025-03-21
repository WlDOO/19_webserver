![image](RukaGithub.jpg)


Rajout des logs, Vert (code 1) pour correct, Rouge (code 2) pour error, Bleu pour sender mais a rajouter le numero socket peut etre ?

Request post securise + code erreur quasiment 100%

Request post cgi pas securise a 100% mais + optimise.

Pour si erreur, rajouter du boolean _Error_Post, si oui, on va stocker ds une string (ex _Error_Post_Msg) le msg d'erreur, je pense par exemple cgi c'est erreur 400

Configurer dans html request que si on trouve cgi, on fait appel a get ou post version cgi mais bien parser la requete (ex si le path existe et si le nom de l'executable est bon + .py a verifier).

requete depuis le terminal + complete dans le nouveau file set_request, parsing si ca vient du terminal, on accapte que le format de requete dans request.txt (nv file). faut copier la commande apres avoir cree un fichier "text.txt" donc :

'cmd du file request.txt' > "text.txt", ensuite se co avec nc ip < "text.txt"

Raf du coup si tu peux rajouter le delete, les pages html automatise en cas d'erreur et si t'as pas la flm peut etre faire les folders sinon je fais lundi

------ 21 mars 2025 

- En ce qui concerne le merge, on peut check du coup les locations. Si la loc existe, on peut checker les mthodes mais a voir encore qqes bugs je crois qd ca commence par GET seulement. 

- Peut etre rajouter la fonction alias, deja fonctionelle mais besoin de rajouter les protections.

- Ce que j'ai fais pour la cgi, si elle s'execute elle donne son output dans une pipe au lieu du stdout(1), execution comme dans Minishell.
du coup je stock un file html + des header dans une std::string, je parse seulement le content type et je stock une reponse html dans une string qui est dans le .hpp --> std::string _Cgi_output;

J'envoie donc cet output dans un html_response personnalise afin d'envoyer la reponse du cgi au client.

- Besoin des reponses automatiques en cas de reponse ou d'erreur et je dois securiser le parser de la requete en fonction du config file (Cgi_parse.cpp)

Peut etre pour les connexion avec nc ou bien avec curl, juste faire une securite pour qu'on les fasses pas et qu'on fasse tout via notre site et les requetes http classique.