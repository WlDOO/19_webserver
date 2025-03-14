![image](RukaGithub.jpg)


Rajout des logs, Vert (code 1) pour correct, Rouge (code 2) pour error, Bleu pour sender mais a rajouter le numero socket peut etre ?

Request post securise + code erreur quasiment 100%

Request post cgi pas securise a 100% mais + optimise.

Pour si erreur, rajouter du boolean _Error_Post, si oui, on va stocker ds une string (ex _Error_Post_Msg) le msg d'erreur, je pense par exemple cgi c'est erreur 400

Configurer dans html request que si on trouve cgi, on fait appel a get ou post version cgi mais bien parser la requete (ex si le path existe et si le nom de l'executable est bon + .py a verifier).

requete depuis le terminal + complete dans le nouveau file set_request, parsing si ca vient du terminal, on accapte que le format de requete dans request.txt (nv file). faut copier la commande apres avoir cree un fichier "text.txt" donc :

'cmd du file request.txt' > "text.txt", ensuite se co avec nc ip < "text.txt"

Raf du coup si tu peux rajouter le delete, les pages html automatise en cas d'erreur et si t'as pas la flm peut etre faire les folders sinon je fais lundi