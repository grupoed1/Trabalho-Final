# Trabalho-Final

O trabalho final da disciplina de ED 1 corresponde a um sistema de gerenciamento de trânsito, definido através de um sistema de eventos discreto. Basicamente, em um sistema de eventos discretos, um conjunto finito de eventos bem definidos são executados em sequência em tempos apropriados, modificando assim a condição atual do ambiente pelo qual o sistema está inserido. Para o nosso problema, o nosso sistema irá funcionar com uma sequência de ciclos de unidades de tempo, ou seja, a cada unidade de tempo especificado, um conjunto de eventos são executados, modificando assim a situação atual do ambiente. Assim, partindo desse pressuposto, o sistema de gerenciamento de trânsito será definido a seguir.

1. Cenário

O sistema de gerenciamento de trânsito considera um cenário veicular, onde um conjunto de carros são capazes de trafegar por uma via de trânsito especificada. A via de trânsito possui regras bem definidas, relacionadas a: quantidade de carros máxima na via, direção do movimento e vazão de tráfego. Além disso, também são definidas as origens dos carros (entrada de veículos), bem como os destinos finais de cada um (saída de carro do ambiente). Para o nosso sistema, o cenário abaixo é definido:

2. Descrição do Cenário

  Basicamente, o cenário definido possui as seguintes características, que são descritas posteriormente:
• Duas vias, nomeadas de via 1 e via 2;
• Um estacionamento privado de uma empresa;
• Um hospital localizado na via 1;
• Uma unidade do SAMU localizado na entrada 1;
• Duas entradas de veículos no cenário, nomeadas de Entrada 1 e Entrada 2;
• Duas saídas de veículos do cenário, nomeadas de Saída 1 e Saída 2.
VIAS
O cenário possui duas vias: via 1 e via 2. A Via 1 é mão dupla e tem uma capacidade máxima de x veículos, em cada sentido. Já a Via 2 é de mão única formada por duas faixas e tem uma capacidade máxima de y veículos (em cada faixa). Os carros do sistema devem trafegar por essas vias, seguindo suas características, origem e destino (definidas a posteriori).
ENTRADAS
Através das entradas 1 e 2, os veículos são inseridos no cenário, com suas principais características, instante de entrada e destino. Assim, de acordo com a entrada, temos as seguintes características:
• Entrada 1: veículos que entram no sistema pela entrada 1 podem seguir seu curso para a saída 1, a saída 2, estacionamento ou ser uma ambulância que sai do SAMU em direção ao hospital.
• Entrada 2: veículos que entram no sistema pela entrada 2 podem seguir seu curso para a saída 2 ou estacionamento. Ambulâncias não são geradas a partir da Entrada 2 e veículos que entram pela Entrada 2 não podem sair pela Saída 1.
SAÍDAS
Todos os veículos, com exceção das ambulâncias, são configurados removidos do sistema através de uma das saídas. Cabe ao programador registrar com exatidão o exato momento que o veículo deixará o sistema.
HOSPITAL/SAMU
O cenário é constituído de um tráfego especial prioritário composto de ambulâncias. As ambulâncias possuem características especiais que o diferenciam dos veículos comuns. Primeiramente, as ambulâncias apenas são geradas a partir do SAMU em direção ao hospital ou então do Hospital em direção ao SAMU. Além disso, as ambulâncias têm uma dinâmica diferente em relação à velocidade de tráfego e ultrapassagem, que serão descritos com exatidão no funcionamento do sistema. Dessa forma, os veículos que saem do SAMU em direção ao hospital, entram diretamente na Via 1 através da Entrada 1. Por outro lado, os veículos que saem do hospital em direção ao SAMU já entram diretamente na Via 1, em uma posição fixa dessa via (posição h, contada na direção OESTE-LESTE).
ESTACIONAMENTO
O cenário possui uma zona de estacionamento de uma empresa privada. Infelizmente, devido ao pequeno espaço, os veículos são estacionados alinhadamente (um atrás do outro) e sua saída só poderá ser realizada quando não existir nenhum veículo o bloqueando. Basicamente, um veículo entra de frente e só sai de ré. Mesmo que o veículo já tenha atingindo o seu horário de saída, ele só sairá do estacionamento quando não existir nenhum veículo atrás dele. O estacionamento possui uma lotação máxima que, após ser preenchida, não poderá aceitar nenhum carro a mais. Se o estacionamento estiver lotado, o veículo deverá seguir para seu destino final (saída) sem o uso do estacionamento. Caso no mesmo ciclo, um carro vindo da Entrada 1 e um outro da Entrada 2 forem entrar no estacionamento, terá prioridade o carro que venha da Entrada 2.

