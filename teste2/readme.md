#Teste 2

Neste teste foi avaliada a performance de uma aplicação multithread que implementa uma estratégia de disseminação por gossiping usando interfaces de comunicação

##Proposta

Os programas devem receber dois inteiros N e k. São criados N processos simultâneos que se conectam por meio de sockets, onde cada um desses processos pode se conectar a outro processo ou receber uma conexão de outro processo. Um único processo inicia a disseminação. Ao receber uma nova informação, o processo deve tentar "fofocar", ou seja, repassar a nova informação para outro processo escolhido aleatoriamente. Se o processo escolhido já possuir a informação a ser repassada, o processo que tentou fofocar é encerrado com probabilidade 1/k. Caso contrário, o processo continua disseminando para outros processos.


##Como executar

Entre na pasta /teste2 e execute o seguinte comando:
```
python gossip.py [N] [k]
```
, sendo N o número de processos simultâneos e k o fator de disseminação

##Resultados

N=100 e k=2
Processos alcancadas: 94/100
Indice de fofocas bem sucedidas: 0.33098591549295775
Minimo: 1; Maximo: 13; Media: 2

N=100 e k=8
Processos alcancadas: 100/100
Indice de fofocas bem sucedidas: 0.12239902080783353
Minimo: 1; Maximo: 38; Media: 8

N=250 e k=2
Processos alcancadas: 235/250
Indice de fofocas bem sucedidas: 0.32867132867132864
Minimo: 1; Maximo: 13; Media: 2

N=250 e k=8
Processos alcancadas: 248/250
Indice de fofocas bem sucedidas: 0.113345521023766
Minimo: 1; Maximo: 41; Media: 8

N=500 e k=2
Processos alcancadas: 455/500
Indice de fofocas bem sucedidas: 0.3551912568306011
Minimo: 1; Maximo: 13; Media: 2

N=500 e k=8
Processos alcancadas: 482/500
Indice de fofocas bem sucedidas: 0.10773357174787662
Minimo: 1; Maximo: 61; Media: 8


##Discussão

Limite local: ~250