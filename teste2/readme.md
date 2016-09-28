#Teste 2

Neste teste foi avaliada a performance de uma aplicação multithread que implementa uma estratégia de disseminação por gossiping usando interfaces de comunicação

##Proposta

Os programas devem receber dois inteiros N e k. São criados N processos simultâneos que se conectam por meio de sockets, onde cada um desses processos pode se conectar a outro processo ou receber uma conexão de outro processo. Um único processo inicia a disseminação. Ao receber uma nova informação, o processo deve tentar "fofocar", ou seja, repassar a nova informação para outro processo escolhido aleatoriamente. Se o processo escolhido já possuir a informação a ser repassada, o processo que tentou fofocar é encerrado com probabilidade 1/k. Caso contrário, o processo continua disseminando para outros processos.


##Como executar

Entre na pasta /teste2 e execute o seguinte comando:
```
python gossip.py [N] [k]
```
, sendo N o número de processos simultâneos e k o fator de disseminação.

Assim que o programa parar de fornecer novos outputs, pressione 'c' para receber os dados do experimento.

##Resultados

>```
N=100  k=2 
Processos alcancadas: 94/100
Indice de fofocas bem sucedidas: 0.33098591549295775
Minimo: 1 Maximo: 13 Media: 2
```
```
N=100 e k=8
Processos alcancadas: 100/100
Indice de fofocas bem sucedidas: 0.12239902080783353
Minimo: 1; Maximo: 38; Media: 8
```
```
N=250 e k=2
Processos alcancadas: 235/250
Indice de fofocas bem sucedidas: 0.32867132867132864
Minimo: 1; Maximo: 13; Media: 2
```
```
N=250 e k=8
Processos alcancadas: 248/250
Indice de fofocas bem sucedidas: 0.113345521023766
Minimo: 1; Maximo: 41; Media: 8
```
```
N=500 e k=2
Processos alcancadas: 455/500
Indice de fofocas bem sucedidas: 0.3551912568306011
Minimo: 1; Maximo: 13; Media: 2
```
```
N=500 e k=8
Processos alcancadas: 482/500
Indice de fofocas bem sucedidas: 0.10773357174787662
Minimo: 1; Maximo: 61; Media: 8
```

##Discussão

Como o aumento no valor de k faz com que os processos de fofoca realizem mais tentativas de disseminação, foi possível comprovar que a informação nova alcança um número maior de processos na medida que k aumenta. Em contraparte, como os processos de fofoca tentaram realizar mais disseminações, o tempo de execução também aumenta de maneira proporcional ao k. Embora não tenha sido coletado nesta versão do experimento, captar o tempo de execução de maneira precisa ajudará a pontuar com dados o aumento do tempo de maneira proporcional ao valor de k. 
Acabei esbarrando com um limite do uso de threads, mas não sei se este era atrelado ao SO ou à máquina. Inicialmente, uma execução com N = 300+ threads disparavam um erro de limite de arquivos abertos simultaneamente. Através do comando `ulimit`, foi possível dobrar o limite de arquivos simultaneamente abertos, fazendo o experimento funcionar com até N = 500 threads.