3. Configuração do Cenário

  Cada veículo do sistema de gerenciamento de tráfego será gerado no sistema com as seguintes informações:
• Tipo de veículo: um caractere com os valores “C” para carros e “A” para ambulâncias;
• Número do veículo: um número inteiro representando sequencialmente o veículo (1, 2, 3, ...);
• Origem: um valor inteiro com os valores 1 para Entrada 1 e 2 para Entrada 2, informando em
que entrada o veículo será gerado no sistema. Para o caso de ser ambulância, o valor 1 significa que a ambulância irá sair do SAMU, enquanto um valor 2 significa que ela sairá do Hospital;
• Instante: instante de tempo (em contagem de ciclos) representado por um valor inteiro, informando o momento que o carro é gerado no sistema;
• Destino Final: um inteiro com os valores 1 para Saída 1 e 2 para Saída 2, informando o destino final para a remoção do veículo do sistema;
• Estacionamento: um caractere com os valores “S” para sim e “N” para não, informando se o veículo irá em direção ao estacionamento;
• Tempo de Estacionamento: um valor inteiro que representa a quantidade de ciclos de tempo que o veículo permanecerá estacionado. Após esse período estacionado, o veículo estará apto a sair do estacionamento (se possível) e seguir para seu destino final. Caso o veículo não seja marcado para Estacionamento (char “S”), esse valor deverá ser desconsiderado;
As informações de veículos do sistema serão inseridas a partir de um arquivo texto (veiculos.txt), onde cada linha corresponde às informações de um veículo, separadas por um espaço simples. Cabe ao programador implementar os mecanismos de leitura desse arquivo.
Para o cenário, o sistema deverá considerar os seguintes parâmetros:
• Via 1: a via 1 terá uma quantidade máxima “x” de 40 carros, tanto no sentido LESTE/OESTE,
quanto no sentido OESTE/LESTE.
• Via 2: a via 2 é composta de duas faixas com uma quantidade máxima “y” de 20 carros (para
cada uma), seguindo o sentido NORTE/SUL. Os carros ao acessarem a Via 2, irão entrar na
faixa que contiver o menor número de carros no momento.
• Estacionamento: o estacionamento particular terá uma quantidade máxima “z” de 15 carros.
Além da configuração do tráfego de veículos, eventos esporádicos poderão ser considerados no sistema. Eventos esporádicos serão gerados a partir de um arquivo texto (eventos.txt), onde cada linha corresponde às informações de um evento, separadas por um espaço simples. O evento terá as seguintes informações:
• Tipo de evento: um caractere com o valor “D” representando um veículo com defeito;
• Instante: um inteiro representando o ciclo específico do acontecimento do evento;
• Duração: um inteiro representando a quantidade de ciclos que o veículo permanecerá nesse
estado;
• Via: um valor inteiro contendo a via onde o evento irá acontecer;
• Faixa: um valor inteiro que corresponde à faixa da via.
o Para via 1, considere “1” como sendo a faixa no sentido LESTE/OESTE e “2” como sendo a faixa no sentido OESTE/LESTE.
o Para a via 2, considere “1” como sendo a faixa da esquerda (mais a OESTE) e “2” como sendo a faixa da direita (mais a LESTE);
• Posição: a posição do veículo que acontecerá o evento. Note que a posição leva em consideração a direção da via. Por exemplo, se o evento for na posição 0 da via 1 e faixa 1, isso implica que o evento será no primeiro veículo considerando o sentido OESTE/LESTE (primeiro veículo da faixa).
Na ocorrência do evento de defeito, o veículo defeituoso deverá ficar parado na sua posição e todos os outros veículos deverão se movimentar, ultrapassando esse veículo, ou seja, a posição do veículo defeituoso ficará bloqueada. A ultrapassagem corresponde a simplesmente saltar a posição do carro defeituoso. Se não existir nenhum veículo no momento de um evento específico, o mesmo deverá ser desconsiderado.

