# PROJETO CERO 

Projeto desenvolvido se baseando no famoso jogo de cartas UNO para aplicar os conceitos de bibliotecas, alocação dinâmica, fila, pilha, lista e API para desenvolver uma versão jogável pelo terminal (tanto para Windowns, quanto para Linux) utilizando a linguagem C e os conhecimentos de Estrutura de Dados passados pelo docente Mario Liziér no campus Sorocaba da UFSCAR.
## INFORMAÇÕES TÉCNICAS
As estruturas de dados citadas foram usadas nas seguintes aplicações:
- FILA: foi utilizada para armazenar as cartas que foram utilizadas pelos jogadores (usuário e IA), além de possuir uma função que apresenta a útlima carta jogada. Contruída utilizado encademento simples.
- PILHA: foi utilizada com o intuito de armazenar as cartas que podem ser compradas pelos jogadores, além disso possui uma função para embaralhá-las. Construída utilizando armazenamento sequencial.
- LISTA: foi utilizada para armazenar as cartas das mãos dos jogadores, foi construída utilizando encadeamento duplo, com sentinela e circular. Além disso, foram utilizados iteradores para acessar as cartas.

### CARTAS

O jogo é composto por 108 cartas, 19 cartas normais, 2 cartas bloqueio, 2 cartas reverso, 2 cartas compra dois (2), das cores vermelho, amarelo, verde e azul, 4 cartas muda cor e 4 cartas compra quatro (4) da cor preta, seguindo a imagem de referência a seguir:
!(https://upload.wikimedia.org/wikipedia/commons/thumb/9/95/UNO_cards_deck.svg/1024px-UNO_cards_deck.svg.png)
Cada carta possui ou um número, ou um símbolo, ou uma descrição e uma cor (vermelho, amarelo, verde, azul e preto) que define quando as mesmas podem ser jogadas seguindo o tópico "COMO JOGAR" que será tratado adiante.
As cartas são subdivididas nos seguintes tipos, cada uma com a sua função:
- CartaNormal: representada por um número (0, 1, 2, 3, 4, 5, 6, 7, 8, 9) e por uma cor (menos o preto);
- CartaBloqueio: representada por um 'X' e uma cor (menos o preto) e tem como função passar a vez do oponente, a retornando para o jogador;
- CartaReverso: representada pela descrição "reverso" ou o símbolo '<->' e uma cor (menos o preto) e teria como função inverter a ordem de jogadas (do sentido horário para o anti-horário e vice-versa) porém, como existe apenas um oponente, ela funcionará igual à "CartaBloqueio";
- CartaCompra2: representada por um '+ 2' e uma cor (menos o preto) e tem como função fazer o oponente comprar duas (2) cartas da pilha de cartas da mesa e o fazer passar a vez (igual à CartaBloqueio);
- CartaMudaCor: descrita como MudaCor e possuindo a cor preta, a função dessa carta é possibilitar ao jogador escolher qual cor ele quer que a última carta jogada assuma, ele digitará r ou R para vermelho, b ou B para azul, g ou G para verde e y ou Y para amarelo, após isso, a carta assume a cor escolhida pelo jogador;
- CartaCompra4: representada por um '+ 4' e a cor preta, a função dessa carta é fazer o oponente comprar quatro (4) cartas da pilha de cartas da mesa, o fazer passar a vez (igual à CartaBloqueio) e possibilita o jogador a escolher uma cor para a última carta (igual à CartaMudaCor), após isso a carta assume a cor escolhida pelo jogador;


### COMO JOGAR

Inicialmente o jogador e a IA (Inteligência Artificial) recebem 6 cartas e uma carta é retirada da pilha de cartas da mesa e colocada em cima da mesa, com exceção das cartas muda cor e compra 4. Será disponibilizado para o jogador as cartas precedidas de um número (seguindo a ordem da lista de cartas na mão dele), a cor escrita por extenso (vermelho, amarelo, verde, azul ou preto) e depois o símbolo ou a descrição da carta. Cada carta será apresentada em uma linha com o *background* colorido seguindo a cor da carta (menos para a carta preta que tem o seu *background* definido como roxo).

!(data/image_01.png)
    
Para jogar é necessário que o jogador digite o número precedido pela carta, porém isso apenas acontecerá se o mesmo possuir cartas válidas em sua mão, caso não tenha será necessário apertar "ENTER" para comprar uma carta, o mesmo ocorre com a IA. Para ter ao menos uma carta válida é necessário que o jogador possua uma carta que cumpra pelo menos um desses requisitos:
- Uma carta que possui a mesma cor da última carta jogada;
- Uma carta que possui o mesmo número ou símbolo da última carta jogada;
- Uma carta preta (muda cor ou compra 4);

O objetivo de ambos os jogadores é zerar as suas cartas, quando o jogador jogar sua última carta é preciso que ele digite o nome do jogo 'cero' (todas as possibilidades de cero serão aceitas, exemplos: CeRo, CERO, cerO, etc...) para realmente ganhar. Caso ele digite errado serão dadas duas cartas para o jogador e o jogo continuará. O mesmo ocorre com a IA que possui uma chance de falar 'cero' errado ao jogar sua última carta.

##### DESENVOLVIDO POR
##### - ALEXANDRE DE OLIVEIRA KIST JUNIOR
##### - GABRIEL SANTOS DE ANDRADE
##### - JEAN RODRIGUES ROCHA
##### - LEONARDO PRADO SILVA

### DIVIRTA-SE :)