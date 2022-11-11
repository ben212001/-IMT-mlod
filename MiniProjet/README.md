[README]


--------------------------------------------------------------------------------------------------------------------------------------
INTRODUCTION

Pour mon mini-projet à réaliser en langage C, j’ai décidé de me pencher sur le jeu Floppy, de la bibliothèque Raylib. J’ai décidé d’étendre son fonctionnement en y ajoutant une fonctionnalité, que je détaillerai dans un prochain paragraphe.


--------------------------------------------------------------------------------------------------------------------------------------
PRESENTATION DU JEU

Floppy est un jeu d’arcade, très proche du célèbre jeu Flappy Bird, dans lequel le joueur pilote une boule à l’aide de la touche Espace du clavier. La boule effectue du sur place et peut simplement se déplacer verticalement à l’aide la touche Espace, tandis que des paires de tuyaux défilent de droite à gauche de manière automatique, à vitesse constante. C’est dans le déplacement de la boule que réside la plus grande différence entre Floppy et Flappy Bird puisque dans le second jeu, la boule (qui est en réalité un oiseau) se déplace verticalement non pas linéairement mais en prenant en compte la gravité terrestre. Cela complique un peu le code qui régit le déplacement de l’oiseau, ce qui ne sera donc pas notre cas avec Floppy.


--------------------------------------------------------------------------------------------------------------------------------------
NOUVELLE(S) FONCTIONNALITE(S)

Pour vous parler à présent de la nouvelle fonctionnalité que j'ai intégrée à Floppy, il s'agit d'une espèce de "portail" qui apparaît de manière aléatoire entre certains tuyaux. En réalité, par lots de 5 tuyaux consécutifs, un seul de ces tuyaux (tiré au hasard) est dôté d'un portail, matérialisé par un rectangle bleu. Lorsque LE CENTRE de la boule entre en contact avec un de ces portails, elle voit sa taille diminuer pendant un temps défini, facilitant alors la progression du joueur entre les tuyaux. A la fin de ce temps imparti, la boule retrouve instantanément sa taille normale et le jeu suit son cours initial.

Pour apporter plus de détails sur les modifications apportées à la boule: Lorsque la boule se déplace selon les conditions initiales (taille de la boule et vitesse de défilement des tuyaux) et qu'elle entre en collision avec un premier portail, son diamètre est divisé par 3 et la vitesse de défilement des tuyaux est multipliée par 3. Ces changements durent 5sec puis le jeu continue en reprenant les conditions initiales de taille et de vitesse. Toutefois, si la boule entre en collision avec un second portail PENDANT que les effets du premier portail sont toujours actifs, la vitesse actuelle est multipliée par 1,5 et sa taille est de nouveau divisée par 3. Ces changements durent 2sec avant de retourner aux conditions de jeu précédentes, qui une fois expirées à leur tour, provoquent un retour aux conditions initiales. Notez que pour conserver une jouabilité agréable, la collision avec un 3ème portail, alors que la boule ressent toujours les effets de collision avec 2 portails, n'a aucun effet sur les conditions de jeu.

Le jeu compte au total 200 tuyaux à franchir. Ainsi, une fois le score de 20 000 atteint et la boule retournée dans les conditions intitiales, le jeu est terminé automatiquement.

--------------------------------------------------------------------------------------------------------------------------------------
COMMENT COMPILER/EXECUTER ?

La ligne de compilation est la suivante: 

gcc floppy.c -Wall -std=c11 /Users/ben/Documents/_IMT_NORD_EUROPE/M1/MLOD/Raylib.git/src/libraylib.a -lm  -Wno-missing-braces -s  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo -DPLATFORM_DESKTOP

Elle peut être retouvée en ligne 15 du fichier floppy.c


--------------------------------------------------------------------------------------------------------------------------------------
COMMENT UTILISER LE JEU ?

Aucune commande n’a été modifiée. Le jeu reste jouable de la même manière qu’avant l’implémentation de la nouvelle fonctionnalité: la barre espace permet de faire monter la boule, à vitesse constante pendant toute la durée de maintient de la touche enfoncée.


--------------------------------------------------------------------------------------------------------------------------------------
URL DE LA VIDEO DE DEMO DU JEU

partie classique: https://youtu.be/B2dj5KLvUR8

(Si vous souhaitez voir l'affichage en fin de jeu, vous pouvez modifier la ligne 171 de floppy.c et vous doter du score que vous souhaitez en début de partie)


--------------------------------------------------------------------------------------------------------------------------------------
EXTENSION/AMELIORATION POSSIBLE

J’aurais également pu développer des portails différents, qui auraient eu des impacts différents sur le jeu, à durée limitée ( prise en compte de la gravité dans le déplacement de la boule, mise en place de nouveaux tuyaux entre ceux existants, mise en mouvement des tuyaux etc). 

J'essayerai d'implémenter cela sur mon temps personnel plus tard.




Je vous remercie pour tous les cours et les connaissances que vous avez pu m'apporter lors de cet UV. Je l'ai trouvé très intense et compact, mais j'en ressors avec une envie d'apprendre encore plus grande !


Benjamin Puzenat