--//--

4. Funcionamento do Sistema

O sistema de gerenciamento de tráfego irá funcionar com base em ciclos de tempo. Em cada ciclo, todos os elementos do sistema deverão ser atualizados.
Os veículos percorrem cada posição nas vias em um ciclo de tempo, ou seja, a cada 1 ciclo de tempo, um veículo anda uma posição na sua via específica. Por outro lado, as ambulâncias andam 3 posições na via a cada ciclo. Além disso, diferentemente dos veículos, as ambulâncias podem ultrapassar os outros veículos. Assim, a cada ciclo de tempo, se existir tráfego, as ambulâncias irão ocupar os espaços do tráfego a frente, fazendo com que os carros que sejam ultrapassados fiquem parados em suas posições. Por exemplo: Se uma ambulância estiver na 10a posição de uma vida e existem 9 carros à sua frente, após um ciclo de tempo, a ambulância irá ocupar a 7a posição, os carros das posições 9 e 8 ficarão em suas mesmas posições, os carros de 2 a 7 avançarão uma posição e o carro da posição 1 mudará para a via 2.
Em relação ao Hospital, as ambulâncias entram exatamente na posição 20 da Via 1, Faixa 1, sentido LESTE/OESTE, ou seja, à sua frente, existirá exatamente 19 veículos ou posições na via. Cabe ao implementador considerar essas questões.
Se um veículo for gerado no sistema e as vias estiverem congestionadas (nenhuma posição disponível), impedindo assim a sua entrada, o respectivo veículo vai para um elemento do sistema chamado de engarrafamento. Note que, cada Entrada (1 e 2) terá sua estrutura de engarrafamento própria. Esses veículos deverão esperar em suas posições no engarrafamento até que surjam vagas nas vias para que eles possam ir entrando, um por um. A ambulância tem prioridade sobre todos os veículos na estrutura engarrafamento.
Veículos gerados para o estacionamento a partir da Entrada 1, entram diretamente no estacionamento, independente da condição das vias (congestionada ou não).
O principal objetivo de cada grupo é implementar toda a dinâmica do sistema e registrar o momento (ciclo do sistema) em que cada veículo irá sair. Essas informações deverão ser registradas em um arquivo texto (saida.txt), seguindo o formato:
• Tipo de veículo: um caractere com os valores “C” para carro e “A” para ambulâncias;
• Número do veículo: um número inteiro representando sequencialmente o veículo (1, 2, 3, ...);
• Instante de saída: instante de tempo (em contagem de ciclos) representado por um valor
inteiro, informando o momento em que o carro deixou o sistema.
Considerem que o primeiro ciclo do sistema é o CICLO 1. Para registrar a saída do veículo, considere o incremento do ciclo de sua última posição na via, ou seja, se o veículo estiver na posição de sair (cabeça da via) no ciclo 300, seu registro de saída será o ciclo 301.
Quaisquer questões que não estejam presentes nesse documento poderão ser acrescentadas em documentos adicionais ou notícias através do SIGAA.

5. Método de Avaliação da Atividade

Cada grupo é responsável por todos os detalhes de implementação, bem como a escolha apropriada das estruturas de dados que serão utilizadas. As questões de implementação, o cuidado com o código, comentários no código e a organização da aplicação serão considerados para a avaliação final de cada grupo. Assim, as notas dos grupos serão diferenciadas, baseadas na qualidade da aplicação apresentada. É de extrema importância a justifica da escolha das estruturas de dados em questão, que será um ponto de avaliação.

6. Cronograma da Atividade
Será considerado o seguinte cronograma:
• Até dia 16/11: Compilar dúvidas com relação à especificação do trabalho;
• Dia 20/11: Possível aula para tirar dúvidas com relação ao cenário definido (Em sala);
• Dia 11/12: Previsão de Apresentação dos trabalhos.
   Profs. André Soares e Erico Leão
